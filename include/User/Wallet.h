#ifndef COINBILL_USER_WALLET
#define COINBILL_USER_WALLET

#include <vector>
#include <Support/Types.h>

namespace CoinBill
{
    class Wallet
    {
    public:
        SHA256_t m_Owner;
        SHA512_t m_Block;

        uint64_t m_Balance;
    };
}

#endif