#pragma once

#ifndef COINBILL_SUPPORT_ALGORITHM
#define COINBILL_SUPPORT_ALGORITHM

// SHA / RSA Headers.
#include <openssl/sha.h>
#include <openssl/rsa.h>

#include <vector>
#include <Support/Types.h>
#include <Support/Basic.h>

namespace CoinBill
{
    void InitCryption();
    void StopCryption();

    enum CRESULT {
        SUCCESSED                           = 0x00,
        FAILED_UNKNOWN                      = 0xFF,

        FAILED_INIT                         = 0x01,
        FAILED_UPDATE                       = 0x02, 
        FAILED_FINAL                        = 0x03,
        FAILED_ENCRYPT                      = 0x04,
        FAILED_DECRYPT                      = 0x05,
        FAILED_NOT_ROUNDED                  = 0x06,

        INVALID_PUB_KEY                     = 0x11,
        INVALID_PRV_KEY                     = 0x12
    };

    struct BlockHeaderV1;
    namespace Cryption 
    {
        // Low Level Binding Methods.
        // This is very basic methods for cryption. 
        CRESULT getRSAPrvEncrypt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Private);
        CRESULT getRSAPubDecrpyt(void* pOut, void* pIn, unsigned int szIn, RSA2048_t& Public);
        template <class InTy>
        CRESULT getRSAPrvEncrypt(void* pOut, InTy* pIn, RSA2048_t& Private) { 
            return getRSAPrvEncrypt(pOut, (void*)pIn, sizeof(InTy), Private); 
        }
        template <class InTy>
        CRESULT getRSAPubDecrpyt(void* pOut, InTy* pIn, RSA2048_t& Public) {
            return getRSAPubDecrpyt(pOut, (void*)pIn, sizeof(InTy), Public);
        }
        template <class InTy, size_t size>
        CRESULT getRSAPrvEncrypt(void* pOut, InTy(&pIn)[size], RSA2048_t& Private) {
            return getRSAPrvEncrypt(pOut, (void*)pIn, sizeof(InTy) * size, Private);
        }
        template <class InTy, size_t size>
        CRESULT getRSAPubDecrpyt(void* pOut, InTy(&pIn)[size], RSA2048_t& Public) {
            return getRSAPubDecrpyt(pOut, (void*)pIn, sizeof(InTy) * size, Public);
        }

        CRESULT getSHA256Hash(SHA256_t& Out, void* pIn, size_t szIn);
        CRESULT getSHA512Hash(SHA512_t& Out, void* pIn, size_t szIn);

        template <class Ty>
        CRESULT getSHA256Hash(SHA256_t& Out, Ty* pIn) { 
            return getSHA256Hash(Out, (void*)pIn, sizeof(Ty)); 
        }
        template <class Ty>
        CRESULT getSHA512Hash(SHA512_t& Out, Ty* pIn) { 
            return getSHA512Hash(Out, (void*)pIn, sizeof(Ty)); 
        }
        template <class Ty, size_t size>
        CRESULT getSHA256Hash(SHA256_t& Out, Ty(&pIn)[size]) { 
            return getSHA256Hash(Out, (void*)pIn, sizeof(Ty) * size); 
        }
        template <class Ty, size_t size>
        CRESULT getSHA512Hash(SHA512_t& Out, Ty(&pIn)[size]) { 
            return getSHA512Hash(Out, (void*)pIn, sizeof(Ty) * size); 
        }

        bool isSHA256HashEqual(const SHA256_t& LHS, const SHA256_t& RHS);
        bool isSHA512HashEqual(const SHA512_t& LHS, const SHA512_t& RHS);

        CRESULT getSignature256(SHA256_t& SigOut, void* pIn, size_t szIn, RSA2048_t& PrvKey);
        CRESULT getSignature512(SHA512_t& SigOut, void* pIn, size_t szIn, RSA2048_t& PrvKey);

        template <class Ty, class AlignedTy = ALIGN_V_BIT(Ty, 2048)>
        CRESULT getSignature256(SHA256_t& SigOut, Ty& In, RSA2048_t& PrvKey) {
            AlignedTy AlignedIn; 
            memset((void*)&AlignedIn, 0         , sizeof(AlignedTy) );
            memcpy((void*)&AlignedIn, (void*)&In, sizeof(Ty)        );
            return getSignature256(SigOut, (void*)&AlignedIn, sizeof(AlignedTy), PrvKey);
        }
        template <class Ty, class AlignedTy = ALIGN_V_BIT(Ty, 2048)>
        CRESULT getSignature256(SHA256_t& SigOut, Ty* In, RSA2048_t& PrvKey) {
            AlignedTy AlignedIn;
            memset((void*)&AlignedIn, 0         , sizeof(AlignedTy) );
            memcpy((void*)&AlignedIn, (void*)In , sizeof(Ty)        );
            return getSignature256(SigOut, (void*)In, sizeof(AlignedTy), PrvKey);
        }
        template <class Ty, unsigned int size>
        CRESULT getSignature256(SHA256_t& SigOut, Ty(&In)[size], RSA2048_t& PrvKey) {
            Ty AlignedIn[round_up<2048>(size)] = { 0, };
            memcpy((void*) AlignedIn, (void*)In , sizeof(Ty));
            return getSignature256(SigOut, (void*)In, sizeof(AlignedTy), PrvKey);
        }
        template <class Ty, class AlignedTy = ALIGN_V_BIT(Ty, 2048)>
        CRESULT getSignature512(SHA512_t& SigOut, Ty& In, RSA2048_t& PrvKey) {
            AlignedTy AlignedIn;
            memset((void*)&AlignedIn, 0         , sizeof(AlignedTy));
            memcpy((void*)&AlignedIn, (void*)&In, sizeof(Ty));
            return getSignature512(SigOut, (void*)&In, sizeof(AlignedTy), PrvKey);
        }
        template <class Ty, class AlignedTy = ALIGN_V_BIT(Ty, 2048)>
        CRESULT getSignature512(SHA512_t& SigOut, Ty* In, RSA2048_t& PrvKey) {
            AlignedTy AlignedIn;
            memset((void*)&AlignedIn, 0         , sizeof(AlignedTy));
            memcpy((void*)&AlignedIn, (void*)In , sizeof(Ty));
            return getSignature512(SigOut, (void*)In, sizeof(AlignedTy), PrvKey);
        }
        template <class Ty, unsigned int size, class AlignedTy = ALIGN_V_BIT(Ty, 2048)>
        CRESULT getSignature512(SHA512_t& SigOut, Ty(&In)[size], RSA2048_t& PrvKey) {
            Ty AlignedIn[round_up<2048>(size)] = { 0, };
            memcpy((void*)AlignedIn, (void*)In  , sizeof(Ty));
            return getSignature512(SigOut, (void*)In, sizeof(AlignedTy), PrvKey);
        }
    };
};

#endif