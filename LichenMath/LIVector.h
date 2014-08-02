//
//  LIVector.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIVector_t.h>

extern NSString *LIVectorToString(LIVector_t v);
extern LIVector_t LIVectorFromString(NSString *s);

@interface LIVector : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIVector_t vector;

- (instancetype)initWithVector:(LIVector_t)vector;
+ (instancetype)vectorWithVector:(LIVector_t)vector;
+ (instancetype)vectorWithX:(float)x y:(float)y z:(float)z;

@end
