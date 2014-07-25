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
} LIRange2f;

NS_INLINE LIRange2f LIRange2fMake(float position, float distance) {
	return (LIRange2f){ .p = position, .d = distance };
};

NS_INLINE BOOL LIRange2fEquals( LIRange2f r1, LIRange2f r2) {
	return r1.p == r2.p && r1.d == r2.d;
}

@interface LIRange : NSObject<NSCopying, NSCoding>

@property (nonatomic, readonly) LIRange2f range2f;

- (instancetype)initWithRange:(LIRange2f)range;
+ (instancetype)rangeWithRange:(LIRange2f)range;
+ (instancetype)rangeWithPosition:(float)position distance:(float)distance;

@end
