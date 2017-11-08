#include <memory>

#include <Support/Basic.h>
#include <Support/Cryption.h>

#include <User/Blockv1.h>

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

    // SHA Hasing Method Implements.
    CRESULT Cryption::getSHA256Hash(SHA256_t& Out, void* pIn, size_t szIn) {
        SHA256_CTX sha256;
        // Hash creation.
        IF_FAILED(SHA256_Init(&sha256)                          , CRESULT::FAILED_INIT  );
        IF_FAILED(SHA256_Update(&sha256, pIn, szIn)             , CRESULT::FAILED_UPDATE);
        IF_FAILED(SHA256_Final(Out.toUint8(), &sha256)          , CRESULT::FAILED_UPDATE);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getSHA512Hash(SHA512_t& Out, void* pIn, size_t szIn) {
        SHA512_CTX sha512;
        // Hash creation.
        IF_FAILED(SHA512_Init(&sha512)                          , CRESULT::FAILED_INIT  );
        IF_FAILED(SHA512_Update(&sha512, pIn, szIn)             , CRESULT::FAILED_UPDATE);
        IF_FAILED(SHA512_Final(Out.toUint8(), &sha512)          , CRESULT::FAILED_UPDATE);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getRSAPrvEncrypt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Private) {
        RSA     *PrvKey;
        void    *RawKey = Private;

        d2i_RSAPrivateKey(&PrvKey, (uint8_t**)&RawKey, Private.getSize());

        // Encrypting pIn(Signature)
        IF_FAILED( RSA_private_encrypt(
            szIn,                   // Signature Size.
            (unsigned char*)pIn,    // Signature Buffer.
            (unsigned char*)pOut,   // Output.
            PrvKey,                 // Signature Key.
            RSA_PKCS1_PADDING       // Signature Padding.
        ), CRESULT::FAILED_ENCRYPT);

        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getRSAPubDecrpyt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Public) {
        RSA     *PubKey;
        void    *RawKey = Public;

        d2i_RSAPublicKey(&PubKey, (uint8_t**)&RawKey, Public.getSize());

        // Decrypting pIn(Signature)
        IF_FAILED(RSA_public_decrypt(
            szIn,                   // Signature Size.
            (unsigned char*)pIn,    // Signature Buffer.
            (unsigned char*)pOut,   // Output.
            PubKey,                 // Signature Key.
            RSA_PKCS1_PADDING       // Signature Padding.
        ), CRESULT::FAILED_DECRYPT);

        return CRESULT::SUCCESSED;
    }
}