// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZRENDERTEXTURE_H_INCLUDED__
#define __FZRENDERTEXTURE_H_INCLUDED__
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

#include "FZNode.h"
#include "FZGrabber.h"
#include "FZTexture2D.h"


namespace FORZE {
    
    enum  
    {
        kFZImageFormatJPG = 0,
        kFZImageFormatPNG = 1,
        kFZImageFormatRawData =2
    };
    
    class Sprite;
    /**
     RenderTexture is a generic rendering target. To render things into it,
     simply construct a render target, call begin on it, call visit on any FORZE2D.
     scenes or objects to render them, and call end. For convienience, render texture
     adds a sprite as it's display child with the results, so you can simply add
     the render texture to your scene and treat it like any other CCNode.
     There are also functions for saving the render texture to disk in PNG or JPG format.
     */
    class RenderTexture : public Node
    {
    protected:
        FBOTexture      m_grabber;
        fzMat4          m_renderTransform;
        Sprite          *p_sprite;
        
        fzTextureFormat m_format;
        
    public:
        // Constructor
        RenderTexture(const fzSize& size, fzTextureFormat format = kFZTextureFormat_RGBA8888);
        
        // Destructor
        ~RenderTexture();
        
        /** The Sprite being used.
         The sprite, by default, will use the following blending function: GL_ONE, GL_ONE_MINUS_SRC_ALPHA.
         The blending function can be changed in runtime by calling:
         - [[renderTexture sprite] setBlendFunc:(ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
         */
        void setSprite(Sprite*);
        Sprite* getSprite() const;
        

        //! starts grabbing
        void begin();
        
        
        /** starts rendering to the Texture2D while clearing the Texture2D first.
         This is more efficient then calling -clear first and then -begin */
        void beginWithClear(const fzColor4F& color);
        
        
        //! ends grabbing
        void end();
        
        
        //! clears the texture with a color
        void clear(const fzColor4F& color);
        
        //virtual void draw() override;
    };
}
#endif
