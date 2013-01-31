// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZALLOCATOR_H_INCLUDED__
#define __FZALLOCATOR_H_INCLUDED__
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


namespace FORZE
{   
    class fzBuffer
    {
    private:
        char *p_ptr;
        fzUInt m_len;
        
    public:
        
        //! Returns the default empty fzBuffer.
        static fzBuffer empty() {
            return fzBuffer(NULL, 0);
        }
        
        //! Default constructor.
        fzBuffer() = default;
        
        //! Constructs a buffer from a pointer and a length.
        fzBuffer(char *pointer, fzUInt length);
        
        
        //! Returns the buffer start constant pointer.
        const char* getPointer() const {
            return p_ptr;
        }
        
        
        //! Returns the buffer start pointer.
        char* getPointer() {
            return p_ptr;
        }
        
        
        //! Returns the buffer's length.
        fzUInt getLength() const {
            return m_len;
        }
        
        
        //! Releases the memory of the buffer and makes the buffer empty.
        void free() {
            delete [] p_ptr;
            p_ptr = NULL;
            m_len = 0;
        }
        
        
        //! Returns true if the buffer is empty.
        bool isEmpty() const {
            return (p_ptr == NULL || m_len == 0);
        }
        
        
        //! Copies the content of the buffer into a new buffer.
        fzBuffer copy() const;
    };
}

#endif
