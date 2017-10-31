#ifndef COINBILL_NETWORK_SOCKET
#define COINBILL_NETWORK_SOCKET

#include <Network/SocketFuncBinding.h>

namespace CoinBill
{
    using namespace SocketBinding;

    class Host;
    class Socket
    {
        // Basic socket binding methods.
        // This is directly binded to raw socket functions.
        size_t Recv(void* pBuf, size_t& szBuf);
        size_t Send(void* pBuf, size_t& szBuf);

        template <class Ty, size_t Len>
        size_t Send(Ty (&Buf)[Len]) {
            return Send(Buf, sizeof(Ty * Len));
        }
        template <class Ty, size_t Len>
        size_t Recv(Ty (&Buf)[Len]) {
            return Recv(Buf, sizeof(Ty * Len));
        }

    public:
        Host* getParent() const;
        SOCKET_HANDLE getNativeHandle() const;

    private:
        Host*           m_Host;
        SOCKET_HANDLE   m_SockHandle;
        SOCK_TYPE       m_SockType;
    };
}

#endif