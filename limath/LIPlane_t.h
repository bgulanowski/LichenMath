//
//  LIPlane_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-08-29.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#ifndef LIPlane_t_h
#define LIPlane_t_h

#include <LichenMath/LILine_t.h>

typedef LIPoint_t LIPlane_t;

#define LIPlaneZero LIPointZero


#define LIPlaneMake(p, q, r) LIPointMake((p), (q), (r))
#define LIPlaneEqualToPlane(p1, p2) LIPointEqualToPoint((p1), (p2))


// Parametric plane
typedef struct {
    LIPoint_t p;
    LIPoint_t q;
    LIPoint_t r;
} LIPlanePPP_t;

// Simplified parametric plane
typedef struct {
    LIPoint_t p;
    LIVector_t s;
    LIVector_t t;
} LIPlanePVV_t;

extern const LIPlanePVV_t LIPlanePVVZero;
extern const LIPlanePVV_t LIPlanePVVXY;
extern const LIPlanePVV_t LIPlanePVVYZ;
extern const LIPlanePVV_t LIPlanePVVZX;

static inline LIPlanePVV_t LIPlanePVVMake(LIPoint_t p, LIVector_t v1, LIVector_t v2) {
    return (LIPlanePVV_t) { p, v1, v2 };
}

static inline LIPlanePPP_t LIPlanePPPMake(LIPoint_t p, LIPoint_t q, LIPoint_t r) {
    return (LIPlanePPP_t) { p, q, r };
}

static inline LIPlanePVV_t LIPlanePVVFromPlanePPP(LIPlanePPP_t p) {
    return LIPlanePVVMake(p.p, LIVectorFromPoint(p.q), LIVectorFromPoint(p.r));
}

static inline LIPlanePPP_t LIPlanePPPFromPlanePVV(LIPlanePVV_t p) {
    return LIPlanePPPMake(p.p, LIPointFromVector(p.s, 1.0f), LIPointFromVector(p.t, 1.0f));
}

static inline LIPlane_t LIPlaneFromPoints(LIPoint_t p, LIPoint_t q, LIPoint_t r) {

    // TODO

    return LIPlaneZero;
}

static inline LIPlane_t LIPlaneFromPlanePPP(LIPlanePPP_t p) {
    return LIPlaneFromPoints(p.p, p.q, p.r);
}

static inline LIPlanePVV_t LIPlaneNormalize(LIPlanePVV_t p) {
    return (LIPlanePVV_t){ p.p, LIVectorNormalize(p.s), LIVectorNormalize(p.t) };
}

static inline bool LILineIsParallelToPlane(LILine_t l, LIPlanePVV_t p) {
    return false;
}

static inline LIPlane_t LIPlaneFromLines(LILine_t l1, LILine_t l2) {
    LIPoint_t x = LILineLineIntersection(l1, l2);
    if (LIPointIsZero(x)) {
        return LIPlaneZero;
    }
    
    // Calculate A, B, C and D

    // FIXME: temporary
    return LIPlaneZero;
}

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



#endif /* LIPlane_t_h */
