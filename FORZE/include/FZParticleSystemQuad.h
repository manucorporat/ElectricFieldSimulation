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


namespace FORZE {
    
    /** ParticleSystemQuad is a subclass of CCParticleSystem
     It includes all the features of ParticleSystem.
     */
    class ParticleSystemQuad : public ParticleSystem
    {
    protected:
        fzC4_T2_V2_Quad     *p_quads;
        
        GLuint              m_indicesVBO;
#if FZ_VBO_STREAMING
        GLuint				m_quadsVBO;
#endif
        
        // Redefined functions
        virtual void updateQuadWithParticle(const fzParticle& particle) override;
        void postStep();
        
    public:
        ParticleSystemQuad(fzUInt numberOfParticles, Texture2D *texture);
        
        ~ParticleSystemQuad();
        
        /** initialices the indices for the vertices */
        void initIndices();
        
        /** initilizes the Texture2D with a rectangle measured Points */
        void initTexCoordsWithRect(fzRect rect);
        
        /** Sets a new fzSpriteFrame as particle.
         WARNING: this method is experimental. Use setTexture:withRect instead.
         */
        void setDisplayFrame(const fzSpriteFrame& s);
        
        /** Sets a new Texture2D with a rect. The rect is in Points */
        void setTexture(Texture2D *texture, const fzRect& rect);
        void setTexture(Texture2D *texture);
        
        
        void draw();
    };
}
#endif
