// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZGRID_H_INCLUDED__
#define __FZGRID_H_INCLUDED__
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
#include "FZGrabber.h"


namespace FORZE {
    
    /** Base class for other */
    class Node;
    class Texture2D;
    class GLProgram;
    class GridBase
    {
    protected:
        GLint m_indicesVBO;
        bool		m_isActive;
        fzGridSize	m_gridSize;
        fzGridSize	m_gridSize_1;
        fzPoint		m_step;
        fzInt	    m_reuseGrid;
        Texture2D   *p_texture;
        
    public:
        // Constructors
        GridBase(const fzGridSize& size, Texture2D *texture, bool flipped = false);
        
        // Destructor
        virtual ~GridBase();

        /** wheter or not the grid is active */
        void setIsActive(bool);
        bool getIsActive() const;

        /** number of times that the grid will be reused */
        void setReuseGrid(fzInt);
        fzInt getReuseGrid() const;
        
        /** size of the grid */
        void setGridSize(const fzGridSize&);
        const fzGridSize& getGridSize() const;

        /** pixels between the grids */
        void setStep(const fzPoint&);
        const fzPoint& getStep() const;

        /** texture used */
        void setTexture(Texture2D*);
        Texture2D* getTexture() const;

        
        virtual void blit() = 0;
        virtual void reuse() = 0;
        virtual void calculateVertexPoints() = 0;
    };
    

    /**
     Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
     */
    class Grid3D : public GridBase
    {
    protected:
        fzVec2      *p_texCoords;
        fzVec3      *p_vertices;
        fzVec3      *p_originalVertices;
        
    public:
        ~Grid3D();
        
        /** returns the vertex at a given position */
        const fzVec3& getVertex(const fzGridSize& pos) const;
        
        /** returns the original (non-transformed) vertex at a given position */
        const fzVec3& getOriginalVertex(const fzGridSize& pos) const;

        /** sets a new vertex at a given position */
        void setVertex(const fzGridSize& pos, const fzVec3& newVertex);
        
        // Redefined functions
        virtual void calculateVertexPoints() override;
        virtual void blit() override;
        virtual void reuse() override;
    };
    
    
    /**
     CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
     the tiles can be separated from the grid.
     */
    class GridTiled3D : public GridBase
    {
    protected:
        fzQuad2F		*p_texCoords;
        fzQuad3F		*p_vertices;
        fzQuad3F		*p_originalVertices;
        
    public:
        virtual ~GridTiled3D();

        /** returns the tile at the given position */
        const fzQuad3F& getTile(const fzGridSize& pos) const;
        
        /** returns the original tile (untransformed) at the given position */
        const fzQuad3F& getOriginalTile(const fzGridSize& pos) const;

        /** sets a new tile */
        void setTile(const fzGridSize& pos, const fzQuad3F& newQuad);
        
        // Redefined functions
        virtual void calculateVertexPoints() override;
        virtual void blit() override;
        virtual void reuse() override;
    };
}
#endif
