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

typedef enum {
    LIVectorElementX,
    LIVectorElementY,
    LIVectorElementZ
} LIVectorElement;

extern const LIVector_t LIVectorZero;

static inline LIVector_t LIVectorMake(float x, float y, float z) {
	return (LIVector_t){x, y, z};
}

static inline bool LIVectorEqualToVector(LIVector_t v1, LIVector_t v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

static inline bool LIVectorIsZero(LIVector_t v) {
    return LIVectorEqualToVector(v, LIVectorZero);
}

static inline LIVector_t LIVectorInverse(LIVector_t v) {
	return LIVectorMake(-v.x, -v.y, -v.z);
}

static LIVectorElement LIVectorDominantElement(LIVector_t v) {
    LIVector_t a = (LIVector_t) { ABS(v.x), ABS(v.y), ABS(v.z) };
    if (a.x > a.y && a.x > a.z) {
        return LIVectorElementX;
    }
    else if (a.y > a.z) {
        return LIVectorElementY;
    }
    else {
        return LIVectorElementZ;
    }
}

static inline LIVector_t LIVectorClosestAxis(LIVector_t v) {
    LIVector_t r = LIVectorZero;
    switch (LIVectorDominantElement(v)) {
        case LIVectorElementX:
            r.x = v.x > 0 ? 1.0f : -1.0f;
            break;
        case LIVectorElementY:
            r.y = v.y > 0 ? 1.0f : -1.0f;
            break;
        case LIVectorElementZ:
            r.z = v.z > 0 ? 1.0f : -1.0f;
            break;
    }
    return r;
}

static inline LIVector_t LIVectorAdd(LIVector_t a, LIVector_t b) {
    return LIVectorMake(a.x+b.x, a.y+b.y, a.z+b.z);
}

static inline LIVector_t LIVectorSubtract(LIVector_t a, LIVector_t b) {
    return LIVectorMake(a.x-b.x, a.y-b.y, a.z-b.z);
}

static inline float LIVectorLength(LIVector_t v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

static inline LIVector_t LIVectorNormalize(LIVector_t a) {
    if (LIVectorIsZero(a)) {
        return a;
    }
    else {
        float length = LIVectorLength(a);
        return LIVectorMake(a.x/length, a.y/length, a.z/length);
    }
}

static inline LIVector_t LIVectorCrossProduct(LIVector_t a, LIVector_t b) {
	LIVector_t v;
	v.x = a.y*b.z - a.z*b.y;
	v.y = a.z*b.x - a.x*b.z;
	v.z = a.x*b.y - a.y*b.x;
	return v;
}

static inline float LIVectorDotProduct(LIVector_t a, LIVector_t b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline float LIVectorInteriorAngle(LIVector_t a, LIVector_t b) {
    
    a = LIVectorNormalize(a);
    b = LIVectorNormalize(b);
    
    return acosf( LIVectorDotProduct(a, b) );
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
