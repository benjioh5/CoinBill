#ifndef COINBILL_NETWORK_HOST
#define COINBILL_NETWORK_HOST

namespace CoinBill
{
    class Host
    {
    public:

        unsigned int getNumConnections() const;
        unsigned int getNumManagedThreads() const;
    private:
    };
}

#endif