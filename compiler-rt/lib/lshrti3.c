//===-- lshrti3.c - Implement __lshrti3 -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements __lshrti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#if __x86_64

#include "int_lib.h"

// Returns: logical a >> b

// Precondition:  0 <= b < bits_in_tword

ti_int
__lshrti3(ti_int a, si_int b)
{
    const int bits_in_dword = (int)(sizeof(di_int) * CHAR_BIT);
    utwords input;
    utwords result;
    input.all = a;
    if (b & bits_in_dword)  // bits_in_dword <= b < bits_in_tword
    {
        result.high = 0;
        result.low = input.high >> (b - bits_in_dword);
    }
    else  // 0 <= b < bits_in_dword
    {
        if (b == 0)
            return a;
        result.high  = input.high >> b;
        result.low = (input.high << (bits_in_dword - b)) | (input.low >> b);
    }
    return result.all;
}

#endif
