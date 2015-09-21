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

static inline LISize_t LISizeMake(float width, float height, float depth) {
	return (LISize_t) { .w = width, .h = height, .d = depth };
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

static inline bool LIPointInRegion(LIPoint_t p, LIRegion_t r) {
    return LIPointBetweenPoints(p, LIRegionOrigin(r), LIRegionExtent(r));
}

#pragma mark -

typedef struct {
    LIPoint_t point;
    LIRegionBoundary type;
    int boundary;
} LIRegionSurfacePoint;

typedef struct {
    LIRegionSurfacePoint entry;
    LIRegionSurfacePoint exit;
} LIRegionLineIntersection;

extern LIRegionSurfacePoint LIRegionSurfacePointZero;

static inline LIRegionSurfacePoint LIRegionSurfacePointMake(LIPoint_t point, LIRegionBoundary type, int boundary) {
    return (LIRegionSurfacePoint){ .point = point, .type = type, .boundary = boundary };
}

extern LIRegionLineIntersection LIRegionIntersectWithLine(LIRegion_t r, LILine_t l);
