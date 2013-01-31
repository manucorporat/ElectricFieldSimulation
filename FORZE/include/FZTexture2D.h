// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTEXTURE2D_H_INCLUDED__
#define __FZTEXTURE2D_H_INCLUDED__
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

#include "FZPlatforms.h"
#include "FZLifeCycle.h"


namespace FORZE {
        
    /** @typedef fzPixelFormat
     Possible texture pixel formats
     */
    enum fzPixelFormat
    {
        kFZPixelFormat_RGBA8888,
        kFZPixelFormat_BGRA8888,
        kFZPixelFormat_RGB888,
        kFZPixelFormat_RGBA4444,
        kFZPixelFormat_RGB5A1,
        kFZPixelFormat_RGB565,
        kFZPixelFormat_LA88,
        kFZPixelFormat_A8,
        kFZPixelFormat_L8,
        kFZPixelFormat_PVRTC4,
        kFZPixelFormat_PVRTC2,
    };
    
    
    /** @typedef fzTextureFormat
     Possible texture pixel formats
     */
    enum fzTextureFormat
    {
        kFZTextureFormat_RGBA8888,
        kFZTextureFormat_BGRA8888,
        kFZTextureFormat_RGB888,
        kFZTextureFormat_RGBA4444,
        kFZTextureFormat_RGB5A1,
        kFZTextureFormat_RGB565,
        kFZTextureFormat_LA88,
        kFZTextureFormat_A8,
        kFZTextureFormat_L8,
        kFZTextureFormat_PVRTC4,
        kFZTextureFormat_PVRTC2,
        
        kFZTextureFormat_invalid = -1,
        kFZTextureFormat_auto = -2,
        kFZTextureFormat_quality = -3,
        kFZTextureFormat_performance = -4
    };
    
    
    struct fzPixelInfo
    {
        fzTextureFormat textureFormat;
        uint32_t dataFormat;
        uint32_t dataType;
        uint8_t dataBBP;
        bool isCompressed;
    };
    
    
    struct fzTextureInfo
    {
        GLint openGLFormat;
        uint8_t dataBBP;
        bool isCompressed;
    };
    
    
    //CLASS INTERFACES:
    
    /** Texture2D class.
     * This class allows to easily create OpenGL 2D textures from images, text or raw data.
     * The created Texture2D object will always have power-of-two dimensions. 
     * Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
     * Be aware that the content of the generated textures will be upside-down!
     */
    class Texture2D : public LifeCycle
    {
    private:
        static fzTextureFormat _defaultPixelFormat;
        
        void allocTexture();
        
    protected:
        GLuint          m_textureID;
        fzSize          m_size;
        GLsizei         m_width, m_height;
        fzTextureFormat m_format;
        fzTexParams     m_texParams;
        fzFloat         m_factor;
      
        unsigned char* expand(fzPixelFormat format, fzUInt fromX, fzUInt fromY, fzUInt toX, fzUInt toY, const void *ptr);
        void upload(fzPixelFormat format, GLint level, GLsizei width, GLsizei height, GLsizei packetSize, const void *ptr);
        void setPixelFormat(fzPixelFormat pixelFormat, fzTextureFormat textureFormat);
        
        void loadPNGFile(const char*);
        void loadPVRFile(const char*);
        void loadPVRCCZFile(const char*);
        
        
    public:
        
        static const fzTextureInfo& getDefaultTextureConfig(fzTextureFormat format);
        
        //! Default constructor
        Texture2D();

        
        //! Constructs a Texture2D with a data pointer, a format, POT width, height and the content size.
        Texture2D(const void* ptr, fzPixelFormat pixelFormat, fzTextureFormat textureFormat, GLsizei width, GLsizei height, const fzSize &size);
        
        
        //! Constructs a blank Texture2D with a format and size.
        Texture2D(fzTextureFormat format, const fzSize& size);
        
        
        //! Constructs a Texture2D from an image in ROM.
        Texture2D(const char* filename);
        
        // Destructor
        ~Texture2D();
        
        void loadPVRData(const char*);

        
        //! Returns the texture format.
        fzTextureFormat getTextureFormat() const {
            return m_format;
        }
        
        
        //! Returns the texture width in pixels.
        //! @warning if you are trying to do something complex with this value, remember that FORZE only works with points, not pixels.
        //! @see getPixelsHigh()
        fzUInt getPixelsWide() const {
            return m_width;
        }
        
        
        //! Returns the texture height in pixels.
        //! @warning if you are trying to do something complex with this value, remember that FORZE only works with points, not pixels
        //! @see getPixelsWide()
        fzUInt getPixelsHigh() const {
            return m_height;
        }
        
        
        //! Returns the texture Opengl ID.
        GLuint getName() const {
            return m_textureID;
        }
        
        
        //! Returns the texture scaling factor.
        //! texture-x2.png -> factor 2
        //! texture-x4.png -> factor 4 ...
        //! @see setFactor()
        fzFloat getFactor() const {
            return m_factor;
        }
        
        
        //! @see getFactor()
        void setFactor(fzFloat factor) {
            m_factor = factor;
        }
        
        //! Returns the content size of the texture in points.
        //! @see getContentSizeInPixels()
        fzSize getContentSize() const;
        
        
        //! Returns the content size of the texture in points.
        //! @see getContentSize()
        const fzSize& getContentSizeInPixels() const {
            return m_size;
        }
        
        
        //! Binds the opengl texture.
        //! @code fzGLBindTexture2D(texture->getName());
        void bind() const;
        
        
        //! Sets the min filter, mag filter, wrap s and wrap t texture parameters.
        //! If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
        void setTexParameters(const fzTexParams&);
        
        
        //! Sets antialias texture parameters:
        //! - GL_TEXTURE_MIN_FILTER = GL_LINEAR
        //! - GL_TEXTURE_MAG_FILTER = GL_LINEAR
        //! @see setTexParameters()
        //! @see setAliasTexParameters()
        void setAntiAliasTexParameters();
        
        
        //! Sets alias texture parameters:
        //! - GL_TEXTURE_MIN_FILTER = GL_NEAREST
        //! - GL_TEXTURE_MAG_FILTER = GL_NEAREST
        //! @see setTexParameters()
        //! @see setAntiAliasTexParameters()
        void setAliasTexParameters();
        
        
        //! Generates mipmap images for the texture.
        //! It only works if the texture size is POT (power of 2).
        void generateMipmap() const;
        
        
        //! Used in debug mode to quickly render a texture.
        void draw(fzFloat sX = 1, fzFloat sY = 1) const;
        
        
        void log() const;
        
        /** Sets the default pixel format for non-PVR images.
         If the image contains alpha channel, then the options are:
         - generate 32-bit textures:    kFZTexture2DPixelFormat_RGBA8888 (default)
         - generate 16-bit textures:    kFZTexture2DPixelFormat_RGBA4444
         - generate 16-bit textures:    kFZTexture2DPixelFormat_RGB5A1
         - generate 16-bit textures:    kFZTexture2DPixelFormat_RGB565
         - generate 16-bit textures:    kFZTexture2DPixelFormat_IA88
         - generate 8-bit textures:     kFZTexture2DPixelFormat_A8
         */
        static fzTextureFormat getDefaultTextureFormat();
        static void setDefaultTextureFormat(fzTextureFormat);
        
        
        static fzTextureFormat screenTextureFormat();
        static fzPixelInfo getPixelInfo(fzPixelFormat format);
        static fzTextureInfo getTextureInfo(fzTextureFormat format);

        
        //! Returns the alpha pixel format.
        bool getHasPremultipliedAlpha() const;
    };
}
#endif
