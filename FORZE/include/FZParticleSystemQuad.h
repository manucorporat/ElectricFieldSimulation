// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZPARTICLESYSTEMQUAD_H_INCLUDED__
#define __FZPARTICLESYSTEMQUAD_H_INCLUDED__
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

#include "FZParticleSystem.h"
#include "FZConfig.h"
#include "FZSpriteFrame.h"
#include "FZTextureAtlas.h"


namespace FORZE {
    
    /** ParticleSystemQuad is a subclass of CCParticleSystem
     It includes all the features of ParticleSystem.
     */
    class ParticleSystemQuad : public Node, public Protocol::Texture, public Protocol::Blending
    {
    protected:
        TextureAtlas m_textureAtlas;
        ParticleSystemLogic *p_logic;
        fzBlendFunc m_blendFunc;
        

        void initTexCoordsWithRect(fzRect rect);
        void update(fzFloat);
        
    public:
        ParticleSystemQuad(ParticleSystemLogic *logic);
        ParticleSystemQuad(ParticleSystemLogic *logic, Texture2D *texture);
        
        ~ParticleSystemQuad();
        
        ParticleSystemLogic *getLogic() const
        {
            return p_logic;
        }
        
        //! Sets a new fzSpriteFrame as particle.
        //! @warning this method is experimental. Use setTexture:withRect instead.
        void setDisplayFrame(const fzSpriteFrame& s);
        
        
        //! Sets a new Texture2D with a rect. The rect is in Points.
        void setTexture(Texture2D *texture, const fzRect& rect);
        
        
        // Redefined
        virtual void setTexture(Texture2D *texture) override;
        virtual Texture2D* getTexture() const override;
        virtual void setBlendFunc(const fzBlendFunc& b) override;
        virtual const fzBlendFunc& getBlendFunc() const override;
        virtual void draw() override;
    };
}
#endif
