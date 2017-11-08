#pragma once

#ifndef COINBILL_SUPPORT_ALGORITHM
#define COINBILL_SUPPORT_ALGORITHM

// SHA / RSA Headers.
#include <openssl/sha.h>
#include <openssl/rsa.h>

#include <vector>
#include <Support/Types.h>

namespace CoinBill
{
    void InitCryption();
    void StopCryption();

    enum class SHA_REASON {
        SUCCESSED, FAILED_INIT, FAILED_UPDATE, FAILED_FINAL
    };

    enum class RSA_REASON {
        SUCCESSED, NOT_VALID, KEY_INVALID, FAILED_DECRYPT, FAILED_ENCRYPT
    };

    class BlockHeaderV1;
    namespace Cryption 
    {
        // Low Level Binding Methods.
        // This is very basic methods for cryption. 
        void* get256AlignedBuffer(size_t szBuf);
        void* get512AlignedBuffer(size_t szBuf);
        SHA_REASON getSHA256Hash(SHA256_t& Out, void* pIn, size_t szIn);
        SHA_REASON getSHA512Hash(SHA512_t& Out, void* pIn, size_t szIn);
        template <class Ty>
        SHA_REASON getSHA256Hash(SHA256_t& Out, Ty* pIn) { return getSHA256Hash(Out, (void*)pIn, sizeof(Ty)); }
        template <class Ty>
        SHA_REASON getSHA512Hash(SHA512_t& Out, Ty* pIn) { return getSHA512Hash(Out, (void*)pIn, sizeof(Ty)); }
        template <class Ty, size_t size>
        SHA_REASON getSHA256Hash(SHA256_t& Out, Ty(&pIn)[size]) { return getSHA256Hash(Out, (void*)pIn, sizeof(Ty) * size); }
        template <class Ty, size_t size>
        SHA_REASON getSHA512Hash(SHA512_t& Out, Ty(&pIn)[size]) { return getSHA512Hash(Out, (void*)pIn, sizeof(Ty) * size); }

        RSA_REASON getRSASignature(void* pOut, void* pIn, unsigned int szIn, RSA* pPrivate);
        RSA_REASON isRSASignatureValid(void* pRaw, void* pSig, unsigned int szSig, RSA* pPublic);

        bool isSHA256HashEqual(const SHA256_t& LHS, const SHA256_t& RHS);
        bool isSHA512HashEqual(const SHA512_t& LHS, const SHA512_t& RHS);
        bool Dispose256AlignedBuffer(void* pBuf, size_t szBuf);
        bool Dispose512AlignedBuffer(void* pBuf, size_t szBuf);

        bool getHashBasedSignature256(RSA256_t& Sig, void* pIn, unsigned int szIn, RSA* pPrivate);
        bool proofHashBasedSignature256(RSA256_t& Sig, void* pRaw, unsigned int szRaw, RSA* pPublic);
        bool getHashBasedSignature512(RSA512_t& Sig, void* pIn, unsigned int szIn, RSA* pPrivate);
        bool proofHashBasedSignature512(RSA512_t& Sig, void* pRaw, unsigned int szRaw, RSA* pPublic);
    };
};

#endif