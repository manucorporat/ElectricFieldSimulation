// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZSPRITE_H_INCLUDED__
#define __FZSPRITE_H_INCLUDED__
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

#include "FZNode.h"
#include "FZProtocols.h"
#include "FZSpriteFrame.h"
#include STL_STRING


using namespace STD;

#pragma mark Sprite

namespace FORZE {
    
    enum {
        kFZSpriteIndexNotInitialized = 0xffffffff
    };
    
    class SpriteBatch;


    
    /** Sprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) )
     *
     * Sprite can be created with an image, or with a sub-rectangle of an image.
     *
     * If the parent or any of its ancestors is a SpriteBatch then the following features/limitations are valid
     *	- Features when the parent is a SpriteBatch:
     *		- MUCH faster rendering, specially if the SpriteBatch has many children. All the children will be drawn in a single batch.
     *
     *	- Limitations
     *		- Camera is not supported yet (eg: OrbitCamera action doesn't work)
     *		- GridBase actions are not supported (eg: Lens, Ripple, CCTwirl)
     *		- The Alias/Antialias property belongs to SpriteBatch, so you can't individually set the aliased property.
     *		- The Blending function property belongs to SpriteBatch, so you can't individually set the blending function property.
     *		- Parallax scroller is not supported, but can be simulated with a "proxy" sprite.
     *
     *  If the parent is an standard Node, then Sprite behaves like any other Node:
     *    - It supports blending functions
     *    - It supports aliasing / antialiasing
     *    - But the rendering will be slower: 1 draw per children.
     *
     * The default anchorPoint in Sprite is (0.5, 0.5).
     */
    
    class TextureAtlas;
    class Sprite : public Node, public Protocol::Color, public Protocol::Texture, public Protocol::Blending
    {
        friend class SpriteBatch;
        friend class TMXLayer;
        
    private:
        char m_mode;

    protected:
        
        union{
            /** A: self rendering mode */
            struct {
                Texture2D *p_texture;
                fzVec4 m_finalVertices[4];
            } A;
            
            /** B: batch rendering mode */
            struct {
                fzHonorTransform m_honorTransform;
                SpriteBatch *p_batchNode;
                fzV4_T2_C4_Quad *p_currentQuad;
            } B;
        } mode;
        

        fzBlendFunc m_blendFunc;

        fzVec2 m_vertices[4];
        fzVec2 m_texCoords[4];

        // SHARED DATA
        
        // rect that defines the portion of the texture that is rendered.
        fzRect m_textureRect;
        
        // tells if the portion of texture that is rendered is rotated (used by Zwoptex)
        bool m_rectRotated : 1;
        
        // untransformed offset Position (used by Zwoptex)
        fzPoint	m_offset;
        
        // transformed offset position
        fzPoint m_unflippedOffset;
        
        // relative alpha
        unsigned char m_alpha;
        
        // 3bytes color
        fzColor3B	m_color;
        
        // is x axis flipped
        bool m_flipX : 1;
        
        // is y axis flipped
        bool m_flipY : 1;
        

        void updateTextureCoords(fzRect rect);
        void draw();
        
        /** tells or not the Sprite is rendered using a SpriteBatch */
        void useBatchRender(SpriteBatch* batch);
        
        
        /** The batch render uses this method to updates the quad according the transform values
         * position, rotation, scale ...
         */
        bool updateTransform(fzV4_T2_C4_Quad **quadp);
        
        virtual void insertChild(Node*) override;
        

    public:
        //! Constructs a void Sprite.
        Sprite();
        
        //! Constructs a sprite with a texture.
        //! The rect used will be the size of the texture.
        //! The offset will be (0,0).
        explicit Sprite(Texture2D* texture);
        
        
        //! Constructs a sprite with a Texture2D and a rect in points.
        //! The offset will be (0,0).
        //! @param rect defines the portion of the Texture2D to be rendered by the Sprite.
        Sprite(Texture2D* texture, const fzRect& rect);
        
        
        //! Constructs a sprite with an image filename.
        //! The offset will be (0,0).
        Sprite(const string& name);
        
        
        //! Constructs a sprite with an image filename, and a rect.
        //! The offset will be (0,0).
        //! @param rect defines the portion of the Texture2D to be rendered by the Sprite.
        Sprite(const string& filename, const fzRect& rect);
        
        
        //! Constructs a sprite with a rect in points.
        //! @param rect defines the portion of the Texture2D to initialize the sprite.
        //! @warning this method is only a good practice if the sprite will be attached to a SpriteBatch.
        Sprite(const fzRect& rect);
        
        
        //! Constructs an sprite from a fzSpriteFrame.
        Sprite(const fzSpriteFrame& spriteFrame);
        
        // Destructor
        ~Sprite();

        
        //! Configures the sprite to use self-rendering.
        void useSelfRender();
        
        
        //! Sets the sprite's texture.
        //! @param texture if this param is NULL the current Texture2D will be released.
        //! @warning this method only can be used when the sprite is using self-rendering.
        virtual void setTexture(Texture2D *texture) override;
        
        
        //! Returns the Texture2D used by the sprite.
        virtual Texture2D* getTexture() const override;
        
        
        //! Updates the texture rect of the sprite.
        //! This method complex method is used by zwoptex.
        //! @see setTextureRect()
        void setTextureRect(const fzRect& rect, const fzSize& untrimmedSize, bool rotated = false);
        
        
        //! Updates the texture rect of the sprite.
        //! Offset is (0, 0), no rotated
        //! @see setTextureRect()
        void setTextureRect(const fzRect& rect) {
            setTextureRect(rect, rect.size, false);
        }
        
        
        //! Configures the sprite automatically giving a fzSpriteFrame.
        void setDisplayFrame(const fzSpriteFrame& spriteFrame);
        
        
        //! Configures the Sprite automatically giving the frame name.
        void setDisplayFrame(const char *spriteFrameName);
        
        
        //! Returns the rect of the sprite in points.
        const fzRect& getTextureRect() const {
            return m_textureRect;
        }
        
        
        /** whether or not the sprite is flipped horizontally. 
         It only flips the texture of the sprite, and not the texture of the sprite's children.
         Also, flipping the texture doesn't alter the anchorPoint.
         If you want to flip the anchorPoint too, and/or to flip the children too use:
         
         sprite.scaleX *= -1;
         */
        void setFlipX(bool);
        bool getFlipX() const {
            return m_flipX;
        }
        
        
        /** whether or not the sprite is flipped vertically.
         It only flips the Texture2D of the sprite, and not the Texture2D of the sprite's children.
         Also, flipping the texture doesn't alter the anchorPoint.
         If you want to flip the anchorPoint too, and/or to flip the children too use:
         
         sprite.scaleY *= -1;
         */
        void setFlipY(bool);
        bool getFlipY() const {
            return m_flipY;

        }
        
        
        bool isRectRotated() const {
            return m_rectRotated;
        }
        
        
        //! Sets the alpha channel (no recursive opacity).
        //! @see getAlpha()
        //! @see setOpacity()
        virtual void setAlpha(unsigned char a) {
            if(a != m_alpha) {
                m_alpha = a;
                makeDirty(kFZDirty_color);
            }
        }
        
        
        //! Returns the alpha channel (no recursive opacity).
        //! @see setAlpha()
        //! @see getOpacity()
        unsigned char getAlpha() const {
            return m_alpha;
        }

        
        //! Returns the fzSpriteFrame based in the Sprite config.
        //! Texture2D, rect, size...
        fzSpriteFrame getDisplayFrame() const;
        
        
        //! Returns the sprite's vertices.
        void getVertices(float *vertices) const;
        
        
        //! Sets a weak reference to the SpriteBatch that renders the Sprite.
        //! @see getBatch()
        virtual void setBatch(SpriteBatch*);
        
        
        //! Returns a weak reference to the SpriteBatch that renders the Sprite.
        //! @see setBatch()
        SpriteBatch* getBatch() const;
        
        
        //! Returns a weak reference to the TextureAtlas used by the SpriteBatch.
        TextureAtlas* getTextureAtlas() const;
        

        /** whether or not to transform according to its parent transfomrations.
         Useful for health bars. eg: Don't rotate the health bar, even if the parent rotates.
         IMPORTANT: Only valid if it is rendered using an SpriteBatch.
         */
        void setHonorTransform(fzHonorTransform);
        fzHonorTransform getHonorTransform() const;
        
        
        //! [ZWOPTEX SUPPORT] @return offset position
        const fzPoint& getOffsetPosition() const {
            return m_offset;
        }
        
        // Redefined
        virtual void setColor(const fzColor3B& c) override;
        virtual const fzColor3B& getColor() const override;
        virtual void setBlendFunc(const fzBlendFunc&) override;
        virtual const fzBlendFunc& getBlendFunc() const override;
        virtual void updateStuff() override;
    };
}
#endif // 
