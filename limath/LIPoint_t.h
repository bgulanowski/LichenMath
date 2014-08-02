//
//  LIPoint_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#pragma once

#include <LichenMath/LIVector_t.h>

#include <stdbool.h>

typedef struct {
	float x;
	float y;
	float z;
	float w;
} LIPoint_t;

#define LIVector4_t LIPoint_t

static inline LIPoint_t LIPointMake(float x, float y, float z, float w) {
	return (LIPoint_t){.x = x, .y = y, .z = z, .w = w};
}

static inline LIPoint_t LIPointTranslate(LIPoint_t p, LIVector_t v) {
	LIPoint_t p2;
	p2.x = p.x + v.x, p2.y = p.y + v.y, p2.z = p.z + v.z, p2.w = p.w;
	return p2;
}

static inline LIPoint_t LIPointScale(LIPoint_t p, float factor) {
	LIPoint_t p2;
	p2.x = p.x*factor, p2.y = p.y*factor, p2.z = p.z*factor, p2.w = 1;
	return p2;
}

static inline bool LIPointIsOrigin(LIPoint_t p) {
	return p.x == 0.0f && p.y == 0.0f && p.z == 0.0f;
}
