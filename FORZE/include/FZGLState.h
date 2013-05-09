// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZGLSTATE_H_INCLUDED__
#define __FZGLSTATE_H_INCLUDED__
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

#include "FZOSW.h"


namespace FORZE {
    
    enum {
        kGLColors = 1 << 0,
        kGLTexcoords = 1 << 1
    };
    
    enum fzGLMode
    {
        kFZGLMode_Primitives        = 0,
        kFZGLMode_NoTexture         = kGLColors,
        kFZGLMode_TextureNoColor    = kGLTexcoords,
        kFZGLMode_Texture           = kGLColors | kGLTexcoords
    };
    
    
    //! Sets OpenGL settings.
    void fzGLSetMode( fzGLMode mode );
    
    
    //! Uses the GL program in case program is different than the current one.
    //! @see GLProgram
    void fzGLUseProgram( GLuint program );
    
    
    //! Binds a texture in case it is not already bound.
    //! @see Texture2D
    void fzGLBindTexture2D( GLuint textureID );
    
    
    //! Binds a framebuffer in case it is not already bound.
    //! @see Grabber
    void fzGLBindFramebuffer(GLuint framebuffer);

    
    //! Used internally to cache the current FBO.
    //! @see Grabber
    GLuint fzGLGetFramebuffer();
    
    
    //! Uses a blending function in case it not already used.
    void fzGLBlendFunc(GLenum sfactor, GLenum dfactor);
    void fzGLBlendFunc(const fzBlendFunc& blend);

    
    //! Sets a new clear color in case it is different than the current one.
    void fzGLClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void fzGLClearColor(const fzColor4F& color);
    
    
    //! Deletes the GL program. If it is the one that is being used, it invalidates it.
    void fzGLDeleteProgram( GLuint program );
    
    
    //! Deletes a texture ID a resets the texture ID cache in case it is being used.
    void fzGLDeleteTexture( GLuint textureID );
}
#endif
