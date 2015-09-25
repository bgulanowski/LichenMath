//
//  LIMath.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-10-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#include "LIPlane_t.h"
#include "LIPoint_t.h"
#include "LILine_t.h"
#include "LIRegion_t.h"
#include "LIVector_t.h"

#define VectorZero { 0, 0, 0 }
#define VectorUnitX { 1.0f, 0, 0 }
#define VectorUnitY { 0, 1.0f, 0 }
#define VectorUnitZ { 0, 0, 1.0f }

const LIVector_t LIVectorZero = VectorZero;
const LIVector_t LIVectorUnitX = VectorUnitX;
const LIVector_t LIVectorUnitY = VectorUnitY;
const LIVector_t LIVectorUnitZ = VectorUnitZ;

#define PointZero { 0, 0, 0, 0 }
#define PointOrigin { 0, 0, 0, 1.0f }

const LIPoint_t LIPointZero = PointZero;
const LIPoint_t LIPointOrigin = PointOrigin;

const LILine_t LILineZero = { PointZero, VectorZero };
const LILine_t LILineXAxis = { PointZero, VectorUnitX };
const LILine_t LILineYAxis = { PointZero, VectorUnitY };
const LILine_t LILineZAxis = { PointZero, VectorUnitZ };

const LIPlanePVV_t LIPlanePVVZero = { PointZero, VectorZero, VectorZero };
const LIPlanePVV_t LIPlanePVVXY = { PointZero, VectorUnitX, VectorUnitY };
const LIPlanePVV_t LIPlanePVVYZ = { PointZero, VectorUnitY, VectorUnitZ };
const LIPlanePVV_t LIPlanePVVZX = { PointZero, VectorUnitZ, VectorUnitX };

LIRegionLineIntersection LIRegionIntersectWithLine(LIRegion_t r, LILine_t l) {
    
    LIPoint_t points[2] = { LIPointZero, LIPointZero };
    int count = 0;
    
    LIPoint_t origin = LIRegionOrigin(r);
    LIPoint_t extent = LIRegionExtent(r);
    
    LIPoint_t test = LILineInterceptX(l, origin.x);

    /*
     If the line passes through the origin, it will satisfy all three checks
     for faces 0, 1, and 2; skip individual checks for faces 0, 1 and 2
     */
    
    if (LIPointEqualToPoint(origin, test)) {
        points[count++] = test;
    }
    else {
        if (!LIPointIsZero(test) && LIPointBetweenPointsYZ(test, origin, extent)) {
            points[count++] = test;
        }
        test = LILineInterceptY(l, origin.y);
        if (!LIPointIsZero(test) && LIPointBetweenPointsZX(test, origin, extent)) {
            points[count++] = test;
        }
        if (count < 2) {
            test = LILineInterceptZ(l, origin.z);
            if (!LIPointIsZero(test) && LIPointBetweenPointsXY(test, origin, extent)) {
                points[count++] = test;
            }
        }
    }
    
    bool skip = false;
    if (count < 2) {
        test = LILineInterceptX(l, extent.x);
        /*
         If line passes through the extent, it will fail all three checks
         for faces 3, 4 and 5; skip individual checks for faces 3, 4 and 5
         */
        if (LIPointEqualToPoint(test, extent)) {
            points[count++] = test;
            skip = true;
        }
        if (!skip && !LIPointIsZero(test) && LIPointBetweenPointsYZ(test, origin, extent)) {
            points[count++] = test;
        }
    }
    if (!skip && count < 2) {
        test = LILineInterceptY(l, extent.y);
        if (!LIPointIsZero(test) && LIPointBetweenPointsZX(test, origin, extent)) {
            points[count++] = test;
        }
    }
    if (!skip && count < 2) {
        test = LILineInterceptZ(l, extent.z);
        if (!LIPointIsZero(test) && LIPointBetweenPointsXY(test, origin, extent)) {
            points[count++] = test;
        }
    }
    
    if (count == 2 && LILineParamForPoint(l, points[1]) < LILineParamForPoint(l, points[0])) {
        return (LIRegionLineIntersection){ points[1], points[0] };
    }
    else {
        return (LIRegionLineIntersection){ points[0], points[1] };
    }
}
