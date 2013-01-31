// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZACTIONINTERVAL_H_INCLUDED__
#define __FZACTIONINTERVAL_H_INCLUDED__
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

#include "FZAction.h"
#include "FZSpriteFrame.h"
#include "FZMacros.h"


namespace FORZE {
    
    /** An interval action is an action that takes place within a certain period of time.
     It has an start time, and a finish time. The finish time is the parameter
     duration plus the start time.
     
     These ActionInterval actions have some interesting properties, like:
     - They can run normally (default)
     - They can run reversed with the reverse method
     - They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.
     
     For example, you can simulate a Ping Pong effect running the action normally and
     then running it again in Reverse mode.
     */
    class ActionInterval : public FiniteTimeAction
    {
    protected:
        fzFloat m_elapsed;
        bool m_firstTick;
        
        // Constructor
        ActionInterval(fzFloat duration);
        
    public:
                
        // Redefined
        virtual fzFloat getElapsed() const override;
        virtual bool isDone() const override;
        virtual void step(fzFloat dt) override;
        virtual void startWithTarget(void *t) override;
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    //! Runs actions sequentially, one after another.
    class Sequence : public ActionInterval
    {
    protected:
        FiniteTimeAction **p_actions;
        fzUInt m_currentAction;
        fzUInt m_numActions;
        bool m_startedAction;

        Sequence();
    public:
        //! Constructs a Sequence action.
        Sequence(FiniteTimeAction *action1, ...) NULL_TERMINATION;
        Sequence(FiniteTimeAction **actions, fzUInt nuActions);

        ~Sequence();
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void step(fzFloat dt) override;
        virtual bool isDone() const override;
        virtual void stop() override;
        virtual Sequence* reverse() const override;
        virtual Sequence* copy() const override;
    };
    
    
    //! Spawn a new action immediately.
    class Spawn : public ActionInterval
    {
    protected:
        FiniteTimeAction **p_actions;
        fzUInt m_numActions;
        
        Spawn();
    public:
        //! Constructs a Spawn action.
        Spawn(FiniteTimeAction *action1, ...);
        Spawn(FiniteTimeAction **actions, fzUInt nuActions);

        ~Spawn();
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual void stop() override;
        virtual Spawn* reverse() const override;
        virtual Spawn* copy() const override;
    };
    
    
    //! Repeats an action a number of times.
    //! To repeat an action forever use the RepeatForever action.
    class Repeat : public ActionInterval
    {
    protected:
        FiniteTimeAction *p_innerAction;
        fzUInt m_times;
        fzUInt m_total;
        
    public:
        //! Constructs a Repeat action.
        Repeat(FiniteTimeAction *action, fzUInt times);
        ~Repeat();
        
        //! Sets the inner action.
        void setInnerAction(FiniteTimeAction *action);
        
        
        //! Returns the inner action.
        FiniteTimeAction* getInnerAction() const;
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual void stop() override;
        virtual bool isDone() const override;
        virtual Repeat* reverse() const override;
        virtual Repeat* copy() const override;
    };
    
    
    class ReverseTime : public ActionInterval
    {
    protected:
        FiniteTimeAction *p_innerAction;
        
    public:
        //! Constructs a Repeat action.
        ReverseTime(FiniteTimeAction *action);
        ~ReverseTime();
        
        //! Sets the inner action.
        void setInnerAction(FiniteTimeAction *action);
        
        
        //! Returns the inner action.
        FiniteTimeAction* getInnerAction() const;
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual void stop() override;
        virtual ActionInterval* reverse() const override;
        virtual ReverseTime* copy() const override;
    };

    
    //! Rotates a Node object clockwise a number of degrees by modiying it's rotation attribute.
    class RotateBy : public ActionInterval
    {
    protected:
        fzFloat m_delta;
        fzFloat m_startAngle;
        
    public:
        //! Constructs a RotateBy action.
        RotateBy(fzFloat duration, fzFloat angle);
        
        // Redefined functions
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual RotateBy* reverse() const override;
        virtual RotateBy* copy() const override;
    };

    
    //! Rotates a Node object to a certain angle by modifying it's rotation attribute.
    //! The direction will be decided by the shortest angle.
    //! @warning This action doesn't support "reverse()".
    class RotateTo : public RotateBy
    {
    protected:
        fzFloat m_original;
        
    public:
        //! Constructs a RotateTo action.
        RotateTo(fzFloat duration, fzFloat angleDelta);
        
        // Redefined functions
        virtual void startWithTarget(void *t) override;
        virtual RotateTo* copy() const override;
        virtual RotateTo* reverse() const override;
    };
    

    //! Moves a Node object x,y pixels by modifying it's position attribute.
    //! x and y are relative to the position of the object.
    //! Duration is is seconds.
    class MoveBy : public ActionInterval
    {
    protected:
        fzPoint m_delta;
        fzPoint m_startPosition;
        
    public:
        //! Constructs a MoveBy action.
        MoveBy(fzFloat duration, const fzPoint& positionDelta);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual MoveBy* reverse() const override;
        virtual MoveBy* copy() const override;
    };

    //! Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
    //! @warning This action doesn't support "reverse()".
    class MoveTo : public MoveBy
    {
    protected:
        fzPoint m_original;
        
    public:
        //! Constructs a MoveTo action.
        MoveTo(fzFloat duration, const fzPoint& newPosition);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual MoveTo* copy() const override;
        virtual MoveTo* reverse() const override;
    };
    
    
    //! Skews a Node object to given angles by modifying it's skewX and skewY attributes.
    class SkewBy : public ActionInterval
    {
    protected:
        fzFloat m_deltaX;
        fzFloat m_deltaY;
        fzFloat m_startSkewX;
        fzFloat m_startSkewY;
        
    public:
        //! Constructs a SkewBy action.
        SkewBy(fzFloat duration, fzFloat skewX, fzFloat skewY);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual SkewBy* reverse() const override;
        virtual SkewBy* copy() const override;
    };
    
    
    //! Skews a Node object by skewX and skewY degrees.
    //! @warning This action doesn't support "reverse()".
    class SkewTo : public SkewBy
    {
    protected:
        fzFloat m_originalX;
        fzFloat m_originalY;
        
    public:
        //! Constructs a SkewTo action.
        SkewTo(fzFloat duration, fzFloat skewX, fzFloat skewY);
        
        // Redefined functions
        virtual void startWithTarget(void *t) override;
        virtual SkewTo* copy() const override;
        virtual SkewTo* reverse() const override;
    };

    
    //! Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
    class JumpBy : public ActionInterval
    {
    protected:
        fzPoint m_delta;
        fzFloat m_height;
        fzUInt  m_jumps;
        fzPoint m_startPosition;
        
    public:
        //! Constructs a JumpBy action.
        JumpBy(fzFloat duration, const fzPoint& position, fzFloat height, fzUInt jumps);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual JumpBy* reverse() const override;
        virtual JumpBy* copy() const override;
    };

    
    //! Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
    //! @warning This action doesn't support "reverse()".
    class JumpTo : public JumpBy
    {
    protected:
        fzPoint m_original;
        
    public:
        //! Constructs a JumpTo action.
        JumpTo(fzFloat duration, const fzPoint& position, fzFloat height, fzUInt jumps);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual JumpTo* copy() const override;
        virtual JumpTo* reverse() const override;
    };

    
    //! Bezier configuration structure
    struct fzBezierConfig {
        //! End position of the bezier
        fzPoint endPosition;
        //! Bezier control point 1
        fzPoint controlPoint_1;
        //! Bezier control point 2
        fzPoint controlPoint_2;
    };
    
    
    //! An action that moves the target with a cubic Bezier curve by a certain distance.
    class BezierBy : public ActionInterval
    {
    protected:
        fzBezierConfig m_config;
        fzPoint m_startPosition;
        
        fzFloat bezierat(fzFloat, fzFloat, fzFloat, fzFloat, fzFloat);
        
    public:
        //! Constructs a BezierBy action.
        BezierBy(fzFloat duration, const fzBezierConfig& config);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual BezierBy* reverse() const override;
        virtual BezierBy* copy() const override;
    };
    
    
    //! An action that moves the target with a cubic Bezier curve to a destination point.
    //! @warning This action doesn't support "reverse()".
    class BezierTo : public BezierBy
    {
    protected:
        fzBezierConfig m_original;
        
    public:
        //! Constructs a BezierTo action.
        BezierTo(fzFloat duration, const fzBezierConfig& config);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual BezierTo* copy() const override;
        virtual BezierTo* reverse() const override;
    };
    
    
    //! Scales a Node object a zoom factor by modifying it's scale attribute.
    class ScaleBy : public ActionInterval
    {
    protected:
        fzFloat m_originalX;
        fzFloat m_originalY;
        fzFloat m_deltaX;
        fzFloat m_deltaY;
        fzFloat m_startScaleX;
        fzFloat m_startScaleY;
        
    public:
        //! Constructs a ScaleBy action.
        ScaleBy(fzFloat duration, fzFloat scale);
        ScaleBy(fzFloat duration, fzFloat scaleX, fzFloat scaleY);
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual ScaleBy* reverse() const override;
        virtual ScaleBy* copy() const override;
    };
    
    
    //! Scales a Node object to a zoom factor by modifying it's scale attribute.
    //! @warning This action doesn't support "reverse()".
    class ScaleTo : public ScaleBy
    {
    public:
        //! Constructs a ScaleTo action.
        ScaleTo(fzFloat duration, fzFloat scale);
        ScaleTo(fzFloat duration, fzFloat scaleX, fzFloat scaleY);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual ScaleTo* copy() const override;
        virtual ScaleTo* reverse() const override;
    };
    
    
    //! Blinks a Node object by modifying it's visible attribute.
    class Blink : public ActionInterval
    {
    protected:
        fzUInt m_blinks;
        fzFloat m_percentVisible;
        bool m_initialState;
        
    public:
        //! Constructs a Blink action.
        Blink(fzFloat duration, fzUInt blinks, fzFloat percentVisible = 0.5f);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void stop() override;
        virtual void update(fzFloat dt) override;
        virtual Blink* reverse() const override;
        virtual Blink* copy() const override;
    };
    
    
    //! Fades an object that implements the Protocol::Color protocol. It modifies the opacity from the current value to a custom one.
    //! @warning This action doesn't support "reverse"
    class FadeTo : public ActionInterval
    {
    protected:
        fzFloat m_original;
        fzFloat m_startOpacity;
        fzFloat m_delta;
        
    public:
        //! Constructs a FadeTo action.
        FadeTo(fzFloat duration, fzFloat opacity);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual FadeTo* copy() const override;
        virtual FadeTo* reverse() const override;
    };
    
    
    class FadeOut;
    //! Fades In an object that implements the Protocol::Color protocol. It modifies the opacity from 0 to 255.
    //! The "reverse" of this action is FadeOut.
    class FadeIn : public ActionInterval
    {
    public:
        //! Constructs a FadeIn action.
        explicit FadeIn(fzFloat duration);
        
        // Redefined
        virtual void update(fzFloat dt) override;
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    //! Fades Out an object that implements the Protocol::Color protocol. It modifies the opacity from 255 to 0.
    //! The "reverse" of this action is FadeIn.
    class FadeOut : public ActionInterval
    {
    public:
        //! Constructs a FadeOut action.
        explicit FadeOut(fzFloat duration);
        
        // Redefined
        virtual void update(fzFloat dt) override;
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    

    
    //! Tints a Node that implements the Protocol::Color protocol from current tint to a custom one.
    //! @warning This action doesn't support "reverse()".
    class TintBy : public ActionInterval
    {
    protected:
        fzFloat m_deltaR;
        fzFloat m_deltaG;
        fzFloat m_deltaB;
        fzColor3B m_startColor;
        
    public:
        //! Constructs a TintBy action.
        TintBy(fzFloat duration, fzFloat redDelta, fzFloat greenDelta, fzFloat blueDelta);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual TintBy* reverse() const override;
        virtual TintBy* copy() const override;
    };
    
    
    //! Tints a Node that implements the Protocol::Color protocol from current tint to a custom one.
    class TintTo : public TintBy
    {
    protected:
        fzFloat m_originalR;
        fzFloat m_originalG;
        fzFloat m_originalB;

        
    public:
        //! Constructs a TintTo action.
        TintTo(fzFloat duration, fzFloat red, fzFloat green, fzFloat blue);
        TintTo(fzFloat duration, const fzColor3B& color);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual TintTo* copy() const override;
        virtual TintTo* reverse() const override;
    };

    
    //! Delays the action a certain amount of seconds.
    class DelayTime : public ActionInterval
    {
    public:
        //! Constructs a DelayTime action.
        explicit DelayTime(fzFloat duration);
        
        // Redefined
        virtual void update(fzFloat dt) override;
        virtual DelayTime* reverse() const override;
        virtual DelayTime* copy() const override;
    };
    
    
    class Animation;
    class Texture2D;
    class Animate : public ActionInterval
    {
    protected:
        Animation       *p_animation;
        fzInt			m_nextFrame;
        fzUInt			m_executedLoops;
        fzFloat         *p_splitTimes;
        fzSpriteFrame	m_origFrame;
        
    public:
        //! Constructs a Animate action.
        explicit Animate(Animation *animation);
        
        // Destructor
        ~Animate();
        
        //! Returns the Animation.
        Animation* getAnimation() const;
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void update(fzFloat dt) override;
        virtual void stop() override;
        virtual Animate* reverse() const override;
        virtual Animate* copy() const override;
    };
}
#endif
