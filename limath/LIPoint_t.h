//
//  LIPoint_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#pragma once

#include <LichenMath/LIVector_t.h>
#include <LichenMath/LIMathUtilities.h>

#include <stdbool.h>

typedef struct {
	float x;
	float y;
	float z;
	float w;
} LIPoint_t;

extern const LIPoint_t LIPointZero;
extern const LIPoint_t LIPointOrigin;

typedef LIPoint_t LIVector4_t;

static inline LIPoint_t LIPointMake(float x, float y, float z, float w) {
	return (LIPoint_t){ x, y, z, w };
}

static inline bool LIPointIsZero(LIPoint_t p) {
    return p.w == 0.0f;
}

static inline bool LIPointIsNormal(LIPoint_t p) {
    return p.w == 1.0f;
}

static inline LIPoint_t LIPointNormalize(LIPoint_t p) {
    float invw = 1.0f/p.w;
    return p.w == 1.0f ? p : LIPointMake(p.x*invw, p.y*invw, p.z*invw, 1.0f);
}

static inline bool LIPointEqualToPoint(LIPoint_t p1, LIPoint_t p2) {
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z && p1.w == p2.w;
}

static inline bool LIPointEqualToPoint2D(LIPoint_t p1, LIPoint_t p2) {
    return ((p1.x == p2.x && p1.y == p2.y) ||
            (p1.x == p2.x && p1.z == p2.z) ||
            (p1.y == p2.y && p1.z == p2.z));
}

static inline bool LIPointIsOrigin(LIPoint_t p) {
    return LIPointEqualToPoint(p, LIPointOrigin);
}

static inline LIPoint_t LIPointTranslate(LIPoint_t p, LIVector_t v) {
    return LIPointMake(p.x + v.x, p.y + v.y, p.z + v.z, p.w);
}

static inline LIPoint_t LIPointScale(LIPoint_t p, float s) {
    return LIPointMake(p.x*s, p.y*s, p.z*s, 1.0f);
}

static inline LIPoint_t LIPointMap(LIPoint_t p, float(^block)(float e)) {
    p.x = block(p.x); p.y = block(p.y); p.z = block(p.z);
    return p;
}

static inline LIPoint_t LIPointAlign(LIPoint_t p) {
    return LIPointMake(LIFloatAlign(p.x), LIFloatAlign(p.y), LIFloatAlign(p.z), p.w);
}

static inline LIVector_t LIVectorFromPoint(LIPoint_t p) {
    return LIVectorMake(p.x, p.y, p.z);
}

static inline LIPoint_t LIPointFromVector(LIVector_t v, float w) {
    return LIPointMake(v.x, v.y, v.z, w);
}

static inline bool LIPointEqualToVector(LIPoint_t p, LIVector_t v) {
    return p.w == 1.0f && p.x == v.x && p.y == p.y && p.z == p.z;
}

static inline LIVector_t LIPointDifference(LIPoint_t p1, LIPoint_t p2) {
    return LIVectorSubtract(LIVectorFromPoint(LIPointNormalize(p1)), LIVectorFromPoint(LIPointNormalize(p2)));
}

static inline float LIPointDistance(LIPoint_t p1, LIPoint_t p2) {
    return LIVectorLength(LIPointDifference(p1, p2));
}

static inline bool LIPointBetweenPointsX(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIFloatBetweenFloats(p.x, p1.x, p2.x);
}

static inline bool LIPointBetweenPointsY(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIFloatBetweenFloats(p.y, p1.y, p2.y);
}

static inline bool LIPointBetweenPointsZ(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIFloatBetweenFloats(p.z, p1.z, p2.z);
}

static inline bool LIPointBetweenPointsXY(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIPointBetweenPointsX(p, p1, p2) && LIPointBetweenPointsY(p, p1, p2);
}

static inline bool LIPointBetweenPointsYZ(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIPointBetweenPointsY(p, p1, p2) && LIPointBetweenPointsZ(p, p1, p2);
}

static inline bool LIPointBetweenPointsZX(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIPointBetweenPointsZ(p, p1, p2) && LIPointBetweenPointsX(p, p1, p2);
}

static inline bool LIPointBetweenPoints(LIPoint_t p, LIPoint_t p1, LIPoint_t p2) {
    return LIPointBetweenPointsX(p, p1, p2) && LIPointBetweenPointsY(p, p1, p2) && LIPointBetweenPointsZ(p, p1, p2);
}
