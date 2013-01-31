// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZZIPUTILS_H_INCLUDED__
#define __FZZIPUTILS_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 FORZEFIELD Studios S.L.
 * Copyright (c) 2012 Manuel Martínez-Almeida
 * Copyright (c) 2008-2010 Ricardo Quesada
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

/*
 *
 * inflateMemory_ based on zlib example code
 *		http://www.zlib.net
 *
 * Some ideas were taken from:
 *		http://themanaworld.org/
 *		from the mapreader.cpp file 
 *
 */

#include "FZAllocator.h"


namespace FORZE {
    
    class Data
    {
    public:
        //! Decodes a 64base encoded memory. The decoded memory is
        //! expected to be freed by the caller.
        //! @return the length of the out buffer
        static fzBuffer B64Decode(const char *input, fzUInt inLength);
        
        
        //! Encodes plain memory to a 64base encoded memory. The encoded memory is
        //! expected to be freed by the caller.
        //! @return the length of the out buffer
        static fzBuffer B64Encode(const char *input, fzUInt inLength);
        
        
        //! Inflates a CCZ data.
        static fzBuffer inflateCCZ(unsigned char *input, unsigned int inLength);
        
        
        //! Inflates either zlib or gzip deflated memory. The inflated memory is
        //! expected to be freed by the caller. It will allocate 256k for the destination buffer.
        //! If it is not enought it will multiply the previous buffer size per 2, until there is enough memory.
        //! @return the length of the deflated buffer.
        static fzBuffer inflateZIP(unsigned char *input, unsigned int inLength);
        
        
        /**
         * Inflates either zlib or gzip deflated memory. The inflated memory is
         * expected to be freed by the caller.
         *
         * outLenghtHint is assumed to be the needed room to allocate the inflated buffer.
         *
         * @return the length of the deflated buffer
         */
        static fzBuffer inflateZIPWithHint(unsigned char *input, unsigned int inLength, unsigned int outLenghtHint );
    };
}
#endif
