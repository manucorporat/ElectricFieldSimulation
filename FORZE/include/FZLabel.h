// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZLABEL_H_INCLUDED__
#define __FZLABEL_H_INCLUDED__
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

#include "FZSpriteBatch.h"
#include STL_STRING


using namespace STD;

namespace FORZE {
    
    enum fzLabelAlignment {
        kFZLabelAlignment_left,
        kFZLabelAlignment_center,
        kFZLabelAlignment_right,
    };
        
    class Font;
    class Label : public SpriteBatch, public Protocol::Color
    {
    protected:
        string m_string;
        fzColor3B m_color;
        fzFloat m_verticalPadding;
        fzFloat m_horizontalPadding;
        fzLabelAlignment m_alignment;

        Font *p_font;
        
        void createFontChars();
        
    public:
        //! Constructs a void label.
        //! @warning you must set a valid font before set a text
        Label();
        
        
        //! Constructs a bitmap font label, you should use this method when creating .TTF(vectorial) fonts.
        Label(const char* text, const char* fontFilename, fzFloat lineHeight);
        
        
        //! Constructs a bitmap font label, this method is recomemded for .FNT fonts.
        Label(const char* text, const char* fontFilename);
        
        // Destructor
        ~Label();
        
        
        //! Sets a different Font.
        void setFont(Font* font);
        
        
        //! Sets a new label's string.
        void setString(const char* str);
        
        
        //! Returns the label's string.
        const char* getString() const {
            return m_string.c_str();
        }
        
        
        //! Sets the vertical padding between lines.
        //! This value is 0 by default.
        void setVerticalPadding(fzFloat vertical);
        
        
        //! Sets the horizontal padding between characters.
        //! This value is 0 by default.
        void setHorizontalPadding(fzFloat vertical);

        
        //! Sets the text alignment for multiline labels.
        //! kFZLabelAlignment_left by default.
        void setAlignment(fzLabelAlignment alignment);
        
        
        //! Returns the text aligment.
        fzLabelAlignment getAlignment() const {
            return m_alignment;
        }
        
        
        //! Returns the vertical padding between lines.
        fzFloat getVerticalPadding() const {
            return m_verticalPadding;
        }
        
        
        //! Returns the horizontal padding between characters.
        fzFloat getHorizontalPadding() const {
            return m_horizontalPadding;
        }

        
        // Redefined
        virtual void setColor(const fzColor3B& color) override;
        virtual const fzColor3B& getColor() const override;
    };
}
#endif
