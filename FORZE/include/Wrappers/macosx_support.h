// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZ_SUPPORT_MAC_H_INCLUDED__
#define __FZ_SUPPORT_MAC_H_INCLUDED__
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


#if defined(FZ_OS) && (FZ_OS == kFZ_OS_MAC)

// Import OSX base headers
#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>

// Import OpenGL headers
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <OpenGL/OpenGL.h>
#import <Cocoa/Cocoa.h>


#pragma mark - OpenGL extensions

#define FZ_EXTENSION_PVRTC "GL_IMG_texture_compression_pvrtc"
#define FZ_EXTENSION_POT "GL_ARB_texture_non_power_of_two"
#define FZ_EXTENSION_BGRA "GL_EXT_bgra"
#define FZ_EXTENSION_DISCARD_FRAMEBUFFER "GL_EXT_discard_framebuffer"


#pragma mark - OpenGL config

#define FZ_GL_SHADERS 1
#define FZ_OS_DESKTOP 1

#pragma mark - OpenGL API

#define FZ_T_RGBA8888     GL_RGBA8
#define FZ_T_RGB888       GL_RGB8
#define FZ_T_BGBA8888     GL_BGRA
#define FZ_T_RGBA4444     GL_RGBA4
#define FZ_T_RGBA5551     GL_RGB5_A1
#define FZ_T_RGB565       GL_RGB
#define FZ_T_LA88         GL_LUMINANCE8_ALPHA8
#define FZ_T_A8           GL_ALPHA8
#define FZ_T_L8           GL_LUMINANCE8

#pragma mark - OS WRAPPER

namespace FORZE {
    class Director;
    class EventManager;
}

@interface _FZOSWRAPPER : NSView <NSApplicationDelegate, NSWindowDelegate>
{
@private
    // managers
    FORZE::Director *mgrDirector_;
    FORZE::EventManager *mgrEvents_;
    
    // UI
    NSWindow *window_;
    
    // Threading
    CVDisplayLinkRef displayLink_;
    
    // OpenGL
    NSOpenGLContext *context_;
    NSOpenGLPixelFormat *pixelFormat_;    
}
@property(nonatomic, readonly)  NSOpenGLContext *openGLContext;
@property(nonatomic, readonly)  NSOpenGLPixelFormat *pixelFormat;

- (void) startRendering:(float)interval;
- (void) stopRendering;
- (void) updateEvents:(uint16_t)dirtyFlags flags:(uint16_t)flags;
- (void) updateWindow;

- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime;

@end

#endif
#endif
