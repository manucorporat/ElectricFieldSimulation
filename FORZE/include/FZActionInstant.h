// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZACTIONINSTANT_H_INCLUDED__
#define __FZACTIONINSTANT_H_INCLUDED__
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
#include "FZSelectors.h"


namespace FORZE {
    
    //! Instant actions are immediate actions.
    //! They don't have a duration like the ActionInterval actions.
    class ActionInstant : public FiniteTimeAction
    {
    protected:
        // Constructor
        ActionInstant();

    public:
        
        // Redefined
        virtual bool isDone() const override;
        virtual void step(fzFloat dt) override;
        
        virtual ActionInstant* copy() const;
        virtual ActionInstant* reverse() const;
    };
    
    
    //! Show the node.
    class Show : public ActionInstant
    {
    public:
        // Constructor
        Show() { };
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual Show* copy() const override;
    };
    
    
    //! Hide the node.
    class Hide : public ActionInstant
    {
    public:
        // Constructor
        Hide() { };
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual Hide* copy() const override;
    };
    
    
    //! Toggles the visibility of a node.
    class ToggleVisibility : public ActionInstant
    {
    public:
        // Constructor
        ToggleVisibility() { };
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual ActionInstant* copy() const override;
    };
    
    
    //! Flips the Sprite horizontally.
    class FlipX : public ActionInstant
    {
    protected:
        bool m_flipX;
        
    public:
        // Constructor
        FlipX(bool flipx);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual ActionInstant* copy() const override;
        
    };
    
    
    //! Flips the Sprite vertically.
    class FlipY : public ActionInstant
    {
    protected:
        bool m_flipY;
        
    public:
        // Constructor
        FlipY(bool flipy);
        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual ActionInstant* copy() const override;
    };
    
    
    //! Places the node in a certain position.
    class Place : public ActionInstant
    {
    protected:
        fzPoint m_position;
        
    public:
        Place(const fzPoint& position);
        Place(fzFloat x, fzFloat y);

        
        // Redefined
        virtual void startWithTarget(void *t) override;
        virtual ActionInstant* copy() const override;
    };
    
    
    //! Calls a 'callback'.
    class CallFunc : public ActionInstant
    {
    protected:
        SELProtocol *p_targetCallback;
        SELECTOR_VOID p_selector;
        
        void execute();

    public:
        // Constructor
        CallFunc(SELProtocol *target, SELECTOR_VOID selector);        
        
        // Redefined functions
        virtual void startWithTarget(void *target) override;
        virtual ActionInstant* copy() const override;
    };
    
    
    //! Calls a 'callback' with the node as the first argument.
    class CallFuncN : public ActionInstant
    {
    protected:
        SELProtocol *p_targetCallback;
        SELECTOR_PTR p_selector;
        
        virtual void execute();
        
    public:
        //! Constructs a CallFuncN action.
        CallFuncN(SELProtocol *target, SELECTOR_PTR selector);
        
        
        // Redefined
        virtual void startWithTarget(void *target) override;
        virtual ActionInstant* copy() const override;
    };
    
    
    //!Calls a 'callback' with the node as the first argument and the 2nd argument is data.
    //! ND means: Node and Data. Data is void *, so it could be anything.
    class CallFuncND : public ActionInstant
    {
    protected:
        SELProtocol *p_targetCallback;
        SELECTOR_2PTR p_selector;
        void *p_pointer;
        
        void execute();

    public:
        //! Constructs a CallFuncND action.
        CallFuncND(SELProtocol *target, SELECTOR_2PTR selector, void *data);
        
        
        // Redefined
        virtual void startWithTarget(void *target) override;
        virtual ActionInstant* copy() const override;
    };

    
    //! Calls a 'callback' with an object as the first argument.
    //! O means Object.
    class CallFuncO : public CallFuncN
    {
    protected:
        void *p_pointer;
        
    public:
        //! Constructs a CallFuncO action.
        CallFuncO(SELProtocol *t, SELECTOR_PTR selector, void *object);
        
        // Redefined
        virtual void execute() override;
        virtual ActionInstant* copy() const override;
    };
}
#endif
