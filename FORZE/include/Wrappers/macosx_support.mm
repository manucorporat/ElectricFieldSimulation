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

#include "macosx_support.h"

#if defined(FZ_OS) && (FZ_OS == kFZPLATFORM_MAC)

#include <sys/types.h>
#include <sys/sysctl.h>
#include <OpenGL/OpenGL.h>
#include <CoreGraphics/CoreGraphics.h>
#include "../FZEventManager.h"
#include "../FZDeviceConfig.h"
#include "../FZDirector.h"
#include "../FZMacros.h"

using namespace FORZE;

namespace FORZE {
    
#pragma mark - OS WRAPPER communication protocol

    void OSW::init(int argc, char *argv[])
    {
        ////////////////////////////////////////////////
        // CUSTOM IMPLEMENTATION OF NSApplicationMain //
        ////////////////////////////////////////////////
        @autoreleasepool {
            
            NSApplication *app = [NSApplication sharedApplication];
            
            
            // Try to load the default Info.plist interface
            NSDictionary* infoDictionary = [[NSBundle mainBundle] infoDictionary];
            NSString *principalClass = [infoDictionary objectForKey:@"NSPrincipalClass"];
            
            if(principalClass == nil || ![NSBundle loadNibNamed:principalClass owner:app])
            {
                // we could not load the NIB
                [app setDelegate:[[_FZOSWRAPPER alloc] init]];
                {
                    NSMenu *menubar = [[[NSMenu alloc] init] autorelease];
                    NSMenuItem *appMenuItem = [[NSMenuItem new] autorelease];
                    [menubar addItem:appMenuItem];
                    [app setMainMenu:menubar];
                    
                    NSMenu *appMenu = [[[NSMenu alloc] init] autorelease];
                    NSMenuItem *quitMenuItem = [[[NSMenuItem alloc] initWithTitle:@"Quit app"
                                                                           action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
                    [appMenu addItem:quitMenuItem];
                    [appMenuItem setSubmenu:appMenu];
                }
                
            }else{
                // the NIB was loaded, now we have to check if the NIB is compatible with FORZE.
                // FORZE needs to catch all application events, so the app delegate must be the OSWrapper.
                if(![[app delegate] isKindOfClass:[_FZOSWRAPPER class]])
                    FZ_RAISE("OS Wrapper: Fatal error. The app delegate specified in the NIB must be subclass of \"_FZOSWRAPPER\"");
            }        
            
            [[NSApplication sharedApplication] run];
        }
    }
    
    
    void OSW::startRendering(fzFloat interval)
    {
        [(_FZOSWRAPPER*)Instance() startRendering:interval];
    }
    
    
    void OSW::stopRendering()
    {
        [(_FZOSWRAPPER*)Instance() stopRendering];
    }
    
    
    void OSW::updateWindow()
    {
        [(_FZOSWRAPPER*)Instance() updateWindow];
    }
    
    
    void OSW::configEvents(uint16_t dirtyFlags, uint16_t flags)
    {
        [(_FZOSWRAPPER*)Instance() updateEvents:dirtyFlags flags:flags];
    }
    
    
    void OSW::setEventsInterval(fzFloat interval)
    {
        // CONSTANT TIME EVENTS DON'T EXIST IN OSX
        // Nothing to do here :)
    }
    
    
    void OSW::setOrientation(int orientation)
    {
        // ORIENTATION DOESN'T MAKE SENSE IN OSX
        // Nothing to do here :)
    }
    
    
#pragma mark Device
    
    bool fzOSW_getSystemVersion(char *v, fzUInt maxLength)
    {
        SInt32 major, minor, bugFix;
        Gestalt(gestaltSystemVersionMajor, &major);
        Gestalt(gestaltSystemVersionMinor, &minor);
        Gestalt(gestaltSystemVersionBugFix, &bugFix);
        
        return snprintf(v, maxLength, "%ld.%ld.%ld", major, minor, bugFix) > 0;
    }
    
    
    void fzOSW_getScreenSize(fzSize *size, fzFloat *factor)
    {
        *factor = [[NSScreen mainScreen] backingScaleFactor];
        NSRect rect = [[NSScreen mainScreen] frame];
        size->width = rect.size.width * (*factor);
        size->height = rect.size.height * (*factor);
    }
    
    
    uint16_t fzOSW_getCapacities()
    {
        return kFZEventType_Mouse | kFZEventType_MouseRight | kFZEventType_Keyboard | kFZEventType_Trackpad | kFZEventType_MouseMoved;
    }
    
    
    int fzOSW_getUserInterfaceIdiom()
    {
        return kFZUserInterfaceIdiomPC;
    }
    
    
    bool fzOSW_getDeviceCode(char *deviceCode, fzUInt maxLength)
    {
        size_t size;
        if(sysctlbyname("hw.model", deviceCode, &size, NULL, 0)== -1) {
            FZLOGERROR("OS Wrapper: sysctlbyname() failed.");
            return false;
        }        
        deviceCode[size] = '\0';
        
        if(size > maxLength)
            FZ_RAISE("OS Wrapper: Memory overload. You should allocate more memory.");
        
        return true;
    }
    
    
    bool fzOSW_getProductName(char *path, fzUInt bufferLength)
    {
        NSDictionary* infoDictionary = [[NSBundle mainBundle] infoDictionary];
        NSString *productName = [infoDictionary objectForKey:@"CFBundleName"];
        return [productName getCString:path maxLength:bufferLength encoding:NSUTF8StringEncoding];
    }
    
    
    bool fzOSW_getResourcesPath(char *path, fzUInt maxLength)
    {
        NSString *resourcesPath = [[NSBundle mainBundle] resourcePath];
        return [resourcesPath getCString:path maxLength:maxLength encoding:NSUTF8StringEncoding];
    }
    
    
    bool fzOSW_getPersistentPath(const char *filename, char *absolutePath, fzUInt bufferLength)
    {
        // GET APPLICATION SUPPORT DIRECTORY
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
        NSString *nspath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
        
        // GET PRODUCT NAME
        char productName[512];
        if(!fzOSW_getProductName(productName, 512))
            FZ_RAISE("OS Wrapper: Imposible to get product name. No enough memory.");
        
        
        // GENERATE ABSOLUTE PATH
        nspath = [nspath stringByAppendingPathComponent:[NSString stringWithCString:productName encoding:NSUTF8StringEncoding]];
        nspath = [nspath stringByAppendingPathComponent:[NSString stringWithCString:filename encoding:NSUTF8StringEncoding]];
        
        return [nspath getCString:absolutePath maxLength:bufferLength encoding:NSUTF8StringEncoding];
    }
    
    
    bool fzOSW_createDirectory(const char *path, bool pathIsDirectory)
    {
        NSString *nspath = [NSString stringWithCString:path encoding:NSUTF8StringEncoding];
        BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:nspath isDirectory:NULL];
        
        // Create directory
        if(exists == NO) {
            nspath = (pathIsDirectory) ? nspath : [nspath stringByDeletingLastPathComponent];
            return [[NSFileManager defaultManager] createDirectoryAtPath:nspath withIntermediateDirectories:YES attributes:nil error:nil];
        }
        return YES;
    }
    
    
    bool fzOSW_removePath(const char *path)
    {
        NSString *nspath = [NSString stringWithCString:path encoding:NSUTF8StringEncoding];
        return [[NSFileManager defaultManager] removeItemAtPath:nspath error:nil];
    }
}


#pragma mark -
#pragma mark - OS WRAPPER IMPLEMENTATION

static CVReturn drawScene(CVDisplayLinkRef dl, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags fIn, CVOptionFlags* fOut, void* dlContext)
{
    return [(_FZOSWRAPPER*)dlContext getFrameForTime:outputTime];
}


@interface FZNSWindow : NSWindow
@end
@implementation FZNSWindow

- (NSRect)constrainFrameRect:(NSRect)frameRect toScreen:(NSScreen *)screen {
    return frameRect;
}

@end
@interface _FZOSWRAPPER ( Private )

- (void) setupOpenGL;
- (void) setupDisplayLink;

@end


@implementation _FZOSWRAPPER
@synthesize openGLContext = context_;
@synthesize pixelFormat = pixelFormat_;

- (id) init
{
    self = [super init];
    if (self)
    {
        context_        = NULL;
        displayLink_    = NULL;
        mgrDirector_    = NULL;
        mgrEvents_      = NULL;
    }
    return self;
}


- (void) dealloc
{
    // Stop and release display link
	CVDisplayLinkStop(displayLink_);
    CVDisplayLinkRelease(displayLink_);

    // Release Opengl stuff
    [pixelFormat_ release];
    [context_ release];
    
    // destroy window
    [window_ release];
    
	[super dealloc];
}

-(BOOL) becomeFirstResponder
{
	return YES;
}

-(BOOL) acceptsFirstResponder
{
	return YES;
}

-(BOOL) resignFirstResponder
{
	return YES;
}

- (BOOL) isOpaque
{
    return YES;
}


#pragma mark - Configuring

- (void) updateEvents:(uint16_t)dirtyFlags flags:(uint16_t)flags
{
    if(dirtyFlags & kFZEventType_Trackpad) {
        [self setAcceptsTouchEvents:!!(flags & kFZEventType_Trackpad)];
        [self setWantsRestingTouches:!!(flags & kFZEventType_Trackpad)];
    }
    
    if(dirtyFlags & kFZEventType_MouseMoved) {
        [window_ setAcceptsMouseMovedEvents:!!(flags & kFZEventType_MouseMoved)];
    }
    
    if(dirtyFlags & kFZEventType_Mouse)
        [window_ setIgnoresMouseEvents:!(flags & kFZEventType_Mouse)];    
}


- (void) setupOpenGL
{
    GLConfig& glconfig = mgrDirector_->getGLConfig();
    NSOpenGLPixelFormatAttribute attribs[] =
    {
        NSOpenGLPFAAccelerated,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, glconfig.depthFormat,
        NSOpenGLPFAColorSize, glconfig.colorFormat,
        NSOpenGLPFABackingStore, glconfig.preserveBackBuffer,
        0,
    };
    pixelFormat_ = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    context_ = [[NSOpenGLContext alloc] initWithFormat:pixelFormat_ shareContext:nil];
    if(!context_)
        FZ_RAISE_STOP("OS Wrapper: OpenGL context failed.");
    
    
    [context_ makeCurrentContext];
    
    glEnable(GL_MULTISAMPLE);
    
    CGLContextObj ctx = (CGLContextObj)[context_ CGLContextObj];
    
    //CGLEnable( ctx, kCGLCEMPEngine);
    if(glconfig.quality != 1) {
        CGLEnable(ctx, kCGLCESurfaceBackingSize);
    }

    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [context_ setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; 
    
    
    mgrDirector_->updateViewRect();
    fzRect rect = mgrDirector_->getRenderingRect();
    [[window_ contentView] addSubview:self];
    [self setFrame:NSMakeRect(rect.origin.x, rect.origin.y,
                              rect.size.width, rect.size.height)];
    
    [self setupDisplayLink];
}


- (void) setupUI
{
    // CONFIG VIEW / CONFIG WINDOW
    if([self respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)])
        [self setWantsBestResolutionOpenGLSurface:YES];

    fzSize canvasSize = mgrDirector_->getCanvasSize();
    NSRect windowFrame = NSMakeRect(0, 0, canvasSize.width, canvasSize.height);
    
    window_ = [[FZNSWindow alloc] initWithContentRect:windowFrame
                                          styleMask:(NSTitledWindowMask | NSResizableWindowMask)
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    
    NSDictionary* infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *productName = [infoDictionary objectForKey:@"CFBundleName"];
    [window_ setTitle:productName];
    [window_ setDelegate:self];
    [window_ setOpaque:YES];
    [window_ setBackgroundColor:[NSColor blackColor]];
}


- (void) updateWindow
{
    FZ_ASSERT(context_ != NULL, "Opengl context has not been created.");
    @autoreleasepool
    {
        fzSize windowSize       = mgrDirector_->getWindowSize();
        fzSize viewPort         = mgrDirector_->getViewPort();
        fzRect renderingRect    = mgrDirector_->getRenderingRect();
        bool isFullscreen       = mgrDirector_->isFullscreen();
        
        // WINDOW SIZE
        if(isFullscreen == true)
        {
            [window_ setHidesOnDeactivate:YES];
            [window_ setFrameOrigin:NSZeroPoint];
            [window_ setLevel:NSMainMenuWindowLevel+1];
            [window_ setHasShadow:NO];
            
        }else{
            [window_ setHidesOnDeactivate:NO];
            [window_ setLevel:0];
            [window_ setHasShadow:YES];
        }
        [window_ setContentSize:NSMakeSize(windowSize.width, windowSize.height)];
        
        
        // VIEW SIZE
        [self setFrame:NSMakeRect(renderingRect.origin.x, renderingRect.origin.y,
                                  renderingRect.size.width, renderingRect.size.height)];
        
        // BACKING RENDER BUFFER SIZE
        GLint dim[2] = {
            (GLint)(viewPort.width),
            (GLint)(viewPort.height)
        };
        CGLSetParameter((CGLContextObj)[context_ CGLContextObj], kCGLCPSurfaceBackingSize, dim);
        
        
        // UPDATE
        [window_ display];
        [context_ update];
    }
}

#pragma mark - Threading

- (void) setupDisplayLink
{
    FZ_ASSERT(context_ != NULL, "Opengl context has not been created.");

    CVReturn status;
    status = CVDisplayLinkCreateWithActiveCGDisplays(&displayLink_);
    if(status != kCVReturnSuccess)
        FZLOGERROR("OS Wrapper: ERROR creating the DisplayLink, %d.", status);

    status = CVDisplayLinkSetOutputCallback(displayLink_, &drawScene, self);
    if(status != kCVReturnSuccess)
        FZLOGERROR("OS Wrapper: ERROR setting DisplayLink callback, %d.", status);
    
    CGLContextObj cglContext = (CGLContextObj)[context_ CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[pixelFormat_ CGLPixelFormatObj];
    status = CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink_, cglContext, cglPixelFormat);
    
    if(status != kCVReturnSuccess)
        FZLOGERROR("OS Wrapper: ERROR attaching OpenGL with the DisplayLink, %d.", status);
}


- (void) startRendering:(float)interval
{
    FZ_ASSERT(displayLink_, "DisplayLink was not created.");
	if (displayLink_ && !CVDisplayLinkIsRunning(displayLink_))
		CVDisplayLinkStart(displayLink_);
}


- (void) stopRendering
{
    FZ_ASSERT(displayLink_, "DisplayLink was not created.");
	if (displayLink_ && CVDisplayLinkIsRunning(displayLink_))
		CVDisplayLinkStop(displayLink_);
}


- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime
{
    FZ_ASSERT(context_ != NULL, "Opengl context has not been created.");
    FZ_ASSERT([context_ view] == self, "Context has not been attached to a view.");

    CGLLockContext((CGLContextObj)[context_ CGLContextObj]);
    [context_ makeCurrentContext];
    
    CHECK_GL_FRAMEBUFFER();

    // drawing code
    bool toFlush = mgrDirector_->drawScene();
    
    if(toFlush)
    [context_ flushBuffer];
    
	CGLUnlockContext((CGLContextObj)[context_ CGLContextObj]);
    
    return kCVReturnSuccess;
}


#pragma mark - Application delegates

- (void)applicationDidFinishLaunching:(NSNotification *)options
{
    // STEP ZERO. weak pointers
    mgrDirector_ = &Director::Instance();
    mgrEvents_ = &EventManager::Instance();
    
    // FIRST STEP. Notify Director::applicationLaunching()
    // - gets opengl context config
    // - attachs OS wrapper to director
    mgrDirector_->applicationLaunching(self); //self = OS Wrapper pointer
    
    
    // SECOND STEP. Config UI.
    // - configs view: opacity, retina display...
    // - creates the window
    [self setupUI];
    
    
    // THIRD STEP. OpenGL initialization.
    // - creates the opengl context.
    // - set the default window size.
    // - attachs the context to the view.
    [self setupOpenGL];
    
    
    // FOURTH STEP. Make window visible.
    // - "connects" the windows with the screen.
    // - begins receiving events.
    [window_ makeKeyAndOrderFront:self];
    
    
    // FIFTH STEP. Notify Directed::applicationLaunched()
    // - ends director's initialization
    // - appdelegate->applicationLaunched() is called
    // - -> game loop starts
    mgrDirector_->applicationLaunched(options);
}


- (void) applicationWillResignActive:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationPaused();
}


- (void) applicationDidBecomeActive:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationResumed();
}

- (void) applicationWillTerminate:(NSApplication *)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationTerminate();
}


#pragma mark - UIKit methods

- (void)lockFocus
{
    FZ_ASSERT(context_ != NULL, "Opengl context has not been created.");
    
    [super lockFocus];
    if ([context_ view] != self)
        [context_ setView:self];    
}


-(void) viewDidMoveToWindow
{ 
    FZ_ASSERT(context_ != NULL, "Opengl context has not been created.");

    [super viewDidMoveToWindow];
    if ([self window] == nil)
        [context_ clearDrawable];
}

- (void) windowDidResize:(NSNotification *)notificatio
{
    NSRect frame = [[window_ contentView] frame];
    Director::Instance().setWindowSize(fzSize(frame.size.width, frame.size.height));
}


#pragma mark - Tracking events

- (void) dispatchMouse:(NSEvent*)nsevent type:(fzEventType)type state:(fzEventState)state
{   
    FZ_ASSERT(mgrEvents_ != NULL, "HAT isn't configured properly, the events can't be dispatched.");
    NSPoint mouseP = [self convertPoint:[nsevent locationInWindow] fromView:[window_ contentView]];
    
    fzPoint point(mouseP.x, mouseP.y);
    point = mgrDirector_->convertToGL(point, false);
    
    intptr_t identifier = (intptr_t)[nsevent eventNumber];
    Event event(self, identifier,
                type,
                state,
                point, 0
                );
    
    mgrEvents_->catchEvent(event);
}


- (void) dispatchKey:(NSEvent*)nsevent state:(fzEventState)state
{   
    FZ_ASSERT(mgrEvents_ != NULL, "HAT isn't configured properly, the events can't be dispatched.");
    
    //NSString *chars = [nsevent charactersIgnoringModifiers];
    //intptr_t keyCode = [chars characterAtIndex:0]; // identifier = keyCode
    intptr_t keyCode = [nsevent keyCode];

    Event event(self, keyCode,
                kFZEventType_Keyboard,
                state);
    
    mgrEvents_->catchEvent(event);
}


- (void) dispatchTrackpad:(NSSet*)touches state:(fzEventState)state
{   
    FZ_ASSERT(mgrEvents_ != NULL, "HAT isn't configured properly, the events can't be dispatched.");
    for(NSTouch *touch in touches)
    {
        NSPoint cgp = [touch normalizedPosition];
        
        intptr_t identifier = (intptr_t)[[touch identity] hash];
        Event event(self, identifier,
                    kFZEventType_Trackpad,
                    state,
                    fzPoint(cgp.x, cgp.y), 0
                    );
        
        mgrEvents_->catchEvent(event);
    }
}


#pragma mark Left mouse events

- (void)mouseDown:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_Mouse state:kFZEventState_Began];
}

- (void)mouseDragged:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_Mouse state:kFZEventState_Updated];
}


- (void)mouseMoved:(NSEvent *)nsevent
{
    FZ_ASSERT(mgrEvents_ != NULL, "HAT isn't configured properly, the events can't be dispatched.");
    NSPoint mouseP = [self convertPoint:[nsevent locationInWindow] fromView:[window_ contentView]];
    
    fzPoint point(mouseP.x, mouseP.y);
    point = mgrDirector_->convertToGL(point, false);
    
    intptr_t identifier = (intptr_t)[nsevent eventNumber];
    Event event(self, identifier,
                kFZEventType_MouseMoved,
                kFZEventState_Indifferent,
                point, 0
                );
    
    mgrEvents_->catchEvent(event);
}

- (void)mouseUp:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_Mouse state:kFZEventState_Ended];
}


#pragma mark Right mouse events

- (void)rightMouseDown:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_MouseRight state:kFZEventState_Began];
}

- (void)rightMouseDragged:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_MouseRight state:kFZEventState_Updated];
}

- (void)rightMouseUp:(NSEvent *)nsevent {
    [self dispatchMouse:nsevent type:kFZEventType_MouseRight state:kFZEventState_Ended];
}


#pragma mark Keyboard events

- (void)keyDown:(NSEvent *)nsevent {
    if(![nsevent isARepeat])
        [self dispatchKey:nsevent state:kFZEventState_Began];
    else
        [self dispatchKey:nsevent state:kFZEventState_Updated];
}

- (void)keyUp:(NSEvent *)nsevent {
    [self dispatchKey:nsevent state:kFZEventState_Ended];
}


#pragma mark Trackpad events

- (void)touchesBeganWithEvent:(NSEvent *)nsevent {
    NSSet *touches = [nsevent touchesMatchingPhase:NSTouchPhaseBegan inView:self];
    [self dispatchTrackpad:touches state:kFZEventState_Began];
}

- (void)touchesMovedWithEvent:(NSEvent *)nsevent {
    NSSet *touches = [nsevent touchesMatchingPhase:NSTouchPhaseMoved inView:self];
    [self dispatchTrackpad:touches state:kFZEventState_Updated];
}

- (void)touchesEndedWithEvent:(NSEvent *)nsevent {
    NSSet *touches = [nsevent touchesMatchingPhase:NSTouchPhaseEnded inView:self];
    [self dispatchTrackpad:touches state:kFZEventState_Ended];
}

- (void)touchesCancelledWithEvent:(NSEvent *)nsevent {
    NSSet *touches = [nsevent touchesMatchingPhase:NSTouchPhaseCancelled inView:self];
    [self dispatchTrackpad:touches state:kFZEventState_Cancelled];
}


@end

#endif
