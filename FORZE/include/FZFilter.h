// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZFILTER_H_INCLUDED__
#define __FZFILTER_H_INCLUDED__
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

#include "FZGLProgram.h"

#if FZ_GL_SHADERS

#include "FZTypes.h"
#include "FZGrabber.h"
#include "FZMath.h"
#include "FZProtocols.h"


using namespace STD;

namespace FORZE {
    
    class Texture2D;
    class Node;
    class Filter : public LifeCycle, public Protocol::Texture
    {
        friend class Node;
        
    protected:
        GLProgram *p_glprogram;
        Texture2D *p_texture;        
        _fzT2_V2_Quad m_quad;
        
        void setGLProgram(GLProgram*);
        
        // Redefined
        virtual void setTexture(Texture2D*) override;
        virtual Texture2D *getTexture() const override;
        
    private:
        //! Used internally to initialize the filter
        Filter(fzFloat quality);
        
        
    public:
        //! Constructs an user defined filter specifing the fragmentshader filename
        Filter(const string& fragmentFilename, fzFloat quality);
        
        //! Constructs an user defined filter with a fragment shader
        Filter(const GLShader& fragmentShader, fzFloat quality);

        void draw();
    };
    
    
    class FilterColor : public Filter
    {
    private:        
        fzFloat m_brightness;
        fzFloat m_contrast;

    public:
        //! Constructs a FilterColor, default quality is 1
        FilterColor(fzFloat quality = 1.0f);
        
        void setBrightness(fzFloat brightness);
        void setContrast(fzFloat contrast);
        
        fzFloat getBrightness() const;
        fzFloat getContrast() const;
    };
    
    
    class FilterGrayscale : public Filter
    {
    private:
        fzPoint3 m_intensity;
        
    public:
        //! Constructs a FilterGrayscale, default quality is 1
        FilterGrayscale(fzFloat quality = 1.0f);
        
        
        void setIntensity(const fzPoint3& intensity);        
        const fzPoint3& getIntensity() const;
    };
    
    class FilterXRay : public Filter
    {
    private:
        fzPoint3 m_intensity;
        
        
    public:
        //! Constructs a FilterGrayscale, default quality is 1
        FilterXRay(fzFloat quality = 1.0f);
        
        
        void setIntensity(const fzPoint3& intensity);        
        const fzPoint3& getIntensity() const;
    };
    
    
    class FilterInvert : public Filter
    {
    public:
        //! Constructs a FilterInvert, default quality is 1
        FilterInvert(fzFloat quality = 1.0f);        
    };
    
    
    class FilterToon : public Filter
    {
    private:
        fzFloat m_factor;
        
    public:
        //! Constructs a FilterToon, default quality is 1
        FilterToon(fzFloat quality = 1.0f);
        
        void setFactor(fzFloat factor);
        
        fzFloat getFactor() const;
    };
}
#endif
#endif
