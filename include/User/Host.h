#ifndef COINBILL_USER_HOST
#define COINBILL_USER_HOST

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;
    class Host
    {
    public:
        void notifyNewContract();
        void notifyNewWallet();
        void notifyNewTransaction();
        void notifyPeers();

        static uint64_t getHostVersion();
        static uint64_t getHostTime();
        static uint64_t getNumNewDiff();
        static uint32_t getHashCycle();

    private:
    };
}

#endif