//
//  ViewController.h
//  Day Calculator
//
//  Created by Andrew Long on 11/27/12.
//  Copyright (c) 2012 Andrew Long. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITextFieldDelegate>{
    IBOutlet UITextField* startDate;
    IBOutlet UITextField* endDate;
    IBOutlet UILabel* output;
    IBOutlet UILabel* daysLabel;
    IBOutlet UILabel* startDateWarning;
    IBOutlet UILabel* endDateWarning;
    IBOutlet UIButton* calculate;
}

-(IBAction)calculateDays:(id)sender;
-(IBAction)dismissField:(id)sender;
-(BOOL)hasValidInput:(NSString*)inputField;

@end
