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
        // Initializing all OpenSSL functions.
        ERR_load_crypto_strings();
        OpenSSL_add_all_algorithms();
    }
    void StopCryption() {
        // Releasing / Cleanup all OpenSSL functions.
        EVP_cleanup();
        CRYPTO_cleanup_all_ex_data();
        ERR_free_strings();
    }

    /// TODO : is there are better way to check is equal using SIMD..
    ///        Maybe we can use XOR with it.
#ifdef COINBILL_USE_SIMD
    bool Cryption::isSHA256HashEqual(SHA256_t& LHS, SHA256_t& RHS) {
        __m256i vl = _mm256_load_si256(LHS.toType<__m256i>());
        __m256i vr = _mm256_load_si256(RHS.toType<__m256i>());
        __m256i result = _mm256_xor_si256(vl, vr);

        // XOR result should zero, so there is no diffrence between LHS and RHS.
        // we are checking that result is zero by testing bits. if the zero flag is 1 means zero.
        return !_mm256_testz_si256(result, result);
    }
    bool Cryption::isSHA512HashEqual(SHA512_t& LHS, SHA512_t& RHS) {
        __m256i* pvl = LHS.toType<__m256i>();
        __m256i* pvr = RHS.toType<__m256i>();

        __m256i masked1 = _mm256_xor_si256(
            _mm256_load_si256(&pvl[0]),
            _mm256_load_si256(&pvr[0])
        );
        __m256i masked2 = _mm256_xor_si256(
            _mm256_load_si256(&pvl[1]),
            _mm256_load_si256(&pvr[1])
        );

        __m256i result = _mm256_or_si256(masked1, masked2);
        return  !_mm256_testz_si256(result, result);
    }
#else  // COINBILL_USE_SIMD
    bool Cryption::isSHA256HashEqual(SHA256_t& LHS, SHA256_t& RHS) {
        return LHS == RHS;
}
    bool Cryption::isSHA512HashEqual(SHA512_t& LHS, SHA512_t& RHS) {
        return LHS == RHS;
    }
#endif // !COINBILL_USE_SIMD

    // SHA Hasing Method Implements.
    CRESULT Cryption::getSHA256Hash(SHA256_t& Out, void* pIn, size_t szIn) {
        SHA256_CTX sha256;
        // Hash creation.
        IF_FAILED_RET(SHA256_Init(&sha256)                          , CRESULT::FAILED_INIT  );
        IF_FAILED_RET(SHA256_Update(&sha256, pIn, szIn)             , CRESULT::FAILED_UPDATE);
        IF_FAILED_RET(SHA256_Final(Out.toUint8(), &sha256)          , CRESULT::FAILED_UPDATE);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getSHA512Hash(SHA512_t& Out, void* pIn, size_t szIn) {
        SHA512_CTX sha512;
        // Hash creation.
        IF_FAILED_RET(SHA512_Init(&sha512)                          , CRESULT::FAILED_INIT  );
        IF_FAILED_RET(SHA512_Update(&sha512, pIn, szIn)             , CRESULT::FAILED_UPDATE);
        IF_FAILED_RET(SHA512_Final(Out.toUint8(), &sha512)          , CRESULT::FAILED_UPDATE);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getRSAPrvEncrypt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Private) {
        RSA     *PrvKey;
        void    *RawKey = Private;

        // extract key from a buffer. 
        // this will return the OpenSSL managed RSA key.
        d2i_RSAPrivateKey(&PrvKey, (const unsigned char**)&RawKey, Private.getSize());

        // check the key valid.
        if (!!RSA_check_key(PrvKey) != true)
            // This is a invalid private key.
            return CRESULT::INVALID_PRV_KEY;

        // Encrypting pIn(Signature)
        IF_FAILED_RET( RSA_private_encrypt(
            szIn,                   // Signature Size.
            (unsigned char*)pIn,    // Signature Buffer.
            (unsigned char*)pOut,   // Output.
            PrvKey,                 // Signature Key.
            RSA_PKCS1_PADDING       // Signature Padding.
        ), CRESULT::FAILED_ENCRYPT);

        RSA_free(PrvKey);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getRSAPubDecrypt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Public) {
        RSA     *PubKey;
        void    *RawKey = Public;

        // extract key from a buffer. 
        // this will return the OpenSSL managed RSA key.
        d2i_RSAPublicKey(&PubKey, (const unsigned char**)&RawKey, Public.getSize());

        // check the key valid.
        if (!!RSA_check_key(PubKey) != true)
            // This is a invalid public key.
            return CRESULT::INVALID_PUB_KEY;

        // Decrypting pIn(Signature)
        IF_FAILED_RET(RSA_public_decrypt(
            szIn,                   // Signature Size.
            (unsigned char*)pIn,    // Signature Buffer.
            (unsigned char*)pOut,   // Output.
            PubKey,                 // Signature Key.
            RSA_PKCS1_PADDING       // Signature Padding.
        ), CRESULT::FAILED_DECRYPT);

        RSA_free(PubKey);
        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::getSignature(RSA2048_t& SigOut, void* pIn, size_t szIn, RSA2048_t& PrvKey) {
        // szIn always have to be aligned as 2048 bits. 
        // we will return if its not rounded size.
        if (round_up<2048 / 8>(szIn) != szIn)
            // pIn isn't a aligned variable, align it first.
            return CRESULT::FAILED_NOT_ROUNDED;

        SHA512_t tempHash;

        // now hashing, encrypting.
        getSHA512Hash(tempHash, pIn, szIn);
        getRSAPrvEncrypt(&SigOut, &tempHash, PrvKey);
        

        return CRESULT::SUCCESSED;
    }

    CRESULT Cryption::proofSignature(RSA2048_t& Sig, void* pIn, size_t szIn, RSA2048_t& PubKey) {
        // szIn always have to be aligned as 2048 bits. 
        // we will return if its not rounded size.
        if (round_up<2048 / 8>(szIn) != szIn)
            // pIn isn't a aligned variable, align it first.
            return CRESULT::FAILED_NOT_ROUNDED;

        SHA512_t tempHash;
        SHA512_t tempSign;

        // now hashing, decrypting.
        getSHA512Hash(tempHash, pIn, szIn);         // get original hash by hashing pIn
        getRSAPubDecrypt(&tempSign, &Sig, PubKey);  // get original hash by decrypting signature.

        // tempSig will return original hash value.
        // we are going to compare it.
        return isSHA512HashEqual(tempHash, tempSign) ? CRESULT::SUCCESSED : CRESULT::INVALID_SIGNATURE;
    }
}