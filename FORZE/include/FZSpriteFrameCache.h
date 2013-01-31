// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSPRITEFRAMECACHE_H_INCLUDED__
#define __FZSPRITEFRAMECACHE_H_INCLUDED__
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

#include "FZSpriteFrame.h"

#if FZ_STL_CPLUSPLUS11
#include STL_UNORDERED_MAP
#else
#include STL_MAP
#endif


using namespace STD;

namespace FORZE {
    
    class Texture2D;
    class Sprite;
    class SpriteFrameCache
    {
    private:
        // Simplified types
#if FZ_STL_CPLUSPLUS11
        typedef unordered_map<int32_t, fzSpriteFrame> framesMap;
#else
        typedef map<int32_t, fzSpriteFrame> framesMap;
#endif
        typedef pair<int32_t, fzSpriteFrame> framesPair;


        /* Cache's instance */
        static SpriteFrameCache* p_instance;
        framesMap m_frames;
        
        fzSpriteFrame getSpriteFrameByHash(int32_t hash) const;
        
    protected:
        SpriteFrameCache();
        SpriteFrameCache(const SpriteFrameCache& ) ;
        SpriteFrameCache &operator = (const SpriteFrameCache& );
        
        
    public:
        //! Gets and allocates the singleton.
        static SpriteFrameCache& Instance();
        
        
        //! Adds multiple Sprite Frames from a plist file.
        //! The Texture2D will be associated with the created sprite frames.
        void addSpriteFrames(const char* xmlFilename, Texture2D *texture = NULL);
        
        
        //! Adds multiple Sprite Frames from a plist file.
        //! The Texture2D will be associated with the created sprite frames.
        void addSpriteFramesWithImage(const char* xmlFileName, const char* textureFilename);

        
        //! Adds an sprite frame with a given name.
        //! If the name already exists, then the old content will be replaced with the new one.
        void addSpriteFrame(const fzSpriteFrame& frame, const char* frameName);
        
        
        //! Removes all the stored sprite frames.
        void removeAllSpriteFrames();
        
        
        //! Deletes an sprite frame from the sprite frame cache.
        void removeSpriteFrameByName(const char* name);
        
        
        /** Removes multiple Sprite Frames from a plist file.
         * Sprite Frames stored in this file will be removed.
         * It is convinient to call this method when a specific texture needs to be removed.
         */
        void removeSpriteFramesFromFile(const char* plist);
        
        
        /** Removes all Sprite Frames associated with the specified textures.
         * It is convinient to call this method when a specific texture needs to be removed.
         */
        void removeSpriteFramesFromTexture(Texture2D *texture);
        
        
        /** Returns an Sprite Frame that was previously added.
         If the name is not found it will return nil.
         You should retain the returned copy if you are going to use it.
         */
        fzSpriteFrame getSpriteFrameByKey(const char* key) const;
        
        
        const framesMap& getFrames() const {
            return m_frames;
        }
    };
}
#endif
