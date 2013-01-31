// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZACTIONEASE_H_INCLUDED__
#define __FZACTIONEASE_H_INCLUDED__
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

#include "FZActionInterval.h"


namespace FORZE {
    
    //! Base class for Easing actions.
    class ActionEase : public ActionInterval
    {
    protected:
        ActionInterval *p_innerAction;
        
        ActionEase(ActionInterval *action);
        
    public:
        ~ActionEase();

        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual void stop() override;
        virtual void update(fzFloat) override;
    };

    
    //! Base class for Easing actions with rate parameters.
    class EaseRateAction : public ActionEase
    {
    protected:
        fzFloat m_rate;
        
        virtual void update(fzFloat) override;
        
    public:
        //! Constructs a EaseRateAction action.
        EaseRateAction(ActionInterval *action, fzFloat rate);
        
        //! Sets the rate.
        void setRate(fzFloat);
        
        //! Returns the rate.
        fzFloat getRate() const;
        
        //! Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    //! EaseIn action with a rate.
    class EaseIn : public EaseRateAction
    {
    public:
        EaseIn(ActionInterval *action, fzFloat rate)
        : EaseRateAction(action, rate) {}
    };
    
    
    //! EaseOut action with a rate.
    class EaseOut : public EaseRateAction
    {
    public:
        EaseOut(ActionInterval *action, fzFloat rate)
        : EaseRateAction(action, 1/rate) {}
    };
    
    
    //! EaseInOut action with a rate.
    class EaseInOut : public EaseRateAction
    {
        virtual void update(fzFloat) override;

    public:
        EaseInOut(ActionInterval *action, fzFloat rate)
        : EaseRateAction(action, rate) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    //! Ease Exponential In.
    class EaseExponentialIn : public ActionEase
    {
        virtual void update(fzFloat) override;

    public:
        EaseExponentialIn(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    //! Ease Exponential Out.
    class EaseExponentialOut : public ActionEase
    {
        virtual void update(fzFloat) override;

    public:
        EaseExponentialOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    

    //! Ease Exponential InOut.
    class EaseExponentialInOut : public ActionEase
    {
        virtual void update(fzFloat) override;

    public:
        EaseExponentialInOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    //! Ease Sine In.
    class EaseSineIn : public ActionEase
    {
        virtual void update(fzFloat) override;

    public:
        EaseSineIn(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    //! Ease Sine Out.
    class EaseSineOut : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseSineOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    //! Ease Sine InOut.
    class EaseSineInOut : public ActionEase
    {
        virtual void update(fzFloat) override;

    public:
        EaseSineInOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    //! Ease Elastic abstract class.
    class EaseElastic : public ActionEase
    {
    protected:
        fzFloat m_period;
        
        EaseElastic(ActionInterval *action, fzFloat period = 0.3f);
        
    public:
        //! Sets the period.
        void setPeriod(fzFloat);
        
        //! Returns the period.
        fzFloat getPeriod() const;
    };

    
    /** Ease Elastic In action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseElasticIn : public EaseElastic
    {
        virtual void update(fzFloat) override;

    public:
        EaseElasticIn(ActionInterval *action, fzFloat period)
        : EaseElastic(action, period) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };


    /** Ease Elastic Out action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseElasticOut : public EaseElastic
    {
        virtual void update(fzFloat) override;

    public:
        EaseElasticOut(ActionInterval *action, fzFloat period)
        : EaseElastic(action, period) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    /** Ease Elastic InOut action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseElasticInOut : public EaseElastic
    {
        virtual void update(fzFloat) override;

    public:
        EaseElasticInOut(ActionInterval *action, fzFloat period)
        : EaseElastic(action, period) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
        
    /** EaseBounceIn action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBounceIn : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBounceIn(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    /** EaseBounceOut action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBounceOut : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBounceOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    /** EaseBounceInOut action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBounceInOut : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBounceInOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
    
    
    /** EaseBackIn action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBackIn : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBackIn(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    /** EaseBackOut action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBackOut : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBackOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };

    
    /** EaseBackInOut action.
     @warning This action doesn't use a bijective fucntion. Actions like Sequence might have an unexpected result when used with this action.
     */
    class EaseBackInOut : public ActionEase
    {
        virtual void update(fzFloat) override;
        
    public:
        EaseBackInOut(ActionInterval *action)
        : ActionEase(action) {}
        
        // Redefined
        virtual ActionInterval* reverse() const override;
        virtual ActionInterval* copy() const override;
    };
}
#endif
