#include <Network/SocketFuncBinding.h>

#ifdef COINBILL_USE_BOOST_ASIO
#include <boost/asio.hpp>
#elif COINBILL_WINDOWS
#include <Windows.h>
#include <WinSock2.h>
#endif

namespace CoinBill
{
    namespace SocketBinding
    {
        bool InitSocket()
        {

        }
        bool StopSocket()
        {

        }
        bool SocketCreateUDP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type)
        {

        }
        bool SocketCreateTCP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type)
        {

        }
        bool SocketClose(const SOCKET_HANDLE Handle)
        {

        }
        bool SocketDisconnect(const SOCKET_HANDLE Handle)
        {

        }
        bool SocketBind(const SOCKET_HANDLE Handle, const std::string& Address, short Port)
        {

        }
        bool SocketListen(const SOCKET_HANDLE Handle)
        {

        }
        bool SocketAccept(const SOCKET_HANDLE Handle, SOCKET_HANDLE& Accepted)
        {

        }
        size_t SocketSend(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf)
        {

        }
        size_t SocketRecv(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf, int timeout)
        {

        }
    }
}