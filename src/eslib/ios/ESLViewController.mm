//
//  GWViewController.m
//  glesworld
//
//  Created by wuhao on 13-7-9.
//  Copyright (c) 2013年 wuhao. All rights reserved.
//

#import "ESLViewController.h"
#import "eslib/Application.h"

USING_NS_ESLIB


@interface ESLViewController () {

}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ESLViewController

- (void)dealloc
{
    Application::exit();
    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [_context release];

    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
    
    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    glEnable(GL_DEPTH_TEST);
    
    CGRect bounds = self.view.bounds;
    
    Application::SetScreenSize(bounds.size.width, bounds.size.height);
    Application::init();
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    NSTimeInterval time = self.timeSinceLastUpdate;
    //NSLog(@"time=%f",time);
    Application::update(time);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{    
    Application::render();
}


@end
