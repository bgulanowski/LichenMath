//
//  LILine_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-08-29.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#ifndef LILine_t_h
#define LILine_t_h

#import <LichenMath/LIPoint_t.h>

// Parametric line
typedef struct {
    LIPoint_t p;
    LIVector_t v;
} LILine_t;

extern const LILine_t LILineZero;
extern const LILine_t LILineXAxis;
extern const LILine_t LILineYAxis;
extern const LILine_t LILineZAxis;

static inline LILine_t LILineMake(LIPoint_t p, LIVector_t v) {
    return (LILine_t){ p, LIVectorNormalize(v) };
}

static inline bool LILineIsZero(LILine_t l) {
    return LIVectorIsZero(l.v) || LIPointEqualToVector(l.p, l.v);
}

static inline bool LILineIsValid(LILine_t l) {
    return !LILineIsZero(l);
}

// Line Equation
// P' = P + tV
// where P is a point on the line, P = line.p = l.p = <x, y, z>
//       V = line.v = l.v = <a, b, c>
//       P' is a new point, P' = <x', y', z'>
// and therefore <x', y', z'> = <x, y, z> + t<a, b, c>
// or x' = x + ta, y' = y + tb, z' = z + tc
// or t = (x' - x)/a = (y' - y)/b = (z' - z)/c
// or t = (p2.x - l.p.x)/l.v.x = (p2.y - l.p.y)/l.v.y = (p2.z - l.p.z)/l.v.z

static inline float LILineParamX(LILine_t l, float x) {
    return (x - l.p.x) / l.v.x;
}

static inline float LILineParamY(LILine_t l, float y) {
    return (y - l.p.y) / l.v.y;
}

static inline float LILineParamZ(LILine_t l, float z) {
    return (z - l.p.z) / l.v.z;
}

static inline float LILineParamForPoint(LILine_t l, LIPoint_t p) {
    if (l.v.x != 0) {
        return LILineParamX(l, p.x);
    }
    else if (l.v.y != 0) {
        return LILineParamY(l, p.y);
    }
    else {
        return LILineParamZ(l, p.z);
    }
}

static inline LIPoint_t LILinePointForParameter(LILine_t l, float t) {
    return (isfinite(t)) ? LIPointTranslate(l.p, LIVectorScale(l.v, t)) : LIPointZero;
}

// Note that LIPointZero is a point at Infinity, *not* the Origin
static inline LIPoint_t LILineInterceptX(LILine_t l, float x) {
    return (l.v.x == 0) ? LIPointZero : LILinePointForParameter(l, LILineParamX(l, x));
}

static inline LIPoint_t LILineInterceptY(LILine_t l, float y) {
    return (l.v.y == 0) ? LIPointZero : LILinePointForParameter(l, LILineParamY(l, y));
}

static inline LIPoint_t LILineInterceptZ(LILine_t l, float z) {
    return (l.v.z == 0) ? LIPointZero : LILinePointForParameter(l, LILineParamZ(l, z));
}

static inline LIPoint_t LILineInterceptX0(LILine_t l) {
    return LILineInterceptX(l, 0);
}

static inline LIPoint_t LILineInterceptY0(LILine_t l) {
    return LILineInterceptY(l, 0);
}

static inline LIPoint_t LILineInterceptZ0(LILine_t l) {
    return LILineInterceptZ(l, 0);
}

extern LILine_t LILineNormalize(LILine_t l);

static inline bool LILineEqualToLine(LILine_t l1, LILine_t l2) {
    LILine_t l1n = LILineNormalize(l1);
    LILine_t l2n = LILineNormalize(l2);
    return LIPointEqualToPoint(l1n.p, l2n.p) && LIVectorEqualToVector(l1n.v, l2n.v);
}

static inline bool LILineParallelToLine(LILine_t l1, LILine_t l2) {
    LIVector_t lv1n = LIVectorNormalize(l1.v);
    LIVector_t lv2n = LIVectorNormalize(l2.v);
    return LIVectorEqualToVector(lv1n, lv2n) || LIVectorEqualToVector(lv1n, LIVectorInverse(lv2n));
}


// Line-Line Intersections

extern float LILineLineIntersectionParameterX(LILine_t l1, LILine_t l2);
extern float LILineLineIntersectionParameterY(LILine_t l1, LILine_t l2);
extern float LILineLineIntersectionParameterZ(LILine_t l1, LILine_t l2);

extern LIPoint_t LILineLineIntersection(LILine_t l1, LILine_t l2);

static inline bool LILineIntersectsLine(LILine_t l1, LILine_t l2) {
    // is there a faster check?
    return LIPointIsNormal(LILineLineIntersection(l1, l2));
}

static inline float LILineDistanceToLine(LILine_t l1, LILine_t l2) {
    // FIXME: temporary
    return 0.0f;
}

#endif /* LILine_t_h */
