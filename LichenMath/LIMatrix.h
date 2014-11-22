//
//  LIMatrix.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIMatrix_t.h>

@class LIPoint;

extern NSString *LIMatrixToString(LIMatrix_t m);
extern LIMatrix_t LIMatrixFromString(NSString *string);

@interface LIMatrix : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIMatrix_t matrix;
@property (nonatomic, readonly) LIMatrix_t * const r_matrix;

- (instancetype)initWithMatrix:(LIMatrix_t)matrix;
+ (instancetype)matrixWithMatrix:(LIMatrix_t)matrix;
+ (instancetype)matrixWithElements:(float *)elements;
+ (instancetype)identity;

- (void)concatenate:(LIMatrix *)matrix;
- (LIPoint *)transformPoint:(LIPoint *)point;

- (void)setValue:(float)v forElement:(intptr_t)e;
- (float)valueForElement:(intptr_t)e;

- (void)setValues:(float *)v forElements:(intptr_t *)elements count:(NSUInteger)count;

@end
