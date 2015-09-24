//
//  LIRegion_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#pragma once

#include <LichenMath/LIPoint_t.h>
#include <LichenMath/LILine_t.h>

// Numbered ZYX, so 001 is (1, 0, 0), etc.
// X values iterate first, then Y, then Z
typedef enum {
    LIRegionVertexUndefined = -1,
    
    LIRegionVertex000,
    LIRegionVertex001,
    LIRegionVertex010,
    LIRegionVertex011,
    
    LIRegionVertex100,
    LIRegionVertex101,
    LIRegionVertex110,
    LIRegionVertex111,
    
    LIRegionVertexCount
    
} LIRegionVertex;

/*
typedef enum {
    
    LIRegionEdgeUndefined = -1,
    LIRegionEdgeStart = LIRegionVertexCount,
    
    LIRegionEdgeX0X0 = LIRegionEdgeUndefined,
    LIRegionEdgeX0X1 = LIRegionEdgeUndefined,
    LIRegionEdgeX0Y0 = LIRegionEdgeStart + 2,
    LIRegionEdgeX0Y1 = LIRegionEdgeStart + 3,
    LIRegionEdgeX0Z0 = LIRegionEdgeStart + 4,
    LIRegionEdgeX0Z1 = LIRegionEdgeStart + 5,
    
    LIRegionEdgeX1X0 = LIRegionEdgeUndefined, // 6
    LIRegionEdgeX1X1 = LIRegionEdgeUndefined, // 7
    LIRegionEdgeX1Y0 = LIRegionEdgeStart + 8,
    LIRegionEdgeX1Y1 = LIRegionEdgeStart + 9,
    LIRegionEdgeX1Z0 = LIRegionEdgeStart + 10,
    LIRegionEdgeX1Z1 = LIRegionEdgeStart + 11,

    LIRegionEdgeY0Y0 = LIRegionEdgeUndefined, // 12
    LIRegionEdgeY0Y1 = LIRegionEdgeUndefined, // 13
    LIRegionEdgeY0X0 = LIRegionEdgeX0Y0,      // 14
    LIRegionEdgeY0X1 = LIRegionEdgeX1Y0,      // 15
    LIRegionEdgeY0Z0 = LIRegionEdgeStart + 16,
    LIRegionEdgeY0Z1 = LIRegionEdgeStart + 17,
    
    LIRegionEdgeY1X0 = LIRegionEdgeX0Y1,      // 18
    LIRegionEdgeY1X1 = LIRegionEdgeX1Y1,      // 19
    LIRegionEdgeY1Y0 = LIRegionEdgeUndefined, // 20
    LIRegionEdgeY1Y1 = LIRegionEdgeUndefined, // 21
    LIRegionEdgeY1Z0 = LIRegionEdgeStart + 22,
    LIRegionEdgeY1Z1 = LIRegionEdgeStart + 23,
    
    LIRegionEdgeZ0X0 = LIRegionEdgeX0Z0,      // 24
    LIRegionEdgeZ0X1 = LIRegionEdgeX1Z0,      // 25
    LIRegionEdgeZ0Y0 = LIRegionEdgeY0Z0,      // 26
    LIRegionEdgeZ0Y1 = LIRegionEdgeY1Z0,      // 27
    LIRegionEdgeZ0Z0 = LIRegionEdgeUndefined, // 28
    LIRegionEdgeZ0Z1 = LIRegionEdgeUndefined, // 29
    
    LIRegionEdgeZ1X0 = LIRegionEdgeX0Z1,      // 30
    LIRegionEdgeZ1X1 = LIRegionEdgeX1Z1,      // 31
    LIRegionEdgeZ1Y0 = LIRegionEdgeY0Z1,      // 32
    LIRegionEdgeZ1Y1 = LIRegionEdgeY1Z1,      // 33
    LIRegionEdgeZ1Z0 = LIRegionEdgeUndefined, // 34
    LIRegionEdgeZ1Z1 = LIRegionEdgeUndefined, // 35
    
    LIRegionEdgeCount
} LIRegionEdge;
 */

typedef enum {
    LIRegionEdgeUndefined = -1,
    
    LIRegionEdgeX0Y0,
    LIRegionEdgeX0Y1,
    LIRegionEdgeX0Z0,
    LIRegionEdgeX0Z1,
    
    LIRegionEdgeX1Y0,
    LIRegionEdgeX1Y1,
    LIRegionEdgeX1Z0,
    LIRegionEdgeX1Z1,
    
    LIRegionEdgeY0Z0,
    LIRegionEdgeY0Z1,
    LIRegionEdgeY1Z0,
    LIRegionEdgeY1Z1,
    
    LIRegionEdgeCount
    
} LIRegionEdge;

typedef enum {
    LIRegionFaceUndefined = -1,
    
    LIRegionFaceX0,
    LIRegionFaceX1,
    LIRegionFaceY0,
    LIRegionFaceY1,
    LIRegionFaceZ0,
    LIRegionFaceZ1,
    
    LIRegionFaceCount
    
} LIRegionFace;

typedef enum {
    LIRegionBoundaryUndefined = -1,
    LIRegionBoundaryVertex,
    LIRegionBoundaryEdge,
    LIRegionBoundaryFace,
} LIRegionBoundary;

typedef struct {
	float w;
	float h;
	float d;
} LISize_t;

typedef union {
	LIPoint_t p;
	float i[4];
} LILocation_t;

typedef union {
	LISize_t s;
	float i[3];
} LIVolume_t;

typedef struct {
	LILocation_t origin;
	LIVolume_t volume;
} LIRegion_t;

extern const LISize_t LISizeZero;

static inline LISize_t LISizeMake(float width, float height, float depth) {
	return (LISize_t) { .w = width, .h = height, .d = depth };
}

static inline bool LISizeEqualToSize(LISize_t s1, LISize_t s2) {
    return s1.w == s2.w && s1.h == s2.h && s1.w == s2.w;
}

static inline bool LISizeIsZero(LISize_t s) {
    return LISizeEqualToSize(s, LISizeZero);
}

static inline bool LISizeIsEmpty(LISize_t s) {
    return s.w <= 0 || s.h <= 0 || s.d <= 0;
}

static inline LIVector_t LIVectorFromSize(LISize_t s) {
    return LIVectorMake(s.w, s.h, s.d);
}

static inline LIRegion_t LIRegionMake(float x, float y, float z, float width, float height, float depth) {
	return (LIRegion_t) { .origin.p = LIPointMake(x, y, z, 1), .volume.s = LISizeMake(width, height, depth) };
}

static inline LIPoint_t LIRegionOrigin(LIRegion_t r) {
    return r.origin.p;
}

static inline LIPoint_t LIRegionExtent(LIRegion_t r) {
    return LIPointTranslate(r.origin.p, LIVectorFromSize(r.volume.s));
}

static inline bool LIRegionIsEmpty(LIRegion_t r) {
    return LISizeIsEmpty(r.volume.s);
}

static inline bool LIPointInRegion(LIPoint_t p, LIRegion_t r) {
    return LIPointBetweenPoints(p, LIRegionOrigin(r), LIRegionExtent(r));
}

#pragma mark -

typedef struct {
    LIPoint_t entry;
    LIPoint_t exit;
} LIRegionLineIntersection;

extern LIRegionLineIntersection LIRegionIntersectWithLine(LIRegion_t r, LILine_t l);
