// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZMACROS_H_INCLUDED__
#define __FZMACROS_H_INCLUDED__
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

#include <assert.h>

#include "FZOSW.h"
#include "FZConfig.h"
#include "FZCommon.h"


//! @def FZ_SWAP
//! Simple macro that swaps 2 variables
#define FZ_SWAP( __X__, __Y__ ) {   \
__typeof__(__X__) temp  = (__X__);  \
__X__ = __Y__; __Y__ = temp;        \
}


//! @def FZ_RANDOM_MINUS1_1
//! Returns a random float between -1 and 1
#define FZ_RANDOM_MINUS1_1() ((::random() / (float)0x3fffffff )-1.0f)


//! @def FZ_CRANDOM_0_1
//! Returns a random float between 0 and 1
#define FZ_RANDOM_0_1() ((::random() / (float)0x7fffffff ))


//! @def FZ_DEGREES_TO_RADIANS
//! Converts degrees to radians
#define FZ_DEGREES_TO_RADIANS(__ANGLE__) (0.01745329252f * (__ANGLE__)) // PI / 180


//! @def FZ_RADIANS_TO_DEGREES
//! Converts radians to degrees
#define FZ_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180


#ifndef NDEBUG

//! @def FZ_ASSERT
//! Built-in custom assert
#define FZ_ASSERT(__CONDITION__, __MESSAGE__) { \
if (!(__CONDITION__)) { \
printf("\n\n" FORZE_SIGN "ASSERTION: Line %d - \"" __FILE__ "\"\n" \
       " - CONDITION: \"" #__CONDITION__ "\"\n" \
       " - MESSAGE: \"" __MESSAGE__ "\" \n", __LINE__); \
abort(); \
}}

#else

#define FZ_ASSERT(__CONDITION__, __MESSAGE__) { }

#endif


#define FZ_RAISE(__MESSAGE__) { \
    throw FORZE::fzException(__MESSAGE__); \
}

#define FZ_RAISE_STOP(__MESSAGE__) {    \
    FZ_ASSERT(false, __MESSAGE__);             \
    FZ_RAISE(__MESSAGE__);              \
}




//! @def FORZE_INIT
//! Initializes FORZE ENGINE. This macro must be called just once in main().
//! @param APPDELEGATE is a weak pointer to a instance of your custom subclass of ApplicationSupport (AppDelegate).
//! @param CANVASSIZE is a fzSize. This will be the canvas size in which you will design the game.
//! @param __ARGC__ passed by int main(int argc, char *argv[]).
//! @param __ARGV__ passed by int main(int argc, char *argv[]).
//! @warning this method must be called just once in the application's entry point.
//! @code FORZE_INIT(new MyAppDelegate(), kFZSize_auto, argc, argv);
#define FORZE_INIT(APPDELEGATE, CANVASSIZE, __ARGC__, __ARGV__) {   \
    FORZE::Director& __director = FORZE::Director::Instance();      \
    __director.setDelegate((APPDELEGATE));                          \
    __director.setCanvasSize((CANVASSIZE));                         \
    FORZE::OSW::init((__ARGC__), (__ARGV__));                       \
}

 
//! @def FORZE_END
//! Stops and removes the director from memory.
//!  Removes the EAGLView from its parent-
#define FORZE_END()							\
do {										\
	FORZE::Director::Instance().end()		\
} while(0)


#define FZ_SAFE_RELEASE(__OBJ__) {  \
if(__OBJ__) {                       \
__OBJ__->release();                 \
__OBJ__ = NULL;                     \
}                                   \
}

#if FZ_RENDERING_SUBPIXEL
#define FZSUBPIXEL
#else
#define FZSUBPIXEL(__A__) static_cast<fzInt>((__A__))
#endif


#ifndef NULL_TERMINATION
#define NULL_TERMINATION __attribute__((sentinel(0)))
#endif



#define FZRETAIN_TEMPLATE(__NEWPTR__, __OLDPTR__) { \
if(__NEWPTR__) {(__NEWPTR__)->retain();} \
if(__OLDPTR__) {__OLDPTR__->release();} \
__OLDPTR__ = __NEWPTR__; \
}



/*
 * if FORZE_DEBUG is not defined, or if it is 0 then
 *	all FZLOGXXX macros will be disabled
 *
 * if FORZE_DEBUG==1 then:
 *		FZLOG() will be enabled
 *		FZLOGERROR() will be enabled
 *		FZLOGINFO()	will be disabled
 *
 * if FORZE_DEBUG==2 or higher then:
 *		FZLOG() will be enabled
 *		FZLOGERROR() will be enabled
 *		FZLOGINFO()	will be enabled 
 */
#if FORZE_DEBUG > 2

#warning "FORZE_DEBUG: Invalid debug mode"

#elif FORZE_DEBUG == 2

#define FZLOGERROR(...) FZLog(__VA_ARGS__)
#define FZLOGINFO(...) FZLog(__VA_ARGS__)
#define CHECK_GL_ERROR_DEBUG() CHECK_GL_ERROR()

#elif FORZE_DEBUG == 1

#define FZLOGERROR(...) FZLog(__VA_ARGS__)
#define FZLOGINFO(...) do {} while (0)
#define CHECK_GL_ERROR_DEBUG() CHECK_GL_ERROR()

#elif !defined(FORZE_DEBUG) || FORZE_DEBUG == 0

#define FZLOGERROR(...) do {} while (0)
#define FZLOGINFO(...) do {} while (0)
#define CHECK_GL_ERROR_DEBUG() do {} while (0)

#endif // FORZE_DEBUG


inline bool check_gl_error(const char *function, int line)
{
    GLenum error = glGetError();
    if(error) {
        FORZE::FZLog("OpenGL error: 0x%04X in %s, line %d", error, function, line);
        return true;
    }
    return false;
}

#define CHECK_GL_FRAMEBUFFER() { \
GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER); \
if(status != GL_FRAMEBUFFER_COMPLETE) \
FZLog("OpenGL issue: Framebuffer is not ready. 0x%04X in %s, line %d", status, __FUNCTION__, __LINE__); \
}

#define CHECK_GL_ERROR() check_gl_error(__FUNCTION__, __LINE__)


#endif

