// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZHASH_H_INCLUDED__
#define __FZHASH_H_INCLUDED__
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

#include <stdint.h>

namespace FORZE
{
#pragma mark - HASH ITERATION FUNCTION

#define __HASH_FUNCTION(__HASH__, __VALUE__) \
((((__HASH__) << 5) + (__HASH__)) + (__VALUE__))
    

#pragma mark - Compiler time recursive implementation
    
    constexpr int32_t __fzHashRecursive(int32_t hash, const char* str)
    {
        return (!*str ? hash
                : __fzHashRecursive(__HASH_FUNCTION(hash, *str), str+1));
    }
    
    
    constexpr int32_t fzHashConst(const char* str)
    {
        return (!str ? 0 : __fzHashRecursive(5381, str));
    }
    
    
#pragma mark - Runtime implementation
    
    int32_t fzHash(const char *str, size_t length);
    
    //! Returns an int32 hash value giving a string.
    int32_t fzHash(const char *str);
    
    //! Parses a string describing a version "x.y.z" and converts it to an integer.
    uint32_t fzVersion(const char *str);
}

#endif
