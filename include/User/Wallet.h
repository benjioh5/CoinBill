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
        WalletData  m_data;

    public:
        SHA256_t&   getAccount();
        RSA4096_t&  getPubKey();
        RSA4096_t&  getPrvKey();
        
        SHA512_t&   getWalletBlock();
        uint64_t    getWalletCoin();
        WalletData& getWalletData();

        bool refreshAccount();
        bool refreshPublicKey();
        void dump();
    };

    Wallet* createManagedWallet();
    void deleteManagedWallet(CoinBill::Wallet* wallet);

    Wallet* createAccount(BlockV1* block, RSA4096_t& PrvKey, RSA4096_t& PubKey);
    Wallet* createAccount(BlockV1* block, RSA4096_t& PrvKey);
    Wallet* createAccount(RSA* Key);
    Wallet* createAccountPrv(RSA4096_t& PrvKey);
    Wallet* createAccountPub(RSA4096_t& PubKey);
    Wallet* createAccount();
}

#endif // COINBILL_USER_WALLET