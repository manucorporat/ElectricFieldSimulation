// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZMENUITEM_H_INCLUDED__
#define __FZMENUITEM_H_INCLUDED__
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
#include "FZLabel.h"
#include "FZProtocols.h"
#include "FZEventManager.h"
#include STL_STRING


using namespace STD;

namespace FORZE {
    
#define kItemSize 32
    
#pragma mark - MenuItem
    
    /** MenuItem base class
     *  Subclass MenuItem (or any subclass) to create your custom MenuItem objects.
     */
    class MenuItem : public Node, public EventDelegate
    {
        friend class Menu;
        
    private:
        char m_mode;
        bool m_isWaiting;

        void useBatchMode();
        void useSelfMode();
        virtual bool event(Event& event) override;
      
#if 0
        void *p_leftItem;
        void *p_rightItem;
        void *p_topItem;
        void *p_bottomItem;
#endif
        
        
    protected:        
        SELProtocol *p_targetCallback;
        SELECTOR_PTR m_selector;
        
        bool m_isEnabled;
        bool m_isSelected;
        
        //! Makes the MenuItem active.
        virtual void activate();
        
        
        //! Makes the MenuItem selected.
        //! This method is used internally by the Menu.
        //! @see unselected()
        virtual void selected();
        
        
        //! Makes the MenuItem unselected.
        //! This method is used internally by the Menu.
        //! @see selected()
        virtual void unselected();
        
        
    public:
        //! Constructs a base menu item.
        MenuItem(SELProtocol *target, SELECTOR_PTR selector);
        
        
        //! Returns true if the MenuItem is enabled.
        bool isEnabled() const;
        
        
        //! Returns whether or not the item is selected.
        bool isSelected() const;
        
        
        //! Enable or disabled the MenuItem.
        virtual void setIsEnabled(bool);
        
        
        // Redefined
        virtual void onEnter() override;
        virtual void onExit() override;
    };
    
#pragma mark - Button
    
    /** MenuItem can be used as an independent button if it's attached to a non Menu class.
     * Button is the same as MenuItem in order to avoid semantic misunderstandings.
     */
    typedef MenuItem Button;
    
    
#pragma mark - MenuItemLabel
    
    class Label;
    class MenuItemLabel : public MenuItem, public Protocol::Color
    {
    protected:
        fzColor3B   m_colorBackup;
        fzColor3B   m_disabledColor;
        fzFloat     m_originalScale;
        Label       *p_label;
        
        virtual void selected() override;
        virtual void unselected() override;
        virtual void activate() override;
        
    public:
        //! Constructs a MenuItem with a label.
        MenuItemLabel(Label *label, SELProtocol *target, SELECTOR_PTR selector);
        MenuItemLabel(const string& str, const string& filename, SELProtocol *target, SELECTOR_PTR selector);

        
        //! Sets the color for the disabled state.
        void setDisabledColor(const fzColor3B&);
        
        
        //! Returns the color for the disabled state.
        const fzColor3B& getDisabledColor() const;
        
        
        /** Label that is rendered. It can be any Node that implements the LabelProtocol */
        void setLabel(Label*);
        Label* getLabel() const;
        
        
        //! Sets a new string to the inner label.
        void setString(const char* str);
        
        
        // Redefined functions
        virtual void setColor(const fzColor3B&) override;
        virtual const fzColor3B& getColor() const override;
        virtual void setIsEnabled(bool) override;
    };
    
    
#pragma mark - MenuItemImage
    
    class Sprite;

    //! A MenuItemFont.
    //! Helper class that creates a MenuItemLabel class with a Label.
    class MenuItemImage : public MenuItem
    {
    protected:
        //! used sprite
        Sprite *p_sprite;
        
        //! normal color: fzWHITE
        fzColor3B m_colorNormal;
        
        //! selected color: fzGREEN
        fzColor3B m_colorSelected;
        
        //! selected color: fzGRAY
        fzColor3B m_colorDisabled;
        
        virtual void selected() override;
        virtual void unselected() override;

        
    public:
        //! Constructs a MenuItemImage from a custom sprite.
        MenuItemImage(Sprite *sprite, SELProtocol *target, SELECTOR_PTR selector);
        
        
        //! Constructs a MenuItemImage from an image filename.
        MenuItemImage(const string& filename, SELProtocol *target, SELECTOR_PTR selector);
        
        
        void setColorNormal(const fzColor3B&);
        void setColorSelected(const fzColor3B&);
        void setColorDisabled(const fzColor3B&);
        
        const fzColor3B& getColorNormal() const;
        const fzColor3B& getColorSelected() const;
        const fzColor3B& getColorDisabled() const;
        
        
        // Redefined methods
        virtual void setIsEnabled(bool) override;
    };
    
    
#pragma mark - MenuItemSprite
    
    /** MenuItemSprite accepts Node<CCProtocol::Color> objects as items.
     The images has 3 different states:
     - unselected image
     - selected image
     - disabled image    
     */
    class MenuItemSprite : public MenuItem, public Protocol::Color
    {
    protected:
        Sprite *p_normalSprite;
        Sprite *p_selectedSprite;
        Sprite *p_disabledSprite;
     
        virtual void selected() override;
        virtual void unselected() override;
        
        
    public:
        MenuItemSprite(const string& normalFilename,
                       const string& selectedFilename,
                       const string& disabledFilename, SELProtocol *target, SELECTOR_PTR selector);
        
        MenuItemSprite(Sprite *normalSprite,
                       Sprite *selectedSprite,
                       Sprite *disabledSprite, SELProtocol *target, SELECTOR_PTR selector);
        
        void setNormalSprite(Sprite*);
        void setSelectedSprite(Sprite*);
        void setDisabledSprite(Sprite*);

        // Redefined functions
        virtual void setIsEnabled(bool) override;
    };
}
#endif
