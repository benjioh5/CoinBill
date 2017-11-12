#ifndef COINBILL_USER_WALLET
#define COINBILL_USER_WALLET

#include <vector>
#include <Support/Types.h>
#include <Support/Cryption.h>

namespace CoinBill
{
    class BlockV1;

    class WalletData
    {
    public:
        
        RSA4096_t   m_PubKey;
        RSA4096_t   m_PrvKey;

        SHA512_t    m_Block;
        uint64_t    m_Money;
    };

    class Wallet
    {
        SHA256_t    m_account;
        WalletData* m_data;

    public:
        SHA256_t&   getAccount();
        RSA4096_t&  getPubKey() const;
        RSA4096_t&  getPrvKey() const;
        
        SHA512_t&   getWalletBlock() const;
        uint64_t    getWalletCoin() const;
        WalletData* getWalletData() const;

        bool refreshAccount();
        bool refreshPublicKey();
    };

    Wallet* createAccount();
    Wallet* createAccount(BlockV1* block, SHA256_t& hash);
    Wallet* createAccount(RSA* Key);
    Wallet* createAccountPrv(RSA4096_t& PrvKey);
    Wallet* createAccountPub(RSA4096_t& PubKey);
}

#endif // COINBILL_USER_WALLET