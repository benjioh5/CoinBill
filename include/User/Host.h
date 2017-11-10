#ifndef COINBILL_USER_HOST
#define COINBILL_USER_HOST

#include <Support/Types.h>

namespace CoinBill
{
    class Wallet;
    class Host
    {
    public:
        // TODO : implemnt notify methods based on P2P network.
        //        so that we can send / share objects on other peers.
        void notifyNewContract();
        void notifyNewWallet();
        void notifyNewTransaction();
        void notifyConnectedPeers();

        static uint64_t getHostVersion();
        static uint64_t getHostTime();
        static uint64_t getNumNewDiff();
        static uint32_t getHashCycle();

    private:
    };
}

#endif