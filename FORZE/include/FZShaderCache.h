// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSHADERCACHE_H_INCLUDED__
#define __FZSHADERCACHE_H_INCLUDED__
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

#include "FZGLProgram.h"


namespace FORZE {
    
    enum {
        kFZShader_mat_aC4_TEX,
        kFZShader_mat_aC4,
        kFZShader_mat_TEX,
        
        kFZShader_mat_uC4_TEX,
        kFZShader_mat_uC4,
        
        kFZShader_nomat_aC4_TEX
    };
    
#if FZ_GL_SHADERS
#define NUM_SHADERS 6

    class ShaderCache
    {
    private:
        static ShaderCache* p_instance;
        GLProgram *m_programs[NUM_SHADERS];
        
        
    protected:
        // Constructors
        ShaderCache();
        ShaderCache(const ShaderCache& );
        ShaderCache &operator = (const ShaderCache& );
        
        //! Used internally to load the basic shaders in batch.
        void loadDefaultShaders();
        
        
    public:
        //! Gets and allocates the singleton.
        static ShaderCache& Instance();
        
        
        //! Returns the GLProgram associated with the key.
        //! @return NULL if key is invalid.
        GLProgram* getProgramByKey(fzUInt key) const;
    };
#endif
}
#endif
