// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTMXPARSER_H_INCLUDED__
#define __FZTMXPARSER_H_INCLUDED__
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
#include "FZConfig.h"
#include STL_STRING
#include STL_MAP
#include STL_VECTOR

using namespace STD;

// Bits on the far end of the 32-bit global tile ID (GID's) are used for tile flags
#define kFlippedHorizontallyFlag	0x80000000
#define kFlippedVerticallyFlag		0x40000000
#define kFlippedMask				~(kFlippedHorizontallyFlag|kFlippedVerticallyFlag)



namespace FORZE {
    
    //! Possible oritentations of the TMX map
    enum fzTMXOrientation
    {
        //! Orthogonal orientation
        kFZTMXOrientationOrtho,
        
        //! Isometric orientation
        kFZTMXOrientationIso,
        
        //! Hexagonal orientation
        kFZTMXOrientationHex,
    };
    
    struct TMXProperties
    {
        struct
        {
            string key;
            string value;
        } m_properties[4];
    };
    
#pragma mark - TMXLayerInfo
    
    struct TMXLayerInfo
    {
        friend class TMXMapInfo;
        
    protected:
        bool        m_visible;
        fzFloat     m_opacity;
        int32_t     m_nameHash;
        uint32_t    *p_tiles;
        fzPoint     m_offset;
        fzSize      m_size;        
       
        
    public:
        TMXLayerInfo()
        : m_visible(false)
        , m_opacity(1.0f)
        , m_offset(FZPointZero)
        , m_size(FZSizeZero)
        , m_nameHash(-1)
        , p_tiles(NULL)
        { }
        
        
        bool isVisible() const {
            return m_visible;
        }
        
        fzFloat getOpacity() const {
            return m_opacity;
        }
        
        int32_t getHashName() const {
            return m_nameHash;
        }
        
        const fzPoint& getOffset() const {
            return m_offset;
        }
        
        const fzSize& getSize() const {
            return m_size;
        }
        
        uint32_t* getTiles() const {
            return p_tiles;
        }
    };
    
    
#pragma mark - TMXTilesetInfo
    
    struct TMXTilesetInfo
    {
        friend class TMXMapInfo;
        
    protected:
        string  m_name;
        string  m_filename;
        fzUInt  m_firstGID;
        fzFloat m_spacing;
        fzFloat m_margin;
        fzSize  m_tileSize;
        
        
    public:
        fzSize  m_textureSize;

        TMXTilesetInfo()
        : m_firstGID(0)
        , m_spacing(0)
        , m_margin(0)
        , m_tileSize(FZSizeZero)
        , m_textureSize(FZSizeZero)
        , m_name()
        , m_filename()
        { }
        
        
        const string& getName() const {
            return m_name;
        }
        
        const string& getFilename() const {
            return m_filename;
        }
        
        fzFloat getFirstGID() const {
            return m_firstGID;
        }
        
        fzFloat getSpacing() const {
            return m_spacing;
        }
        
        fzFloat getMargin() const {
            return m_margin;
        }
        
        const fzSize& getTileSize() const {
            return m_tileSize;
        }
        
        const fzSize& getTexturesize() const {
            return m_textureSize;
        }
        
        fzRect rectForGID(uint32_t GID) const;
    };
    
    
#pragma mark - TMXObjectGroup
    
    struct TMXObjectGroup
    {
    public:
        char                *p_name;
        fzPoint             m_offset;
        vector<void*>       m_objects;
        map<int, string>    m_properties;
        
        
        TMXObjectGroup()
        : m_offset(FZPointZero)
        , m_objects()
        , m_properties()
        , p_name(NULL)
        { }
        
        ~TMXObjectGroup() {
            if(p_name)
                delete p_name;
        }
    };
    
    
#pragma mark - TMXMapInfo

    class TMXMapInfo
    {
    protected:
        bool parseLayer(void* outputData, TMXLayerInfo& info);
        bool parseTileset(void* outputData, TMXTilesetInfo& info);
        bool parseObjectGroup(void* outputData, TMXObjectGroup& info);
        bool parseProperties(void* outputData, TMXProperties& info);

        fzUInt m_factor;
        fzTMXOrientation m_orientation;
        fzSize m_mapSize;
        fzSize m_tileSize;
        TMXTilesetInfo m_tileset;
        
        
    public:
        vector<TMXLayerInfo> m_layers;
        vector<TMXObjectGroup> m_objectgroups;
        
        explicit TMXMapInfo();
        explicit TMXMapInfo(const char* filename);
        
        void parseTMXFile(const char*);
        void parseTMXData(char*);
        
        
        fzTMXOrientation getOrientation() const {
            return m_orientation;
        }
        
        
        const fzSize& getMapSize() const {
            return m_mapSize;
        }
        
        
        const fzSize& getTileSize() const {
            return m_tileSize;
        }
        
        
        TMXTilesetInfo& getTileset() {
            return m_tileset;
        }
    };
}
#endif
