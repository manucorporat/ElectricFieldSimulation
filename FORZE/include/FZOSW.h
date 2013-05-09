// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZPLATFORMS_H_INCLUDED__
#define __FZPLATFORMS_H_INCLUDED__
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

#include "FZOSW_header.h"

#ifndef FZ_OS

//#warning FORZE: The operative system was not specified.
//#warning You must define FZ_OS. See FZOSW_header.h

#define FZ_OS kFZ_OS_MODEL
#endif

#include "FZTypes.h"

#if (FZ_OS == kFZ_OS_IOS_GL1)
#include "Wrappers/iOSGL1_support.h"

#elif (FZ_OS == kFZ_OS_IOS_GL2)
#include "Wrappers/iOSGL2_support.h"

#elif (FZ_OS == kFZ_OS_MAC)
#include "Wrappers/macosx_support.h"

#elif (FZ_OS == kFZ_OS_PSVITA)
#include "Wrappers/psvita_support.h"

#elif (FZ_OS == kFZ_OS_MODEL)
#include "Wrappers/model_support.h"

#else

#error "FORZE: Invalid operative system."

#endif

#ifndef FZ_OS_DESKTOP
#define FZ_OS_DESKTOP 0
#endif

#include "FZDefaultOpenGLAPI.h"


namespace FORZE {
    
    class GLConfig;
    class GLManager;
    class EventManager;
        
    // OS WRAPPER
    // FORZE allocates an private class (Objective-C or C++ class) that connects the OS API with FORZE.
    // All this methods are low level, and they have a different implementation for each platform.
    // The common use never should have to use this methods.
    class OSW
    {        
    public:
        static void* p_oswrapper;
        static void* Instance();
        static void setInstance(void *instance);
        
        
        //! Initializes the wrapper class, initialize all OS runtime tasks and call notify that to the Director.
        static void init(int argc, char *argv[]);
        
        //! Starts the loop thread giving the OSWRAPPER pointer
        static void startRendering(fzFloat interval);
        
        //! Stops the loop thread giving the OSWRAPPER pointer
        static void stopRendering();
        
        //! Updates the window size and the rendering rect.
        static void updateWindow();
        
        //! Enables or disables the IO events, (touch, accelerometer) giving the OSWRAPPER
        static void configEvents(uint16_t dirtyFlags, uint16_t flags);
        
        //! Sets event internval
        static void setEventsInterval(fzFloat interval);
        
        //! Sets orientation
        static void setOrientation(int orientation);
    };
    
    

    // DEVICE
    //! Returns the OS version.
    bool fzOSW_getSystemVersion(char *v, fzUInt maxLength);
  
    //! Returns the screen size in points and the factor scale.
    void fzOSW_getScreenSize(fzSize *size, fzFloat *factor);
    
    //! Returns system capacities (accelerometer...)
    uint16_t fzOSW_getCapacities();
    
    //! Returns the device's user interface idiom.
    int fzOSW_getUserInterfaceIdiom();
  
    //! Returns the device identifier code.
    bool fzOSW_getDeviceCode(char *deviceCode, fzUInt maxLength);
  
    //! Returns the product name.
    bool fzOSW_getProductName(char *path, fzUInt bufferLength);
  
    //! Returns the application's absolute resources path.
    bool fzOSW_getResourcesPath(char *path, fzUInt maxLength);
  
    //! Returns the application persistent resources path.
    bool fzOSW_getPersistentPath(const char *filename, char *absolutePath, fzUInt bufferLength);
    
    //! Returns the application persistent resources path.
    bool fzOSW_createDirectory(const char *path, bool pathIsDirectory);
    
    //! Removes the specified path.
    bool fzOSW_removePath(const char *path);
}
#endif
