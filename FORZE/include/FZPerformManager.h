// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZPERFORMMANAGER_H_INCLUDED__
#define __FZPERFORMMANAGER_H_INCLUDED__
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

#include "FZTypes.h"
#include "FZSelectors.h"
#include STL_QUEUE


using namespace STD;

namespace FORZE {

    class recursive_mutex;
    class PerformManager
    {        
    private:
        struct fzPerform {
            SELProtocol *target;
          
            char valueType;
            union {
                SELECTOR_FLOAT argFloat;
                SELECTOR_VOID argVoid;
                SELECTOR_PTR argPTR;
                SELECTOR_2PTR arg2PTR;
            } selector;
          
            union {
                float valueFloat;
                void *ptr[2];
            } value;
        };
        typedef queue<fzPerform> performsQueue;
        
        recursive_mutex *p_mutex;
        
        // Manager's instance
        static PerformManager* p_instance;
        
        performsQueue m_syncPerforms;
        performsQueue m_asyncPerforms;

        void execute(const fzPerform& perform) const;
        void schedule(const fzPerform&, bool async);
        
        
    protected:
        // Constructors
        PerformManager();
        PerformManager(const PerformManager&);
        PerformManager &operator = (const PerformManager& );
        
        
    public:
        // Get and alloc instance
        static PerformManager& Instance();
        
        
        void perform(SELProtocol *target, SELECTOR_FLOAT selector, float withFloat, bool async);
        void perform(SELProtocol *target, SELECTOR_VOID selector, bool async);
        void perform(SELProtocol *target, SELECTOR_PTR selector, void *withPointer, bool async);
        void perform(SELProtocol *target, SELECTOR_2PTR selector, void *withPointer, void *withPointer2, bool async);
      
        void clean();
    };
}
#endif
