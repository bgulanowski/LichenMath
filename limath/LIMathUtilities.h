//
//  LIMathUtilities.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-21.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#ifndef LIMathUtilities_h
#define LIMathUtilities_h

static inline bool LIFloatBetweenFloats(float v, float a, float b) {
    return (a < b) ? (v >= a && v < b) : (v >= b && v < a);
}

#endif /* LIMathUtilities_h */
