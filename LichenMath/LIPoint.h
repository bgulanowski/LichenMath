//
//  LIPoint_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIVector.h>

typedef struct {
	float x;
	float y;
	float z;
	float w;
} LIPoint_t;

#define LIVector4_t LIPoint_t

NS_INLINE LIPoint_t LIPointMake(float x, float y, float z, float w) {
	return (LIPoint_t){.x = x, .y = y, .z = z, .w = w};
}

static inline LIPoint_t LIPointTranslate(LIPoint_t p, LIVector_t v) {
	LIPoint_t r;
	r.x = p.x + v.x, r.y = p.y + v.y, r.z = p.z + v.z, r.w = p.w;
	return r;
}

static inline LIPoint_t LIPointScale(LIPoint_t a, float factor) {
	LIPoint_t v;
	v.x = a.x*factor, v.y = a.y*factor, v.z = a.z*factor, v.w = 1;
	return v;
}

extern NSString *LIPointToString(LIPoint_t p);
extern LIPoint_t LIPointFromString(NSString *string);

@interface LIPoint : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIPoint_t point;

- (instancetype)initWithPoint:(LIPoint_t)point;
+ (instancetype)pointWithPoint:(LIPoint_t)point;
+ (instancetype)pointWithX:(float)x y:(float)y z:(float)z w:(float)w;

@end
