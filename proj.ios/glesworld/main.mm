//
//  main.m
//  glesworld
//
//  Created by wuhao on 13-7-9.
//  Copyright (c) 2013年 wuhao. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "eslib/Application.h"
#import "lessons/LessonDelegate.h"
#import "GWAppDelegate.h"

int main(int argc, char *argv[])
{
    LessonDelegate delegate;
    
	AppConfig config;
	config.mDelegate = &delegate;
	
	Application::setConfig(config);
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([GWAppDelegate class]));
    }
}
