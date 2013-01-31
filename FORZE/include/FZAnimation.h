// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZANIMATION_H_INCLUDED__
#define __FZANIMATION_H_INCLUDED__
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
#include "FZLifeCycle.h"
#include STL_VECTOR

using namespace STD;

namespace FORZE {
    
    struct fzAnimationFrame {
    public:
        fzSpriteFrame frame;
        fzFloat delay;
        void *userInfo;
        
        fzAnimationFrame(const fzSpriteFrame& spriteFrame, fzFloat delayUnits, void *userinfo = NULL)
        : frame(spriteFrame), delay(delayUnits), userInfo(userinfo) { }
    };
    
    /** A Animation object is used to perform animations on the Sprite objects.
     * The Animation object contains fzSpriteFrame objects, and a possible delay between the frames.
     * You can animate a Animation object by using the Animate action. Example:
     */
    class Texture2D;
    class SpriteFrame;
    class Animation : public LifeCycle
    {        
    protected:
        vector<fzAnimationFrame> m_frames;
        fzFloat m_totalDelayUnits;
        fzFloat m_delayPerUnit;
        fzUInt  m_loops;
        bool	m_restoreOriginalFrame;

        
    public:
        //! Constructs an animation with frames and a delay between frames.
        Animation(const vector<fzAnimationFrame>& frames, fzFloat delayPerUnit, fzUInt loops);
        
        
        Animation(const vector<fzSpriteFrame>& frames, fzFloat delay);

        
        //! Sets delay
        void setDelay(fzFloat);
        fzFloat getDelay() const;
        
        fzFloat getTotalDelayUnit() const;
        fzUInt getLoops() const;
        fzFloat getDuration() const;
        bool restoreOriginalFrame() const;
        
        /** std vector with all frames */
        const vector<fzAnimationFrame>& getFrames() const;
        
        
        //! Adds a frame.
        void addFrame(const fzSpriteFrame&);
        
        
        //! Adds a frame.
        void addFrame(const fzAnimationFrame&);
        
        
        /** Adds a frame with an image filename. Internally it will create a fzSpriteFrame and it will add it */
        void addFrameWithFilename(const char* filename);

        
        /** Adds a frame with a Texture2D and a rect. Internally it will create a fzSpriteFrame and it will add it.
         Added to facilitate the migration from v0.8 to v0.9.
         */
        void addFrameWithTexture(Texture2D *texture, const fzRect& rect);
    };
}
#endif
