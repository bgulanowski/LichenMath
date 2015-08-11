//
//  LIMath.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-10-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIVector_t.h"
#import "LIPoint_t.h"

#define VectorZero { 0, 0, 0 }
#define VectorUnitX { 1.0f, 0, 0 }
#define VectorUnitY { 0, 1.0f, 0 }
#define VectorUnitZ { 0, 0, 1.0f }

const LIVector_t LIVectorZero = VectorZero;


#define PointZero { 0, 0, 0, 0 }
#define PointOrigin { 0, 0, 0, 1.0f }

const LIPoint_t LIPointZero = PointZero;
const LIPoint_t LIPointOrigin = PointOrigin;

const LILine_t LILineZero = { PointZero, VectorZero };
const LILine_t LILineXAxis = { PointZero, VectorUnitX };
const LILine_t LILineYAxis = { PointZero, VectorUnitY };
const LILine_t LILineZAxis = { PointZero, VectorUnitZ };

const LIPlane_t LIPlaneZero = { PointZero, VectorZero, VectorZero };
const LIPlane_t LIPlaneXY = { PointZero, VectorUnitX, VectorUnitY };
const LIPlane_t LIPlaneYZ = { PointZero, VectorUnitY, VectorUnitZ };
const LIPlane_t LIPlaneZX = { PointZero, VectorUnitZ, VectorUnitX };
