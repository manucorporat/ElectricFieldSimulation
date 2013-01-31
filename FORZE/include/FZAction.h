// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZACTION_H_INCLUDED__
#define __FZACTION_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 Manuel Martinez-Almeida
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
 @author Manuel Martinez-Almeida
 */

#include "FZTypes.h"
#include "FZLifeCycle.h"

namespace FORZE {
        
    enum {
        //! Default tag
        kFZActionTagInvalid = -1
    };
    
    class Node;
    
    //! Base class for Action objects.
    class Action : public LifeCycle
    {
        friend class ActionManager;
        
    protected:
        void *p_target;
        fzInt m_tag;
        
        
        //! Called once per frame.
        //! @param time a value between 0 and 1.
        //! For example:
        //! - 0 means that the action just started
        //! - 0.5 means that the action is in the middle
        //! - 1 means that the action is over
        //! @warning this method never should be called manually.
        virtual void update(fzFloat time) {};
        
        // Constructor
        Action();
        
    public:
        
        //! Called before the action start. It will also set the target.
        virtual void startWithTarget(void* target);
        
        
        //! Called every frame with it's delta time. DON'T override unless you know what you are doing.
        virtual void step(fzFloat dt) = 0;
        
        
        //! Called after the action has finished. It will set the 'target' to NULL.
        virtual void stop();
        
        
        //! Finish the action
        virtual void finish();
        
        
        //! Returns true if the action has finished.
        virtual bool isDone() const;
        
        
        //! Returns the action's target.
        void* getTarget() const {
            return p_target;
        }
        
        
        //! Sets an tag value to identify the action.
        void setTag(fzInt tag) {
            m_tag = tag;
        }
        
        
        //! Returns an tag value to identify the action.
        fzInt getTag() const {
            return m_tag;
        }
        
        
        //! Returns a reversed action.
        virtual Action* reverse() const;
        
        
        //! Returns a copied action.
        virtual Action* copy() const;
    };
    
    
    /** Base class actions that do have a finite time duration.
     Possible actions:
     - An action with a duration of 0 seconds
     - An action with a duration of 35.5 seconds
     Infitite time actions are valid
     */
    class FiniteTimeAction : public Action
    {
    protected:
        fzFloat m_duration;
        FiniteTimeAction();
        
    public:
        
        //! Sets the duration in seconds of the action.
        virtual void setDuration(fzFloat);
        
        //! Returns the duration in seconds of the action.
        fzFloat getDuration() const {
            return m_duration;
        }
        
        //! Returns the time elapsed in seconds.
        virtual fzFloat getElapsed() const;
        
        virtual FiniteTimeAction* reverse() const override;
        virtual FiniteTimeAction* copy() const override;
    };
    
    
    /** Repeats an action for ever.
     To repeat the an action for a limited number of times use the Repeat action.
     @warning This action can't be Sequenceable because it is not an IntervalAction
     */
    class ActionInterval;
    class RepeatForever : public Action
    {
    protected:
        FiniteTimeAction *p_innerAction;
        
    public:
        //! Constructs a RepeatForever action from the specified inner action.
        RepeatForever(FiniteTimeAction *action);
        
        // Destructor
        ~RepeatForever();
        
        //! Sets the inner action.
        void setInnerAction(FiniteTimeAction*);
        
        
        //! Returns the inner action.
        FiniteTimeAction* getInnerAction() const {
            return p_innerAction;
        }
        
        
        // Redefined
        virtual void startWithTarget(void *t)override;
        virtual bool isDone() const override;
        virtual void step(fzFloat dt) override;
        virtual RepeatForever* reverse() const override;
        virtual RepeatForever* copy() const override;
    };
    
    
    /** Changes the speed of an action, making it take longer (speed>1)
     or less (speed<1) time.
     Useful to simulate 'slow motion' or 'fast forward' effect.
     @warning This action can't be Sequenceable because it is not an CCIntervalAction
     */
    class Speed : public Action
    {
    protected:
        Action *p_innerAction;
        fzFloat m_speed;
        
    public:
        //! Constructs a Speed action from the specified inner action.
        Speed(Action *action, fzFloat speed);
        ~Speed();
        
        //! Sets the inner action.
        void setInnerAction(Action*);
        
        //! Returns the inner action.
        Action* getInnerAction() const;
        
        /** alter the speed of the inner function in runtime */
        void setSpeed(fzFloat);
        fzFloat getSpeed() const;
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void stop() override;
        virtual void step(fzFloat dt) override;
        virtual bool isDone() const override;
        virtual Speed* reverse() const override;
        virtual Speed* copy() const override;
    };
    
    
    class Step : public Action
    {
    protected:
        Action *p_innerAction;
        fzFloat m_step;
        fzFloat m_elapsed;
        
    public:
        //! Constructs a Step action from the specified inner action and step interval.
        Step(Action *action, fzFloat step);
        ~Step();
        
        //! Sets the inner action.
        void setInnerAction(Action *a);
        
        
        //! Returns the inner action.
        Action* getInnerAction() const;
        
        
        //! Sets the step in seconds.
        void setStep(fzFloat);
        
        
        //! Returns the step in seconds.
        fzFloat getStep() const;
        
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void stop() override;
        virtual void step(fzFloat dt) override;
        virtual bool isDone() const override;
        virtual Step* reverse() const override;
        virtual Step* copy() const override;
    };
    
    
    /** Follow is an action that "follows" a node.
     Instead of using CCCamera as a "follower", use this action instead.
     */
    class Node;
    class Follow : public Action
    {
    protected:
        // node to follow
        Node	*followedNode_;
        
        // fast access to the screen dimensions
        fzPoint fullScreenSize_;
        fzPoint halfScreenSize_;
        
        // whether camera should be limited to certain area
        bool boundarySet_;
        
        // if screensize is bigger than the boundary - update not needed
        bool boundaryFullyCovered_;
        
        // world boundaries
        bool leftBoundary_;
        bool rightBoundary_;
        bool topBoundary_;
        bool bottomBoundary_;
        
    public:
        //! Constructs a Follow action.
        //! The rect will be the canvas size.
        Follow(Node *followed);
        
        //! Constructs a Follow action.
        Follow(Node *followed, const fzRect& rect);
        
        /** alter behavior - turn on/off boundary */
        void setBoundarySet(bool);
        bool getBoundarySet() const;
        
        // Redefined
        virtual void step(fzFloat delta) override;
        virtual bool isDone() const override;
    };
}
#endif

