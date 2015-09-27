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
