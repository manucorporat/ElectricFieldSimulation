// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZFONTMANAGER_H_INCLUDED__
#define __FZFONTMANAGER_H_INCLUDED__
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
#include "FZSelectors.h"
#if FZ_STL_CPLUSPLUS11
#include STL_UNORDERED_MAP
#else
#include STL_MAP
#endif

using namespace STD;

namespace FORZE {
    
    class Font;
    
    /** Singleton that handles the loading of textures
     * Once the Texture2D is loaded, the next time it will return
     * a reference of the previously loaded Texture2D reducing GPU & CPU memory
     */
    class FontCache : public SELProtocol
    {
    private:
        // Simplified typedefs
#if FZ_STL_CPLUSPLUS11
        typedef unordered_map<int32_t, Font*> fontsMap;
#else
        typedef map<int32_t, Font*> fontsMap;
#endif
        typedef pair<int32_t, Font*> fontsPair;
        
        // Director's instance
        static FontCache* p_instance;
        fontsMap m_fonts;
        
        Font* getFontForHash(int32_t hash) const;
        
        
    protected:
        // Constructors
        FontCache();
        FontCache(const FontCache& ) = delete;
        FontCache &operator = (const FontCache& ) ;

        
    public:
        //! Gets and allocates the singleton.
        static FontCache& Instance();
        
        
        //! Returns and loads if needed a Font instance giving the filename.
        Font* addFont(const char* filename, fzFloat lineHeight);
        
        
        //! Removes a Font from the cache given the font instance.
        void removeFont(Font *font);
        
        
        //! Removes a Font from the cache given a its key name.
        //! @param filename is a NULL terminated char string.
        void removeFontByName(const char* filename);
        
        Font* getFontByName(const char* filename) const;

        
        //! Removes unused Fonts.
        //! This method will be called if the system througs a memory warning.
        void removeUnusedFonts();
        
        
        //! Removes all the fonts stored in the cache.
        void removeAllFonts();
        
        
        const fontsMap& getFonts() const {
            return m_fonts;
        }
    };
}
#endif
