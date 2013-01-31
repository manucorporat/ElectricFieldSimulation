// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSPRITEBATCH_H_INCLUDED__
#define __FZSPRITEBATCH_H_INCLUDED__
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
#include "FZProtocols.h"
#include "FZTextureAtlas.h"
#include STL_STRING


using namespace STD;

namespace FORZE {

    /** SpriteBatch is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
     * (often known as "batch draw").
     *
     * A SpriteBatch can reference one and only one Texture2D (one image file, one texture atlas).
     * Only the Sprites that are contained in that Texture2D can be added to the SpriteBatch.
     * All Sprite added to a SpriteBatch are drawn in one OpenGL ES draw call.
     * If the Sprite are not added to a SpriteBatch then an OpenGL ES draw call will be needed for each one, which is less efficient.
     *
     *
     * Limitations:
     *  - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is Cprite or any subclass of Sprite. eg: particles, labels and layer can't be added to a SpriteBatchN.
     *  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
     * 
     */
    class Sprite;
    class SpriteBatch : public Node, public Protocol::Texture, public Protocol::Blending
    {
        friend class Sprite;        
        
    protected:
        TextureAtlas m_textureAtlas;
        fzBlendFunc m_blendFunc;
        
        virtual void insertChild(Node*) override;
        
    public:
        //! Constructs a SpriteBatch with a Texture2D and an initial capacity.
        explicit SpriteBatch(Texture2D *texture, fzUInt capacity = 0);

        
        //! Constructs a SpriteBatch with am image filename(.png, .pvr..) and an initial capacity.
        explicit SpriteBatch(const string& filename, fzUInt capacity = 0);
        
        
        //! Returns the TextureAtlas used by.
        TextureAtlas* getTextureAtlas() {
            return &m_textureAtlas;
        }
        
        
        //! Returns the current capacity of the SpriteBatch.
        //! The capacity is resized dynamically.
        fzUInt getCapacity() const {
            return m_textureAtlas.getCapacity();
        }

        
        // Redefined functions
        virtual void setBlendFunc(const fzBlendFunc& blend) override;
        virtual const fzBlendFunc& getBlendFunc() const override;
        virtual void setTexture(Texture2D*) override;
        virtual Texture2D* getTexture() const override;
        virtual void render(unsigned char) override;
        virtual void draw() override;
    };
}
#endif
