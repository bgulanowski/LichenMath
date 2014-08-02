//
//  LIRegion_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#ifndef LichenMath_LIRegion_t_h
#define LichenMath_LIRegion_t_h

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

typedef struct {
	LILocation_t origin;
	LIVolume_t volume;
} LIRegion_t;

static inline LISize_t LISizeMake(float width, float height, float depth) {
	return (LISize_t) { .w = width, .h = height, .d = depth };
}

static inline LIRegion_t LIRegionMake(float x, float y, float z, float width, float height, float depth) {
	return (LIRegion_t) { .origin.p = LIPointMake(x, y, z, 1), .volume.s = LISizeMake(width, height, depth) };
}

#endif
