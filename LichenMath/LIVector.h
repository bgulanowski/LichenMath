//
//  LIVector.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
	float x;
	float y;
	float z;
} LIVector_t;

NS_INLINE LIVector_t LIVectorMake(float x, float y, float z) {
	return (LIVector_t){.x = x, .y = y, .z = z};
}

NS_INLINE LIVector_t LIVectorInverse(LIVector_t v) {
	return LIVectorMake(-v.x, -v.y, -v.z);
}

NS_INLINE LIVector_t LIVectorAdd(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.x+b.x, v.y = a.y+b.y, v.z = a.z+b.z;
	return v;
}

NS_INLINE LIVector_t LIVectorSubtract(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	v.z = a.z-b.z;
	return v;
}

NS_INLINE float LIVectorLength(LIVector_t v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

NS_INLINE LIVector_t LIVectorNormalize(LIVector_t a) {
	
	LIVector_t v = {};
	float length = LIVectorLength(a);
    
    if(length)
        v.x = a.x/length, v.y = a.y/length, v.z = a.z/length;
	
	return v;
}

NS_INLINE LIVector_t LICrossProductVectors3(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.y*b.z - a.z*b.y;
	v.y = a.z*b.x - a.x*b.z;
	v.z = a.x*b.y - a.y*b.x;
	return v;
}

NS_INLINE float LIDotProductVectors3(LIVector_t a, LIVector_t b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

NS_INLINE float LIInteriorAngleVector3(LIVector_t a, LIVector_t b) {
    
    a = LIVectorNormalize(a);
    b = LIVectorNormalize(b);
    
    return acosf( LIDotProductVectors3(a, b) );
}

extern NSString *LIVectorToString(LIVector_t v);
extern LIVector_t LIVectorFromString(NSString *s);

@interface LIVector : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIVector_t vector;

- (instancetype)initWithVector:(LIVector_t)vector;
+ (instancetype)vectorWithVector:(LIVector_t)vector;
+ (instancetype)vectorWithX:(float)x y:(float)y z:(float)z;

@end
