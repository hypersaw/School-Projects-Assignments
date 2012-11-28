//
//  JulianDate.h
//  Day Calculator
//
//  Created by Andrew Long on 11/27/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JulianDate : NSObject {
    NSInteger month;
    NSInteger day;
    NSInteger year;
}
@property (readwrite,nonatomic) NSInteger month;
@property (readwrite,nonatomic) NSInteger day;
@property (readwrite,nonatomic) NSInteger year;

-(id)initWithString:(NSString*)input;
-(NSString*)display;
-(NSInteger)daysInMonth;
-(NSInteger)daysLeftInMonth;
-(NSInteger)daysInYear;
-(BOOL)comesBefore:(JulianDate*)otherDate;

@end
