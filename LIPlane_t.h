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

typedef struct {
    LIPoint_t p;
    LIVector_t s;
    LIVector_t t;
} LIPlane_t;

extern const LIPlane_t LIPlaneZero;
extern const LIPlane_t LIPlaneXY;
extern const LIPlane_t LIPlaneYZ;
extern const LIPlane_t LIPlaneZX;

static inline bool LILineIsParallelToPlane(LILine_t l, LIPlane_t p) {
    return false;
}

static inline LIPlane_t LIPlaneMake(LIPoint_t p, LIVector_t v1, LIVector_t v2) {
    return (LIPlane_t) { p, v1, v2 };
}

static inline LIPlane_t LIPlaneFromLines(LILine_t l1, LILine_t l2) {
    // FIXME: temporary
    return LIPlaneZero;
}

static inline LIPlane_t LIPlaneNormalize(LIPlane_t p) {
    // FIXME: temporary
    return LIPlaneZero;
}

#endif /* LIPlane_t_h */
