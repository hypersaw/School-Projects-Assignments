//
//  ViewController.m
//  Day Calculator
//
//  Created by Andrew Long on 11/27/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#import "JulianDate.h"
#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

// Called when startDate and endDate text fields
// are done editing ('Did End On Exit' and 'Editing Did End').
// Checks the input and validates it. If everything checks out it continues
// by calling calculateDays
-(IBAction)dismissField:(id)sender{
    [self resignFirstResponder];
    BOOL validInput = [self hasValidInput:[sender text]];
    
    if(validInput){
        [self calculateDays:self];
    }
    else{
        [sender setText:@""];
        [sender setPlaceholder:@"Invalid Format"];
    }
}

// Pulls the data from the text fields and calculates
// days between startDate and endDate
-(IBAction)calculateDays:(id)sender{
    if([[startDate text] length] == 0 || [[endDate text] length] == 0){
        NSLog(@"Fields are empty!");
    }
    else{
        JulianDate* firstDate = [[JulianDate alloc] initWithString:[startDate text]];
        JulianDate* secondDate = [[JulianDate alloc] initWithString:[endDate text]];
        
        if([firstDate comesBefore:secondDate]){
            NSInteger days = 0;
            JulianDate* temp = [[JulianDate alloc] initWithString:@"00/00/0000"];
            
            // Break the difference into five parts if not within
            // the same calendar year
            if([firstDate year] != [secondDate year]){
                // First part is the time from (beginning of) first month to end of year
                for([temp setMonth:[firstDate month]]; [temp month] <= 12; [temp setMonth:([temp month] + 1)]){
                    days += [temp daysInMonth];
                }
                
                // Second: Now we subtract how many days into the month we already had
                days -= [firstDate day];
                
                // Third: Add the full years in between our initial and target years
                for([temp setYear:([firstDate year] + 1)]; [temp year] < [secondDate year]; [temp setYear:([temp year] + 1)]){
                    days += [temp daysInYear];
                }
                
                // Fourth: Get the number of days between beginning of year and target month
                for([temp setMonth:1]; [temp month] < [secondDate month]; [temp setMonth:([temp month] + 1)]){
                    days += [temp daysInMonth];
                }
                
                // Fifth: Add number of days passed in month
                days += [secondDate day];
            }
            else{
                // Get the number of days between initial month and target month
                for([temp setMonth:[firstDate month]]; [temp month] < [secondDate month]; [temp setMonth:([temp month] + 1)]){
                    days += [temp daysInMonth];
                }
                
                // Subtract days that have already passed in initial month
                days -= [firstDate day];
            
                // Add remaining days in target month
                days += [secondDate day];
            }
        
            [output setText:[NSString stringWithFormat:@"%d",days]];
            if([[daysLabel text] length] == 0){
                [daysLabel setText:@"DAYS"];
            }
        }
        else{
            [output setText:@"?"];
        }
    }
}

// Checks whether a passed in string follows the correct
// format for a JulianDate. If format is correct, validates that
// the numbers are valid (month stays within 1-12, days are correct, etc.)
-(BOOL)hasValidInput:(NSString *)inputField{
    // If our string doesn't have exactly 10 characters
    // (2 + '/' + 2 + '/' + 4) then invalid.
    if([inputField length] != 10){
        return NO;
    }
    
    NSArray* dateArray = [inputField componentsSeparatedByString:@"/"];
    
    // If our array does not have 3 elements then
    // there were 10 characters but wrong format
    // Ex. (3 + '/' + 6)
    if([dateArray count] != 3){
        return NO;
    }
    
    NSInteger m, d, y;
    m = [[dateArray objectAtIndex:0] integerValue];
    d = [[dateArray objectAtIndex:1] integerValue];
    y = [[dateArray objectAtIndex:2] integerValue];
    
    // 
    // Is month within range
    if(!((m > 0) && (m < 13))){
        return NO;
    }
    // Is day within range
    if(!((d > 0) && (d < 32))){
        return NO;
    }
    // Is day within range for 30 day months
    if((m == 4 || m == 6 || m == 9 || m == 11) && (d > 30)){
        return NO;
    }
    // Is day within range for normal Feb
    if((m == 2) && (d > 28) && (y % 4 != 0)){
        return NO;
    }
    // Is day within range for leap Feb
    if((m == 2) && (d > 29) && (y % 4 == 0)){
        return NO;
    }
    
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
