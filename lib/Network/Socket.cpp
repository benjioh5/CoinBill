#include <Network/Socket.h>

namespace CoinBill
{
    size_t Socket::Recv(void* pBuf, size_t& szBuf) {
        return SocketRecv(m_SockHandle, pBuf, szBuf);
    }
    size_t Socket::Send(void* pBuf, size_t& szBuf) {
        return SocketSend(m_SockHandle, pBuf, szBuf);
    }

    NetHost* Socket::getParent() const {
        return m_Host;
    }
    SOCKET_HANDLE Socket::getNativeHandle() const {
        return m_SockHandle;
    }
    SOCKET_TYPE Socket::getNativeType() const {
        return m_SockType;
    }
}