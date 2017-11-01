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
        bool InitSocket() {
            return true;
        }
        bool StopSocket() {
            return true;
        }

        bool SocketCreateUDP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type) {
            return true;
        }
        bool SocketCreateTCP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type) {
            return true;
        }

        bool SocketClose(const SOCKET_HANDLE Handle) {
            return true;
        }
        bool SocketDisconnect(const SOCKET_HANDLE Handle) {
            return true;
        }

        bool SocketBind(const SOCKET_HANDLE Handle, const std::string& Address, short Port) {
            return true;
        }
        bool SocketListen(const SOCKET_HANDLE Handle) {
            return true;
        }
        bool SocketAccept(const SOCKET_HANDLE Handle, SOCKET_HANDLE& Accepted) {
            return true;
        }

        size_t SocketSend(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf) {
            return 0;
        }
        size_t SocketRecv(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf, int timeout) {
            return 0;
        }
    }
}