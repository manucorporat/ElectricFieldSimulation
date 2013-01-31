// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZLIST_H_INCLUDED__
#define __FZLIST_H_INCLUDED__
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

#include "FZTypes.h"


namespace FORZE {
    
    
    /** @def FZ_LIST_FOREACH(LIST, NODE)
     * Iterates a AutoList giving to the "NODE" parameter each object pointer
     @param LIST AutoList to be iterated object-per-object.
     @param NODE pointer used to get each list's object
     */
#define FZ_LIST_FOREACH(__LIST__, __NODE__)                                                 \
for(__NODE__ = static_cast<__typeof__(__NODE__)>((__LIST__).front()); __NODE__;   \
__NODE__ = static_cast<__typeof__(__NODE__)>((__NODE__)->next()))
    
    
    
    /** @def FZ_LIST_FOREACH_SAFE(LIST, NODE)
     * Iterates a AutoList giving to the "NODE" parameter each object pointer
     @param LIST AutoList to be iterated object-per-object.
     @param NODE pointer used to get each list's object
     */
#define FZ_LIST_FOREACH_SAFE(__LIST__, __NODE__)                        \
if((__NODE__ = static_cast<__typeof__(__NODE__)>((__LIST__).front())))  \
for(fzListItem *__AUX__;                                     \
(__NODE__ && ((__AUX__ = (__NODE__)->next()) || 1));                       \
(__NODE__ = static_cast<__typeof__(__NODE__)>(__AUX__)))

    
    
    /** @def FZ_LIST_FOREACH_REVERSE(LIST, NODE)
     * Iterates a AutoList in reverse order giving to the "NODE" parameter each object pointer
     @param LIST AutoList to be iterated object-per-object.
     @param NODE pointer used to get each list's object
     */
#define FZ_LIST_FOREACH_REVERSE(__LIST__, __NODE__)                                                 \
for(__NODE__ = static_cast<__typeof__(__NODE__)>((__LIST__).back()); __NODE__;   \
__NODE__ = static_cast<__typeof__(__NODE__)>((__NODE__)->prev()))

    

    class fzListItem
    {
        friend class AutoList;

    private:
        //! Weak pointer to the previous object
        fzListItem *p_prev;
        
        //! Weak pointer to the next object
        fzListItem *p_next;
        
        
    public:
        fzListItem() : p_prev(NULL), p_next(NULL) {}
        
        //! Returns the previous object.
        fzListItem* prev() {
            return p_prev;
        }
        
        //! Returns the next object.
        fzListItem* next() {
            return p_next;
        }
    };
    
    
    class AutoList
    {
    private:
        //! Weak pointer to the first object.
        fzListItem *p_front;
        
        //! Weak pointer to the last object.
        fzListItem *p_back;
        
        //! Number of objects.
        fzUInt m_count;
        
        
    public:
        //! Constructs an empty list.
        AutoList();
        
        
        //! Inserts a object at a given position.
        //! @param position where you want to insert the object
        //! if position is NULL, the object will be inserted at back
        //! @param object to be inserted
        //! @see push_front()
        //! @see push_back()
        void insert(fzListItem *position, fzListItem *object);
        
        
        //! Removes a object from the list.
        //! @see remove()
        void remove(fzListItem *position);
        
        
        //! Moves a object inside the list to a new position.
        void move(fzListItem *object, fzListItem *newPosition);

        
        //! Inserts a object at front (first one).
        //! @see insert()
        //! @see push_back()
        void push_front(fzListItem *node) {
            insert(p_front, node);
        }
        
        
        //! Inserts a object at back (last one).
        //! @see insert()
        //! @see push_back()
        void push_back(fzListItem *node) {
            insert(NULL, node);
        }
        
        
        //! Removes all objects from the list.
        //! @see remove()
        void clear() {
            p_front = NULL;
            p_back = NULL;
            m_count = 0;
        }
        
        
        //! Returns the first object (index 0).
        //! @return NULL if the list is empty.
        //! @see back()
        fzListItem *front() {
            return p_front;
        }
        
        
        //! Returns the last object (last index).
        //! @return NULL if the list is empty.
        //! @see front()
        fzListItem *back() {
            return p_back;
        }
        
        
        //! Returns true if the list is empty.
        //! size() == 0
        //! @see size()
        bool empty() const {
            return m_count == 0;
        }
        
        
        //! Returns the number of objects listed.
        fzUInt size() const {
            return m_count;
        }
    };
    
}
#endif
