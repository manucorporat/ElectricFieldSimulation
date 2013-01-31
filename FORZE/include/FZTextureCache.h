// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTEXTURECACHE_H_INCLUDED__
#define __FZTEXTURECACHE_H_INCLUDED__
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

#include "FZConfig.h"
#include "FZSelectors.h"
#if FZ_STL_CPLUSPLUS11
#include STL_UNORDERED_MAP
#else
#include STL_MAP
#endif


using namespace STD;

namespace FORZE {
    
    class Texture2D;
    
    //! Singleton that handles the loading of textures.
    //! Once the texture is loaded, the next time it will return
    //! a reference of the previously loaded texture reducing GPU & CPU memory
    class TextureCache : public SELProtocol
    {
    private:
        // Simplified typedefs
#if FZ_STL_CPLUSPLUS11
        typedef unordered_map<int32_t, Texture2D*> texturesMap;
#else
        typedef map<int32_t, Texture2D*> texturesMap;
#endif
        typedef pair<int32_t, Texture2D*> texturesPair;
        
        
        // singleton instance
        static TextureCache* p_instance;
        texturesMap m_textures;
        
        Texture2D* getTextureByHash(int32_t hash) const;
        
    protected:
        // Constructors
        TextureCache();
        TextureCache(const TextureCache& ) = delete;
        TextureCache &operator = (const TextureCache& ) ;
        
        
    public:
        //! Gets and allocates the singleton.
        static TextureCache& Instance();
        
        
        //! Returns a Texture2D object given an file image.
        //! If the file image was not previously loaded, it will create a new Texture2D.
        //! object and it will return it. It will use the filename as a key.
        //! Otherwise it will return a reference of a previosly loaded image.
        //! Supported image extensions: .png, .pvr, .pvr.ccz
        Texture2D* addImage(const char* filename);
        
        
        //! Deletes a Texture2D from the cache given the Texture2D pointer.
        void removeTexture(Texture2D *texture);
        
        
        //! Deletes a Texture2D from the cache given a its key name.
        //! @param key is a NULL terminated char string.
        void removeTextureByName(const char* key);
        
        
        Texture2D* getTextureByName(const char* key) const;
        
        
        //! Removes unused textures.
        //! This method will be called if the system througs a memory warning.
        void removeUnusedTextures();
        
        
        //! Removes all the textures stored in the cache.
        void removeAllTextures();
        
        
        const texturesMap& getTextures() const {
            return m_textures;
        }
    };
}
#endif
