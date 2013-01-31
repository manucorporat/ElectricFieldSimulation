// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZIO_H_INCLUDED__
#define __FZIO_H_INCLUDED__
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

#include "FZAllocator.h"
#include STL_STRING


using namespace STD;

namespace FORZE {
    
    class IO
    {
    public:
        //! Loads a file at the specified absolute path.
        //! @param absolutePath is a NULL-terminated char string
        //! @return a empty fzBuffer if the file could not be loaded.
        static fzBuffer loadFile(const char *absolutePath);
        
        
        static bool checkFile(const char *absolutePath);
        
        
        //! Creates a file (overwriting mode "w") at the absolute path with the specified data.
        //! @param data is a NULL-terminated char string (data to be written).
        //! @param absolutePath is a NULL-terminated char string.
        //! @return 0 if the file could not be saved.
        static bool writeFile(const char *data, const char *absolutePath);
        
        
        //! Used internally to remove any suffix started by "-" in the filenames.
        //! Converts "texture-ipad.png" or "texture-x2.png" to "texture.png"
        static void removeFileSuffix(char* filename);
        
        
        //! This method returns the substring that match the filename extension.
        //! For example: "myTexture.pvr.gz" would return "png.gz".
        static const char* getExtension(const char* filename);
        
        
        static char* appendPaths(const char* path1, const char* path2, char *output);
    };
}
#endif
