// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSUPPORT_IOS_H_INCLUDED__
#define __FZSUPPORT_IOS_H_INCLUDED__
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


#if defined(FZ_OS) && (FZ_OS == kFZPLATFORM_IOS_GL_1 || FZ_OS == kFZPLATFORM_IOS_GL_2)

// Import basic iOS headers
#import <Availability.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreMotion/CoreMotion.h>


#pragma mark - OpenGL extensions

#define FZ_EXTENSION_PVRTC "GL_IMG_texture_compression_pvrtc"
#define FZ_EXTENSION_POT "GL_APPLE_texture_2D_limited_npot"
#define FZ_EXTENSION_BGRA "GL_APPLE_texture_format_BGRA8888"
#define FZ_EXTENSION_DISCARD_FRAMEBUFFER "GL_EXT_discard_framebuffer"


#pragma mark - OSWRAPPER

namespace FORZE {
    class Director;
    class EventManager;
}


@interface _FZOSWRAPPER_BASE : UIView <UIApplicationDelegate, UIAccelerometerDelegate> {
@private    
    // weak pointers
    FORZE::Director *mgrDirector_;
    FORZE::EventManager *mgrEvents_;
    
    // UI
    UIWindow *window_;
    
    // Threading
    CADisplayLink *displayLink_;
    
    // Motion events
    CMMotionManager *motionManager_;
    //UIViewController *viewController_;
    
    // OpenGl
    EAGLContext	*context_;
    
    GLuint defaultFramebuffer_;
	GLuint colorRenderbuffer_;
	GLuint depthBuffer_;
    GLuint msaaFramebuffer_;
	GLuint msaaColorbuffer_;
}
- (EAGLRenderingAPI) openGLAPI;

- (void) updateEvents:(uint16_t)dirtyFlags flags:(uint16_t)flags;
- (void) updateWindow;
- (void) setEventInterval:(float)interval;
- (void) startRendering:(float)interval;
- (void) stopRendering;

@end

#endif

#endif
