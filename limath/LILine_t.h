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
    return (LILine_t){ p, v };
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

// Note that LIPointZero is a point at Infinity, *not* the Origin
static inline LIPoint_t LILineXYIntercept(LILine_t l, float z) {
    if (l.v.z == 0) {
        // line is parallel to XY plane
        return LIPointZero;
    }
    else {
        float t = (z - l.p.z) / l.v.z;
        return LIPointMake(l.p.x + t * l.v.x, l.p.y + t * l.v.y, z, 1.0f);
    }
}

static inline LIPoint_t LILineYZIntercept(LILine_t l, float x) {
    if (l.v.x == 0) {
        // line is parallel to YZ plane
        return LIPointZero;
    }
    else {
        float t = (x - l.p.x) / l.v.x;
        return LIPointMake(x, l.p.y + t * l.v.y, l.p.z + t * l.v.z, 1.0f);
    }
}

static inline LIPoint_t LILineZXIntercept(LILine_t l, float y) {
    if (l.v.y) {
        // line is parallel to ZX plane
        return LIPointZero;
    }
    else {
        float t = (y - l.p.y) / l.v.y;
        return LIPointMake(l.p.x + t * l.v.x, y, l.p.z + t * l.v.z, 1.0f);
    }
}

static inline LIPoint_t LILineXYInterceptZ0(LILine_t l) {
    return LILineXYIntercept(l, 0);
}

static inline LIPoint_t LILineYZInterceptX0(LILine_t l) {
    return LILineYZIntercept(l, 0);
}

static inline LIPoint_t LILineZXInterceptY0(LILine_t l) {
    return LILineZXIntercept(l, 0);
}

static inline LILine_t LILineNormalize(LILine_t l) {
    
    if (LIVectorIsZero(l.v)) {
        return LILineZero;
    }
    else {
        switch (LIVectorDominantElement(l.v)) {
            case LIVectorElementX:
                return LILineMake(LILineYZInterceptX0(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementY:
                return LILineMake(LILineZXInterceptY0(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementZ:
                return LILineMake(LILineXYInterceptZ0(l), LIVectorNormalize(l.v));
                break;
        }
    }
}

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

static inline LIPoint_t LILineLineIntersection(LILine_t l1, LILine_t l2) {
    
    
    
    // FIXME: temporary
    return LIPointZero;
}

static inline bool LILineIntersectsLine(LILine_t l1, LILine_t l2) {
    // is there a faster check?
    return LIPointIsNormal(LILineLineIntersection(l1, l2));
}

static inline float LILineDistanceToLine(LILine_t l1, LILine_t l2) {
    // FIXME: temporary
    return 0.0f;
}

#endif /* LILine_t_h */
