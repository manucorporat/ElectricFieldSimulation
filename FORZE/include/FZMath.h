// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZMATH_H_INCLUDED__
#define __FZMATH_H_INCLUDED__
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

#include "FZTypes.h"

namespace FORZE {
    
#if FZ_64BITS

#define fzMath_sqrt(__FZFLOAT__)  sqrt(__FZFLOAT__)
#define fzMath_cos(__FZFLOAT__)   cos(__FZFLOAT__)
#define fzMath_sin(__FZFLOAT__)   sin(__FZFLOAT__)

#else

#define fzMath_sqrt(__FZFLOAT__)  sqrtf(__FZFLOAT__)
#define fzMath_cos(__FZFLOAT__)   cosf(__FZFLOAT__)
#define fzMath_sin(__FZFLOAT__)   sinf(__FZFLOAT__)
    
#endif
    
    
    //! Returns next power of two.
    uint32_t fzMath_nextPOT(uint32_t scalar);
    
    
    //! Returns if "nu" is Power Of Two.
    bool fzMath_isPOT(uint32_t scalar);
    
    
    //! Returns a identity matrix.
    void fzMath_mat4Identity(float *matrix);
    
    
    //! Returns a new matrix after appling the affine transform to the given matrix.
    void fzMath_mat4Multiply(const float* matrixInput, const fzAffineTransform& affine, float* matrixOutput);
    
    
    //! Returns a new matrix after appling the affine transform to the given matrix.
    void fzMath_mat4Multiply(const float* matrixInput, const float* matrixInput2, float* matrixOutput);
    
    void fzMath_mat4Rotate(float* m, float angle);
    
    void fzMath_mat4MultiplySafe(const float* matrixInput, const float* matrixInput2, float* matrixOutput);

    bool fzMath_mat4Invert(const float *m, float *mOut);

    
    //! Returns four vec2 (8 floats).
    void fzMath_mat4Vec2(const float* matrixInput, const float* vertices2DInput, float* vertices2DOutput);

    
    //! Returns four vec4 (16 floats).
    void fzMath_mat4Vec4(const float* matrixInput, const float* vertices2DInput, float* vertices4DOutput);

    
    //! Returns four vec4 (16 floats).
    void fzMath_mat4Vec4Affine(const float* matrixInput, const fzAffineTransform& affine, const float* vertices2DInput, float* vertices4DOutput);
    
    
    //! Copies a matrix 4x4 efficiently.
    void fzMath_mat4Copy(const float* m1, float* mat);
    
    
    //! Prints a log in the console showing the 4x4 matrix.
    void fzMath_mat4Print(const float* matrix);
    
    
    //! Creates an perspective projection matrix.
    void fzMath_mat4PerspectiveProjection(fzFloat fovY, fzFloat aspect,
                                          fzFloat zNear, fzFloat zFar,
                                          float *output);
    
    
    //! Creates an orthographic projection matrix like glOrtho.
    void fzMath_mat4OrthoProjection(fzFloat left, fzFloat right,
                                           fzFloat bottom, fzFloat top,
                                           fzFloat nearVal, fzFloat farVal,
                                           float* output);
    
    
    //! Builds a translation matrix in the same way as gluLookAt().
    //! the resulting matrix is stored in output..
    void fzMath_mat4LookAt(const fzPoint3& eye,
                           const fzPoint3& center,
                           const fzPoint3& up,
                           float *output);
    
    
    
    template <typename T>
    inline T fzMin(T a, T b) {
        return (a<b) ? a : b;
    }
    
    template <typename T>
    inline T fzMax(T a, T b) {
        return (a>b) ? a : b;
    }
}
#endif
