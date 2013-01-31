// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZCOMMON_H_INCLUDED__
#define __FZCOMMON_H_INCLUDED__
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
#include <stdexcept>
#include "FZConfig.h"
#include "FZHash.h"
#include STL_STRING


using namespace STD;

namespace FORZE
{
    class fzException : public std::runtime_error
    {
    public:
        fzException(std::string s)
        : std::runtime_error(s)
        { }
    };
    
    
    //! Custom print function used by FORZE.
    void FZLog(const char *pszFormat, ...);
    
    
    //! String with format.
    char* FZT(const char *pszFormat, ...);
    
    
    //! Allocates the necesary memory and copies the string into.
    //! @param string to be copied.
    //! @param length of the string to be copied. "HOLA" = 4
    //! @return a new pointer to the copied string.
    //! @warning the returned pointer must be released using delete
    char* fzStrcpy(const char *string, size_t length);
    
    
    //! Allocates the necesary memory and copies the string into.
    //! @param string is the NULL-terminated string to be copied.
    //! @return a new pointer to the copied string.
    //! @warning the returned pointer must be released using delete
    char* fzStrcpy(const char *string);
    
    
    //! Returns a localized string for the given key.
    const char* FZTLocalized(const char *key);
}

#endif
