#pragma once

#ifndef COINBILL_SUPPORT_ALGORITHM
#define COINBILL_SUPPORT_ALGORITHM

// SHA / RSA Headers.
#include <openssl/sha.h>
#include <openssl/rsa.h>

#include <vector>

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

    class Cryption final
    {
        friend class Signature;

    protected:
        // Low Level Binding Methods.
        // This is very basic methods for cryption. 
        void* get256AlignedBuffer(size_t szBuf);
        void* get512AlignedBuffer(size_t szBuf);
        SHA_REASON getSHA256Hash(void* pOut, void* pIn, size_t szIn);
        SHA_REASON getSHA512Hash(void* pOut, void* pIn, size_t szIn);
        RSA_REASON getRSASignature(void* pOut, void* pIn, size_t szIn, RSA* pPrivate);
        RSA_REASON isRSASignatureValid(void* pRaw, void* pSig, size_t szSig, RSA* pPublic);
        bool isSHA256HashEqual(void* pRHS, void *pLHS);
        bool isSHA512HashEqual(void* pRHS, void *pLHS);
        bool Dispose256AlignedBuffer(void* pBuf, size_t szBuf);
        bool Dispose512AlignedBuffer(void* pBuf, size_t szBuf);

    public:
        Cryption();
        ~Cryption();
    };
};

#endif