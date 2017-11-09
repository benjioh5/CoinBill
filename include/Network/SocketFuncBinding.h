#ifndef COINBILL_NETWORK_SOCKET_FUNC_BINDING
#define COINBILL_NETWORK_SOCKET_FUNC_BINDING

#include <string>
#include <Network/SocketPasses.h>

namespace CoinBill
{
    bool InitSocket();
    bool StopSocket();

    namespace SocketBinding
    {
        typedef void* SOCKET_HANDLE;

        bool SocketCreateUDP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type);
        bool SocketCreateTCP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type);

        bool SocketClose(const SOCKET_HANDLE Handle);
        bool SocketDisconnect(const SOCKET_HANDLE Handle);
        bool SocketBind(const SOCKET_HANDLE Handle, const std::string& Address, short Port);
        bool SocketListen(const SOCKET_HANDLE Handle);
        bool SocketAccept(const SOCKET_HANDLE Handle, SOCKET_HANDLE& Accepted);
        
        // SocketSend will return buffer size that sent.
        size_t SocketSend(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf);

        // SocketRecv will return buffer size that size left.
        // This will wait until someting recved, or timed out.
        size_t SocketRecv(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf, int timeout = -1);
    }
}

#endif