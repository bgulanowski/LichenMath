//
//  LIRegion_t.c
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-27.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#include "LIRegion_t.h"

LIRegionLineIntersection LIRegionIntersectWithLine(LIRegion_t r, LILine_t l) {
    
    LIPoint_t points[2] = { LIPointZero, LIPointZero };
    int count = 0;
    
    LIPoint_t origin = LIRegionOrigin(r);
    LIPoint_t extent = LIRegionExtent(r);
    
    LIPoint_t test = LIPointAlign(LILineInterceptX(l, origin.x));
    
    /*
     If the line passes through the origin, it will satisfy all three checks
     for faces 0, 1, and 2; skip individual checks for faces 0, 1 and 2
     */
    
    bool skip = false;
    if (!LIPointIsZero(test) && LIPointBetweenPointsYZ(test, origin, extent)) {
        points[count++] = test;
        // if we're on a leading axis-aligned edge, avoid counting same point twice
        skip = LIPointEqualToPoint2D(test, origin);
    }
    if (!skip) {
        test = LILineInterceptY(l, origin.y);
        if (!LIPointIsZero(test) && LIPointBetweenPointsZX(test, origin, extent)) {
            points[count++] = test;
        }
        if (count < 2) {
            test = LIPointAlign(LILineInterceptZ(l, origin.z));
            if (!LIPointIsZero(test) && LIPointBetweenPointsXY(test, origin, extent)) {
                points[count++] = test;
            }
        }
    }
    
    skip = false;
    if (count < 2) {
        test = LIPointAlign(LILineInterceptX(l, extent.x));
        /*
         If line passes through trailing axis-aligned edge, it will fail all three checks
         for faces 3, 4 and 5; skip those checks
         */
        if (LIPointEqualToPoint2D(test, extent)) {
            points[count++] = test;
            skip = true;
        }
        if (!skip && !LIPointIsZero(test) && LIPointBetweenPointsYZ(test, origin, extent)) {
            points[count++] = test;
        }
    }
    if (!skip && count < 2) {
        test = LIPointAlign(LILineInterceptY(l, extent.y));
        if (!LIPointIsZero(test) && LIPointBetweenPointsZX(test, origin, extent)) {
            points[count++] = test;
        }
    }
    if (!skip && count < 2) {
        test = LIPointAlign(LILineInterceptZ(l, extent.z));
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
