// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZPRIMITIVES_H_INCLUDED__
#define __FZPRIMITIVES_H_INCLUDED__
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

#include "FZTypes.h"

/**
 @file
 Drawing OpenGL ES primitives.
 - fzDrawPoint
 - fzDrawLine
 - fzDrawPoly
 - fzDrawCircle
 - fzDrawQuadBezier
 - fzDrawCubicBezier
 
 You can change the color, width and other property by calling the
 glColor4ub(), glLineWidth(), glPointSize().
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch.
 */

namespace FORZE {
    
    //! Changes the color of the primitives.
    void fzGLColor(const fzColor4F& color);
    
    
    //! Best way to changes the line width.
    void fzGLLineWidth(fzFloat points);

    
    //! Draws a point given x and y coordinate measured in points.
    void fzDrawPoint( const fzVec2& point );
    
    
    //! Draws an array of points.
    void fzDrawPoints( const fzVec2 *points, fzUInt numberOfPoints );
    
    
    //! Draws a line given the origin and destination point.
    void fzDrawLine( const fzVec2& origin, const fzPoint& destination );
    
    
    //! Draws an array of lines.
    void fzDrawLines( const fzVec2 *vertices, fzUInt numOfVertices);
    
    
    //! Draws a poligon given a pointer to the coordiantes and the number of vertices.
    void fzDrawPoly( const fzVec2 *vertices, fzUInt numOfVertices, bool closePolygon );
    
    
    void fzDrawRect( const fzRect& rect );

    //! Draws an shape given a pointer to CGPoint coordiantes and the number of vertices.
    void fzDrawShape( const fzVec2 *vertices, fzUInt numOfVertices);
    
    
    //! Draws a circle given the center, radius and number of segments.
    void fzDrawCircle( const fzVec2& center, fzFloat radius, fzFloat angle, fzUInt segments, bool drawLineToCenter);
    
    
    //! Draws a quad bezier path.
    void fzDrawQuadBezier(const fzVec2& origin, const fzVec2& c, const fzVec2& destination, fzUInt segments);
    
    
    //! Draws a cubic bezier path.
    void fzDrawCubicBezier(const fzVec2& origin, const fzVec2& c1, const fzVec2& c2, const fzVec2& destination, fzUInt segments);

}
#endif
