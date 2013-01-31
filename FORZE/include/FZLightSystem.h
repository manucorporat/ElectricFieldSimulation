// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZLIGHTSYSTEM_H_INCLUDED__
#define __FZLIGHTSYSTEM_H_INCLUDED__
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

#include "FZSprite.h"
#include "FZLayer.h"
#include "FZGrabber.h"


using namespace STD;

namespace FORZE {
    
    class LightSystem;
    class Light : public Sprite
    {
        friend class LightSystem;
        
    protected:
        fzBlendFunc m_shadowBlend;
        fzColor3B m_shadowColor;
                
    public:
        //! Default constructor.
        explicit Light();
        
        
        //! Sets the shadow color. fzBLACK is default.
        void setShadowColor(const fzColor3B& color) {
            m_shadowColor = color;
        }
        
        //! Returns the shadow color.
        const fzColor3B& getShadowColor() const {
            return m_shadowColor;
        }
        
        
        void setShadowBlendFunc(const fzBlendFunc& blend) {
            m_shadowBlend = blend;
        }
        const fzBlendFunc& getShadowBlendFunc() const {
            return m_shadowBlend;
        }
    };
    
    
    class LightSystem : public Layer, public Protocol::Texture
    {
    protected:
        Texture2D *p_texture;
        FBOTexture m_grabber;
        Node *p_batch;
        _fzT2_V2_Quad m_quad;
        
        void drawTexture();
        virtual void insertChild(Node* node) override;
        
    public:
        //! Constructs a LightSystem given the texture for the light and a node of sprites.
        LightSystem(Texture2D *lightTexture, Node *batch);
        
        
        //! Constructs a LightSystem given the light filename and a node of sprites.
        LightSystem(const string& filename, Node *batch);
        
        // Destructor
        ~LightSystem();

        
        //! Sets the batch used by.
        void setBatch(Node *batch);
        
        
        // Redefined
        virtual void setTexture(Texture2D*) override;
        virtual Texture2D *getTexture() const override;
        virtual void render(unsigned char) override;
        virtual void updateStuff() override;
    };
}

#endif
