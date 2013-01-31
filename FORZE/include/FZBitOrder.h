// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZBYTEUTILS_H_INCLUDED__
#define __FZBYTEUTILS_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 FORZEFIELD Studios S.L.
 * Copyright (c) 2012 Manuel Martínez-Almeida
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 @author Manuel Martínez-Almeida
 */

#include "FZTypes.h"


namespace FORZE {
    
    //! Swap between byte order, short types, 16 bits.
    uint16_t fzBitOrder_int16Swap (uint16_t n);
    
    
    //! Swap between byte order, long types, 32 bits.
    uint32_t fzBitOrder_int32Swap (uint32_t n);
    
    
    //! Swap between byte order, long long types, 64bits.
    uint64_t fzBitOrder_int64Swap (uint64_t n);
    
    
    //! Little endian to host, "Short".
    uint16_t fzBitOrder_int16LittleToHost(uint16_t little);
    
    
    //! Little endian to host, "Long" i.e. int.
    uint32_t fzBitOrder_int32LittleToHost(uint32_t little);
    
    
    //! Little endian to host, "double" i.e. long long.
    uint64_t fzBitOrder_int64LittleToHost(uint64_t little);
    
    
    //! Big endian to host, "Short".
    uint16_t fzBitOrder_int16BigToHost(uint16_t big);
    
    
    //! Big endian to host, "Long" i.e. int.
    uint32_t fzBitOrder_int32BigToHost(uint32_t big);
    
    
    //! Big endian to host, "double" i.e. long long.
    uint64_t fzBitOrder_int64BigToHost(uint64_t big);
}
#endif
