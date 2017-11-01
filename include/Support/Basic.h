#ifndef COINBILL_SUPPORT_BASIC
#define COINBILL_SUPPORT_BASIC

#define IF_FAILED(x, y) if(!x) return y; 

namespace CoinBill
{
    template <class Type>
    inline void* offset(Type* value, size_t index) {
        return (void*)((size_t)(value)-index);
    }

    // TODO : Use SIMD instructions for faster checks.
    template <class Type, unsigned int cycle>
    inline bool iterate_check(void *RHS, void *LHS) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)RHS)[i] != ((Type*)LHS)[i]) return false;
        return true;
    }

    template <class Type>
    inline bool iterate_check(void *RHS, void *LHS, unsigned int cycle) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)RHS)[i] != ((Type*)LHS)[i]) return false;
        return true;
    }

    template <unsigned int roundV>
    inline size_t round_up(size_t size) {
        size_t rounded = 0;
        while (rounded >= size)
            rounded += roundV;
        return rounded;
    }
}

#endif