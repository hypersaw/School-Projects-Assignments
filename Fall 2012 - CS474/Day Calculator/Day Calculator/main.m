//
//  main.m
//  Day Calculator
//
//  Created by Andrew Long on 11/27/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "JulianDate.h"
#import "AppDelegate.h"

int main(int argc, char *argv[])
{
    JulianDate* aDate;
    JulianDate* bDate;
    JulianDate* cDate;
    JulianDate* dDate;
    
    aDate = [[JulianDate alloc] initWithString:@"07/12/2012"];
    bDate = [[JulianDate alloc] initWithString:@"05/16/1991"];
    cDate = [[JulianDate alloc] initWithString:@"02/13/2012"];
    dDate = [[JulianDate alloc] initWithString:@"02/13/2011"];
    
    NSLog(@"aDate: %@\n",[aDate display]);
    NSLog(@"bDate: %@\n",[bDate display]);
    NSLog(@"cDate: %@\n",[cDate display]);
    NSLog(@"dDate: %@\n",[dDate display]);
    
    NSLog(@"Days in month of aDate: %d\n",[aDate daysInMonth]);
    NSLog(@"Days in month of bDate: %d\n",[bDate daysInMonth]);
    NSLog(@"Days in month of cDate: %d\n",[cDate daysInMonth]);
    NSLog(@"Days in month of dDate: %d\n",[dDate daysInMonth]);
    
    NSLog(@"Days left in month aDate: %d\n",[aDate daysLeftInMonth]);
    NSLog(@"Days left in month bDate: %d\n",[bDate daysLeftInMonth]);
    NSLog(@"Days left in month cDate: %d\n",[cDate daysLeftInMonth]);
    NSLog(@"Days left in month dDate: %d\n",[dDate daysLeftInMonth]);
    
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
