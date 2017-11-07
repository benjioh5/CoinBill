#ifndef COINBILL_SUPPORT_BASIC
#define COINBILL_SUPPORT_BASIC

#define IF_FAILED(x, y) if(!x) return y; 

namespace CoinBill
{
    template <class Type>
    inline void* offset(Type* value, int index) {
        return (void*)((size_t)(value)+index);
    }

    // TODO : Use SIMD instructions for faster checks.
    template <class Type, unsigned int cycle>
    inline int iterate_cmp(void *LHS, void *RHS) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)LHS)[i] != ((Type*)RHS)[i]) 
                return ((Type*)LHS)[i] - ((Type*)RHS)[i];
        return 0;
    }

    template <class Type>
    inline Type iterate_cmp(void *LHS, void *RHS, unsigned int cycle) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)LHS)[i] != ((Type*)RHS)[i])
                return ((Type*)LHS)[i] - ((Type*)RHS)[i];
        return 0;
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