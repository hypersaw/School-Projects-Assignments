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

-(IBAction)dismissField:(id)sender{
    [self resignFirstResponder];
    NSLog(@"First responder should resign\n");
}

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
