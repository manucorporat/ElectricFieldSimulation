// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZACTIONMANAGER_H_INCLUDED__
#define __FZACTIONMANAGER_H_INCLUDED__
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
#if FZ_STL_CPLUSPLUS11
#include STL_UNORDERED_MAP
#else
#include STL_MAP
#endif


using namespace STD;

namespace FORZE {

    
    /** ActionManager is a singleton that manages all the actions.
     Normally you won't need to use this singleton directly. 99% of the cases you will use the Node interface,
     which uses this singleton.
     But there are some cases where you might need to use this singleton.
     Examples:
     - When you want to run an action where the target is different from a Node. 
     - When you want to pause / resume the actions
     */
    class ActionManager : public SELProtocol
    {
        friend class Director;
        
    private:
        struct fzActionHandler {
            Action *action;
            bool isPaused;
            bool isStarted;
        };
       
        // Simplified types
#if FZ_STL_CPLUSPLUS11
        typedef unordered_multimap<void*, fzActionHandler> actionsMap;
#else
        typedef multimap<void*, fzActionHandler> actionsMap;
#endif
        typedef pair<void*, fzActionHandler> pairAction;
        typedef pair<actionsMap::iterator, actionsMap::iterator> pairSearch;
        
        
        // Manager's instance
        static ActionManager* p_instance;
        actionsMap m_actions;
        
        void update(fzFloat dt);
        
    protected:
        // Constructors
        ActionManager();
        ActionManager(const ActionManager& ) ;
        ActionManager &operator = (const ActionManager& ) ;
        
        
    public:
        // Gets and allocates the instance.
        static ActionManager& Instance();
        
        
        /** Adds an action with a target.
         If the target is already present, then the action will be added to the existing target.
         If the target is not present, a new instance of this target will be created either paused or paused, and the action will be added to the newly created target.
         When the target is paused, the queued actions won't be 'ticked'.
         */
        void addAction(Action *action, void *target, bool paused);
        
        
        //! Gets an action given its tag an a target.
        //! @return NULL is no action was found.
        Action* getActionByTag(fzInt tag, void *target);
        
        
        //! Returns the numbers of actions that are running in a certain target.
        //! Composable actions are counted as 1 action.
        //! Example: 1 Sequence of 8 actions are counted as 1 action.
        fzUInt getNumberActions(void *target) const;
        
        
        //! Returns the total numbers of actions that are running.
        fzUInt getNumberActions() const;
        
        
        //! Pauses the specified target. All running actions will be paused.
        //! @see resumeTarget()
        void pauseTarget(void *target);
        
        
        //! Resumes the specified target. All queued actions will be resumed.
        //! @see pauseTarget()
        void resumeTarget(void *target);
        
        
        //! Removes an action.
        void removeAction(const Action* action);
        
        
        //! Removes an action given its tag and the owner target.
        void removeAction(fzInt tag, void *target);
        
        
        //! Removes all actions from a certain target.
        //! All the actions that belongs to the target will be removed.
        void removeAllActions(void *target);
        
        
        //! Removes all actions from all the targers.
        void removeAllActions();
    };
}
#endif
