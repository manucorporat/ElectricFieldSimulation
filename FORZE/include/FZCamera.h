// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZCAMERA_H_INCLUDED__
#define __FZCAMERA_H_INCLUDED__
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

#include "FZMath.h"


namespace FORZE {
    
    class Node;
    /**
     A Camera is used in every Node.
     Useful to look at the object from different views.
     The OpenGL gluLookAt() function is used to locate the
     camera.
     
     If the object is transformed by any of the scale, rotation or
     position attributes, then they will override the camera.
     
     IMPORTANT: Either your use the camera or the rotation/scale/position properties. You can't use both.
     World coordinates won't work if you use the camera.
     
     Limitations:
     
     - Some nodes, like ParallaxNode, Particle uses world node coordinates, and they won't work properly if you move them (or any of their ancestors)
     using the camera.
     
     - It doesn't work on batched nodes like Sprite objects when they are parented to a SpriteBatch object.
     
	 - It is recommended to use it ONLY if you are going to create 3D effects. For 2D effecs, use the action Follow or position/scale/rotate.
     */
    class Camera
    {
    private:
        bool m_isDirty;

        fzPoint3 m_eye;
        fzPoint3 m_center;
        fzPoint3 m_up;
        Node *p_parent;
        fzAffineTransform m_lookupTransform;
        
        
    public:
        static const fzFloat defaultEyeZ;

        //! Constructs a default ortho camera.
        Camera(Node *parent);
        
        
        //! Sets if the camera values are dirty.
        //! @see getDirty()
        void setDirty(bool);
        
        
        //! Returns if the camera values are dirty.
        //! @see setDirty()
        bool isDirty() const;
        
        
        //! Restores the camera to his default position.
        void restore();
        
        
        //! Sets the camera using gluLookAt using its eye, center and up_vector.
        const fzAffineTransform& getLookupMatrix();

        
        //! Sets the eye values in points.
        //! @see getEye()
        void setEye(const fzPoint3& eye);
        
        
        //! Sets the center values in points.
        //! @see getCenter()
        void setCenter(const fzPoint3& center);

        
        //! Sets the up values.
        //! @see getUp()
        void setUp(const fzPoint3& up);
        
        
        //! Returns the eye vector values in points.
        //! @see setEye()
        const fzPoint3& getEye() const;

        
        //! Returns the center vector values in points.
        //! @see setCenter()
        const fzPoint3& getCenter() const;

        
        //! Returns the up vector values.
        //! @see setUp()
        const fzPoint3& getUp() const;
    };
}
#endif
