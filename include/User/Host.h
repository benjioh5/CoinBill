#ifndef COINBILL_USER_HOST
#define COINBILL_USER_HOST

#include <Support/Types.h>
#include <vector>

namespace CoinBill
{
    class Wallet;
    class Socket;

    class Host
    {
    public:
        // TODO : implemnt notify methods based on P2P network.
        //        so that we can send / share objects on other peers.
        void notifyNewContract();
        void notifyNewAccount();
        void notifyNewTransaction();
        void notifyConnectedPeers();
        void ProcessQueues();

        static uint64_t getHostVersion();
        static uint64_t getHostTime();
        static uint64_t getNumNewDiff();
        static uint32_t getHashCycle();
    private:
        Wallet* hostWallet;
        Socket* hostSocket;
    };


    Host* createHost(Wallet* wallet);
}

#endif