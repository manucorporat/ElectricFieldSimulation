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

// BASE
#include "FZOSW.h"
#include "FZCommon.h"
#include "FZAllocator.h"
#include "FZTypes.h"
#include "FZConfig.h"
#include "FZMacros.h"
#include "FZProtocols.h"


// RENDERING
#include "FZTextureAtlas.h"
#include "FZTexture2D.h"
#include "FZGLProgram.h"
#include "FZGLState.h"
#include "FZGrabber.h"
#include "FZPrimitives.h"


// MANAGERS
#include "FZActionManager.h"
#include "FZAnimationCache.h"
#include "FZDataStore.h"
#include "FZDirector.h"
#include "FZDeviceConfig.h"
#include "FZEventManager.h"
#include "FZFontCache.h"
#include "FZResourcesManager.h"
#include "FZScheduler.h"
#include "FZShaderCache.h"
#include "FZSpriteFrameCache.h"
#include "FZTextureCache.h"
#include "FZPerformManager.h"


// ACTIONS
#include "FZAction.h"
#include "FZActionInstant.h"
#include "FZActionInterval.h"
#include "FZActionEase.h"
#include "FZActionCamera.h"
#include "FZActionEase.h"


// NODES
#include "FZSprite.h"
#include "FZSpriteBatch.h"
#include "FZLightSystem.h"
#include "FZLabel.h"
#include "FZParticleSystem.h"
#include "FZParticleSystemQuad.h"
#include "FZParticleExamples.h"
#include "FZLayer.h"
#include "FZMenu.h"
#include "FZMenuItem.h"
#include "FZScene.h"
#include "FZCamera.h"
#include "FZNode.h"
#include "FZRenderTexture.h"
#include "FZTMXTiledMap.h"
#include "FZTMXLayer.h"


// OTHERS
#include "FZIO.h"
#include "FZFont.h"
#include "FZEvent.h"
#include "FZFilter.h"
#include "FZGrid.h"
#include "FZAnimation.h"
#include "FZSpriteFrame.h"
#include "FZConsole.h"


#pragma mark - HELPER MACROS

// HELPER MACROS FOR DEVELOPERS
#define FZ_NEEDS(__VERSION__) ( FORZE::DeviceConfig::Instance().getSystemVersion() >= fzVersion(__VERSION__) )
#define FZ_USER_INTERFACE_IDIOM() FORZE::DeviceConfig::Instance().getUserInterfaceIdiom()
#define FZ_CANVAS_SIZE() FORZE::Director::Instance().getCanvasSize()
#define FZ_VIEW_PORT() FORZE::Director::Instance().getViewPort()
