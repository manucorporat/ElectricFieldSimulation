// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZEVENTMANAGER_H_INCLUDED__
#define __FZEVENTMANAGER_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 FORZEFIELD Studios S.L.
 * Copyright (c) 2012 Manuel Martínez-Almeida
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

#include "FZEvent.h"
#include STL_QUEUE
#include STL_LIST


using namespace STD;

namespace FORZE {
    
    //! EventDelegate is the protocol for catch events.
    class EventDelegate
    {
    public:
        virtual ~EventDelegate() {}
        virtual bool event(Event& event);
    };
    
    enum fzEventHandlerMode
    {
        //! This event handler mode is transparent for the next handlers.
        kFZEventHandlerMode_NoShallow,
        
        //! This event handler mode can stop the propagation of the event.
        kFZEventHandlerMode_Shallow,
        
        //! This event handler mode receives all catched events.
        kFZEventHandlerMode_Global
        
    };
    
    class recursive_mutex;
    
    //! EventManager catch and dispatch events.
    class EventManager
    {
        friend class Director;
        
    private:
        struct fzEventHandler
        {
            uint16_t flags;
            fzEventHandlerMode mode;
            fzInt priority;
            EventDelegate *delegate;
        };
        friend bool isHandlerFinished(const EventManager::fzEventHandler&);

        
        // Simplified typedefs
        typedef list<fzEventHandler> handlerList;
        typedef list<Event> eventList;
        typedef queue<Event> eventQueue;
        
        // Mutex
        recursive_mutex *p_mutex;
        
        // Director's instance
        static EventManager* p_instance;
        
        // events requested
        uint16_t m_flags;
        
        // Events vector
        eventList m_events;
        eventQueue m_buffer;
        
        // Delegates
        handlerList m_handlers;
        
        // is enabled
        bool m_enabled;
        
        handlerList::iterator indexForPriority(fzInt priority);
        void updateFlags();
        
        fzEventHandler* getHandlerForTarget(void* target);
        void updateHandlerFlags(fzEventHandler*, uint16_t);
        bool invalidateDelegate(EventDelegate *target);
        Event* addEvent(const Event&);
        
        void dispatchEvents();
        
    protected:
        // Constructors
        EventManager();
        EventManager(const EventManager& ) ;
        EventManager &operator = (const EventManager& ) ;
        
        // Destructor
        ~EventManager();

                
    public:
        //! Gets and allocates the singleton.
        static EventManager& Instance();
        
        
        //! Sets if you want to track events.
        void setIsEnabled(bool);
        
        
        //! Returns if the system is tracking events.
        bool isEnabled() const;
        
        
        //! Add a new event handler.
        //! @param target that will receive the events.
        //! @param flags tell what kind of events will track the target. If this value is 0, removeDelegate(target) is executed.
        void addDelegate(EventDelegate *target, uint16_t flags, fzInt priority, fzEventHandlerMode mode = kFZEventHandlerMode_NoShallow);
        
        
        //! Removes the specified target.
        //! The system will stop sending events to the target.
        void removeDelegate(EventDelegate *target);
        
        
        //! This method is used internally to track the incoming events.
        void catchEvent(const Event& newEvent);
        
        
        const eventList& getEvent() const {
            return m_events;
        }
        
        
        void cancelAllEvents();
        
        void setAccelGyroInterval(fzFloat interval);
        
        fzUInt getNumberOfEvents(uint16_t type) const;
        
        uint16_t checkCompatibility(uint16_t flags) const;
    };

}
#endif
