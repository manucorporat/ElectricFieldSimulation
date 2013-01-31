// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZNODE_H_INCLUDED__
#define __FZNODE_H_INCLUDED__
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

#include "FZPlatforms.h"
#include "FZTypes.h"
#include "FZLifeCycle.h"
#include "FZAutoList.h"
#include "FZSelectors.h"
#include "FZMath.h"
#include "FZDirector.h"

namespace FORZE {
    
    /** @enum fzDirtyFlags
     * flags used internally by FORZE to prevent unneeded tasks.
     */
    enum fzDirtyFlags
    {
        kFZDirty_transform_relative = 1 << 0,
        kFZDirty_transform_absolute = 1 << 1,
        kFZDirty_transform_inverse  = 1 << 2,
        kFZDirty_opacity            = 1 << 3,
        kFZDirty_color              = 1 << 4,
        kFZDirty_texcoords          = 1 << 5,
        kFZDirty_opengl             = 1 << 6,
        
        kFZDirty_transform          = kFZDirty_transform_absolute | kFZDirty_transform_relative | kFZDirty_transform_inverse,
        kFZDirty_recursive          = kFZDirty_transform_absolute | kFZDirty_opacity,
        kFZDirty_all                = 0xff
    };
    

    /**
     Whether or not an FZ::Sprite will rotate, scale or translate with it's parent.
     Useful in health bars, when you want that the health bar translates with it's parent but you don't want it to rotate with its parent.
     */
    enum fzHonorTransform
    {
        //! Translate with it's parent
        FZ_HONOR_TRANSFORM_TRANSLATE    =  1 << 0,
        //! Rotate with it's parent
        FZ_HONOR_TRANSFORM_ROTATE       =  1 << 1,
        //! Scale with it's parent
        FZ_HONOR_TRANSFORM_SCALE		=  1 << 2,
        //! Skew with it's parent
        FZ_HONOR_TRANSFORM_SKEW         =  1 << 3,
        
        //! All possible transformation enabled. Default value.
        FZ_HONOR_TRANSFORM_ALL          =  FZ_HONOR_TRANSFORM_TRANSLATE | FZ_HONOR_TRANSFORM_ROTATE | FZ_HONOR_TRANSFORM_SCALE | FZ_HONOR_TRANSFORM_SKEW
        
    };
    
    
    enum {
        NODE_BACK = INTPTR_MIN,
        NODE_TOP = INTPTR_MAX,
        kFZNodeTagInvalid = -1,
        kFZNodeDefaultPadding = 30
    };
    
    
    class FBOTexture;
    class GridBase;
    class Filter;
    class Camera;
    class Action;
    class GLProgram;    
    
    /** Node is the main element.
     * Everything to be rendered inside FORZE must be a subclass of Node.
     */
    class Node : public fzListItem, public LifeCycle
    {
        friend class NodeManager;
        friend class NodeList;
        friend class Sprite;
        friend class Director;
        
    private:
        bool    m_isRunning;
        bool    m_isRelativeAnchorPoint;
        
    protected:
        
        // is visible
        bool    m_isVisible;

        // dirty tags
        unsigned char m_dirtyFlags;
        
        // cached absolute transform matrix
        fzMat4 m_transformMV;
        
        // z-order value
        fzInt   m_zOrder;
        fzInt   m_realZOrder;
        
        // a tag
        fzInt   m_tag;
        
        // rotation angle
        fzFloat m_rotation;	
        
        // scaling factors
        fzFloat m_scaleX, m_scaleY;
        
        // openGL real Z vertex
        fzFloat m_vertexZ;
        
        // opacity
        fzFloat m_opacity;
        
        // cached opacity 
        fzFloat m_cachedOpacity;
        
        // skew angles
        fzFloat m_skewX, m_skewY;
        
        // camera management
        Camera *p_camera;
        
        FBOTexture *p_FBO;
        
#if FZ_GL_SHADERS
        // filter management
        Filter *p_filter;
        GLProgram *p_glprogram;
#endif
        
        // weak ref to parent
        Node    *p_parent;
        
        // grid management
        GridBase *p_grid;
        
        // user data field
        void    *p_userData;
        
        // array of children
        AutoList m_children;
        
        // position of the node
        fzPoint  m_position;
        
        // anchor point in points
        fzPoint  m_anchorPointInPoints;	
        
        // anchor point normalized
        fzPoint  m_anchorPoint;	
        
        // untransformed size of the node
        fzSize  m_contentSize;
        
        // transform matrix
        fzAffineTransform m_transform;
        
        
        //! Resumes all scheduled selectors and actions.
        void resumeSchedulerAndActions();
        
        
        //! Pauses all scheduled selectors and actions.
        void pauseSchedulerAndActions();
        

#pragma mark - Internal children management

        //! Interal protocol to reconfigure a child before removing
        virtual bool detachChild(Node*, bool);
        
        
        //! Internal protocol to insert a child.
        virtual void insertChild(Node*);
      
        
        //! Reorders a child (Node) according to a new z value.
        void reorderChild(Node*);
        
        
        //! Returns the child(position) giving a zOrder.
        fzListItem* indexForZOrder(fzInt z);
        
        
        //! Sets parent.
        void setParent(Node* p) {
            p_parent = p;
        }
        
        //! Opacity protocol.
        fzFloat getCachedOpacity() const {
            return m_cachedOpacity;
        }
        
        void allocFBO();

        
        void internalVisit();
        void internalRender();        
        
        //! Override this method to draw your own node.
        //! If you enable any other GL state, you should disable it after drawing your node
        virtual void updateStuff();

        
        //! Override this method to draw your own node.
        //! If you enable any other GL state, you should disable it after drawing your node.
        virtual void render(unsigned char);
        
        
        //! Override this method to draw your own node.
        //! If you enable any other GL state, you should disable it after drawing your node.
        virtual void draw();
        
        
        virtual void updateLayout();
        
    
    public:
        //! Constructs a blank node.
        explicit Node();
        ~Node();
        

#pragma mark - Setters
        
        void makeDirty(unsigned char flags) {
            m_dirtyFlags |= flags;
#if FZ_RENDER_ON_DEMAND
            Director::Instance().m_sceneIsDirty = true;
#endif
        }
        
        //! Tells this object whether to be visible or not.
        void setIsVisible(bool v) {
            m_isVisible = v;
            makeDirty(0);
        }
        
        
        //! Sets the same scale factor for both x and y coordinates.
        void setScale(fzFloat s) {
            m_scaleX = m_scaleY = s;
            makeDirty(kFZDirty_transform);
        }
        
        
        //! Sets the x scale.
        void setScaleX(fzFloat sx) {
            m_scaleX = sx;
            makeDirty(kFZDirty_transform);
        }
        
        
        //! Sets the y scale.
        void setScaleY(fzFloat sy) {
            m_scaleY = sy;
            makeDirty(kFZDirty_transform);
        }
        
        
        //! Sets the node's rotation in degrees. Clockwise direction.
        void setRotation(fzFloat degrees) {
            if(m_rotation != degrees) {
                m_rotation = degrees;
                makeDirty(kFZDirty_transform);
            }
        }
        
        
        //! Sets the relative node's position giving a fzPoint.
        void setPosition(const fzPoint& newPosition) {
            m_position = newPosition;
            makeDirty(kFZDirty_transform);
        }
        
        
        //! Sets the relative node's position giving two scalars.
        void setPosition(fzFloat x, fzFloat y) {
            setPosition(fzPoint(x, y));
        }
        
        
        //! Tells if the anchor point affect the node's position.
        void setIsRelativeAnchorPoint(bool rAP) {
            m_isRelativeAnchorPoint = rAP;
            makeDirty(kFZDirty_transform);
        }
        
        
        //! Sets the relative center of transform giving a fzPoint.
        void setAnchorPoint(const fzPoint& normalized);
        
        
        //! Sets the relative center of transform giving two scalars.
        void setAnchorPoint(fzFloat x, fzFloat y) {
            setAnchorPoint(fzPoint(x, y));
        }
        
        
        //! Sets the absolute center of transform (in points).
        void setAnchorPointInPoints(const fzPoint& points);
        
        
        //! Sets the node's content size, something like bounds (width and height).
        void setContentSize(const fzSize& points);
        
        
        void setContentSize(fzFloat width, fzFloat height) {
            setContentSize(fzSize(width, height));
        }
        
        
        //! Sets the z vertex.
        //! Due to the fact that FORZE is a 2D engine the Z vertex is separared from the "position" property.
        void setVertexZ(fzFloat z) {
            m_vertexZ = z;
            m_dirtyFlags |= kFZDirty_transform;
        }
        
        
        //! Sets the recursive opacity. This property will affect all children.
        //! @param normalizedOpacity [0, 1].
        void setOpacity(fzFloat normalizedOpacity);
        
        
        //! Sets the per-pixel-filter effect applied as post-rendering technique to all Opengl stuff rendered inside the node (INCLUDING children).
        //! Filters will be make your node opaque so it only should be used as post-processing effect for just a layer (like gameplay) or in the whole scene.
        void setFilter(Filter *filter);
        
        
        //! Sets the node's tag.
        void setTag(fzInt tag) {
            m_tag = tag;
        }
        
        
        void setName(const char* name);
        
        //! Sets an optional user-defined pointer.
        //! Useful to link the node with an external system, like a phsics system.
        //! @see getUserData()
        void setUserData(void* data) {
            p_userData = data;
        }
        
        
#pragma mark - Getters
        
        //! Returns if the node is visible or not.
        bool isVisible() const {
            return m_isVisible;
        }
        
        
        //! Returns the scale factor if both factors (x, y) are the same.
        fzFloat getScale() const;
        
        
        //! Returns the x scale.
        fzFloat getScaleX() const {
            return m_scaleX;
        }
        
        //! Returns the y scale.
        fzFloat getScaleY() const {
            return m_scaleY;
        }
        
        
        //! Returns the node's rotation in degress.
        fzFloat getRotation() const {
            return m_rotation;
        }
        
        //! Returns the list of children contained in a FORZE::Autolist.
        AutoList& getChildren() {
            return m_children;
        }
        
        
        //! Returns the relative node's position in points.
        const fzPoint& getPosition() const {
            return m_position;
        }
        
        
        //! Returns if the anchor point affect the node's position.
        bool isRelativeAnchorPoint() const {
            return m_isRelativeAnchorPoint;
        }
        
        
        //! Returns the anchor point.
        const fzPoint& getAnchorPoint() const {
            return m_anchorPoint;
        }
        
        
        //! Returns the absolute center of transform (in points).
        const fzPoint& getAnchorPointInPoints() const {
            return m_anchorPointInPoints;
        }
        
        
        //! Returns the node's content size, (width and height).
        const fzSize& getContentSize() const {
            return m_contentSize;
        }
        
        
        //! Returns the node's z vertex.
        //! Default value: 0
        fzFloat getVertexZ() const {
            return m_vertexZ;
        }
        
        
        //! Returns the recursive opacity.
        fzFloat getOpacity() const {
            return m_opacity;
        }
        
        
        //! Sets the value used by FORZE to order the rendering of all node siblings, higher value will be rendered over smaller ones.
        void setZOrder(fzInt);
        
        
        //! Returns the value used by FORZE to order the rendering of all node siblings, higher value will be rendered over smaller ones.
        fzInt getZOrder() const {
            return m_zOrder;
        }
        
        
        //! Returns the node's tag.
        //! @see getChildByTag()
        //! @see removeChildByTag()
        fzInt getTag() const {
            return m_tag;
        }
        
        
        //! Returns an optional user-defined pointer.
        //! @see setUserData()
        void* getUserData() const {
            return p_userData;
        }
        
        
        //! Returns if the node is running.
        //! @see onEnter()
        //! @see onExit()
        bool isRunning() const {
            return m_isRunning;
        }
        
        
        //! Returns the node's parent.
        Node* getParent() const {
            return p_parent;
        }
        
        
        //! Returns the node's camera.
        Camera* getCamera();
        
        
        void setSkewX(fzFloat);
        fzFloat getSkewX() const;
        
        
        void setSkewY(fzFloat);
        fzFloat getSkewY() const;
        
        
#pragma mark - Children management
        
        //! Adds a child to the container.
        //! @param node to be added.
        //! @param zOrder this value is used as rendering priority
        void addChild(Node* node, fzInt zOrder);
        void addChild(Node* node);
        
        
        //! Remove itself from its parent node.
        //! @param cleanup all running actions.
        //! @see removeChild()
        void removeFromParent(bool cleanup = true);
        
        
        //! Removes a child from the container.
        //! @param child to remove.
        //! @param cleanup all running actions.
        //! @see removeChildByTag()
        void removeChild(Node* child, bool cleanup = true);

        
        //! Removes a child from the container by tag value.
        //! @param tag 's child to remove.
        //! @param cleanup all running actions.
        //! @see removeChild()
        void removeChildByTag(fzInt tag, bool cleanup = true);
        
        
        //! Removes a child from the container by tag value.
        //! @param tag 's child to remove.
        //! @param cleanup all running actions.
        //! @see removeChild()
        void removeChildByName(const char* name, bool cleanup = true);
        
        
        //! Removes all children.
        //! @param cleanup all running actions.
        void removeAllChildren(bool cleanup = true);
        
        
        //! Gets a child from the container given its tag.
        //! @param tag used to search the child.
        //! @return returns a Node object.
        //! @see setTag()
        //! @see getTag()
        Node* getChildByTag(fzInt tag);
        
        
        //! Gets a child from the container given its tag.
        //! @param name used to search the child.
        //! @return returns a Node object.
        //! @see setTag()
        //! @see getTag()
        Node* getChildByName(const char* name);
        
        
        //! Stops all running actions and schedulers.
        virtual void cleanup();
        
        
#pragma mark - Scene management
        
        //! Callback that is called every time the Node enters the 'stage'.
        //! In transitions, this callback is called when the transition starts.
        //! @see onExit()
        //! @see isRunning()
        virtual void onEnter();
        
        
        //! Callback that is called every time the Node leaves the 'stage'.
        //! In transitions, this callback is called when the transition finishes.
        //! @see onEnter()
        //! @see isRunning()
        virtual void onExit();
        
        
#pragma mark - Schedule management
        
        virtual void update(fzFloat);

        //! Schedules a custom selector with an calling interval.
        //! @param interval cannot be negative.
        //! @see unschedule()
        //! @see unscheduleAllSelectors()
        void schedule(const SELECTOR_FLOAT selector, fzFloat interval);
        
        
        //! Schedules the update(fzFloat) selector.
        //! Interval time is 0 by default
        //! @see unschedule()
        void schedule();
        
        
        //! Unschedules a custom selector.
        //! @see schedule()
        void unschedule(const SELECTOR_FLOAT selector);
        
        
        //! Unschedules the update(fzFloat) selector.
        //! @see schedule()
        void unschedule();
        
        
    protected:
        //! Unschedule the current schedule.
        void unscheduleCurrent();
        
    public:
        //! Unschedules all selectors.
        void unscheduleAllSelectors();
        
        
#pragma mark - Actions management
        
        //! Executes an action.
        Action* runAction(Action *action);
        
        
        //! Returns an action from the container given its tag.
        Action* getActionByTag(fzInt tag);
        
        
        //! Removes the specified action from the run loop.
        void stopAction(Action *action);
        
        
        //! Removes an action from the run loop given its tag.
        void stopActionByTag(fzInt tag);
        
        
        //! Removes all actions from the container.
        void stopAllActions();
        
        
        //! Retuns the numbers of actions that are running plus the ones that are schedule to run.
        fzUInt numberOfRunningActions();
        
        
#pragma mark - Rendering
        
        //! Recursive method that visit its children and draw them.
        void visit();
        
        
        //! Returns a "global" axis aligned bounding box of the node in points.
        //! The returned box is in absolute position.
        fzRect getBoundingBox();
        
        
        //! Returns a "global" axis aligned bounding box of the node in points.
        //! The returned box is relative only to its parent.
        fzRect getLocalBoundingBox();


#pragma mark - Miscelaneous
        
        //! This function align vertically the menu items.
        void alignVertically(fzFloat padding, const fzPoint& center, const fzRange& range, bool (*func)(Node*));
        void alignVertically(fzFloat padding, const fzPoint& center, const fzRange& range);
      
      
        //! This function align horizontally the menu items.
        void alignHorizontally(fzFloat padding, const fzPoint& center, const fzRange& range, bool (*func)(Node*));
        void alignHorizontally(fzFloat padding, const fzPoint& center, const fzRange& range);
      
        
        //! This function align vertically the menu items.
        void alignChildrenVertically(fzFloat padding = kFZNodeDefaultPadding);
        
        
        //! This function align horizontally the menu items.
        void alignChildrenHorizontally(fzFloat padding = kFZNodeDefaultPadding);
      
        
#pragma mark Transforms
        
        //! Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
        const fzAffineTransform& getNodeToParentTransform();
        
        
        //! Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
        fzAffineTransform getParentToNodeTransform();
        
        
        //! Return the world affine transform matrix.
        fzAffineTransform getNodeToWorldTransform();
        
        
        //! Returns the inverse world affine transform matrix.
        fzAffineTransform getWorldToNodeTransform();
        
        
        //! Converts a Point to node (local) space coordinates.
        const fzPoint& convertToNodeSpace(fzPoint);
        
        
        //! Converts a Point to world space coordinates. The result is in Points.
        const fzPoint& convertToWorldSpace(fzPoint);
        
        
        /** Converts a Point to node (local) space coordinates. The result is in Points.
         treating the returned/received node point as anchor relative.
         */
        fzPoint convertToNodeSpaceAR(const fzPoint&);
        
        
        /** Converts a local Point to world space coordinates.The result is in Points.
         treating the returned/received node point as anchor relative.
         */
        fzPoint convertToWorldSpaceAR(const fzPoint&);
        
                
        //! Sets the GLProgram used by the node to render his opengl stuff (NOT INCLUDING children).
        //! This parammeter doesn't make sense in void elements such as "Node", "Scene" or "Layer".
        //! @see getGLProgram()
        void setGLProgram(GLProgram*);
        
        
        //! Sets the GLProgram by a tag value
        void setGLProgram(fzUInt programKey);
        
        
        //! Returns the GLProgram.
        GLProgram* getGLProgram() const;
    };
}
#endif
