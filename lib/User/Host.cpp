#include <User/Host.h>

#include <time.h>

namespace CoinBill
{
    uint64_t Host::getHostVersion() {
        return 0;
    }
    uint64_t Host::getHostTime() {
        time_t t;
        time(&t);

        return (uint64_t)t;
    }
    uint64_t Host::getNumNewDiff() {
        // We generate new difficulty every 2 month.
        return 2 * 60 * 30 * 2;
    }
    uint32_t Host::getHashCycle() {
        // The default hash cycle for block is 2.
        return 2;
    }
}