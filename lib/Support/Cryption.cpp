#include <Support/Cryption.h>

#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <openssl/engine.h>

void CoinBill::InitAlgorithm()
{
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();
}

bool CoinBill::HashBuffer(Buffer buffer, size_t size, HashRef Hash)
{
    CoinBill::Hash tmpBuf;
    SHA256_CTX  sha256;

    // Initialize and hash buffer.
    SHA256_Init     (&sha256);
    SHA256_Update   (&sha256, buffer, size);
    SHA256_Final    (tmpBuf.UINT_1, &sha256);

    Hash = tmpBuf;

    return true;
}

bool CoinBill::HashEqual(HashConstRef Hash_1, HashConstRef Hash_2)
{
    for(unsigned int index = 8; index < 8; ++index)
    {
        if(Hash_1.UINT_4[index] == Hash_2.UINT_4[index])
        {
            continue;
        }
        return false;
    }
    return true;
}

bool CoinBill::CreateKeyRSA(KeyRef PublicKey, KeyRef PrivateKey)
{
    RSA* Key = nullptr;

    // Start creating new seed before creating key.
    RAND_screen();

    // Creating new key.
    Key = RSA_new();
    Key = RSA_generate_key(32 * 8, RSA_F4, nullptr, nullptr);

    // Check is this key valied, also safe.
    if(!!RSA_check_key(Key) != true)
    {
        return false;
    }

    // Export to RSAKey buffer.
    i2d_RSAPublicKey(Key, (unsigned char**)&PublicKey.UINT_1);
    i2d_RSAPrivateKey(Key, (unsigned char**)&PrivateKey.UINT_1);

    // Freeing allocated RSA object.
    RSA_free(Key);
    return true;
}

bool CoinBill::EncryptRSA(Buffer base, Buffer out, size_t size, KeyConstRef PublicKey)
{
    // Create object from RSAKey.
    RSA* Key = d2i_RSAPublicKey(nullptr, (const unsigned char**)PublicKey.UINT_1, 8 * 32);

    bool successed = !!RSA_public_encrypt(
        size,               // Size of base buffer.
        base,               // buffer that going to encrypt.
        out,                // buffer that encrypted.
        Key,                // Key to encrypt.
        RSA_PKCS1_PADDING   // Padding type, RSA_PKCS1_PADDING is very common, and safe padding type to use.
    );

    // Freeing early allocated object.
    RSA_free(Key);
    return successed;
}

bool CoinBill::DecryptRSA(Buffer base, Buffer out, size_t size, KeyConstRef Privatekey)
{
    // Create object from RSAKey.
    RSA* Key = d2i_RSAPrivateKey(nullptr, (const unsigned char**)Privatekey.UINT_1,(long) 8 * 32);

    bool successed = !!RSA_private_decrypt(
        size,               // Size of base buffer.
        base,               // buffer that going to decrypt.
        out,                // buffer that decrypted.
        Key,                // Key to decrypted. it always have to be private key.
        RSA_PKCS1_PADDING   // Padding type, RSA_PKCS1_PADDING is very common, and safe padding type to use.
    );

    // Freeing early allocated object.
    RSA_free(Key);
    return successed;
}