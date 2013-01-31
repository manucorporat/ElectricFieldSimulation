// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSELECTORS_H_INCLUDED__
#define __FZSELECTORS_H_INCLUDED__
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
    class SELProtocol
    {
    public:
        virtual ~SELProtocol() {}
    };
    
    // Types
    typedef void (SELProtocol::*SELECTOR_FLOAT)(fzFloat);    
    typedef void (SELProtocol::*SELECTOR_VOID)();
    typedef void (SELProtocol::*SELECTOR_PTR)(void*);
    typedef void (SELProtocol::*SELECTOR_2PTR)(void*, void*);
    
    
    //! @def SEL_VOID
    //! This macro creates a "SELECTOR_VOID". Method without parametters
    //! SEL_VOID(Node::doSomething) points to Node::doSomething() {}
#define SEL_VOID(_SELECTOR) (SELECTOR_VOID)(&_SELECTOR)
    
    
    //! @def SEL_FLOAT
    //! This macro creates a "SELECTOR_FLOAT". Method with a float parameter
    //! SEL_FLOAT(Node::update) points to Node::update(fzFloat myFloat) {}
#define SEL_FLOAT(_SELECTOR) (SELECTOR_FLOAT)(&_SELECTOR)
    
    
    //! @def SEL_PTR
    //! This macro creates a "SELECTOR_PTR". Method with a pointer parameter
    //! SEL_FLOAT(Node::destroy) points to Node::destroy(void *myObject)
#define SEL_PTR(_SELECTOR) (SELECTOR_PTR)(&_SELECTOR)
    
    
    //! @def SEL_2PTR
    //! This macro creates a "SELECTOR_2PTR". Method with a two pointer parameters
    //! SEL_2PTR(Node::connect) points to Node::connect(void *obj1, void *obj2)
#define SEL_2PTR(_SELECTOR) (SELECTOR_2PTR)(&_SELECTOR)
        
}
#endif
