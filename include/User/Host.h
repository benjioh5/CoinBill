#ifndef COINBILL_USER_HOST
#define COINBILL_USER_HOST

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

    private:
    };
}

#endif