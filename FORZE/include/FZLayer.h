// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZLAYER_H_INCLUDED__
#define __FZLAYER_H_INCLUDED__
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

#include "FZNode.h"
#include "FZProtocols.h"
#include "FZEventManager.h"


namespace FORZE {
    
#pragma mark - Layer
    /** Layer is a subclass of Node that implements the EventDelegate protocol.
     */
    class Layer : public Node, public EventDelegate
    {
    private:
        uint16_t m_trackedEvents;
        fzInt m_priority;
        
        
    protected:
        virtual void registerWithEventDispatcher();

        
    public:
        //! Constructs a blank layer
        explicit Layer();
        
        
        //! Sets the event kinds that you want to track (touches, keyboard, accelerometer etc.)
        //! @see fzEventType
        //! @see EventDelegate
        uint16_t setTrackedEvents(uint16_t flags);
        
        
        //! Returns flags with the tracked events.
        uint16_t getTrackedEvents() const;
        
        void setPriority(fzInt priority);
        fzInt getPriority() const;
        
        // Redefined functions
        virtual void onEnter() override;
        virtual void onExit() override;
    };
    
    
#pragma mark - LayerColor
    /** LayerColor is a subclass of Layer that implements the Protocol::Color protocol.
     
     All features from Layer are valid, plus the following new features:
     - opacity
     - RGB colors
     */
    class LayerColor : public Layer, public Protocol::Color, public Protocol::Blending
    {
    protected:
        float         p_squareVertices[16];
        fzColor4B     p_squareColors[4];
        
        GLubyte       m_alpha;
        fzColor3B     m_color;	        
        fzBlendFunc   m_blendFunc;
            
    public:
        //! Constructs a layer with color and a size.
        LayerColor(const fzColor4B& color, const fzSize& size);
        
        
        //! Constructs a full-screen layer with color.
        LayerColor(const fzColor4B& color);
        
        
        //! Sets the alpha channel. No recursive opacity.
        void setAlpha(GLubyte alpha) {
            m_alpha = alpha;
            makeDirty(kFZDirty_color);
        }
        
        
        //! Returns the alpha channel.
        GLubyte getAlpha() const {
            return m_alpha;
        }
        
        
        // Redefined
        virtual void setBlendFunc(const fzBlendFunc& blend) override;
        virtual const fzBlendFunc& getBlendFunc() const override;
        virtual void setColor(const fzColor3B& color) override;
        virtual const fzColor3B& getColor() const override;
        virtual void updateStuff() override;
        virtual void draw() override;
    };
    
    
#pragma mark - LayerGradient
    
    /** LayerGradient is a subclass of LayerColor that draws gradients across
     the background.
     
     All features from LayerColor are valid, plus the following new features:
     - direction
     - final color
     - interpolation mode
     
     Color is interpolated between the startColor and endColor along the given
     vector (starting at the origin, ending at the terminus).  If no vector is
     supplied, it defaults to (0, -1) -- a fade from top to bottom.
     
     If 'compressedInterpolation' is disabled, you will not see either the start or end color for
     non-cardinal vectors; a smooth gradient implying both end points will be still
     be drawn, however.
     
     If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
     
     */
    class LayerGradient : public LayerColor
    {
    protected:
        fzColor3B   m_endColor;
        fzPoint     m_vector;
        GLubyte     m_startAlpha;
        GLubyte     m_endAlpha;
        bool        m_compressedInterpolation;
        
        
    public:
        //! Constructs a full-screen layer with a gradient between start and end in the direction of v
        LayerGradient(const fzColor4B& start, const fzColor4B& end, const fzSize& size);
        
        LayerGradient(const fzColor4B& start, const fzColor4B& end);
        
        
        //! Sets the gradient's start color
        void setStartColor(const fzColor3B&);
        
        
        //! Returns the gradient's start color
        const fzColor3B& getStartColor() const;

        
        //! Sets the gradient's end color
        void setEndColor(const fzColor3B&);
        
        
        //! Returns the gradient's end color
        const fzColor3B& getEndColor() const;
        
        
        //! Sets the gradient's start alpha
        void setStartAlpha(GLubyte);
        
        
        //! Returns the gradient's start alpha
        GLubyte getStartAlpha() const;
        
        
        //! Sets the gradient's end alpha
        void setEndAlpha(GLubyte);
        
        
        //! Returns the gradient's end alpha
        GLubyte getEndAlpha() const;
        
        
        //! Sets the vector along which to fade color.
        void setVector(const fzPoint&);
        
        
        //! Returns the vector along which to fade color.
        const fzPoint& getVector() const;
        
        
        /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
         Default: YES
         */
        void setCompressedInterpolation(bool);
        bool getCompressedInterpolation() const;
        
        
        // Redefined functions
        virtual void updateStuff() override;
    };
}

#pragma mark - LayerMultiplex
#endif
