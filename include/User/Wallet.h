#ifndef COINBILL_USER_WALLET
#define COINBILL_USER_WALLET

#include <vector>
#include <Support/Types.h>

namespace CoinBill
{
    class WalletData
    {
    public:
        RSA2048_t m_PubKey;
        RSA2048_t m_PrvKey;

        SHA512_t m_Block;
        uint64_t m_Money;
    };

    class Wallet
    {
        WalletData* m_data;

    public:
        RSA2048_t& getPubKey() const;
        RSA2048_t& getPrvKey() const;
        RSA2048_t& getOwner() const;

        SHA512_t& getWalletBlock() const;
        uint64_t getWalletCoin() const;
    };
}

#endif