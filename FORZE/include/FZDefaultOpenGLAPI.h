// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZDEFAULTOPENGLAPI_H_INCLUDED__
#define __FZDEFAULTOPENGLAPI_H_INCLUDED__
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

#ifndef fzGLClearDepth
#define	fzGLClearDepth				glClearDepth
#endif

#ifndef fzGLGenerateMipmap
#define fzGLGenerateMipmap			glGenerateMipmap
#endif

#ifndef fzGLGenFramebuffers
#define fzGLGenFramebuffers			glGenFramebuffers
#endif

#ifndef _fzGLBindFramebuffer
#define _fzGLBindFramebuffer        glBindFramebuffer
#endif

#ifndef fzGLFramebufferTexture2D
#define fzGLFramebufferTexture2D	glFramebufferTexture2D
#endif

#ifndef fzGLDeleteFramebuffers
#define fzGLDeleteFramebuffers		glDeleteFramebuffers
#endif

#ifndef fzGLCheckFramebufferStatus
#define fzGLCheckFramebufferStatus	glCheckFramebufferStatus
#endif

#ifndef fzGLDeleteFramebuffers
#define fzGLDeleteFramebuffers      glDeleteFramebuffers
#endif

#ifndef FZ_COLOR_ATTACHMENT0
#define FZ_COLOR_ATTACHMENT0        GL_COLOR_ATTACHMENT0
#endif

#ifndef FZ_FRAMEBUFFER_COMPLETE
#define FZ_FRAMEBUFFER_COMPLETE     GL_FRAMEBUFFER_COMPLETE
#endif

#ifndef FZ_FRAMEBUFFER
#define FZ_FRAMEBUFFER              GL_FRAMEBUFFER
#endif

#ifndef FZ_FRAMEBUFFER_BINDING
#define FZ_FRAMEBUFFER_BINDING      GL_FRAMEBUFFER_BINDING
#endif

#ifndef FZ_DEPTH_ATTACHMENT
#define FZ_DEPTH_ATTACHMENT         GL_DEPTH_ATTACHMENT
#endif

#ifndef FZ_MAX_TEXTURE_SIZE
#define FZ_MAX_TEXTURE_SIZE         GL_MAX_TEXTURE_SIZE
#endif

#ifndef FZ_MAX_SAMPLES
#define FZ_MAX_SAMPLES              GL_MAX_SAMPLES
#endif

#ifndef FZ_T_RGBA8888
#define FZ_T_RGBA8888               GL_RGBA
#endif

#ifndef FZ_T_BGBA8888
#define FZ_T_BGBA8888               GL_BGRA
#endif

#ifndef FZ_T_RGBA4444
#define FZ_T_RGBA4444               GL_RGBA
#endif

#ifndef FZ_T_RGB888
#define FZ_T_RGB888                GL_RGB
#endif

#ifndef FZ_T_RGBA5551
#define FZ_T_RGBA5551               GL_RGBA
#endif

#ifndef FZ_T_RGB565
#define FZ_T_RGB565                 GL_RGB
#endif

#ifndef FZ_T_LA88
#define FZ_T_LA88                   GL_LUMINANCE_ALPHA
#endif

#ifndef FZ_T_A8
#define FZ_T_A8                     GL_ALPHA
#endif

#ifndef FZ_T_L8
#define FZ_T_L8                     GL_LUMINANCE
#endif

#ifndef FZ_P_8888
#define FZ_P_8888                   GL_UNSIGNED_BYTE
#endif

#ifndef FZ_P_888
#define FZ_P_888                    GL_UNSIGNED_BYTE
#endif

#ifndef FZ_P_88
#define FZ_P_88                     GL_UNSIGNED_BYTE
#endif

#ifndef FZ_P_8
#define FZ_P_8                      GL_UNSIGNED_BYTE
#endif

#ifndef FZ_P_4444
#define FZ_P_4444                   GL_UNSIGNED_SHORT_4_4_4_4
#endif

#ifndef FZ_P_565
#define FZ_P_565                    GL_UNSIGNED_SHORT_5_6_5
#endif

#ifndef FZ_P_5551
#define FZ_P_5551                   GL_UNSIGNED_SHORT_5_5_5_1
#endif


// EXTENSIONS
#ifndef FZ_EXTENSION_PVRTC
#define FZ_EXTENSION_PVRTC NULL
#endif

#ifndef FZ_EXTENSION_POT
#define FZ_EXTENSION_POT NULL
#endif

#ifndef FZ_EXTENSION_BGRA
#define FZ_EXTENSION_BGRA NULL
#endif

#ifndef FZ_EXTENSION_DISCARD_FRAMEBUFFER
#define FZ_EXTENSION_DISCARD_FRAMEBUFFER NULL
#endif

#endif
