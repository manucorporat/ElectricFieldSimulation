// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTMXLAYER_H_INCLUDED__
#define __FZTMXLAYER_H_INCLUDED__
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

#include "FZSpriteBatch.h"
#include "FZTMXParser.h"

#include STL_MAP
#include STL_VECTOR

using namespace STD;



namespace FORZE {

    
    class Sprite;
    class TMXTiledMap;
    class TMXTilesetInfo;
    
    
    class TMXLayer : public Node
    {
        friend class TMXTiledMap;
        
    private:
        fzUInt			m_minGID;
        fzUInt			m_maxGID;
        
        void setupTiles();
        
        
    protected:
        // sprite batch used to render the tiles
        TMXTiledMap         *p_batch;
        
        // layer size in tiles
        fzSize				m_layerSize;
        
        // map size in tiles
        fzSize				m_mapTileSize;
        
        // tiles in raw format
        uint32_t			*p_tiles;
        
        // map orientation
        fzTMXOrientation    m_orientation;
        
        // properties
        void                *p_properties;
        

        // Only used when vertexZ is used
        fzInt   vertexZvalue_;
        bool    useAutomaticVertexZ_;
        float	alphaFuncValue_;
        
        void appendTileForGID(uint32_t GID, const fzPoint& position);
        
        // internal protocol
        virtual void insertChild(Node*) override;
        
    public:
        
        //! This constructor is used internally by TMXTilesMap at loading.
        TMXLayer(TMXTiledMap *mapInfo, TMXLayerInfo *layerInfo);
        ~TMXLayer();

        
        //! This method removes the raw data of the tiles.
        //! @see tileGIDAt()
        void releaseMap();
        
        
        //! Returns the sprite at the specified coordinate.
        //! @return NULL is no tile exists at the specified coordinate.
        Sprite* tileAt(const fzPoint& tileCoordinate);
        
        
        //! Retuns the sprite at the specified coordinate.
        uint32_t tileGIDAt(const fzPoint& tileCoordinate, bool flags = false) const;
        
        
        void setTileGID(uint32_t GID, const fzPoint& coord, bool flags = false);
        
        void removeTileAt(const fzPoint& tileCoordinate);
        
        fzPoint positionAt(const fzPoint& tileCoordinate) const;
        fzFloat vertexZAt(const fzPoint& pos) const;

        
        char* propertyNamed(const char* name) const;
        
        
        const TMXTilesetInfo *getTileset() const;

        
        const fzSize& getLayerSize() const {
            return m_layerSize;
        }
        
        const fzSize& getMapSize() const {
            return m_mapTileSize;
        }
        
        void visitTMXLayer(fzV4_T2_C4_Quad **quadp);

        fzPoint calculateLayerOffset(const fzPoint& pos) const;
        
        // Redefined
        virtual void render(unsigned char dirtyFlags) override;
    };
}
#endif
