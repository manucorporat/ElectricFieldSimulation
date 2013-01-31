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

#include "model_support.h"

#if !defined(FZ_OS) || (FZ_OS == kFZPLATFORM_MODEL)

#include "../FZDeviceConfig.h"
#include "../FZDirector.h"
#include "../FZEvent.h"
#include "../FZConsole.h"
#include "../external/tinythread/tinythread.h"


using namespace FORZE;

namespace FORZE {
    
#pragma mark -
#pragma mark - OS WRAPPER IMPLEMENTATION
    
    static void drawScene(void *context);
    
    class _FZOSWRAPPER
    {
        bool isRunning_;
        thread *thread_;
        float interval_;

    public:
        _FZOSWRAPPER()
        : thread_(NULL)
        , isRunning_(false)
        , interval_(0)
        {
            // STEP ZERO.
            
            // FIRST STEP. Notify Director::applicationLaunching()
            // - gets opengl context config
            // - attachs OS wrapper to director
            Director::Instance().applicationLaunching(this); //this = OS Wrapper pointer
            
            
            // SECOND STEP. Config UI.
            // - configs view: opacity, retina display...
            // - creates the window
            
            
            // THIRD STEP. OpenGL initialization.
            // - creates the opengl context.
            // - set the default window size.
            // - attachs the context to the view.
            
            
            // FOURTH STEP. Make window visible.
            // - "connects" the windows with the screen.
            
            
            // FIFTH STEP. Notify Directed::applicationLaunched()
            // - ends director's initialization
            // - appdelegate->applicationLaunched() is called
            // - -> game loop starts
            Director::Instance().applicationLaunched(NULL);
            
            
            // While the console is opened the program will stay running.
            Console console;
            console.join();
        }
        
        
        void startRendering(float interval)
        {
            if(isRunning_ == false) {
                isRunning_ = true;
                interval_ = interval;
                thread_ = new thread(drawScene, this);
            }
        }
        
        
        void stopRendering()
        {
            if(isRunning_ == true) {
                isRunning_ = false;
                
                // wait until to finish to continue.
                thread_->join();
                
                // deallocating thread
                delete thread_;
                thread_ = NULL;
            }
        }
        
        
        void loop()
        {
            while(isRunning_) {
                Director::Instance().drawScene();
                this_thread::sleep_for(chrono::milliseconds(interval_*1000));
            }
        }
    };
    
    static void drawScene(void *context) {
        ((_FZOSWRAPPER*)context)->loop();
    }
    
    
#pragma mark - OS WRAPPER communication protocol
    
    void OSW::init(int argc, char *argv[])
    {
        setInstance(new _FZOSWRAPPER());
    }
    
    
    void OSW::startRendering(fzFloat interval)
    {
        ((_FZOSWRAPPER*)Instance())->startRendering(interval);
    }
    
    
    void OSW::stopRendering()
    {
        ((_FZOSWRAPPER*)Instance())->stopRendering();
    }
    
    
    void OSW::updateWindow()
    {
        // No window
    }
    
    
    void OSW::configEvents(uint16_t dirtyFlags, uint16_t flags)
    {
        // No events
    }
    
    
    void OSW::setEventsInterval(fzFloat interval)
    {
        // Nothing to do here :)
    }
    
    
    void OSW::setOrientation(int orientation)
    {
        // Nothing to do here :)
    }
    
    
#pragma mark - Device info
    
    bool fzOSW_getDeviceCode(char *deviceCode, fzUInt maxLength)
    {
        strncpy(deviceCode, "model", maxLength);
        return true;
    }
    
    
    bool fzOSW_getSystemVersion(char *v, fzUInt maxLength)
    {
        strncpy(v, "1.0.0", maxLength);
        return true;
    }
    
    
    void fzOSW_getScreenSize(fzSize *size, fzFloat *factor)
    {
        *size = fzSize(100, 100);
        *factor = 1.0f;
    }
    
    
    uint16_t fzOSW_getCapacities()
    {
        return kFZEventType_All;
    }
    
    
    int fzOSW_getUserInterfaceIdiom()
    {
        return kFZUserInterfaceIdiomPC;
    }
    
    
    bool fzOSW_getResourcesPath(char *path, fzUInt maxLength)
    {
        getcwd(path, maxLength);
        return true;
    }
    
    
    bool fzOSW_getPersistentPath(const char *filename, char *absolutePath, fzUInt maxLength)
    {
        strncpy(absolutePath, filename, maxLength);
        return true;
    }
    
    
    bool fzOSW_getProductName(char *path, fzUInt maxLength)
    {
        strncpy(path, "sample", maxLength);
        return true;
    }
    
    
    bool fzOSW_createDirectory(const char *path, bool pathIsDirectory)
    {
        return true;
    }
    
    
    bool fzOSW_removePath(const char *path)
    {
        return !remove(path);
    }
}

#endif
