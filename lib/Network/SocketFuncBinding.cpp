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
        WSAData data = { 0, };
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
#elif  COINBILL_WINDOWS
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
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.

            // Returning zero mean successed.
            // directly closing socket by using closesocket.
            isSuccessed = !closesocket((SOCKET)Handle);
#endif
            return isSuccessed;
        }
        bool SocketDisconnect(const SOCKET_HANDLE Handle) {
            bool isSucessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.

            // Returning zero mean successed.
            // shutdown both connection by using shutdown method.
            isSucessed = !shutdown((SOCKET)Handle, SD_BOTH);
#endif
            return isSucessed;
        }

        bool SocketBind(const SOCKET_HANDLE Handle, const std::string& Address, short Port) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            sockaddr_in service;

            service.sin_family          = AF_INET;
            service.sin_addr.s_addr     = inet_addr(Address.c_str());
            service.sin_port            = htons(Port);

            isSuccessed = !bind((SOCKET)Handle, (sockaddr*)&service, sizeof(service));
#endif
            return isSuccessed;
        }
        bool SocketListen(const SOCKET_HANDLE Handle) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            isSuccessed = !listen((SOCKET)Handle, SOMAXCONN);
#endif
            return isSuccessed;
        }
        bool SocketAccept(const SOCKET_HANDLE Handle, SOCKET_HANDLE& Accepted) {
            bool isSuccessed = false;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            int         addr_len;
            sockaddr    addr;

            if (SOCKET ac = accept((SOCKET)Handle, &addr, &addr_len)) {
                Accepted    = (SOCKET_HANDLE)(ac);
                isSuccessed = true;
            }
#endif
            return isSuccessed;
        }

        size_t SocketSend(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf) {
            size_t szSent = 0;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            szSent = (size_t)send((SOCKET)Handle, (char*)pBuf, (int)szBuf, 0);
#endif
            return szSent;
        }
        size_t SocketRecv(const SOCKET_HANDLE Handle, void* pBuf, size_t& szBuf, int timeout) {
            size_t szRecved = 0;

#ifdef COINBILL_USE_BOOST_ASIO
            // TODO : Boost implements.
#elif  COINBILL_WINDOWS
            // Winsock 2 implements. native binding.
            szRecved = (size_t)recv((SOCKET)Handle, (char*)pBuf, (int)szBuf, 0);
#endif
            return szRecved;
        }
    }
}