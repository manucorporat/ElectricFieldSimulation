// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSPRITEFRAME_H_INCLUDED__
#define __FZSPRITEFRAME_H_INCLUDED__
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

#include "FZProtocols.h"

namespace FORZE {
    
    /** A SpriteFrame has:
     - texture: A Texture2D that will be used by the Sprite
     - rectangle: A rectangle of the texture
     
     You can modify the frame of a Sprite by doing:
     fzSpriteFrame frame(texture, rect, offset);
     sprite->setDisplayFrame(frame);
     */
    class fzSpriteFrame : public Protocol::Texture
    {
    protected:
        Texture2D		*p_texture;
       	fzRect			m_rect;
        fzPoint			m_offset;
        fzSize			m_originalSize;
        bool			m_isRotated;
        
    public:
        //! Default constructor.
        fzSpriteFrame();
        
        
        //! Constructs a fzSpriteFrame with a texture, rect, offset, originalSize and rotated.
        fzSpriteFrame(Texture2D *texture, const fzRect& rect, const fzPoint& offset, const fzSize& originalSize,  bool rotated);
        
        
        //! Constructs a fzSpriteFrame with a texture, rect, offset, originalSize and rotated.
        fzSpriteFrame(Texture2D *texture, const fzRect& rect, const fzPoint& offset);
        
        
        //! Constructs a fzSpriteFrame with a Texture2D and a rect.
        fzSpriteFrame(Texture2D *texture, const fzRect& rect);
        
        
        //! Copying constructor.
        fzSpriteFrame(const fzSpriteFrame&);

        
        // Destructor
        ~fzSpriteFrame();
        
        
        //! Sets the rect of the frame in points.
        //! @see getRect()
        void setRect(const fzRect&);
        
        
        //! Returns the rect of the frame in points.
        //! @see setRect()
        const fzRect& getRect() const;
        

        //! Sets if the frame is rotated.
        //! This value is used by a lot of sprite packing programs like zwoptex.
        //! @see isRotated()
        void setIsRotated(bool);
        
        
        //! Returns yes if the frame is rotated.
        //! @see setIsRotated()
        bool isRotated() const;
        
        
        //! Sets the offset of the frame in points.
        //! @see getOffset()
        void setOffset(const fzPoint&);
        
        
        //! Returns the offset of the frame in points.
        //! @see setOffset()
        const fzPoint& getOffset() const;
        
        
        //! Sets the original size of the frame in points.
        //! Some atlas creator tools can trim the frame rect in order to improve the rendering performance.
        //! In this case we need to get the original size in order to render it properly positioned.
        //! @see getOriginalSize()
        void setOriginalSize(const fzSize&);
        
        
        //! Returns the original size of the frame in points.
        //! @see setOriginalSize()
        const fzSize& getOriginalSize() const;
        
        
        //! Used internally to check if the frame is valid to be applied.
        bool isValid() const {
            return p_texture != NULL;
        }
        
        
        void log() const;

        
        // Operators
        bool operator == (const fzSpriteFrame&) const;
        bool operator != (const fzSpriteFrame&) const;
        
        
        // Redefined
        virtual void setTexture(Texture2D*) override;
        virtual Texture2D* getTexture() const override;
    };
}
#endif
