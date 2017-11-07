#include <memory>

#include <Support/Basic.h>
#include <Support/Cryption.h>

#include <User/Block.h>

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

    bool Cryption::isSHA256HashEqual(const SHA256_t& LHS, const SHA256_t& RHS) {
        return LHS == RHS;
    }
    bool Cryption::isSHA512HashEqual(const SHA512_t& LHS, const SHA512_t& RHS) {
        return LHS == RHS;
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
    SHA_REASON Cryption::getSHA256Hash(SHA256_t& Out, void* pIn, size_t szIn) {
        SHA256_CTX sha256;
        // Hash creation.
        IF_FAILED(SHA256_Init(&sha256)                          , SHA_REASON::FAILED_INIT  );
        IF_FAILED(SHA256_Update(&sha256, pIn, szIn)             , SHA_REASON::FAILED_UPDATE);
        IF_FAILED(SHA256_Final(Out.toUint8(), &sha256)          , SHA_REASON::FAILED_UPDATE);
        return SHA_REASON::SUCCESSED;
    }
    SHA_REASON Cryption::getSHA512Hash(SHA512_t& Out, void* pIn, size_t szIn) {
        SHA512_CTX sha512;
        // Hash creation.
        IF_FAILED(SHA512_Init(&sha512)                          , SHA_REASON::FAILED_INIT  );
        IF_FAILED(SHA512_Update(&sha512, pIn, szIn)             , SHA_REASON::FAILED_UPDATE);
        IF_FAILED(SHA512_Final(Out.toUint8(), &sha512)          , SHA_REASON::FAILED_UPDATE);
        return SHA_REASON::SUCCESSED;
    }
    
    RSA_REASON Cryption::getRSASignature(void* pOut, void* pIn, unsigned int szIn, RSA* pPrivate) {
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
    RSA_REASON Cryption::isRSASignatureValid(void* pRaw, void* pSig, unsigned int szSig, RSA* pPublic) {
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
        if (RoundIndex) {
            IF_FAILED(iterate_cmp<uint64_t>(pSig, pDecrypted, RoundIndex), RSA_REASON::NOT_VALID);
        }

        // Now we need to check it very slowly.
        unsigned int szTip  = szSig % sizeof(uint64_t);
        unsigned int szBody = szSig / sizeof(uint64_t);


        // Now we are going to check the body first, and after tip of signature.
        IF_FAILED(iterate_cmp<uint64_t>(pSig, pDecrypted, szBody), RSA_REASON::NOT_VALID);
        IF_FAILED(
            iterate_cmp<uint8_t >(
                offset(pSig        ,(szSig - szTip)),
                offset(pDecrypted  ,(szSig - szTip)), 
                szTip), 
            RSA_REASON::NOT_VALID);
            

        // If there is no problem, this is valid signature.
        return RSA_REASON::SUCCESSED;
    }

    bool Cryption::hashBlockHeaderSHA256(SHA256_t& hash, const BlockHeader& block) {
        return getSHA256Hash(hash, (void*)&block, sizeof(BlockHeader)) == SHA_REASON::SUCCESSED;
    }
    bool Cryption::hashBlockHeaderSHA512(SHA512_t& hash, const BlockHeader& block) {
        return getSHA512Hash(hash, (void*)&block, sizeof(BlockHeader)) == SHA_REASON::SUCCESSED;
    }
    bool Cryption::hashBlockFullSHA256(SHA256_t& hash) {
        // Not implemented yet.
        return false;
    }
    bool Cryption::hashBlockFullSHA512(SHA512_t& hash) {
        // Not implemented yet.
        return false;
    }

    bool Cryption::proofBlockHeaderSHA256(const SHA256_t& hash, const BlockHeader& block) {
        SHA256_t blockHash;

        if (getSHA256Hash(blockHash, (void*)&block, sizeof(BlockHeader)) != SHA_REASON::SUCCESSED)
            return false;

        return isSHA256HashEqual(blockHash, hash);
    }
    bool Cryption::proofBlockHeaderSHA512(const SHA512_t& hash, const BlockHeader& block) {
        SHA512_t blockHash;

        if (getSHA512Hash(blockHash, (void*)&block, sizeof(BlockHeader)) != SHA_REASON::SUCCESSED)
            return false;

        return isSHA512HashEqual(blockHash, hash);
    }

    Cryption::Cryption() { }
    Cryption::~Cryption() { }
}