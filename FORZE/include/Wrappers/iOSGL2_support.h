// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSUPPORT_IOS2_H_INCLUDED__
#define __FZSUPPORT_IOS2_H_INCLUDED__
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


#if defined(FZ_OS) && (FZ_OS == kFZ_OS_IOS_GL2)

// Import iOS stuff
#include "iOS_support.h"

// Import OpenGL ES 1.0 headers
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


#pragma mark - OpenGL settings

#define FZ_GL_SHADERS 1


#pragma mark - OpenGL API

#define	fzGLClearDepth                  glClearDepthf
#define fzGLGenRenderbuffers            glGenRenderbuffers
#define fzGLBindRenderbuffer            glBindRenderbuffer
#define fzGLFramebufferRenderbuffer     glFramebufferRenderbuffer
#define fzGLRenderbufferStorage         glRenderbufferStorage
#define fzGLGetRenderbufferParameteriv  glGetRenderbufferParameteriv
#define fzGLBindVertexArray             glBindVertexArray
#define FZ_MAX_SAMPLES                  GL_MAX_SAMPLES_APPLE
#define FZ_RENDERBUFFER                 GL_RENDERBUFFER
#define FZ_COLOR_ATTACHMENT0            GL_COLOR_ATTACHMENT0
#define FZ_FRAMEBUFFER_COMPLETE         GL_FRAMEBUFFER_COMPLETE
#define FZ_RENDERBUFFER_WIDTH           GL_RENDERBUFFER_WIDTH
#define FZ_RENDERBUFFER_HEIGHT          GL_RENDERBUFFER_HEIGHT

//#define FZ_T_RGBA8888     GL_RGB
//#define FZ_T_RGB888       GL_RGB
//#define FZ_T_BGBA8888     GL_BGRA_EXT
//#define FZ_T_RGBA4444     GL_RGBA
//#define FZ_T_RGBA5551     GL_RGB5_A1
//#define FZ_T_RGB565       GL_RGB565
//#define FZ_T_LA88         GL_LUMINANCE8_ALPHA8_EXT
//#define FZ_T_A8           GL_ALPHA8_EXT
//#define FZ_T_L8           GL_LUMINANCE8_EXT


#pragma mark - OS WRAPPER

@interface _FZOSWRAPPER : _FZOSWRAPPER_BASE
@end

#endif
#endif
