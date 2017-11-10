#ifndef COINBILL_SUPPORT_BASIC
#define COINBILL_SUPPORT_BASIC

#define IF_FAILED(xv, y)                        if(!xv)                         t
#define IF_FAILED_RET(xv, y)                    if(!xv)                         return y;
#define IF_FAILED_GOTO(xv, y)                   if(!xv)                         goto y;

#define ALIGN_V(ty, val)                        __declspec(align(val))          ty
#define ALIGN_V_TYP(ty, typ)                    __declspec(align(sizeof(typ))   ty
#define ALIGN_V_BIT(ty, bit)                    __declspec(align(bit / 8))      ty

namespace CoinBill
{
    template <class Type>
    inline void* offset(Type* value, int index) {
        return (void*)((size_t)(value)+index);
    }

    // TODO : Use SIMD instructions for faster checks.
    template <class Type, unsigned int cycle>
    inline long long iterate_cmp(void *LHS, void *RHS) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)LHS)[i] != ((Type*)RHS)[i]) 
                return ((Type*)LHS)[i] - ((Type*)RHS)[i];
        return 0;
    }

    template <class Type>
    inline long long iterate_cmp(void *LHS, void *RHS, unsigned int cycle) {
        for (unsigned int i = 0; i < cycle; ++i)
            if (((Type*)LHS)[i] != ((Type*)RHS)[i])
                return ((Type*)LHS)[i] - ((Type*)RHS)[i];
        return 0;
    }

    template <unsigned int roundV, unsigned int roundBV = roundV / 8>
    constexpr inline size_t round_up(size_t size) {
        size_t rounded = 0;
        while (rounded > size)
            rounded += roundBV;
        return rounded;
    }
}

#endif