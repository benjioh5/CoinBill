#include <memory>

#include <Support/Basic.h>
#include <Support/Cryption.h>

// Basic OpenSSL Headers.
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>


namespace CoinBill
{
    void InitCryption() {
        ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();
    }
    void StopCryption() {
        EVP_cleanup();
        CRYPTO_cleanup_all_ex_data();
        ERR_free_strings();
    }

    bool Cryption::isSHA256HashEqual(void* pRHS, void* pLHS) {
        return iterate_check<uint64_t, 4>(pRHS, pLHS);
    }
    bool Cryption::isSHA512HashEqual(void* pRHS, void* pLHS) {
        return iterate_check<uint64_t, 8>(pRHS, pLHS);
    }
    
    // TODO : this buffers to managed buffer for faster allocation speed.
    void * Cryption::get256AlignedBuffer(size_t szBuf) {
        return operator new(round_up<256>(szBuf));
    }
    void * Cryption::get512AlignedBuffer(size_t szBuf) {
        return operator new(round_up<512>(szBuf));
    }
    bool Cryption::Dispose256AlignedBuffer(void* pBuf, size_t szBuf) {
        delete pBuf;
        return true;
    }
    bool Cryption::Dispose512AlignedBuffer(void* pBuf, size_t szBuf) {
        delete pBuf;
        return true;
    }

    // SHA Hasing Method Implements.
    SHA_REASON Cryption::getSHA256Hash(void* pOut, void* pIn, size_t szIn) {
        SHA256_CTX sha256;
        // Hash creation.
        IF_FAILED(SHA256_Init(&sha256)                          , SHA_REASON::FAILED_INIT  );
        IF_FAILED(SHA256_Update(&sha256, pIn, szIn)             , SHA_REASON::FAILED_UPDATE);
        IF_FAILED(SHA256_Final((unsigned char*)pOut, &sha256)   , SHA_REASON::FAILED_UPDATE);
        return SHA_REASON::SUCCESSED;
    }
    SHA_REASON Cryption::getSHA512Hash(void* pOut, void* pIn, size_t szIn) {
        SHA512_CTX sha512;
        // Hash creation.
        IF_FAILED(SHA512_Init(&sha512)                          , SHA_REASON::FAILED_INIT  );
        IF_FAILED(SHA512_Update(&sha512, pIn, szIn)             , SHA_REASON::FAILED_UPDATE);
        IF_FAILED(SHA512_Final((unsigned char*)pOut, &sha512)   , SHA_REASON::FAILED_UPDATE);
        return SHA_REASON::SUCCESSED;
    }
    
    RSA_REASON Cryption::getRSASignature(void* pOut, void* pIn, size_t szIn, RSA* pPrivate) {
        // Encrypting pIn(Signature)
        IF_FAILED( RSA_private_encrypt(
            szIn,                   // Signature Size.
            (unsigned char*)pIn,    // Signature Buffer.
            (unsigned char*)pOut,   // Output.
            pPrivate,               // Signature Key.
            RSA_PKCS1_PADDING       // Signature Padding.
        ), RSA_REASON::FAILED_ENCRYPT);

        return RSA_REASON::SUCCESSED;
    }

    // RSA Signature Check Implements.
    RSA_REASON Cryption::isRSASignatureValid(void* pRaw, void* pSig, size_t szSig, RSA* pPublic) {
        unsigned int RoundIndex = 0;

        // Checking that this is a 256 byte rounded signiture.
        if ((szSig % 256) == 0) {
            RoundIndex = szSig / 256;
        }

        // We can exit everywhere that has IF_FAILED, so we need to delete pDecrypted safely.
        char* pDecrypted = new char[szSig]; std::unique_ptr<char> MemSafety((char*)pDecrypted);

        // try decrypting signature.
        IF_FAILED( RSA_public_decrypt(
            szSig,                      // Signature Size.
            (unsigned char*)pSig,       // Signature Buffer.
            (unsigned char*)pDecrypted, // Output.
            pPublic,                    // Signature Key.
            RSA_PKCS1_PADDING           // Signature Padding.
        ), RSA_REASON::FAILED_DECRYPT);

        // We need to check it rounded, because we are usally goind to use rounded signature.
        switch (RoundIndex) {
        case 0: 
            // This mean not rounded.
            break;
        case 1: 
            IF_FAILED(isSHA256HashEqual(pSig, pDecrypted), RSA_REASON::NOT_VALID); 
            break;
        case 2: 
            IF_FAILED(isSHA512HashEqual(pSig, pDecrypted), RSA_REASON::NOT_VALID); 
            break;
        default: 
            IF_FAILED(iterate_check<uint64_t>(pSig, pDecrypted, RoundIndex * (256 / sizeof(uint64_t))), RSA_REASON::NOT_VALID); 
            break;
        }

        // Now we need to check it very slowly.
        unsigned int szTip  = szSig % sizeof(uint64_t);
        unsigned int szBody = szSig / sizeof(uint64_t);


        // Now we are going to check the body first, and after tip of signature.
        IF_FAILED(iterate_check<uint64_t>(pSig, pDecrypted, szBody), RSA_REASON::NOT_VALID);
        IF_FAILED(
            iterate_check<uint8_t >(
                offset(pSig        ,(szSig - szTip)),
                offset(pDecrypted  ,(szSig - szTip)), 
                szTip), 
            RSA_REASON::NOT_VALID);
            

        // If there is no problem, this is valid signature.
        return RSA_REASON::SUCCESSED;
    }

    Cryption::Cryption() { }
    Cryption::~Cryption() { }
}