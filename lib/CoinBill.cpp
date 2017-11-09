#include <Support/Cryption.h>
#include <Network/SocketFuncBinding.h>

int main(int args, char* argc[], char* argv[])
{
    // Initialize instances.
    CoinBill::InitSocket();
    CoinBill::InitCryption();
}
