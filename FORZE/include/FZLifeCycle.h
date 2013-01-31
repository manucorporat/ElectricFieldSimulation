// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZLIFECICLE_H_INCLUDED__
#define __FZLIFECICLE_H_INCLUDED__
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

#include "FZSelectors.h"
#if FZ_AUTORELEASE
#include "FZPerformManager.h"
#endif

namespace FORZE {
    
    /** LifeCycle is a base class used to control the objects' life cicle.
     * LifeCycle implements a "retaincount" system to control how many instances are using the object
     * and remove it when the object is not longer used.
     */

  class LifeCycle : public SELProtocol
    {
    private:
        // counts the number of retains
        int m_retains;
        
        
    public:
        
        LifeCycle() : m_retains(!!FZ_AUTORELEASE) {
#if FZ_AUTORELEASE
            autorelease();
#endif
        }
        
        virtual ~LifeCycle() {}
        
        
        //! Returns the number of retains.
        int retainCount() {
            return m_retains;
        }
        
        
        //! Increments the retain count by 1.
        //! @warning FORZE manages the memory automatically but if you retain an object you have to release it.
        LifeCycle* retain() {
            ++m_retains;
            return this;
        }
        
        
        //! Reduces the retain count by 1.
        //! If the retain count is less or equal to 0, the object is released from memory (deleted).
        void release() {
            --m_retains;
            if(m_retains <= 0)
                delete this;
        }
        
#if FZ_AUTORELEASE
        //! Autorelease calls release() when just before finish the runloop.
        //! autorelease() is a like scheduling a call to release() when all tasks finished.
        void* autorelease() {
            PerformManager::Instance().perform(this, SEL_VOID(LifeCycle::release), false);
            return this;
        }
#endif
    };
}

#endif
