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

NS_INLINE LIPoint_t LIPointTranslate(LIPoint_t p, LIVector_t v) {
	LIPoint_t p2;
	p2.x = p.x + v.x, p2.y = p.y + v.y, p2.z = p.z + v.z, p2.w = p.w;
	return p2;
}

NS_INLINE LIPoint_t LIPointScale(LIPoint_t p, float factor) {
	LIPoint_t p2;
	p2.x = p.x*factor, p2.y = p.y*factor, p2.z = p.z*factor, p2.w = 1;
	return p2;
}

NS_INLINE BOOL LIPointIsOrigin(LIPoint_t p) {
	return p.x == 0.0f && p.y == 0.0f && p.z == 0.0f;
}

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
