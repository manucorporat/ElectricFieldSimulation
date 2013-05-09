// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZDEVICECONFIG_H_INCLUDED__
#define __FZDEVICECONFIG_H_INCLUDED__
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

#include "FZOSW.h"
#include "FZSelectors.h"


namespace FORZE {
    
    /** @enum fzUserInterface
     Cross platform solution to know at runtime the device's interface idiom, so the developer can
     customize the menu, gameplay... design.
     Use the macro FZ_USER_INTERFACE_IDIOM() to get the current one.
     @see DeviceConfig
     */
    enum fzUserInterface {
        //! Interface idiom from smartphone like iPhone, Xperia Play, Nokia Lumia
        kFZUserInterfaceIdiomPhone,
        
        //! Interface idiom from tablets such as iPad, Nexus 7...
        kFZUserInterfaceIdiomPad,
        
        //! Linux, OSX and Windows desktop devices.
        kFZUserInterfaceIdiomPC,
    };

    
    /** Configuration contains some openGL variables */
    class DeviceConfig : public SELProtocol
    {
    private:
        static DeviceConfig* p_instance;
        
        bool			m_supportsPVRTC;
        bool			m_supportsNPOT;
        bool			m_supportsBGRA8888;
        bool			m_supportsDiscardFB;
        
        GLint			m_maxTextureSize;
        GLint			m_maxSamplesAllowed;
        uint32_t         m_systemVersion;
        fzUserInterface m_userInterfaceIdiom;
        
        char            *p_glExtensions;
        char            *p_deviceCode;
        
    protected:
        // Constructors
        DeviceConfig(int interface);
        DeviceConfig(const DeviceConfig& ) ;
        DeviceConfig &operator = (const DeviceConfig& ) ;
        
        // Destructor
        ~DeviceConfig();
                
    public:
        //! Gets and allocates the singleton
        static DeviceConfig& Instance();
        static void SimulateInterface(int interface);
        
        bool checkForGLExtension(const char* searchName);
        
        //! Returns the maximum number of samples supported by OpenGL.
        const char* getDeviceCode() const;
        
        
        //! Returns the maximum OpenGL texture size.
        GLint getMaxTextureSize() const;
        
        
        //! Returns the maximum number of samples supported by OpenGL.
        GLint getMaxSamplesAllowed() const;
        
        
        //! This value is based in the max texture size value.
        //! It returns the maximun resource factor that the device can support securely.
        //! If getMaxFactor() is 4, FORZE never will try to load a file named: texture@x5.png
        fzUInt getMaxFactor() const;

        
        //!Whether or not the GPU supports NPOT (Non Power Of Two) textures.
        //! NPOT textures have the following limitations:
        //! - They can't have mipmaps
        //! - They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
        bool isNPOTSupported() const;

        
        //! Whether or not PVR Texture Compressed is supported.
        bool isPVRTCSupported() const;

        
        //! Whether or not BGRA8888 textures are supported.
        bool isBGRA8888Supported() const;

        
        //! Whether or not glDiscardFramebufferEXT is supported.
        bool isDiscardFramebufferSupported() const;
        
        
        //! Returns the device's user interface.
        //! @see FZ_USER_INTERFACE_IDIOM()
        fzUserInterface getUserInterfaceIdiom() const;
        
        
        //! Returns the OS version.
        uint32_t getSystemVersion() const;
        
        
        //! Prints a large log with the system info.
        void logDeviceInfo() const;
    };
}
#endif
