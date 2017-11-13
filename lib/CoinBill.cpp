#include <Support/Logger.h>
#include <Support/Cryption.h>

#include <Network/SocketFuncBinding.h>
#include <Network/Socket.h>

#include <User/Host.h>
#include <User/Blockv1.h>
#include <User/Wallet.h>

#include <iostream>

using namespace CoinBill;

int main(int args, char* argc[], char* argv[])
{
    LogInf() << "CoinBill Core Client"                          << std::endl;
    LogInf() << "Host Version : " << Host::getHostVersion()     << std::endl;
    LogInf() << "Starting Up Program Instance...."              << std::endl;

    // Initialize socket.
    bool socketInit = InitSocket();
    LogInf() << "Initialized socket."                           << std::endl;

    // check socket initialized successfully.
    if (!socketInit) {
        LogErr() << "Failed initialize socket!"                 << std::endl;
        return -1;
    }

    // Initialize crypt algorithms.
    InitCryption();
    LogInf() << "Initialized cryption algorithms."              << std::endl;

    Wallet* tw = createAccount();
    tw->dump();

    return 0;
}
