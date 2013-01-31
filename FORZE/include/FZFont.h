// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZFONT_H_INCLUDED__
#define __FZFONT_H_INCLUDED__
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

#include <ctime>
#include "FZTypes.h"
#include "FZConfig.h"
#include "FZLifeCycle.h"


#include STL_MAP

using namespace STD;

namespace FORZE {

    struct fzCharDef
    {
        fzFloat x, y;
        fzFloat width, height;
        fzFloat xOffset, yOffset;
        fzFloat xAdvance;
        
        fzCharDef() : x(0), y(0), width(0), height(0), xOffset(0), yOffset(0), xAdvance(0)
        { }
        
        fzRect getRect() const {
            return fzRect(x, y, width, height);
        }
    };
    
    class Texture2D;
    class Font : public LifeCycle
    {
    protected:
        fzUInt m_factor;
        Texture2D *p_texture;
        fzFloat m_lineHeight;
        fzCharDef m_chars[256];
        map<uint16_t, fzFloat> m_kerning;
        
        
        void loadFNTFile(const char*);
        void loadFNTData(char*);
        void loadTTFFile(const char*, fzFloat);
        void loadTTFData(char*, fzFloat);
        
    public:
        //! Constructs a Font giving the Font's filename and an optional lineHeight param.
        Font(const char* filename, fzFloat lineHeight);
        ~Font();
        
        
        //! Returns the font's line height.
        fzFloat getLineHeight() const {
            return m_lineHeight;
        }
        
        
        //! Returns the font's atlas texture.
        Texture2D *getTexture() const {
            return p_texture;
        }
        
        
        //! Returns char description.
        const fzCharDef& getCharInfo(unsigned char charId) const {
            return m_chars[charId];
        }
        
        
        //! Returns kerning space betwen two characters.
        fzFloat getKerning(unsigned char first, unsigned char second) const;
        
        void log() const;
    };

}
#endif
