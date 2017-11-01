#ifndef COINBILL_NETWORK_HOST
#define COINBILL_NETWORK_HOST

namespace CoinBill
{
    class NetHost
    {
    public:
        unsigned int getNumNodes() const;
        unsigned int getNumCallback() const;

    private:
    };
}

#endif