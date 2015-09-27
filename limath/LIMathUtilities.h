//
//  LIMathUtilities.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-21.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#ifndef LIMathUtilities_h
#define LIMathUtilities_h

#ifndef ALIGN_UNIT
#define ALIGN_UNIT 0x1p+20
#endif
#ifndef ALIGN_UNIT_INV
#define ALIGN_UNIT_INV 0x1p-20
#endif

static inline bool LIFloatBetweenFloats(float v, float a, float b) {
    return (a < b) ? (v >= a && v < b) : (v >= b && v < a);
}

static inline float LIFloatAlign(float f) {
    return roundf(f * ALIGN_UNIT) * ALIGN_UNIT_INV;
}

#endif /* LIMathUtilities_h */
