//
//  LIRange.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
	float p;
	float d;
} LIRange_t;

NS_INLINE LIRange_t LIRangeMake(float position, float distance) {
	return (LIRange_t){ .p = position, .d = distance };
};

NS_INLINE BOOL LIRangeEquals( LIRange_t r1, LIRange_t r2) {
	return r1.p == r2.p && r1.d == r2.d;
}

@interface LIRange : NSObject<NSCopying, NSCoding>

@property (nonatomic, readonly) LIRange_t range;

- (instancetype)initWithRange:(LIRange_t)range;
+ (instancetype)rangeWithRange:(LIRange_t)range;
+ (instancetype)rangeWithPosition:(float)position distance:(float)distance;

@end
