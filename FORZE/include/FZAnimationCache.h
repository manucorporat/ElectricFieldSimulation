// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZANIMATIONCACHE_H_INCLUDED__
#define __FZANIMATIONCACHE_H_INCLUDED__
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

#include "FZAnimation.h"
#include STL_MAP
#include STL_STRING


using namespace STD;

namespace FORZE {
    
    /** Singleton that manages the Animations.
     * It saves in a cache the animations. You should use this class if you want to save your animations in a cache.     
     */
    class AnimationCache
    {
    private:
        // Simplified types
        typedef pair<int32_t, Animation*> animationPair;
        typedef map<int32_t, Animation*> animationMap;
        
        // Director's instance
        static AnimationCache* p_instance;
        
        // map with all cached animations
        animationMap m_animations;
        
        
    protected:
        // Constructors
        AnimationCache();
        AnimationCache(const AnimationCache&);
        AnimationCache& operator = (const AnimationCache&);
        
        
    public:
        //! Get and allocates instance.
        static AnimationCache& Instance();
        
        
        //! Adds a Animation with a name.
        void addAnimation(Animation *animation, const char* name);
        
        
        //! Deletes a Animation from the cache.
        void removeAnimationByName(const char* name);
        
        
        //! Returns a Animation that was previously added.
        //! You should retain the returned copy if you are going to use it.
        //! @return NULL if the name is not found.
        Animation* getAnimationByName(const char* name) const;
    };
}
#endif
