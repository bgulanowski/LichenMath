//
//  LIPoint_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIPoint_t.h>

extern NSString *LIPointToString(LIPoint_t p);
extern LIPoint_t LIPointFromString(NSString *string);

@class LIMatrix;

@interface LIPoint : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIPoint_t point;

- (instancetype)initWithPoint:(LIPoint_t)point;
+ (instancetype)pointWithPoint:(LIPoint_t)point;
+ (instancetype)pointWithX:(float)x y:(float)y z:(float)z w:(float)w;

- (LIPoint *)pointWithMatrix:(LIMatrix *)transform;
- (void)applyMatrix:(LIMatrix *)matrix;

@end
