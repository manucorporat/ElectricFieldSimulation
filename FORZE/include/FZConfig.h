// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZCONFIG_H_INCLUDED__
#define __FZCONFIG_H_INCLUDED__
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

/**
 * @file
 * FORZE (FZ) configuration file
 */

#include "FZOSW_header.h"


#define FORZE_VERSION "v0.1rc2"
#define FORZE_SIGN "FORZE2D: "
#define FORZE_SIGN_LEN 9



#pragma mark - STL config

// You can replace easily the Standard Library used by FORZE.
#define STL_VECTOR <vector>
#define STL_STRING <string>
#define STL_LIST <list>
#define STL_MAP <map>
#define STL_QUEUE <queue>
#define STL_UNORDERED_MAP <unordered_map>
#define STD std // Standard library's namespace (std by default)


#pragma mark - FORZE config

/** @def FZ_RENDER_ON_DEMAND
 * If enabled, FORZE will optimize the GPU usage just rendering if the content changed.
 * This feature is still experimental, but several tests show that it works properly.
 * @warning take care using your own opengl code if this setting is enabled.
 */
#define FZ_RENDER_ON_DEMAND 1


/** @def FZ_STL_CPLUSPLUS11
 * If enabled, FORZE will use features from the STL C++11.
 * unordered_map for example.
 * Currently it's disabled because the STL11 is not compliant in all compilers.
 */
#define FZ_STL_CPLUSPLUS11 0


/** @def FZ_AUTORELEASE
 * If enabled, the autorelease() method will be available in all objects subclass of FORZE::LifeCyle.
 * @warning You should not disable it.
 */
#define FZ_AUTORELEASE 0


/** @def FZ_FIX_ARTIFACTS_BY_STRECHING_TEXEL
 * This formula prevents artifacts by using 99% of the texture.
 * The "correct" way to prevent artifacts is by using the spritesheet-artifact-fixer.py or a similar tool.
 * Disabled by default.
 */
#define FZ_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0


/** @def FZ_DIRECTOR_FPS_INTERVAL
 * Senconds between FPS updates.
 * 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 * Having a bigger number means a more reliable FPS
 *Default value: 0.1f
 */
#define FZ_DIRECTOR_FPS_INTERVAL 0.15f


/** @def FZ_RENDERING_SUBPIXEL
 If enabled, the Node objects (Sprite, Label,etc) will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#define FZ_RENDERING_SUBPIXEL 1


/** @def FZ_VBO_STREAMING
 FORZE will always VBO for static
 If enabled, batch nodes (texture atlas and particle system) will use VBO instead of vertex list (VBO is recommended by Apple)
*/
#define FZ_VBO_STREAMING 0


/** @def FZ_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA
 If most of your imamges have pre-multiplied alpha, set it to 1 (if you are going to use .PNG/.JPG file images).
 Only set to 0 if ALL your images by-pass Apple UIImage loading system (eg: if you use libpng or PVR images)

 To enable set it to a value different than 0. Enabled by default.
 */
#define FZ_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA 1


/** @def FZ_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
 Use GL_TRIANGLE_STRIP instead of GL_TRIANGLES when rendering the texture atlas.
 It seems it is the recommend way, but it is much slower, so, enable it at your own risk
 
 To enable set it to a value different than 0. Disabled by default.

 */
#define FZ_TEXTURE_ATLAS_USE_TRIANGLE_STRIP 0


/** @def FZ_TEXTURE_NPOT_SUPPORT
 If enabled, NPOT textures will be used where available. Only 3rd gen (and newer) devices support NPOT textures.
 NPOT textures have the following limitations:
 - They can't have mipmaps
 - They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define FZ_TEXTURE_NPOT_SUPPORT 0


/** @def FZ_IO_SUBFIX_CHAR
 * This is the character that introduces the filename flags used by FORZE you load the proper file.
 * E.g. if FZ_IO_SUBFIX_CHAR is '@' then the files should named as: "texture@x2.png", "texture@mac.png",
 * "font@x4.fnt"...
 */
#define FZ_IO_SUBFIX_CHAR '@'

#define FZ_SPRITE_DEBUG_DRAW 0


#pragma mark -

// Do not modify this code!!!

#define FZ_SPRITE_CHILDREN 0

#if FZ_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
#define FZ_TRIANGLE_MODE GL_TRIANGLE_STRIP
#else
#define FZ_TRIANGLE_MODE GL_TRIANGLES
#endif

#endif
