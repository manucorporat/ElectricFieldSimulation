// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSCHEDULER_H_INCLUDED__
#define __FZSCHEDULER_H_INCLUDED__
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
#include "FZSelectors.h"
#include STL_LIST


using namespace STD;

namespace FORZE {

    class Scheduler;
    class Timer
    {
        friend class Scheduler;
        
    protected:
        bool m_paused;
        fzFloat m_elapsed;
        fzFloat m_interval;
        fzUInt m_priority;
        SELECTOR_FLOAT m_selector;
        SELProtocol *p_target;
        
        //! triggers the timer
        void update(fzFloat dt)
        {            
            if( m_elapsed == -1)
                m_elapsed = 0;
            else
                m_elapsed += dt;
            
            if( m_elapsed >= m_interval ) {
                (p_target->*m_selector)(m_elapsed);
                m_elapsed = 0;
            }
        }
        
    public:
        //! Constructs a timer with a target, a selector and an interval in seconds.
        Timer(SELProtocol* target, SELECTOR_FLOAT selector, fzUInt priority, fzFloat interval)
        : p_target(target)
        , m_selector(selector)
        , m_interval(interval)
        , m_priority(priority)
        , m_elapsed(-1)
        , m_paused(true)
        { }
        
        
        //! Sets a new interval.
        //! @warning This will restart the timer.
        void setInterval(fzFloat i) {
            m_elapsed = -1;
            m_interval = i;
        }
        
        
        //! Returns the current calling interval.
        fzFloat getInterval() const {
            return m_interval;
        }
        
        
        //! Returns the priority.
        fzUInt getPriority() const {
            return m_priority;
        }
        
        
        //! Enables or disables the timer.
        void setIsPaused(bool p) {
            m_paused = p;
        }
        
        
        //! Returns true is the timer is paused.
        bool isPaused() const {
            return m_paused;
        }
        
        
        //! Returns the target.
        SELProtocol* getTarget() const {
            return p_target;
        }
        
        
        //! Returns the SELECTOR_FLOAT pointer.
        SELECTOR_FLOAT getSelector() const {
            return m_selector;
        }
    };



    /** Scheduler is responsible of triggering the scheduled callbacks.
     You should not use NSTimer. Instead use this class.
     
     There are 2 different types of callbacks (selectors):
     
     - update selector: the 'update' selector will be called every frame. You can customize the priority.
     - custom selector: A custom selector will be called every frame, or with a custom interval of time
     
     The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.
     */
    class Scheduler
    {
        friend class Director;
        
    private:
        typedef list<Timer> timersList;

        static Scheduler* p_instance;
        
        // time scale
        fzFloat m_timeScale;
        
        // list of timers
        timersList m_timers;
        
        //! Returns the index giving a priority
        timersList::iterator indexForPriority(fzUInt priority);
        
        Timer *p_currentTimer;
        
        // 'tick' the scheduler.
        void tick(fzFloat);
        
        
    protected:
        // Constructors
        Scheduler();
        Scheduler(const Scheduler& ) ;
        Scheduler &operator = (const Scheduler& ) ;
        
        // Destructor
        ~Scheduler();
        
        
    public:
        //! Gets and allocates the singleton.
        static Scheduler& Instance();
        
        
        //! Sets a time scaling factor.
        void setTimeScale(fzFloat timeScale);
        
        
        //! Returns the time scaling factor.
        fzFloat getTimeScale() const;
        
        
        //! Returns the current running timer.
        Timer* getCurrentTimer() const;
        
        
        /** The scheduled method will be called every 'interval' seconds.
         If paused is YES, then it won't be called until it is resumed.
         If 'interval' is 0, it will be called every frame, but if so, it recommened to use 'scheduleUpdateForTarget:' instead.
         If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
        */
        void scheduleSelector(const SELECTOR_FLOAT selector, SELProtocol *target, fzFloat interval, bool paused, fzUInt priority = 2);

        
        /** Unshedules a selector for a given target.
         If you want to unschedule the "update", use unscheudleUpdateForTarget.
         */
        void unscheduleSelector(const SELECTOR_FLOAT selector, SELProtocol *target);
        
        
        //! Unschedules all selectors for a given target.
        //! This also includes the "update" selector.
        void unscheduleAllSelectors(SELProtocol *target);
        
        
        //! Unschedules all selectors from all targets.
        //! You should NEVER call this method, unless you know what you are doing.
        void unscheduleAllSelectors();
        
        
        //! Pauses the target.
        //! All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
        //! If the target is not present, nothing happens.
        void pauseTarget(SELProtocol *target);
        
        
        //! Resumes the target.
        //! The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
        //! If the target is not present, nothing happens.
        void resumeTarget(SELProtocol *target);
        
    };
}
#endif
