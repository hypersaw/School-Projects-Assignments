//
//  JulianDate.m
//  Day Calculator
//
//  Created by Andrew Long on 11/27/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#import "JulianDate.h"

@implementation JulianDate
@synthesize month, day, year;

// Initialize with a 10 character string with the following
// format (MM/DD/YYYY). Must be '/' delimited.
-(id)initWithString:(NSString*)input{
    NSArray* dateArray = [input componentsSeparatedByString:@"/"];
    
    [self setMonth:[[dateArray objectAtIndex: 0] integerValue]];
    [self setDay:[[dateArray objectAtIndex: 1] integerValue]];
    [self setYear:[[dateArray objectAtIndex: 2] integerValue]];
    
    return self;
}

// Returns a string with the date in MM/DD/YYYY format
-(NSString*)display{
    NSString* outputString = [[NSString alloc] initWithFormat:@"%d/%d/%d",month,day,year];
    
    return outputString;
}

// Returns how many days are in the date's month
-(NSInteger)daysInMonth{
    NSInteger days = 0;
    
    if(month > 0){
        // If month is Jan, Mar, May, July, Aug, Oct or Dec
        if(month == 1 || month == 3 || month == 5 || month == 7
           || month == 8 || month == 10 || month == 12){
            days = 31;
        }
        // If month is Feb
        else if(month == 2){
            days = 28 + (1 * !(year % 4));
        }
        else {
            days = 30;
        }
    }
    
    return days;
}

// Returns how many days are left in the date's month
-(NSInteger)daysLeftInMonth{
    NSInteger days = [self daysInMonth];

    return (days - day);
}

// Returns how many days are in the date's year
-(NSInteger)daysInYear{
    NSInteger days = 365;
    if([self year] % 4 == 0){
        days += 1;
    }
    
    return days;
}

// Returns whether or not the passed in date comes after
// the current (self) date.
-(BOOL)comesBefore:(JulianDate *)otherDate{
    if([self year] == [otherDate year]){
        if([self month] == [otherDate month]){
            if([self day] <= [otherDate day]){
                return YES;
            }
        }
        else if([self month] < [otherDate month]){
            return YES;
        }
    }
    else if([self year] < [otherDate year]){
        return YES;
    }
    
    return NO;
}
@end
