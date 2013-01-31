// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZGRABBER_H_INCLUDED__
#define __FZGRABBER_H_INCLUDED__
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

#include "FZTexture2D.h"


namespace FORZE {
    
    /** FBO class that grabs the the contents of the screen */
    class Grabber
    {
    private:
        Texture2D *p_texture;
        GLuint	m_fbo;
        GLuint	m_oldFBO;
        
        
    public:
        //! Constructors an high level wrapper for the framebuffer management.
        Grabber();
        ~Grabber();
        
        //! Returns the associated texture.
        Texture2D *getTexture() const;
        
        
        //! Associates a Texture2D with the framebuffer (FBO).
        void grab(Texture2D*);
        
        
        //! Binds the framebuffer.
        //! @see beginWithClear()
        //! @see end()
        void begin();
        
        
        //! Binds and cleans the framebuffer.
        //! @see begin()
        //! @see clear()
        //! @see end()
        void beginWithClear(const fzColor4F& color = fzColor4F(0, 0, 0, 0));
        
        
        //! Restores the current framebuffer before calling begin().
        //! @see begin()
        //! @see beginWithClear()
        void end();
        
        
        //! Cleans the framebuffer. This method is automatically called in beginWithClear().
        //! @see beginWithClear()
        void clear(const fzColor4F& color = fzColor4F(0, 0, 0, 0));
    };
    
    
    class FBOTexture
    {
    private:
        Grabber m_grabber;
        fzMat4 m_transform;

        
    public:
        FBOTexture() = default;
        FBOTexture(fzTextureFormat format, const fzSize& size, fzFloat quality = 1);
        

        void config(fzTextureFormat format, fzSize size, const fzPoint& anchorPoint, fzFloat quality);
        
        
        //! Returns the grabbed texture.
        Texture2D *getTexture() const;
        
        
        //! Binds the framebuffer.
        //! @see beginWithClear()
        //! @see end()
        void begin();
        
        
        //! Binds and cleans the framebuffer.
        //! @see begin()
        //! @see clear()
        //! @see end()
        void beginWithClear(const fzColor4F& color = fzColor4F(0, 0, 0, 0));
        
        
        //! Restores the current framebuffer before calling begin().
        //! @see begin()
        //! @see beginWithClear()
        void end();
        
        
        //! Cleans the framebuffer. This method is automatically called in beginWithClear().
        //! @see beginWithClear()
        void clear(const fzColor4F& color = fzColor4F(0, 0, 0, 0));
    };
}
#endif
