//
//  LIRegion.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIPoint.h>

typedef struct {
	float w;
	float h;
	float d;
} LISize_t;

typedef union {
	LIPoint_t p;
	float i[4];
} LILocation_t;

typedef union {
	LISize_t s;
	float i[3];
} LIVolume_t;

typedef LIVolume_t LIScale_t;

typedef struct {
	LILocation_t origin;
	LIVolume_t volume;
} LIRegion_t;

NS_INLINE LISize_t LISizeMake(float width, float height, float depth) {
	return (LISize_t) { .w = width, .h = height, .d = depth };
}

NS_INLINE LIRegion_t LIRegionMake(float x, float y, float z, float width, float height, float depth) {
	return (LIRegion_t) { .origin.p = LIPointMake(x, y, z, 1), .volume.s = LISizeMake(width, height, depth) };
}

@interface LIRegion : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIRegion_t region;

- (instancetype)initWithRegion:(LIRegion_t)region;
+ (instancetype)regionWithRegion:(LIRegion_t)region;
+ (instancetype)regionWithOrigin:(LIPoint_t)origin size:(LISize_t)size;
+ (instancetype)regionWithX:(float)x y:(float)y z:(float)z width:(float)width height:(float)height depth:(float)depth;

@end
