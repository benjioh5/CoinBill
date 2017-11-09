#include <Network/SocketFuncBinding.h>

#ifdef COINBILL_USE_BOOST_ASIO
#include <boost/asio.hpp>
#elif COINBILL_WINDOWS
#include <Windows.h>
#include <WinSock2.h>
#endif

namespace CoinBill
{
    bool InitSocket() {
        bool isSuccessed = false;
#ifdef COINBILL_USE_BOOST_ASIO
        // TODO : Boost implements.
#elif  COINBILL_WINDOWS
        // Initialize Winsock 2.
        WSAData data;
        isSuccessed = !WSAStartup(MAKEWORD(2, 0), &data);
#endif //COINBILL_WINDOWS

        return isSuccessed;
    }
    bool StopSocket() {
        bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
        // TODO : Boost implements.
#elif  COINBILL_WINDOWS
        // Cleanup Winsock 2.
        WSACleanup();
        isSuccessed = true;
#endif //COINBILL_WINDOWS

        return isSuccessed;
    }
    namespace SocketBinding
    {
        bool SocketCreateUDP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            // if successed, socket function will return socket handle.
            if(SOCKET sock = socket(AF_INET, (int)Type, IPPROTO_UDP)) {
                isSuccessed = true;
                Handle = (SOCKET_HANDLE)sock;
            }
#endif //COINBILL_WINDOWS

            return isSuccessed;
        }
        bool SocketCreateTCP(SOCKET_HANDLE &Handle, const SOCKET_TYPE Type) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            // if successed, socket function will return socket handle.
            if(SOCKET sock = socket(AF_INET, (int)Type, IPPROTO_TCP)) {
                isSuccessed = true;
                Handle = (SOCKET_HANDLE)sock;
            }
#endif //COINBILL_WINDOWS

            return isSuccessed;
        }

        bool SocketClose(const SOCKET_HANDLE Handle) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
            // Winsock 2 implements. native binding.

            // Returning zero mean successed.
            // directly closing socket by using closesocket.
            isSuccessed = !closesocket((SOCKET)Handle);
#endif
            return isSuccessed;
        }
        bool SocketDisconnect(const SOCKET_HANDLE Handle) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return true;
        }

        bool SocketBind(const SOCKET_HANDLE Handle, const std::string& Address, short Port) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return true;
        }
        bool SocketListen(const SOCKET_HANDLE Handle) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return true;
        }
        bool SocketAccept(const SOCKET_HANDLE Handle, SOCKET_HANDLE& Accepted) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return true;
        }

        size_t SocketSend(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return 0;
        }
        size_t SocketRecv(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf, int timeout) {
#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif COINBILL_WINDOWS
#endif
            return 0;
        }
    }
}