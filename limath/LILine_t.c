//
//  LILine_t.c
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-27.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#include "LILine_t.h"

// project lines onto an orthogonal plane and substitute one equation into the other
// plane must not be perpendicular to either line

// There are three combinations, and two variations for each, and two derivations for each variation. Phew.
// For each combination, there are two equations in two unknowns. It's possible to isolate either unknown
// in either equation, and substitute it into the other equation, for 2x2 = 4 variations.

// x' = x + ta, y' = y + tb, z' = z + tc
// aka
// x  = x1 + t1 * a1, y = y1 + t1 * b1, z = z1 + t1 * c1, and
// x  = x2 + t2 * a2, y = y2 + t2 * b2, z = z2 + t2 * c2

// if one line is parallel to the X axis (or nearly so),
// project against Y-Z plane:
// y1 + t1 * b1 = y2 + t2 * b2, and
// z1 + t1 * c1 = z2 + t2 * c2

// isolate t2 in second eq'n:
// z1 + t1 * c1 =  z2 + t2 * c2
//      t2 * c2 =  t1 * c1 + z1 - z2
//      t2      = (t1 * c1 + z1 - z2) / c2 (1)

// substitute t2 into first eq'n
// y1 + t1 * b1 = y2 + t2 * b2
//      t1 * b1 = y2 + t2 * b2 - y1
//      t1 * b1 =      t2 * b2 + y2 - y1

// expand
// t1 * b1 = ((t1 * c1           +  z1 - z2)  / c2) * b2 + y2 - y1
// t1 * b1 = ((t1 * c1)          + (z1 - z2)) / c2  * b2 + y2 - y1
// t1 * b1 =   t1 * c1 / c2 * b2 + (z1 - z2)  / c2  * b2 + y2 - y1

// t1 *  b1 - t1 * c1 / c2 * b2  =  (z1 - z2)/c2 * b2 + y2 - y1
// t1 * (b1 -      c1 / c2 * b2) =  (z1 - z2)/c2 * b2 + y2 - y1
// t1                            = ((z1 - z2)/c2 * b2 + y2 - y1)/(b1 - c1 / c2 * b2)

// t1 = ((z1 - z2) * b2 / c2 + y2 - y1) / (b1 - c1 * b2 / c2)

// then, substitute calculated value of t1 into (1) to get t2
// finally, calculate intersection point using t1 and t2 and parametric eq'ns of the lines

// if one line is parallel to the Y axis (or nearly so),
// project against Z-X plane:
// ... cycle x -> y, y -> z, z -> x, a -> b, b -> c, c-> a
// t1 = ((x1 - x2)/a2 * c2 + z2 - z1)/(c1 - a1/a2)
// t2 = (t1 * a1 + x1 - x2)/a2

// if one line is parallel to the Z axis (or nearly so),
// project against the X-Y plane:
// t1 = ((y1 - y2)/b2 * a2 + x2 - x1)/(a1 - b1/b2)
// t2 = (t1 * b1 + y1 - y2)/b2


// Alternately, solve for t1 with b value in denominator:

// isolate t2 in first eq'n:
// y1 + t1 * b1 = y2 + t2 * b2, or
// y2 + t2 * b2 = y1 + t1 * b1
//      t2 * b2 =      t1 * b1 + y1 - y2
//      t2      =     (t1 * b1 + y1 - y2) / b2

// substitute t2 into second eq'n:
// z1 + t1 * c1 = z2 + t2 * c2
//      t1 * c1 =      t2 * c2 + z2 - z1

// t1 * c1 =  t2                      * c2 + z2 - z1
// t1 * c1 = (t1 * b1 + y1 - y2) / b2 * c2 + z2 - z1

// preferred form ('*' before '/'):
// t1 * c1 = (t1 * b1             + y1 - y2) * c2 / b2 + z2 - z1

// expand
// t1 * c1 = (t1 * b1) * c2 / b2 + (y1 - y2) * c2 / b2 + z2 - z1

// isolate
// t1 *  c1 - (t1 * b1) * c2 / b2  = (y1 - y2) * c2 / b2 + z2 - z1
// t1 * (c1 -       b1  * c2 / b2) = (y1 - y2) * c2 / b2 + z2 - z1

// t1 = ((y1 - y2) * c2 / b2 + z2 - z1) / (c1 - b1 * c2 / b2)

// compare to:
// t1 = ((z1 - z2) * b2 / c2 + y2 - y1) / (b1 - c1 * b2 / c2)
// z's and y's switch places, b's and c's switch places


/// Alternate derivation
// -- These are not used in the functions below. Here purely for

// isolate t1 in second eq'n:
// z1 + t1 * c1 =  z2 + t2 * c2
//      t1 * c1 =  z2 + t2 * c2 - z1
//      t1      = (z2 + t2 * c2 - z1) / c1
//      t1      = (t2 * c2 + z2 - z1) / c1

// simplify first eq'n:
// y1 + t1 * b1 = y2 + t2 * b2, or
// y2 + t2 * b2 = y1 + t1 * b1
//      t2 * b2 =      t1 * b1 + y1 - y2

// substitue t1 into the first eq'n:
// t2 * b2 = ((t2 * c2 + z2 - z1) / c1) * b1 + y1 - y2
// t2 * b2 =  (t2 * c2 + z2 - z1) / c1  * b1 + y1 - y2

// preferred form ( * before / ):
// t2 * b2 =  (t2 * c2 + z2 - z1) * b1  / c1 + y1 - y2

// expand and isolate t2:
// t2 * b2 = (t2 * c2)      + (z2 - z1) * b1 / c1 + y1 - y2
// t2 * b2 = (t2 * c2) / c1 + (z2 - z1) * b1 / c1 + y1 - y2
// t2 * b2 =  t2 * c2  / c1 + (z2 - z1) * b1 / c1 + y1 - y2

// t2 *  b2 - t2 * c2 / c1  = (z2 - z1) * b1 / c1 + y1 - y2
// t2 * (b2      - c2 / c1) = (z2 - z1) * b1 / c1 + y1 - y2

// t2 = ((z2 - z1) * b1 / c1 + y1 - y2) / (b2 - c2 / c1)


// t2 with b1 in the denominator

// isolate t1 in first eq'n, substitute into second eq'n:
// y1 + t1 * b1 = y2 + t2 * b2
// y1 + t1 * b1 =      t2 * b2 + y2
//      t1 * b1 =      t2 * b2 + y2 - y1

// t1 * b1 =  t2 * b2 + y2 - y1
// t1      = (t2 * b2 + y2 - y1) / b1

// z1 + t1 * c1 = z2 + t2 * c2
// z2 + t2 * c2 = z1 + t1 * c1
//      t2 * c2 = z1 + t1 * c1      - z2
//      t2 * c2 =      t1 * c1 + z1 - z2

// t2 * c2 = t1                       * c1 + z1 - z2
// t2 * c2 = (t2 * b2 + y2 - y1) / b1 * c1 + z1 - z2
// t2 * c2 = (t2 * b2 + y2 - y1) * c1 / b1 + z1 - z2

// expand:
// t2 * c2 = ((t2 * b2)            + (y2 - y1)) * c1 / b1 + z1 - z2
// t2 * c2 =  (t2 * b2) * c1 / b1  + (y2 - y1)  * c1 / b1 + z1 - z2
// t2 * c2 =  (t2 * b2  * c1 / b1) + (y2 - y1)  * c1 / b1 + z1 - z2

// collect like terms on left:
// t2 * c2 - t2 * b2 * c1 / b1 = (y2 - y1) * c1 / b1 + z1 - z2

// isolate:
// t2 * (c2 - b2 * c1 / b1) =  (y2 - y1) * c1 / b1 + z1 - z2
// t2                       = ((y2 - y1) * c1 / b1 + z1 - z2)/(c2 - b2 * c1 / b1)



float LILineLineIntersectionParameterX(LILine_t l1, LILine_t l2) {
    if (l2.v.z != 0) {
        // t1 = ((z1 - z2) * b2 / c2 + y2 - y1) / (b1 - c1 * b2 / c2)
        return ((l1.p.z - l2.p.z) * l2.v.y / l2.v.z + l2.p.y - l1.p.y) / (l1.v.y - l1.v.z * l2.v.y / l2.v.z);
    }
    else {
        // t1 = ((y1 - y2) * c2 / b2 + z2 - z1) / (c1 - b1 * c2 / b2)
        return ((l1.p.y - l2.p.z) * l2.v.z / l2.v.y + l2.p.z - l1.p.z) / (l1.v.z - l1.v.y * l2.v.z / l2.v.y);
    }
}

float LILineLineIntersectionParameterY(LILine_t l1, LILine_t l2) {
    if (l2.v.x != 0) {
        // t1 = ((x1 - x2) * c2 / a2 + z2 - z1) / (c1 - a1 * c2 / a2)
        return ((l1.p.x - l2.p.x) / l2.v.x * l2.v.z + l2.p.z - l1.p.z) / (l1.v.z - l1.v.x * l2.v.z / l2.v.x);
    }
    else {
        // t1 = ((z1 - z2) * a2 / c2 + x2 - x1) / (a1 - c1 * a2 / c2)
        return ((l1.p.z - l2.p.z) * l2.v.x / l2.v.z + l2.p.x - l1.p.x) / (l1.v.x - l1.v.z * l2.v.x / l2.v.z);
    }
}

float LILineLineIntersectionParameterZ(LILine_t l1, LILine_t l2) {
    if (l2.v.y != 0) {
        // t1 = ((y1 - y2) * a2 / b2 + x2 - x1) / (a1 - b1 * a2 / b2)
        return ((l1.p.y - l2.p.y) * l2.v.x / l2.v.y + l2.p.x - l1.p.x) / (l1.v.x - l1.v.y * l2.v.x / l2.v.y);
    }
    else {
        // t1 = ((x1 - x2) * b2 / a2 + y2 - y1) / (b1 - a1 * b2 / a2)
        return ((l1.p.x - l2.p.x) * l2.v.y / l2.v.x + l2.p.y - l1.p.y) / (l1.v.y - l1.v.x * l2.v.y / l2.v.x);
    }
}

LIPoint_t LILineLineIntersection(LILine_t l1, LILine_t l2) {
    
    // if both lines are parallel, there is no solution
    LIVector_t x = LIVectorCrossProduct(l1.v, l2.v);
    if (LIVectorIsZero(x)) {
        return LIPointZero;
    }
    
    LIVectorElement axis = LIVectorDominantElement(x);
    
    switch (axis) {
        case LIVectorElementX:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterX(l1, l2));
        case LIVectorElementY:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterY(l1, l2));
        case LIVectorElementZ:
            return LILinePointForParameter(l1, LILineLineIntersectionParameterZ(l1, l2));
    }
}
