// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZTYPES_H_INCLUDED__
#define __FZTYPES_H_INCLUDED__
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

#include <stdint.h>
#include <stddef.h>
#include <float.h>
#include <math.h>
#include "FZConfig.h"


namespace FORZE {
    
#if (INTPTR_MAX == INT32_MAX)
    
    // 32bits environment
#define FZ_64BITS 0
    typedef int32_t fzInt;
    typedef uint32_t fzUInt;
    typedef float fzFloat;


#elif (INTPTR_MAX == INT64_MAX)

    // 64bits environment
#define FZ_64BITS 1
    typedef int64_t fzInt;
    typedef uint64_t fzUInt;
    typedef double fzFloat;
    
#else
    
#error "Environment not 32 or 64-bits."
    
#endif
    
    //! A 32 bits 4x4 matrix.
    typedef float fzMat4[16];
    
    // predefined class
    template<typename T, int N> class _fzColor4;
    template<typename T> class _fzVec2;
    
    
#pragma mark - fzColor3B interface
    
    class fzColor3B
    {
    public:
        unsigned char r; //!< red channel
        unsigned char g; //!< green channel
        unsigned char b; //!< blue channel
        
        //! Default constructor.
        fzColor3B() = default;
        
        
        //! Constructs a fzColor3B given the 3 RGB values.
        fzColor3B(unsigned char red, unsigned char green, unsigned char blue)
        : r(red), g(green), b(blue) {}
        
        
        //! Copy constructor.
        fzColor3B(const _fzColor4<unsigned char, 255>&);
        
        
        //! Copy constructor.
        fzColor3B(const _fzColor4<fzFloat, 1>&);
        
        
        // Operators
        fzColor3B& operator *= (fzFloat k) {
            r *= k;
            g *= k;
            b *= k;
            return *this;
        }
        
        const fzColor3B operator * (fzFloat k) const {
            return fzColor3B(r*k, g*k, b*k);
        }
        
        bool operator == (const fzColor3B& c) const {
            return (r == c.r && g == c.g && b == c.b);
        }
        
        bool operator != (const fzColor3B& c) const {
            return !(operator == (c));
        }
    };
    
#pragma mark - fzColor4 interface

    //! RGB color composed of 3 bytes.
    template<typename T, int N>
    class _fzColor4
    {
    public:
        T r; //!< red channel.
        T g; //!< green channel.
        T b; //!< blue channel.
        T a; //!< alpha channel.
        
        
        //! Default constructor.
        _fzColor4() = default;
        _fzColor4(T red, T green, T blue, T alpha = N)
        : r(red), g(green), b(blue), a(alpha) {}
        
        
        //! Copy constructor for fzColor4B.
        _fzColor4(const _fzColor4<unsigned char, 255>& c)
        : r(c.r * N/255.0f), g(c.g * N/255.0f), b(c.b * N/255.0f), a(c.a * N/255.0f) {}
        
        
        //! Copy constructor for fzColor4F.
        _fzColor4(const _fzColor4<float, 1>& c)
        : r(c.r * N), g(c.g * N), b(c.b * N), a(c.a * N) {}
        
        
        //! Copy constructor for fzColor3B.
        _fzColor4(const fzColor3B& c)
        : r(c.r * N/255.0f), g(c.g * N/255.0f), b(c.b * N/255.0f), a(N) {}
        
        
        //! Overloaded *= operator. Multiplies the color by a scalar.
        _fzColor4<T,N>& operator *= (float k) {
            r *= k;
            g *= k;
            b *= k;
            a *= k;
            return *this;
        }
        
        
        //! overloaded += operator. Color addition.
        _fzColor4<T,N>& operator += (const _fzColor4<T,N>& c) {
            r += c.r;
            g += c.g;
            b += c.b;
            a += c.a;
            return *this;
        }
        
        
        //! overloaded -= operator. Color subtraction.
        _fzColor4<T,N>& operator -= (const _fzColor4<T,N>& c) {
            r -= c.r;
            g -= c.g;
            b -= c.b;
            a -= c.a;
            return *this;
        }
        

        //! overloaded * operator. Multiplies a color by a scalar.
        const _fzColor4<T,N> operator * (float k) const {
            return _fzColor4<T,N>(r*k, g*k, b*k, a*k);
        }
        
        
        //! overloaded + operator. Color addition.
        const _fzColor4<T,N> operator + (const _fzColor4<T,N>& c) const {
            return _fzColor4<T,N>(r+c.r, g+c.g, b+c.b, a+c.a);
        }
        
        
        //! overloaded + operator. Color subtraction.
        const _fzColor4<T,N> operator - (const _fzColor4<T,N>& c) const {
            return _fzColor4<T,N>(r-c.r, g-c.g, b-c.b, a-c.a);
        }


        bool operator == (const _fzColor4<T,N>& c) const {
            return (r == c.r && g == c.g && b == c.b && a == c.a);
        }
        
        bool operator != (const _fzColor4<T,N>& c) const {
            return !(operator == (c));
        }
    };
    
    typedef _fzColor4<unsigned char, 255> fzColor4B;
    typedef _fzColor4<fzFloat, 1> fzColor4F;

    
#pragma mark - fzAffineTransform interface    
    
    //! Affine tranform interface composed of 6 floats.
    class fzAffineTransform
    {
    public:
        //! matrix values
        float m[16];

        //! Default constructor
        fzAffineTransform()
        : m{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        } {}
        
        //! 
        fzAffineTransform(float a, float b, float c, float d, float x, float y, float z)
        : m{
            a, b, 0, 0,
            c, d, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1
        } {}
        
        
        fzAffineTransform(const float *matrix);
        
        
        //! Applies a scale factor. X and Y axies.
        fzAffineTransform& scale(float sx, float sy) {
            m[0] *= sx; m[1] *= sx;
            m[4] *= sy; m[5] *= sy;

            return *this;
        }
        
        
        //! Applies a scale factor.
        fzAffineTransform& scale(float s) {
            return scale(s, s);
        }
        
        
//        fzAffineTransform& setZ(float z) {
//            m[14] = z;
//            return *this;
//        }
        
        // Assigns a new affine translation giving rotation/scale/translate.
        void assign(float *data);
        
        void log() const;
        
        //! Applies a translation.
        fzAffineTransform& translate(float x, float y, float z);
        fzAffineTransform& translate(float x, float y) {
            return translate(x, y, 0);
        }
        
        //! Applies a rotation given an angle in radians.
        fzAffineTransform& rotate(float radians);
        
        //! Applies an affine transform object.
        fzAffineTransform& concat(const fzAffineTransform&);
        
        //! Returns the inverse transform.
        fzAffineTransform getInverse() const;
        
        
        // Operators
        fzAffineTransform operator * (const fzAffineTransform& t) const {
            fzAffineTransform newT(m);
            newT.concat(t);
            return newT;
        }
        
        fzAffineTransform& operator *= (const fzAffineTransform& t) {
            return concat(t);
        }
    };
    
    
#pragma mark - fzSize interface
    
    //! A size composed of 2 GLfloats: width, height.
    class fzSize
    {
    public:
        fzFloat width;
        fzFloat height;
        
        // Constructors
        fzSize() = default;
        fzSize(fzFloat w, fzFloat h)
        : width(w), height(h) {}
        
        
        const fzSize operator + (const fzSize& s) const {
            return fzSize(width + s.width, height + s.height);
        }
        
        const fzSize operator - (const fzSize& s) const {
            return fzSize(width - s.width, height - s.height);
        }
        
        const fzSize operator * (fzFloat k) const {
            return fzSize(width * k, height * k);
        }
        
        const fzSize operator / (fzFloat k) const {
            return fzSize(width / k, height / k);
        }
        
        fzSize& operator += (const fzSize& s) {
            width += s.width; height += s.height;
            return *this;
        }
        
        fzSize& operator -= (const fzSize& s) {
            width -= s.width; height -= s.height;
            return *this;
        }
        
        //! mult cmp
        fzSize compMult(const fzSize& s) const {
            return fzSize(width*s.width, height*s.height);
        }
        
        fzSize& operator *= (fzFloat k) {
            width *= k; height *= k;
            return *this;
        }
        
        fzSize& operator /= (fzFloat k) {
            width /= k; height /= k;
            return *this;
        }
        
        bool operator == (const fzSize& s) const {
            return (width == s.width && height == s.height);

        }
        bool operator != (const fzSize& s) const {
            return !(operator == (s));
        }
    };
    
    
#pragma mark - fzPoint interface
    
    //! A point composed of 2 GLfloats: x, y.
    template<typename T>
    class _fzVec2
    {
    public:
        T x;
        T y;
        
        //! Default constructor.
        _fzVec2() = default;
        _fzVec2(T xx, T yy) : x(xx), y(yy) {}
        
        //! Copy constructor for _fzVec2<double>.
        _fzVec2(const _fzVec2<double>& p)
        : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}
        
        
        //! Copy constructor for _fzVec2<float>.
        _fzVec2(const _fzVec2<float>& p)
        : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}
        
        
        //! Copy constructor for fzSize.
        _fzVec2(const fzSize& s)
        : x(s.width), y(s.height) {}
        
        
        //! Returns the squared length of the vector.
        T lengthSquared() const {
            return x*x + y*y;
        }
        
        
        //! Returns the length of the vector.
        T length() const {
            return sqrtf(lengthSquared());
        }
        
        
        //! Returns a the perpendicular vector.
        _fzVec2<T> getPerp() const {
            return _fzVec2<T>(-y, x);
        }
        
        
        //! Returns the dot product.
        T dot(const _fzVec2<T>& p) const {
            T dot = x; dot *= p.x;
            dot += y*p.y;
            return dot;
        }
        
        
        //! Returns the angle by the vector x.
        T angle() const {
            return atan(y / x);
        }
        
        
        //! Returns the distance from the specified point.
        T distance(const _fzVec2<T>& p) const {
            return sqrtf(distanceSquared(p));
        }
        
        
        //! Returns the squared distance from the specified point.
        T distanceSquared(const _fzVec2<T>& p) const {
            _fzVec2<T> d(x-p.x, y-p.y);
            return d.lengthSquared();
        }
        
        
        //! Retuns the component-by-component multiply.
        _fzVec2<T> compMult(const _fzVec2<T>& p) const {
            return _fzVec2<T>(p.x*x, p.y*y);
        }
        
        
        //! Normalizes the vector (length = 1).
        _fzVec2<T>& normalize() {
            const T invLength = length();
            x /= invLength;
            y /= invLength;
            return *this;
        }
        
        
        //! Applies a fzAffineTransport to the vector.  
        _fzVec2<T>& applyTransform(const fzAffineTransform& t) {
            float x2 = x;
            x *= t.m[0]; x += t.m[4]*y + t.m[12];
            y *= t.m[5]; y += t.m[1]*x2 + t.m[13];
            return *this;
        }
        
        
        const _fzVec2<T> operator / (fzFloat k) const {
            return _fzVec2<T>(x / k, y / k);
        }
        
        //! overloaded += operator. vector + vector = vector
        _fzVec2<T>& operator += (const _fzVec2<T>& p) {
            x += p.x; y += p.y;
            return *this;
        }
        
        //! overloaded -= operator. vector - vector = vector
        _fzVec2<T>& operator -= (const _fzVec2<T>& p) {
            x -= p.x; y -= p.y;
            return *this;
        }
        
        //! overloaded *= operator. vector * scalar = vector
        _fzVec2<T>& operator *= (T k) {
            x *= k; y *= k;
            return *this;
        }
        
        //! overloaded /= operator. vector / scalar = vector
        _fzVec2<T>& operator /= (T k) {
            x /= k; y /= k;
        }
        
        //! overloaded * operator. dot product
        const T operator * (const _fzVec2<T>& p) const {
            return dot(p);
        }

        //! overloaded - operator. invert vector
        const _fzVec2<T> operator - () const {
            return _fzVec2<T>(-x, -y);
        }
        
        bool operator == (const _fzVec2<T>& p) const {
            return (x == p.x && y == p.y);
        }
        
        bool operator != (const _fzVec2<T>& p) const {
            return !(operator == (p));
        }
    };

    typedef _fzVec2<fzFloat> fzPoint;

    
    inline const fzPoint operator + (const fzPoint& p1, const fzPoint& p2) {
        return fzPoint(p1.x + p2.x, p1.y + p2.y);
    }
    
    inline const fzPoint operator - (const fzPoint& p1, const fzPoint& p2) {
        return fzPoint(p1.x - p2.x, p1.y - p2.y);
    }
    
    inline const fzPoint operator * (const fzPoint& p1, fzFloat k) {
        return fzPoint(p1.x * k, p1.y * k);
    }
    
    inline const fzPoint operator / (fzFloat k, const fzPoint& p1) {
        return fzPoint(k / p1.x, k / p1.y);
    }
    
#pragma mark - fzPoint3 interface
    
    //! A vertex composed of 3 floats: x, y, z.
    template<typename T>
    class _fzVec3
    {
    public:
        T x;
        T y;
        T z;

        //! Default constructor.
        _fzVec3() = default;
        _fzVec3(T xx, T yy, T zz)
        : x(xx), y(yy), z(zz) {}
        
        
        //! Copy constructor for fzPoint.
        _fzVec3(const fzPoint& p)
        : x(p.x), y(p.y), z(0) {}
        
        
        //! Returns the squared vector length.
        T lengthSquared() const {
            return x*x + y*y + z*z;
        }
        
        
        //! Returns the vector length.
        T length() const {
            return sqrtf(lengthSquared());
        }
        
        
        //! Normalizes the vector.
        _fzVec3<T>& normalize() {
            const T l = length();
            if(l > 0) {
                x /= l;
                y /= l;
                z /= l;
            }
            return *this;
        }
        
        
        // Returns the cross product.
        _fzVec3<T> getCrossed(const _fzVec3<T>& p) {
            return _fzVec3<T>((y * p.z) - (z * p.y),
                              (z * p.x) - (x * p.z),
                              (x * p.y) - (y * p.x));
        }
        
        
        //! overloaded += operator. vector + vector = vector
        _fzVec3<T>& operator += (const _fzVec3<T>& p) {
            x += p.x; y += p.y; z += p.z;
            return *this;
        }
        
        //! overloaded -= operator. vector - vector = vector
        _fzVec3<T>& operator -= (const _fzVec3<T>& p) {
            x -= p.x; y -= p.y; z -= p.z;
            return *this;
        }
        
        //! overloaded *= operator. vector * scalar = vector
        _fzVec3<T>& operator *= (T k) {
            x *= k; y *= k; z *= k;
            return *this;
        }
        
        //! overloaded /= operator. vector / scalar = vector
        _fzVec3<T>& operator /= (T k) {
            x /= k; y /= k; z /= k;
        }

    };
    
    typedef _fzVec3<fzFloat> fzPoint3;
    typedef _fzVec3<double> fzPoint3Double;


    
#pragma mark - fzRect interface
    
    class fzRect
    {
    public:
        fzPoint origin;
        fzSize size;
        
        // Constructors
        fzRect()
        : origin(0, 0), size(0, 0) {}
        
        fzRect(fzFloat x, fzFloat y, fzFloat width, fzFloat height)
        : origin(x, y), size(width, height) {}
        
        fzRect(const fzPoint& origins, const fzSize& sizes)
        : origin(origins), size(sizes) {}

        
        fzRect& applyTransform(const float *matrix);
        fzRect& applyTransform(const fzAffineTransform& transform);
        
        
        bool contains(const fzPoint& p) const {
            return (p.x >= origin.x &&
                    p.x <= (origin.x + size.width) &&
                    p.y >= origin.y &&
                    p.y <= (origin.y + size.height));
        }
        
        bool intersect(const fzRect& r) const;
        
        bool operator == (const fzRect& r) const {
            return origin == r.origin && size == r.size;
        }
        
        bool operator != (const fzRect& r) const {
            return !(operator == (r));
        }
        
        fzRect& operator *= (fzFloat f) {
            origin *= f;
            size *= f;
            return *this;
        }
    };

    
#pragma mark - Predefined values
    
    //! White color (255,255,255).
    static const fzColor3B fzWHITE(255,255,255);
    //! Yellow color (255,255,0).
    static const fzColor3B fzYELLOW(255,255,0);
    //! Blue color (0,0,255).
    static const fzColor3B fzBLUE(0,0,255);
    //! Green Color (0,255,0).
    static const fzColor3B fzGREEN(0,255,0);
    //! Red Color (255,0,0,).
    static const fzColor3B fzRED(255,0,0);
    //! Magenta Color (255,0,255).
    static const fzColor3B fzMAGENTA(255,0,255);
    //! Black Color (0,0,0).
    static const fzColor3B fzBLACK(0,0,0);
    //! Orange Color (255,127,0).
    static const fzColor3B fzORANGE(255,127,0);
    //! Gray Color (166,166,166).
    static const fzColor3B fzGRAY(166,166,166);
    
    
    //! fzPoint zero value.
    static const fzPoint FZPointZero(0, 0);
    //! fzPoint 3 zero value.
    static const fzPoint3 FZPoint3Zero(0, 0, 0);
    //! fzSize zero value.
    static const fzSize FZSizeZero(0, 0);
    //! fzRect zero value.
    static const fzRect FZRectZero(0, 0, 0, 0);
    
    
    //! fzAffineTransform Identity.
    static const fzAffineTransform FZAffineTransformIdentity(1, 0, 0, 1, 0, 0, 0);

#pragma mark -    
#pragma mark Opengl types
    
    //! Tex parameters.
    class fzTexParams
    {
    public:
        int	minFilter;
        int	magFilter;
        int	wrapS;
        int	wrapT;
        
        fzTexParams()
        : minFilter(0), magFilter(0), wrapS(0), wrapT(0) {}
        
        fzTexParams(int min, int mag, int wrapSs, int wrapTs)
        : minFilter(min), magFilter(mag), wrapS(wrapSs), wrapT(wrapTs) {}
    };
    
    
    //! Blend Function used for textures
    class fzBlendFunc
    {
    public:
        unsigned int src;
        unsigned int dst;
        
        //fzBlendFunc() = default;
        fzBlendFunc();

        fzBlendFunc(unsigned int source, unsigned int destination)
        : src(source), dst(destination) {}
    };
    
    
    //! Blend Function used for textures
    class fzRange
    {
    public:
        fzUInt origin;
        fzUInt size;
        
        fzRange() : origin(0), size(0) {}
        
        fzRange(fzUInt origins, fzUInt sizes)
        : origin(origins), size(sizes) {}
        
        fzUInt endIndex() const {
            return origin + size;
        }
    };

    
    //! A 32bits 2D vector
    typedef _fzVec2<float> fzVec2;

    
    //! A 32bits 3D vector
    struct fzVec3
    {
        float x;
        float y;
        float z;
    };
    
    struct fzVec4
    {
        float x;
        float y;
        float z;
        float w;
    };
    
    
    //! A 2D grid size
    struct fzGridSize
    {
        fzUInt x;
        fzUInt y;
    };

    
    //!	A 2D Quad. 4 * 2 floats
    struct fzQuad2
    {
        fzVec2	tl;
        fzVec2	tr;
        fzVec2	bl;
        fzVec2	br;
    };
    
    
    //!	A 3D Quad. 4 * 3 floats
    struct fzQuad3
    {
        fzVec3 bl;
        fzVec3 br;
        fzVec3 tl;
        fzVec3 tr;
    };
    
    
    
    //! a Point with a vertex point, a tex coord point and a color 4B
    struct _fzV4_T2_C4
    {
        fzVec4      vertex;   // 0  - 16
        fzVec2      texCoord; // 16 - 24
        fzColor4B   color;    // 24 - 28 (28 = 4*7 = 32bits aligned)
    };
    
    
    //! 4 ccVertex3FTex2FColor4B
    struct fzV4_T2_C4_Quad
    {
        _fzV4_T2_C4	bl;
        _fzV4_T2_C4	br;
        _fzV4_T2_C4	tl;
        _fzV4_T2_C4	tr;
    };
    
    
    //! a Point with a vertex point, a tex coord point and a color 4B
    struct _fzC4_T2_V2
    {
        fzColor4B   color;
        fzVec2      texCoord;
        fzVec2      vertex;
    };
    
    
    //! 4 ccVertex2FTex2FColor4B Quad
    struct fzC4_T2_V2_Quad
    {
        _fzC4_T2_V2 bl; // 32
        _fzC4_T2_V2 br; // 64
        _fzC4_T2_V2 tl; // 86
        _fzC4_T2_V2 tr; // 108
    };
    
    
    struct _fzT2_V2
    {
        fzVec2 texCoord;
        fzVec2 vertex;
    };
    
    
    //! 4 ccVertex3FTex2FColor4B
    struct _fzT2_V2_Quad
    {
        _fzT2_V2 bl;
        _fzT2_V2 br;
        _fzT2_V2 tl;
        _fzT2_V2 tr;
    };
    
    
}
#endif
