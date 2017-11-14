#pragma once

#ifndef COINBILL_SUPPORT_ALGORITHM
#define COINBILL_SUPPORT_ALGORITHM

// SHA / RSA Headers.

#include <vector>
#include <Support/Types.h>
#include <Support/Basic.h>

namespace CoinBill
{
    void InitCryption();
    void StopCryption();

    typedef class __CRYPT_HANDLE*   CRYPT_HANDLE;

    typedef CRYPT_HANDLE            SHA256_HANDLE;
    typedef CRYPT_HANDLE            SHA512_HANDLE;
    typedef CRYPT_HANDLE            RSA_HANDLE;


    // key, hash object allocator.
    //
    SHA256_t* createSHA256();
    SHA512_t* createSHA512();
    RSA_t* createRSA();

    // key, hash object disposer.
    //
    void disposeSHA256(SHA256_t* object);
    void disposeSHA512(SHA512_t* object);
    void disposeRSA(RSA_t* object);
        
    // RSA - 4098 Binding.
    void queryRSAEngine(RSA_HANDLE& handle);
    void queryRSADelete(RSA_HANDLE& handle);
    void queryRSAEncryptPub(RSA_HANDLE& handle, RSA_t& Key, void* pIn, size_t szIn);
    void queryRSADecrpytPub(RSA_HANDLE& handle, RSA_t& Key, void* pOut, size_t szOut);
    void queryRSAEncryptPrv(RSA_HANDLE& handle, RSA_t& Key, void* pIn, size_t szIn);
    void queryRSADecryptPrv(RSA_HANDLE& handle, RSA_t& Key, void* pOut, size_t szOut);

    // SHA-3 256 Hash Binding.
    //
    void querySHA256Engine(SHA256_HANDLE& handle);
    void querySHA256Update(SHA256_HANDLE& handle, void* pIn, size_t szIn);
    void querySHA256Verify(SHA256_HANDLE& handle, SHA256_t& out);
    void querySHA256Delete(SHA256_HANDLE& handle);
    void querySHA256Flush(SHA256_HANDLE& handle);

    // SHA-3 512 Hash Binding.
    //
    void querySHA512Engine(SHA512_HANDLE& handle);
    void querySHA512Update(SHA512_HANDLE& handle, void* pIn, size_t szIn);
    void querySHA512Verify(SHA512_HANDLE& handle, SHA512_t& out);
    void querySHA512Delete(SHA512_HANDLE& handle);
    void querySHA512Flush(SHA512_HANDLE& handle);

};
#endif // COINBILL_SUPPORT_ALGORITHM