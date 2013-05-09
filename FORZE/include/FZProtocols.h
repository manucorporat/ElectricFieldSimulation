// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZPROTOCOLS_H_INCLUDED__
#define __FZPROTOCOLS_H_INCLUDED__
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

#include "FZGLConfig.h"

namespace FORZE {
    
#pragma mark - AppDelegateProtocol
    
    class Texture2D;
    class GLProgram;
    
    
#pragma mark - AppDelegateProtocol
    
    //! APPDelegate protocol
    class AppDelegateProtocol
    {
    public:
        virtual ~AppDelegateProtocol() {}
        
        //! The Director calls this method for the designated delegate when the application was launched succesfully.
        //! This is the entry point for all the game logic.
        //! This method is required to be implemented by the developer.
        virtual void applicationLaunched(void *options) = 0;
        
        
        //! The Director calls this method for the designated delegate when the application is paused.
        //! This method is optional.
        virtual void applicationPaused() {}
        
        //! The Director calls this method for the designated delegate when the application is resumed.
        //! This method is optional.
        virtual void applicationResumed() {}
        
        
        //! The Director calls this method for the designated delegate when the application is terminated.
        //! This method is optional.
        virtual void applicationTerminate() {}
        
        
        //! The Director calls this method for the designated delegate before loading the OpenGL context.
        //! By default this method returns the default opengl context config.
        //! But you can override this method and config it by yourself.
        //! @code
        //!            virtual GLConfig fzGLConfig()
        //!            {
        //!                GLConfig config;
        //!                config.quality = 0.8f;
        //!                config.colorFormat = kFZGLConfigColorRGBA8888;
        //!                return config;
        //!            }
        virtual GLConfig fzGLConfig()
        {
            GLConfig config;
            return config;
        }
    };
    
    
    class Protocol
    {
    public:
#pragma mark - Protocol::Blinding

        //! Blending protocol
        class Blending
        {
        public:
            virtual ~Blending(){}
                        
            //! Sets the OpenGl blendfunc used by.
            //! @see getBlendFunc()
            virtual void setBlendFunc(const fzBlendFunc&) = 0;
            
            //! Returns the OpenGl blendfunc used by.
            //! @see setBlendFunc()
            virtual const fzBlendFunc& getBlendFunc() const = 0;
        };
        
        
#pragma mark - Protocol::Color

        //! Color protocol
        class Color
        {
        public:
            virtual ~Color(){}
            
            //! Sets the color used as filter.
            //! @see getColor()
            virtual void setColor(const fzColor3B&) = 0;
            
            //! Returns the color used as filter.
            //! @see setColor()
            virtual const fzColor3B& getColor() const = 0;
        };
        
        
#pragma mark - Protocol::Texture
        
        //! Texture protocol
        class Texture
        {
        public:
            virtual ~Texture(){}
            
            //! Sets the Texture2D used by the node.
            //! @see getTexture()
            virtual void setTexture(Texture2D*) = 0;
            
            //! Returns the Texture2D associated with the node.
            //! @see setTexture()
            virtual Texture2D* getTexture() const = 0;
        };
    };
}
#endif
