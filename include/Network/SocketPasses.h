#ifndef COINBILL_NETWORK_SOCKET_PASSES
#define COINBILL_NETWORK_SOCKET_PASSES

namespace CoinBill
{

    enum SOCKET_TYPE {
#ifdef COINBILL_USE_BOOST_ASIO
        // TODO : Boost implements.
#elif  COINBILL_WINDOWS
        Stream              = 1, 
        DGRAM               = 2, 
        Raw                 = 3
#endif // COINBILL_WINDOWS
    };
}

#endif // COINBILL_NETWORK_SOCKET_PASSES