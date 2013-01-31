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

#include "iOS_support.h"

#if defined(FZ_OS) && (FZ_OS == kFZPLATFORM_IOS_GL_1 || FZ_OS == kFZPLATFORM_IOS_GL_2)

#include "../FZEventManager.h"
#include "../FZDeviceConfig.h"
#include "../FZDirector.h"
#include "../FZMacros.h"
#include "../FZGLState.h"
#include <sys/types.h>
#include <sys/sysctl.h>


using namespace FORZE;

namespace FORZE {
    
#pragma mark - OS WRAPPER communication protocol
    
    void OSW::init(int argc, char *argv[])
    {
        @autoreleasepool {
            UIApplicationMain(argc, argv, nil, @"_FZOSWRAPPER");
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
        [(_FZOSWRAPPER*)Instance() setEventInterval:interval];
    }
    
    
    void OSW::setOrientation(int orientation)
    {
        UIInterfaceOrientation uiorientation;
        switch (orientation) {
            case kFZOrientation_LandscapeLeft: uiorientation = UIInterfaceOrientationLandscapeLeft; break;
            case kFZOrientation_LandscapeRight: uiorientation = UIInterfaceOrientationLandscapeRight; break;
            case kFZOrientation_Portrait: uiorientation = UIInterfaceOrientationPortrait; break;
            case kFZOrientation_PortraitUpsideDown: uiorientation = UIInterfaceOrientationPortraitUpsideDown; break;
            default: return;
        }
        [[UIApplication sharedApplication] setStatusBarOrientation:uiorientation animated:NO];
    }
    
    
    
#pragma mark - Device info
    
    bool fzOSW_getDeviceCode(char *deviceCode, fzUInt maxLength)
    {
#if TARGET_IPHONE_SIMULATOR
        char text[] = "simulator";
        strncpy(deviceCode, text, maxLength);
#else
        size_t size;
        if(sysctlbyname("hw.machine", deviceCode, &size, NULL, 0) == -1) {
            FZLOGERROR("OS Wrapper: sysctlbyname() failed.");
            return false;
        }
        deviceCode[size] = '\0';
        
        if(size >= maxLength)
            FZ_RAISE_STOP("OS Wrapper: Memory overload.");
#endif
        return true;
    }
    
    
    bool fzOSW_getSystemVersion(char *v, fzUInt maxLength)
    {
        NSString *version = [[UIDevice currentDevice] systemVersion];
        return [version getCString:v maxLength:maxLength encoding:NSUTF8StringEncoding];
    }
    
    
    void fzOSW_getScreenSize(fzSize *size, fzFloat *factor)
    {
        @autoreleasepool {
            CGFloat scale =  [[UIScreen mainScreen] scale];
            CGRect rect = [[UIScreen mainScreen] bounds];
            size->width = rect.size.width * scale;
            size->height = rect.size.height * scale;
            *factor = scale;
        }
    }
    
    
    uint16_t fzOSW_getCapacities()
    {
        uint16_t capacities = kFZEventType_Touch;
        
        CMMotionManager *m = [[CMMotionManager alloc] init];
        if([m isAccelerometerAvailable])
            capacities |= kFZEventType_Accelerometer;
        if([m isGyroAvailable])
            capacities |= kFZEventType_Gyro;

        [m release];
        return capacities;
    }
    
    
    int fzOSW_getUserInterfaceIdiom()
    {
        if([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
            return kFZUserInterfaceIdiomPad;
        else
            return kFZUserInterfaceIdiomPhone;
    }
    
    
    bool fzOSW_getResourcesPath(char *path, fzUInt maxLength)
    {
        NSString *resourcesPath = [[NSBundle mainBundle] resourcePath];
        return [resourcesPath getCString:path maxLength:maxLength encoding:NSUTF8StringEncoding];
    }
    
    
    bool fzOSW_getPersistentPath(const char *filename, char *absolutePath, fzUInt maxLength)
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *nspath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
        nspath = [nspath stringByAppendingPathComponent:[NSString stringWithCString:filename encoding:NSUTF8StringEncoding]];
        return [nspath getCString:absolutePath maxLength:maxLength encoding:NSUTF8StringEncoding];
    }
    
    
    bool fzOSW_getProductName(char *path, fzUInt maxLength)
    {
        NSDictionary* infoDictionary = [[NSBundle mainBundle] infoDictionary];
        NSString *productName = [infoDictionary objectForKey:@"CFBundleName"];
        return [productName getCString:path maxLength:maxLength encoding:NSUTF8StringEncoding];
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

@interface _FZUIViewController : UIViewController
@end

@implementation _FZUIViewController

- (BOOL)shouldAutorotate
{
    return [self shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)[[UIDevice currentDevice] orientation]];
}
            
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    int autorotation = Director::Instance().getAutorotation();
    if(interfaceOrientation == UIInterfaceOrientationLandscapeLeft)
        return !!(autorotation & kFZOrientation_LandscapeRight);
    if(interfaceOrientation == UIInterfaceOrientationLandscapeRight)
        return !!(autorotation & kFZOrientation_LandscapeLeft);
    if(interfaceOrientation == UIInterfaceOrientationPortrait)
        return !!(autorotation & kFZOrientation_Portrait);
    if(interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
        return !!(autorotation & kFZOrientation_PortraitUpsideDown);
    
    return false;
}


- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    Director &director = Director::Instance();
    if(toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft) {
        director.setOrientation(kFZOrientation_LandscapeLeft); }
    if(toInterfaceOrientation == UIInterfaceOrientationLandscapeRight) {
        director.setOrientation(kFZOrientation_LandscapeRight); }
    if(toInterfaceOrientation == UIInterfaceOrientationPortrait) {
        director.setOrientation(kFZOrientation_Portrait); }
    if(toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) {
        director.setOrientation(kFZOrientation_PortraitUpsideDown); }
}

@end

@interface _FZOSWRAPPER_BASE ( Private )

-(void) setupOpenGL;
-(void) setupFramebuffer;
-(void) setupUI;
-(void) swapBuffers;
@end

@implementation _FZOSWRAPPER_BASE

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (EAGLRenderingAPI) openGLAPI
{
    FZ_RAISE_STOP("_FZOSWRAPPER_BASE can not be used directly as OS wrapper because no opengl API is specified.");
    return 0;
}

- (id) init
{
    self = [super init];
    if (self) {
        mgrDirector_    = NULL;
        mgrEvents_      = NULL;
        window_         = nil;
        displayLink_    = nil;
        
        defaultFramebuffer_ = 0;
        colorRenderbuffer_ = 0;
        depthBuffer_ = 0;
        msaaColorbuffer_ = 0;
        msaaFramebuffer_ = 0;
    }

    return self;
}


- (void) dealloc
{
    [self stopRendering];
    
    if(defaultFramebuffer_)
        fzGLDeleteFramebuffers(1, &defaultFramebuffer_);
    
    if(colorRenderbuffer_)
        fzGLDeleteFramebuffers(1, &colorRenderbuffer_);
    
	if( depthBuffer_ )
		fzGLDeleteFramebuffers(1, &depthBuffer_);
    
	if ( msaaColorbuffer_)
		fzGLDeleteFramebuffers(1, &msaaColorbuffer_);
	
	if ( msaaFramebuffer_)
		fzGLDeleteFramebuffers(1, &msaaFramebuffer_);
    
    
    // Tear down context
    if ([EAGLContext currentContext] == context_)
        [EAGLContext setCurrentContext:nil];
    
    [window_ release];
    [context_ release];
    [motionManager_ release];
    
	[super dealloc];
}


#pragma mark - Threading management

- (void) startRendering:(float)interval
{
    if(displayLink_ == nil) {
        displayLink_ = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawScene:)];
        
        int frameInterval = (int) floor(interval * 60.0f);
        [displayLink_ setFrameInterval:frameInterval];
        [displayLink_ addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];        
    }
}


- (void) stopRendering
{
    [displayLink_ invalidate];
    displayLink_ = nil;
}


- (void) drawScene:(id)sender
{
    FZ_ASSERT(context_, "OpenGl context was not created.");
    
    mgrDirector_->drawScene();

    [self swapBuffers];
}


#pragma mark - OpenGL management

-(void) setupOpenGL
{
    CAEAGLLayer *surface = (CAEAGLLayer *)[self layer];
    
    // Config surface
    {
        GLConfig& glconfig = mgrDirector_->getGLConfig();
        CGFloat contentScaleFactor = mgrDirector_->getContentScaleFactor();
        [self setContentScaleFactor:contentScaleFactor];
        
        
        NSString *pixel;
        switch (glconfig.colorFormat) {
            case kFZGLConfigColorRGB565:   pixel = kEAGLColorFormatRGB565; break;
            case kFZGLConfigColorRGB888:
            case kFZGLConfigColorRGBA8888: pixel = kEAGLColorFormatRGBA8; break;
            default: FZ_RAISE_STOP("OS Wrapper: Invalid pixel format.");
        }
        NSDictionary *properties = [NSDictionary dictionaryWithObjectsAndKeys:
                 [NSNumber numberWithBool:glconfig.preserveBackBuffer], kEAGLDrawablePropertyRetainedBacking,
                 pixel, kEAGLDrawablePropertyColorFormat, nil];
      
        [surface setDrawableProperties:properties];
        [surface setOpaque:YES];
    }
    
    // Create OpenGL ES context
    context_ = [[EAGLContext alloc] initWithAPI:[self openGLAPI]];
    if(!context_)
        FZ_RAISE_STOP("OS Wrapper: Impossible to create context.");
        
    // set new context as default
    [EAGLContext setCurrentContext:context_];
    
    // setup default framebuffers
    [self setupFramebuffer];
    
    
    // set default window size
    CGRect windowRect = [window_ frame];
    mgrDirector_->setWindowSize(fzSize(windowRect.size.width, windowRect.size.height));
    mgrDirector_->updateViewRect();
    
    // set frambuffer for screen rendering
    [context_ renderbufferStorage:FZ_RENDERBUFFER fromDrawable:surface];
}


- (void) setupFramebuffer
{ 
    GLConfig& glconfig = mgrDirector_->getGLConfig();
    
    // Create default framebuffers
    fzGLGenFramebuffers(1, &defaultFramebuffer_);
    fzGLGenRenderbuffers(1, &colorRenderbuffer_);
    
    if( defaultFramebuffer_ == 0  || colorRenderbuffer_ == 0 )
        FZ_RAISE_STOP("OS Wrapper: Impossible to create default framebuffers.");

    
    // bind framebuffers
    fzGLBindFramebuffer(defaultFramebuffer_);
    fzGLBindRenderbuffer(FZ_RENDERBUFFER, colorRenderbuffer_);
    fzGLFramebufferRenderbuffer(FZ_FRAMEBUFFER, FZ_COLOR_ATTACHMENT0, FZ_RENDERBUFFER, colorRenderbuffer_);
    
    
    // MSAA auxiliar framebuffers ( offscreen )
    if (glconfig.multiSampling > 0)
    {
        GLint maxSamplesAllowed = DeviceConfig::Instance().getMaxSamplesAllowed();
        if(maxSamplesAllowed < static_cast<GLint>(glconfig.multiSampling))
            glconfig.multiSampling = maxSamplesAllowed;
        
        fzGLGenFramebuffers(1, &msaaFramebuffer_);
        if(msaaFramebuffer_ == 0)
            FZ_RAISE_STOP("OS Wrapper: Can't create default MSAA frame buffer.");

        fzGLBindFramebuffer(msaaFramebuffer_);
    }
    CHECK_GL_ERROR_DEBUG();
}


- (void) setupUI
{
    // Config view
    [self setMultipleTouchEnabled:YES];
    [self setAutoresizesSubviews:NO];
    [self setOpaque:YES];
        
    // Config window
    if(window_ == nil)
    {
        window_ = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [window_ setMultipleTouchEnabled:YES];
        [window_ setOpaque:YES];
        [window_ addSubview:self];
    }
    
//    // Create auxiliar viewController
//    if(viewController_ == nil) {
//        viewController_ = [[_FZUIViewController alloc] initWithNibName:nil bundle:nil];
//        [window_ setRootViewController:viewController_];
//        [window_ addSubview:viewController_.view];
//    }
}


- (void) updateWindow
{
    fzRect renderingRect = mgrDirector_->getRenderingRect();
    
    // window size is ignored
    [super setFrame:CGRectMake(renderingRect.origin.x, renderingRect.origin.y, renderingRect.size.width, renderingRect.size.height)];

    //fzGLBindFramebuffer(defaultFramebuffer_);
}


- (void) swapBuffers
{
    const GLConfig& glconfig = mgrDirector_->getGLConfig();
    
#ifdef __IPHONE_4_0
	
	if (glconfig.multiSampling)
	{  
		_fzGLBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, msaaFramebuffer_);
		_fzGLBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, defaultFramebuffer_);
		glResolveMultisampleFramebufferAPPLE();
	}
	
	if( DeviceConfig::Instance().isDiscardFramebufferSupported())
	{	
		if (glconfig.multiSampling)
		{
			if (glconfig.depthFormat)
			{
				GLenum attachments[] = {FZ_COLOR_ATTACHMENT0, FZ_DEPTH_ATTACHMENT};
				glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
			}
			else
			{
				GLenum attachments[] = {FZ_COLOR_ATTACHMENT0};
				glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
			}
			
			fzGLBindRenderbuffer(FZ_RENDERBUFFER, colorRenderbuffer_);
            
		}	
		
		// not MSAA
		else if (glconfig.depthFormat ) {
			GLenum attachments[] = { FZ_DEPTH_ATTACHMENT };
			glDiscardFramebufferEXT(FZ_FRAMEBUFFER, 1, attachments);
		}
	}
    
#endif // __IPHONE_4_0
	
    if(![context_ presentRenderbuffer:FZ_RENDERBUFFER])
        FZLOGERROR("OS Wrapper: Failed to swap renderbuffer.");
    
	
	// We can safely re-bind the framebuffer here, since this will be the
	if( glconfig.multiSampling )
		fzGLBindFramebuffer(msaaFramebuffer_);
}


#pragma mark - Application events

- (BOOL) application:(id)a didFinishLaunchingWithOptions:(NSDictionary *)options
{
    // STEP ZERO.
    motionManager_ = [[CMMotionManager alloc] init];
    mgrDirector_ = &Director::Instance();
    mgrEvents_ = &EventManager::Instance();
    
    
    // FIRST STEP. Notify Director::applicationLaunching()
    // - gets opengl context config
    // - attachs OSWrapper to director
    mgrDirector_->applicationLaunching(self);
    
    
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
    [window_ makeKeyAndVisible];
    
    
    // FIFTH STEP. Notify Directed::applicationLaunched()
    // - ends director's initialization
    // - appdelegate->applicationLaunched() is called
    // - -> game loop starts
    mgrDirector_->applicationLaunched(options);
    
    return YES;
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


- (void) applicationWillTerminate:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationTerminate();
}


- (void) applicationSignificantTimeChange:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationSignificantTimeChange();
}


- (void) applicationDidReceiveMemoryWarning:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->applicationDidReceiveMemoryWarning();
}


- (void) applicationDidEnterBackground:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->stopAnimation();
}


- (void) applicationWillEnterForeground:(id)a
{
    FZ_ASSERT(mgrDirector_, "mgrDirector_ can not be NULL.");
    mgrDirector_->startAnimation();
}


#pragma mark - Physical events

- (void) setEventInterval:(float)interval
{
    [motionManager_ setAccelerometerUpdateInterval:interval];
    [motionManager_ setGyroUpdateInterval:interval];
    [motionManager_ setDeviceMotionUpdateInterval:interval];
}


- (void) updateEvents:(uint16_t)dirtyFlags flags:(uint16_t)flags
{
    if(dirtyFlags & kFZEventType_Touch) {
        [window_ setUserInteractionEnabled:(flags & kFZEventType_Touch)];
        [self setUserInteractionEnabled:(flags & kFZEventType_Touch)];
    }
    
    static NSOperationQueue *queue;
    if(queue == nil)
        queue = [[NSOperationQueue alloc] init];
    
    
    if(dirtyFlags & kFZEventType_Accelerometer)
    {
        if(flags & kFZEventType_Accelerometer) {

            [motionManager_ startAccelerometerUpdatesToQueue:queue withHandler:
             ^(CMAccelerometerData *data, NSError *error)
            {
                 if(data) {
                     CMAcceleration acceleration = [data acceleration];
                     Event event(self, 0, kFZEventType_Accelerometer, kFZEventState_Indifferent,
                                 acceleration.x, acceleration.y, acceleration.z);
                     
                     mgrEvents_->catchEvent(event);
                 }
             }];
        }else{
            [motionManager_ stopAccelerometerUpdates];
        }
    }
    
    if(dirtyFlags & kFZEventType_Gyro)
    {
        if(flags & kFZEventType_Gyro) {
            [motionManager_ startGyroUpdatesToQueue:queue withHandler:
             ^(CMGyroData *data, NSError *error)
             {
                 if(data) {
                     CMRotationRate rotationRate = [data rotationRate];
                     Event event(self, 0, kFZEventType_Gyro, kFZEventState_Indifferent,
                                 rotationRate.x, rotationRate.y, rotationRate.z);
                     
                     mgrEvents_->catchEvent(event);
                 }
             }];
        }else{
            [motionManager_ stopGyroUpdates];
        }
    }
}


- (void) dispatchTouches:(NSSet*) touches type:(fzEventType)type state:(fzEventState)state
{   
    FZ_ASSERT(mgrEvents_ != NULL, "HAT isn't configured properly, the events can't be dispatched.");
    
    for(UITouch *touch in touches)
    {
        CGPoint cgp = [touch locationInView:[touch view]];
        fzPoint point(cgp.x, cgp.y);
        point = mgrDirector_->convertToGL(point, true);
        
        intptr_t identifier = (intptr_t)[touch hash];
        Event event(self,
                    identifier,
                    type,
                    state,
                    point, 0
                    );
        
        mgrEvents_->catchEvent(event);
    }
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self dispatchTouches:touches type:kFZEventType_Touch state:kFZEventState_Began];
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self dispatchTouches:touches type:kFZEventType_Touch state:kFZEventState_Updated];
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self dispatchTouches:touches type:kFZEventType_Touch state:kFZEventState_Ended];
}


- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self dispatchTouches:touches type:kFZEventType_Touch state:kFZEventState_Cancelled];
}

@end

#endif
