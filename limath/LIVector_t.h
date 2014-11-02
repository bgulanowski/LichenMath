//
//  LIVector_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#pragma once

#include <stdbool.h>
#include <math.h>

typedef struct {
	float x;
	float y;
	float z;
} LIVector_t;

typedef struct {
	LIVector_t v;
	float a;
} LIRotation_t;
extern const LIVector_t LIVectorZero;

static inline LIVector_t LIVectorMake(float x, float y, float z) {
	return (LIVector_t){.x = x, .y = y, .z = z};
}

static inline LIVector_t LIVectorInverse(LIVector_t v) {
	return LIVectorMake(-v.x, -v.y, -v.z);
}

static inline LIVector_t LIVectorAdd(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.x+b.x, v.y = a.y+b.y, v.z = a.z+b.z;
	return v;
}

static inline LIVector_t LIVectorSubtract(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	v.z = a.z-b.z;
	return v;
}

static inline float LIVectorLength(LIVector_t v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

static inline LIVector_t LIVectorNormalize(LIVector_t a) {
	
	LIVector_t v = {};
	float length = LIVectorLength(a);
    
    if(length)
        v.x = a.x/length, v.y = a.y/length, v.z = a.z/length;
	
	return v;
}

static inline LIVector_t LICrossProductVectors3(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.y*b.z - a.z*b.y;
	v.y = a.z*b.x - a.x*b.z;
	v.z = a.x*b.y - a.y*b.x;
	return v;
}

static inline float LIDotProductVectors3(LIVector_t a, LIVector_t b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline float LIInteriorAngleVector3(LIVector_t a, LIVector_t b) {
    
    a = LIVectorNormalize(a);
    b = LIVectorNormalize(b);
    
    return acosf( LIDotProductVectors3(a, b) );
}

static inline bool LIVectorIsXAligned(LIVector_t v) {
	return v.y == 0.0f && v.z == 0.0f;
}

static inline bool LIVectorIsYAligned(LIVector_t v) {
	return v.x == 0.0f && v.z == 0.0f;
}

static inline bool LIVectorIsZAligned(LIVector_t v) {
	return v.x == 0.0f && v.y == 0.0f;
}
