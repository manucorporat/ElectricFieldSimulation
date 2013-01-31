// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZDIRECTOR_H_INCLUDED__
#define __FZDIRECTOR_H_INCLUDED__
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

#include "FZConfig.h"
#include "FZProtocols.h"
#include STL_VECTOR


using namespace STD;

namespace FORZE {
    
    /** @typedef fzProjection
     Possible OpenGL projections used by FORZE
     */
    enum fzProjection
    {
        //! sets a 2D projection (orthogonal projection).
        kFZProjection2D,
        
        //! sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        kFZProjection3D,
        
        //! it calls "updateProjection" on the projection delegate.
        kFZProjectionCustom,
        
        //! Detault projection is 3D projection
        kFZProjectionDefault = kFZProjection2D
    };
    
    
    /** @typedef fzOrientation
     Possible device orientations
     */
    enum fzOrientation
    {
        kFZOrientation_Auto = 0,
        
        //! Device oriented vertically, home button on the bottom
        kFZOrientation_Portrait             = 1<<0,
        
        //! Device oriented vertically, home button on the top
        kFZOrientation_PortraitUpsideDown   = 1<<1,
        
        //! Device oriented horizontally, home button on the right
        kFZOrientation_LandscapeLeft        = 1<<2,
        
        //! Device oriented horizontally, home button on the left
        kFZOrientation_LandscapeRight       = 1<<3,
        
        
        kFZOrientation_Landscape            = kFZOrientation_LandscapeLeft | kFZOrientation_LandscapeRight,
        kFZOrientation_All                  = kFZOrientation_Landscape | kFZOrientation_Portrait,
    };
    
    
    /** @typedef fzResizeMode
     Possible auto resizing modes
     */
    enum fzResizeMode
    {
        kFZResizeMode_None,
        kFZResizeMode_Expand,
        kFZResizeMode_Fit,
        kFZResizeMode_FitFill,
        kFZResizeMode_IntFit,
        kFZResizeMode_IntFitFill,
    };
    
    
    static const fzSize kFZSize_Auto(0, 0);

    static const fzSize kFZSize_iPhone(320, 480);
    static const fzSize kFZSize_iPhoneLandscape(480, 320);
    static const fzSize kFZSize_iPad(768, 1024);
    static const fzSize kFZSize_iPadLandscape(1024, 768);
    static const fzSize kFZSize_iPhone5(320, 568);
    static const fzSize kFZSize_iPhone5Landscape(568, 320);



    static const fzSize kFZSize_720p(1280, 720);
    static const fzSize kFZSize_1080p(1920, 1080);
    
    
    class HUD;
    class GLManager;
    class Scene;
    class Director
    {
        friend class Node;
        friend class EventManager;
        friend class Accelerometer;
    private:
        
#if FZ_RENDER_ON_DEMAND
        bool m_sceneIsDirty;
#endif
        
        enum {
            kFZDDirty_viewPort = 1 << 0,
            kFZDDirty_projection = 1 << 1,
        };
        // Application delegate
        AppDelegateProtocol *p_appdelegate;
        
        // Director's instance
        static Director* p_instance;

        // is director initialized
        bool m_isInitialized;
        
        // is the running scene paused
        bool m_isPaused;
        
        // is director running
        bool m_isRunning;
        
        // is director running
        unsigned char m_dirtyFlags;
        
        // device orientation
        fzOrientation m_orientation;
        int m_autoOrientation;
        
        // display size in pixels
        fzSize m_screenSize;
        
        // canvas size
        fzSize m_originalCanvasSize;
        fzSize m_canvasSize;
        
        // window size
        fzSize m_windowSize;

        // rendering rect
        fzRect m_renderingRect;
        
        // screen factor
        fzFloat m_screenFactor;
        
        // resources factor
        fzUInt m_resourcesFactor;
        
        
        fzAffineTransform m_orientationTransform;
        
        // current animation interval
        fzFloat m_animationInterval;
        
        // cached animation interval (during pausing)
        fzFloat m_cachedAnimationInterval;
        
        // projection used (2D, 3D or custom)
        fzProjection m_projection;
        
        // resize mode
        fzResizeMode m_resizeMode;
        
        // The running scene
        Scene *p_runningScene;
        
        /* will be the next 'runningScene' in the next frame
         nextScene is a weak reference. */
        Scene *p_nextScene;
        
        // If YES, then "old" scene will receive the cleanup message
        bool m_sendCleanupToScene;
        
        // scheduled scenes
        vector<Scene*> m_scenesStack;
        
        // This object will be visited after the scene. Useful to hook a notification node
        HUD *p_hud;
        
        // last time the main loop was updated
        struct timeval m_lastUpdate;
        
        // delta time since last tick to main loop
        fzFloat m_dt;
        fzFloat m_frameStep;
        
        // whether or not the next delta time will be zero
        bool m_nextDeltaTimeZero;
        
        bool m_firstFrame;

        // opengl manager
        GLConfig m_glConfig;
        
        
        // display FPS
        bool m_displayFPS;
        fzUInt m_frames;
        fzFloat m_accumDt;
        fzFloat m_frameRate;
        
        fzColor4F m_clearColor;
        
        // Threads
        void updateProjection();
        void setNextScene();
        void setDefaultGLValues();
        void showFPS();
        
    protected:
        Director();
        Director(const Director& );
        Director &operator = (const Director& );
          
        
    public:
        fzAffineTransform m_transform;
        
        int getAutorotation() const {
            return m_autoOrientation;
        }

        //! Gets and allocates the singleton.
        static Director& Instance();
        
        
        //! Sets the application's delegate.
        void setDelegate(AppDelegateProtocol *delegate);
        
        
        //! Returns the application's delegate.
        AppDelegateProtocol* getDelegate() const;

        
        //! Pauses the running scene.
        //! The running scene will be _drawed_ but all scheduled timers will be paused.
        //! While paused, the draw rate will be 4 FPS to reduce CPU consuption.
        //! @see applicationPaused()
        //! @see resume()
        void pause();
        
        
        //! Resumes the paused scene.
        //! The scheduled timers will be activated again.
        //! The "delta time" will be 0 (as if the game wasn't paused.
        //! @see applicationResumed()
        //! @see pause()
        void resume();
        
        
        //! Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
        //! If you wan't to pause your animation call [pause] instead.
        //! @see startAnimation()
        void stopAnimation();
        
        
        //! The main loop is triggered again.
        //! Call this function only if [stopAnimation] was called earlier.
        //! @warning Dont' call this function to start the main loop. To run the main loop. call runWithScene
        //! @see stopAnimation()
        void startAnimation();
        
        
        //! Returns true if the director is paused.
        //! @see pause()
        //! @see resume()
        bool isPaused() const;
        
        
        //! Returns true if the directos us running.
        //! @see stopAnimation()
        //! @see startAnimation()
        bool isRunning() const;
        
        
        //! Retuns the current delta value.
        fzFloat getDelta() const;
        
        
        //! This method calculate the delta value.
        void calculateDeltaTime();
        
        
        //! Only for debug reasons. Simulates a different screen size.
        //! Default window size is screen size.
        void setWindowSize(const fzSize& windowSize);
        
        
        void setFullscreen();
        
        //! Returns the current device orientation.
        //! This value can change dynamically when orientation = kFZOrientation_Auto.
        //! @see setOrientation()
        fzOrientation getOrientation() const;
        
        
        //! Returns the screen size.
        const fzSize& getScreenSize() const;
    
        
        //! Returns the display size in pixels.
        const fzSize& getWindowSize() const;
    
        
        //! Returns the canvas size.
        //! @see FORZE_INIT()
        //! @see setCanvasSize()
        const fzSize& getCanvasSize() const;
        
        
        //! Returns the view rect.
        //! @see getViewPort()
        const fzRect& getRenderingRect() const;
        
        
        //! Returns the default view port.
        //! @return getRenderingRect().size * screenFactor
        fzSize getViewPort() const;

        
        //! Returns the max scaling factor applied by the Autoresizing.
        //! @see setCanvasSize()
        //! @see setResizeMode()
        fzUInt getResourcesFactor() const;
        
        
        //! The scale factor determines how content in the view is mapped from the
        //! logical coordinate space (points) to the opengl backbuffer coordinates (viewPort=pixels)
        //! this value is calculated like this:
        //! contentScaleFactor = screen scaling factor * opengl context quality
        //! @see getViewPort()
        //! @see GLConfig
        fzFloat getContentScaleFactor() const;
        
        
        //! Sets a new canvas size.
        //! @param size. If size is (0, 0) canvas size is equal to screen size
        //! @see getCanvasSize()
        void setCanvasSize(const fzSize& size);
        
        
        //! Sets the orientaion.
        //! Default is kFZOrientation_Auto
        //! @see setOrientation()
        void setOrientation(fzOrientation orientation);


        
        void updateViewRect();
        
        
        // Returns true if the engine is running at full screen.
        bool isFullscreen() const;
        
                
        //! Sets a resizing mode.
        void setResizeMode(fzResizeMode resizeMode);
        
        
        //! Sets if you want to enable the depth test.
        void setDepthTest(bool);
        
        
        //! Sets the animation interval.
        //! @see getAnimationInteval()
        void setAnimationInterval(fzFloat);
        
        
        //! Returns the animation interval.
        //! @see setAnimationInterval()
        fzFloat getAnimationInteval() const;
        
        
        //! Sets if you want to display the FPS stats.
        void setDisplayFPS(bool);
        
        
        //! Sets the default background color.
        //! fzBLACK is default.
        //! @see getClearColor()
        void setClearColor(const fzColor4F&);
        
        
        //! Sets the default background color.
        //! @see setClearColor()
        const fzColor4F& getClearColor() const;
    
        
        //! Returns the current running Scene.
        //! Director can only run one Scene at the time.
        //! @see runWithScene()
        //! @see pushScene()
        //! @see replaceScene()
        Scene* getRunningScene() const;
        
        
        //! Sets the projection type.
        //! @see getProjection()
        void setProjection(fzProjection);
        
        
        //! Returns the projection type.
        //! @see setProjection()
        fzProjection getProjection() const;
        
        
        //! Returns the Z eye value.
        fzFloat getZEye() const;
        
        
        //! This method converts a UI coordinate to a GL coordinate.
        fzPoint convertToGL(fzPoint uiPoint, bool isFlippedY) const;
        
        
        //! This method normalizes a position at the canvas size.
        //! For example: The top-right corner is (1, 1).
        //! Center (0, 0) and Bottom-left corner (-1, -1).
        //! @see unnormalizedCoord()
        fzPoint normalizedCoord(fzPoint point) const;
        
        
        //! @see normalizedCoord()
        fzPoint unnormalizedCoord(fzPoint point) const;

        
        fzRect unnormalizedRect(fzRect rect) const;
        
        //! Returns the Opengl config.
        const GLConfig& getGLConfig() const;
        GLConfig& getGLConfig();
        
        
        //! Prints a log with the debug mode.
        //! This function is useful to ensure you are running at
        //! release mode, debug mode, assertions on/off...
        void logDebugMode() const;
        
        
        //! Draws the scene.
        //! This method is called every frame. Don't call it manually.
        //! Returns true if new content was rendered.
        bool drawScene();
        
        
        //! Enters the Director's main loop with the given Scene.
        //! Call it to run only your FIRST scene.
        //! Don't call it if there is already a running scene.
        void runWithScene(Scene* scene);
          
        
        //! Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
        //! The new scene will be executed.
        //! Try to avoid big stacks of pushed scenes to reduce memory allocation.
        //! ONLY call it if there is a running scene.
        void pushScene(Scene* scene);
        
        
        //! Pops out a scene from the queue.
        //! This scene will replace the running one.
        //! The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
        //! ONLY call it if there is a running scene.
        void popScene();
        
        
        //! Replaces the running scene with a new one. The running scene is terminated.
        //! ONLY call it if there is a running scene.
        void replaceScene(Scene* scene);
        
        
        Texture2D* getScreenshot(int format);
        void* getOSWrapper() const;
        
        
        /** Application callbacks */
        void applicationLaunching(void *OSWrapper);
        void applicationLaunched(void *options);
        void applicationPaused();
        void applicationResumed();
        void applicationTerminate();
        void applicationDidReceiveMemoryWarning();
        void applicationSignificantTimeChange();

    };
}
#endif
