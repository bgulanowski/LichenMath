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
    return LIPointTranslate(l.p, LIVectorScale(l.v, t));
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

static inline LILine_t LILineNormalize(LILine_t l) {
    
    if (LIVectorIsZero(l.v)) {
        return LILineZero;
    }
    else {
        switch (LIVectorDominantElement(l.v)) {
            case LIVectorElementX:
                return LILineMake(LILineInterceptX0(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementY:
                return LILineMake(LILineInterceptY0(l), LIVectorNormalize(l.v));
                break;
                
            case LIVectorElementZ:
                return LILineMake(LILineInterceptZ0(l), LIVectorNormalize(l.v));
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


// Line-Line Intersections

// project lines onto an orthogonal plane and substitute one equation into the other
// plane must not be perpendicular to either line

// x' = x + ta, y' = y + tb, z' = z + tc
// aka
// x  = x1 + t1 * a1, y = y1 + t1 * b1, z = z1 + t1 * c1, and
// x  = x2 + t2 * a2, y = y2 + t2 * b2, z = z2 + t2 * c2

// if one line is parallel to the X axis (or nearly so),
// project against Y-Z plane:
// y1 + t1 * b1 = y2 + t2 * b2, and
// z1 + t1 * c1 = z2 + t2 * c2

// isolate t2 in second eq'n:
// z1 + t1 * c1 = z2 + t2 * c2
// t2 * c2 = z1 + t1 * c1 - z2
// t2 = (z1 + t1 * c1 - z2)/c2 (1)

// substitute t2 into fist eq'n
// y1 + t1 * b1 = y2 + t2 * b2
// t1 * b1 = y2 + t2 * b2 - y1

// t1 * b1 = y2 + ((z1  + t1 * c1  - z2) /c2) * b2 - y1
// t1 * b1 = y2 +  (z1  + t1 * c1  - z2) /c2  * b2 - y1
// t1 * b1 = y2 +  (z1 + (t1 * c1) - z2) /c2  * b2 - y1

// t1 * b1 = y2 + ((t1 * c1)    +  z1 - z2) /c2  * b2 - y1
// t1 * b1 = y2 + ((t1 * c1)    + (z1 - z2))/c2  * b2 - y1
// t1 * b1 = y2 +  (t1 * c1)/c2 + (z1 - z2) /c2  * b2 - y1

// t1 * b1 - (t1 * c1)/c2 =  y2 + (z1 - z2)/c2 * b2 - y1
// t1 *      (b1 - c1/c2) =  y2 + (z1 - z2)/c2 * b2 - y1
// t1                     = (y2 + (z1 - z2)/c2 * b2 - y1)/(b1 - c1/c2)
// then, substitute calculated value of t1 into (1) to get t2
// finally, calculate intersection point using t1 and t2 and parametric eq'ns of the lines

// if one line is parallel to the Y axis (or nearly so),
// project against Z-X plane:
// ... cycle x -> y, y -> z, z -> x, a -> b, b -> c, c-> a
// t1 = (z2 + (x1 - x2)/a2 * c2 - z1)/(c1 - a1/a2)
// t2 = (x1 + t1 * a1 - x2)/a2

// if one line is parallel to the Z axis (or nearly so),
// project against the X-Y plane:
// t1 = (x2 + (y1 - y2)/b2 * a2 - x1)/(a1 - b1/b2)
// t2 = (y1 + t1 * b1 - y2)/b2


typedef struct {
    float t1;
    float t2;
} LILineParametersPair;

static float LILineLineIntersectionParameterX(LILine_t l1, LILine_t l2) {
    // t1 = (y2 + (z1 - z2)/c2 * b2 - y1)/(b1 - c1/c2)
    return (l2.p.y + (l1.p.z - l2.p.z)/l2.v.z * l2.v.y - l1.p.y)/(l1.v.y - l1.v.z/l2.v.z);
}

static float LILineLineIntersectionParameterY(LILine_t l1, LILine_t l2) {
    // t1 = (z2 + (x1 - x2)/a2 * c2 - z1)/(c1 - a1/a2)
    return (l2.p.z + (l1.p.x - l2.p.x)/l2.v.x * l2.v.z - l1.p.z)/(l1.v.z - l1.v.x/l2.v.x);
}

static float LILineLineIntersectionParameterZ(LILine_t l1, LILine_t l2) {
    // t1 = (x2 + (y1 - y2)/b2 * a2 - x1)/(a1 - b1/b2)
    return (l2.p.x + (l1.p.y - l2.p.y)/l2.v.y * l2.v.x - l1.p.x)/(l1.v.x - l1.v.y/l2.v.y);
}

static inline LILineParametersPair LILineLineIntersectionParametersX(LILine_t l1, LILine_t l2) {
    // t2 = (z1 + t1 * c1 - z2)/c2
    float t1 = LILineLineIntersectionParameterX(l1, l2);
    float t2 = (l1.p.z + t1 * l1.v.z - l2.p.z)/l2.v.z;
    return (LILineParametersPair) { t1, t2 };
}

static inline LILineParametersPair LILineLineIntersectionParametersY(LILine_t l1, LILine_t l2) {
    // t2 = (x1 + t1 * a1 - x2)/a2
    float t1 = LILineLineIntersectionParameterY(l1, l2);
    float t2 = (l1.p.x + t1 * l1.v.x - l2.p.x)/l2.v.x;
    return (LILineParametersPair){ t1, t2 };
}

static inline LILineParametersPair LILineLineIntersectionParametersZ(LILine_t l1, LILine_t l2) {
    // t2 = (y1 + t1 * b1 - y2)/b2
    float t1 = LILineLineIntersectionParameterZ(l1, l2);
    float t2 = (l1.p.y + t1 * l1.v.y - l2.p.y)/l2.v.y;
    return (LILineParametersPair){ t1, t2 };
}

static inline LIPoint_t LILineLineIntersection(LILine_t l1, LILine_t l2) {
    
    // if both lines are parallel, there is no solution
    LIVector_t x = LIVectorCrossProduct(l1.v, l2.v);
    if (LIVectorIsZero(x)) {
        return LIPointZero;
    }
    
    int axis = LIVectorMaxElementIndex(x);
    switch (axis) {
        case 0:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterX(l1, l2));
        case 1:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterY(l1, l2));
        case 2:
        default:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterZ(l1, l2));
    }
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
