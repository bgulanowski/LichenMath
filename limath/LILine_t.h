//
//  LILine_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-08-29.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#ifndef LILine_t_h
#define LILine_t_h

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

// Find plane intersections
// Equation of a plane is ax + by + cz + d = 0
// Equation of XY plane is z = 0
// Equation of YZ plane is x = 0
// Equation of ZX plane is y = 0

// set x' (or p2.x), y' (or p2.y) or z' (or p2.z) to 0 and solve for t
// then use t to solve for the remaining elements of p2
// t * l.v.x = l.p.x - p2.x --> p2.x = - (t * l.v.x) / l.p.x
// t * l.v.y = l.p.y - p2.y --> p2.y = - (t * l.v.y) / l.p.y
// t * l.v.z = l.p.z - p2.z --> p2.z = - (t * l.v.z) / l.p.z



static inline LIPoint_t LILineXYIntercept(LILine_t l) {
    if (l.v.z == 0) {
        return LIPointZero;
    }
    else {
        float t = l.p.z / l.v.z;
        return LIPointMake(- (t * l.v.x) / l.p.x, - (t * l.v.y) / l.p.y, 0, 1.0f);
    }
}

static inline LIPoint_t LILineYZIntercept(LILine_t l) {
    if (l.v.x == 0) {
        return LIPointZero;
    }
    else {
        float t = l.p.x / l.v.x;
        return LIPointMake(0, - (t * l.v.y) / l.p.y, - (t * l.v.z) / l.p.z, 1.0f);
    }
}

static inline LIPoint_t LILineZXIntercept(LILine_t l) {
    if (l.v.y) {
        return LIPointZero;
    }
    else {
        float t = l.p.y / l.v.y;
        return LIPointMake(- (t * l.v.x) / l.p.x, 0, - (t * l.v.z) / l.p.z, 1.0f);
    }
}

static inline LILine_t LILineNormalize(LILine_t l) {
    
    if (LIVectorIsZero(l.v)) {
        return LILineZero;
    }
    else {
        switch (LIVectorDominantElement(l.v)) {
            case LIVectorElementX:
                return LILineMake(LILineYZIntercept(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementY:
                return LILineMake(LILineZXIntercept(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementZ:
                return LILineMake(LILineXYIntercept(l), LIVectorNormalize(l.v));
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
    // FIXME: temporary
    return false;
}

static inline float LILineDistanceToLine(LILine_t l1, LILine_t l2) {
    // FIXME: temporary
    return 0.0f;
}

#endif /* LILine_t_h */
