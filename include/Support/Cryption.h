#pragma once

#ifndef COINBILL_SUPPORT_ALGORITHM
#define COINBILL_SUPPORT_ALGORITHM

namespace CoinBill
{
    typedef struct __CRYPTO_BASE
    {
        union
        {
            unsigned char       UINT_1[32];
            unsigned short      UINT_2[16];
            unsigned int        UINT_4[8];
            unsigned long long  UINT_8[4];
        };
    } CryptionBase, Hash, Key;

    typedef Key                     RSAKey;
    typedef Key                     AESKey;

    typedef unsigned char*          Buffer;

    typedef const Hash&             HashConstRef;
    typedef Hash&                   HashRef;
    typedef const Key&              KeyConstRef;
    typedef Key&                    KeyRef;

    // This will initialize algorthms, create algorithm bindings.
    void InitAlgorithm();
    
    // Check is hash equal.
    bool HashEqual(HashConstRef Hash_1, HashConstRef Hash_2);
    // Create hash with buffer.
    bool HashBuffer(Buffer buffer, size_t size, HashRef Hash);
    
    // Creating New Available RSA Key.
    bool CreateKeyRSA(KeyRef Public, KeyRef Privite);
    // Encrypt buffer with RSA Key.
    bool EncryptRSA(Buffer buffer_in, Buffer buffer_out, size_t size, KeyConstRef Key);
    // Decrpyt buffer with RSA Key.
    bool DecryptRSA(Buffer buffer_in, Buffer buffer_out, size_t size, KeyConstRef Key);
};


#endif