// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_CRYPTO_HASHBLAKE3_H
#define BITCOIN_CRYPTO_HASHBLAKE3_H

#include <uint256.h>
#include <serialize.h>
#include "blake3.h"
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <vector>
#include <string>

template<typename T1>
inline uint256 HashBlake3(const T1 pbegin, const T1 pend)
{
    static unsigned char pblank[1];
  
    //Initialize a blake3_hasher in the key derivation mode
    blake3_hasher hasher;
    blake3_hasher_init_derive_key(&hasher, BEGIN(nVersion));
  
    blake3_hasher_update( &hasher, (pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]) );
  
    // Finalize the hash. BLAKE3_OUT_LEN is the default output length, 32 bytes.
    uint8_t output[BLAKE3_OUT_LEN];
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);
}

#endif // BITCOIN_CRYPTO_HASHBLAKE3_H
