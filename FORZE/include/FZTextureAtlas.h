// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTEXTUREATLAS_H_INCLUDED__
#define __FZTEXTUREATLAS_H_INCLUDED__
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
#include "FZProtocols.h"


namespace FORZE {
    
    class Texture2D;
    /** A class that implements a Texture Atlas.
     Supported features:
     * Quads can be udpated in runtime
     * Quads can be added in runtime
     * Quads can be removed in runtime
     * Quads can be re-ordered in runtime
     * Capacity can be resized in runtime
     * OpenGL component: V3F, C4B, T2F.
     The quads are rendered using an OpenGL ES VBO.
     To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file 
     */
    class TextureAtlas : public Protocol::Texture
    {
    private:
        unsigned int        m_VAO;
        unsigned int        m_indicesVBO;
        fzUInt              m_capacity;
        fzUInt              m_count;
        fzV4_T2_C4_Quad     *p_quads;
        Texture2D           *p_texture;

        
#if FZ_VBO_STREAMING
        GLuint              m_quadsVBO;
        fzV4_T2_C4_Quad     *m_dirtyMin;
        fzV4_T2_C4_Quad     *m_dirtyMax;
#endif // FZ_USES_VBO
        
        void generateIndices();
        void initVAO();
        
        
    public:
        //! Constructs a TextureAtlas with a Texture2D object, and with an certain capacity for Quads.
        //! The capacity is increased in runtime.
        TextureAtlas(Texture2D *texture, fzUInt capacity = 24);
        
        // Destructor
        virtual ~TextureAtlas();
        
        
        //! Returns the number of quads that can be stored with the current texture atlas size.
        fzUInt getCapacity() const {
            return m_capacity;
        }
        
        
        //! Returns the number of quads that are going to be drawn.
        fzUInt getCount() const {
            return m_count;
        }
        
        
        //! Sets the last quad point to be drawn.
        void setLastQuad(fzV4_T2_C4_Quad *quad);
        
                
        //! Returns the quads that are going to be rendered.
        fzV4_T2_C4_Quad* getQuads() const {
            return p_quads;
        }

        
        //! Removes all Quads.
        //! The TextureAtlas capacity remains untouched. No memory is freed.
        void removeAllQuads() {
            m_count = 0;
        }
        
        
        //! Resizes the capacity of the TextureAtlas.
        //! The new capacity can be lower or higher than the current one.
        //! @return YES if the resize was successful.
        bool resizeCapacity(fzUInt newCapacity);
        
        
        //! This method is similar to resizeCapacity(),
        //! but in this case the new capacity can not be lower.
        void reserveCapacity(fzUInt necesaryCapacity);
        
        
        //! Draws all quads.
        //! @warning you have to make the GLProgram used before.
        void drawQuads();
        
        
        void updateQuad(fzV4_T2_C4_Quad *quad) {
#if FZ_VBO_STREAMING
            if(m_dirtyMin > quad) m_dirtyMin = quad;
            if(m_dirtyMax < (++quad)) m_dirtyMax = quad;
#endif
        }
        
        
        // Redefined
        virtual void setTexture(Texture2D*) override;
        virtual Texture2D* getTexture() const;
    };
}
#endif
