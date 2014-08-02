//
//  LIMatrix_t.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#ifndef LichenMath_LIMatrix_t_h
#define LichenMath_LIMatrix_t_h

#include <LichenMath/LIPoint_t.h>
#include <LichenMath/LIVector_t.h>

#include <math.h>

// All angles are in radians

#pragma mark - macro definitions

#define sine sinf
#define cosine cosf
#define absolute fabsf

#define LIMatrixIdentity (LIMatrix_t){ { {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} } }

#pragma mark - types

typedef union {
	LIVector4_t v[4];
	float i[16];
} LIMatrix_t;

typedef struct {
	LIPoint_t p;
	LIVector_t v;
} LILine;

#pragma mark - point transformation

#define LIVectorTransform( _v_, _a_, _mi_, _c_ ) do {\
float *_pv_ = (float *)&_v_;\
float *_pa_ = (float *)_a_;\
for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
_pv_[_i_] += _pa_[_j_] * _mi_[_c_*_j_ + _i_];\
} while(0)

static inline LIPoint_t LIMatrixTransformPoint(LIPoint_t * const a, LIMatrix_t * const m) {
	LIPoint_t v = {};
	LIVectorTransform(v, a, m->i, 4);
	return v;
}

#pragma mark - matrix creation

static inline LIMatrix_t LIMatrixMake(float elements[16]) {
	LIMatrix_t matrix;
	for (unsigned i=0; i<16; ++i) {
		matrix.i[i] = elements[i];
	}
	return matrix;
}

static inline void LIMatrixInit(LIMatrix_t *m, float elements[16]) {
	float *mi = m->i;
	for (unsigned i=0; i<16; ++i) {
		mi[i] = elements[i];
	}
}

#pragma mark - matrix operations

extern LIMatrix_t LIMatrixConcatenate(LIMatrix_t * const m, LIMatrix_t * const c);


// Normally you would want to make column-major matrices, but the Row function makes visualization easier in code

static inline LIMatrix_t LIMatrixMakeWithRowElements(float a00, float a01, float a02, float a03,
												 float a10, float a11, float a12, float a13,
												 float a20, float a21, float a22, float a23,
												 float a30, float a31, float a32, float a33) {
	LIMatrix_t m;
	m.v[0].x = a00; m.v[0].y = a10; m.v[0].z = a20; m.v[0].w = a30;
	m.v[1].x = a01; m.v[1].y = a11; m.v[1].z = a21; m.v[1].w = a31;
	m.v[2].x = a02; m.v[2].y = a12; m.v[2].z = a22; m.v[2].w = a32;
	m.v[3].x = a03; m.v[3].y = a13; m.v[3].z = a23; m.v[3].w = a33;
	return m;
}

static inline LIMatrix_t LIMatrixMakeWithColumnElements(float a00, float a01, float a02, float a03,
													float a10, float a11, float a12, float a13,
													float a20, float a21, float a22, float a23,
													float a30, float a31, float a32, float a33) {
	LIMatrix_t m;
	m.v[0].x = a00; m.v[0].y = a01; m.v[0].z = a02; m.v[0].w = a03;
	m.v[1].x = a10; m.v[1].y = a11; m.v[1].z = a12; m.v[1].w = a13;
	m.v[2].x = a20; m.v[2].y = a21; m.v[2].z = a22; m.v[2].w = a23;
	m.v[3].x = a30; m.v[3].y = a31; m.v[3].z = a32; m.v[3].w = a33;
	return m;
}

static inline LIMatrix_t LIMatrixMakeWithTranslation(LIVector_t v) {
	LIMatrix_t m = LIMatrixIdentity;
	m.v[3] = LIPointMake(v.x, v.y, v.z, 1.0f);
	return m;
}

static inline LIMatrix_t LIMatrixMakeWithXAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements(1.0f,    0,    0,    0,
									   0, cosa, -sina,   0,
									   0, sina,  cosa,   0,
									   0,    0,    0, 1.0f);
}

static inline LIMatrix_t LIMatrixMakeWithYAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements( cosa,    0, sina,    0,
									   0, 1.0f,    0,    0,
									   -sina,    0, cosa,    0,
									   0,    0,    0, 1.0f);
}

static inline LIMatrix_t LIMatrixMakeWithZAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements(cosa, -sina,    0,    0,
							           sina,  cosa,    0,    0,
							           0,     0,    1.0f,    0,
							           0,     0,       0, 1.0f);
}

extern LIMatrix_t LIMatrixMakeWithYZRotation(LIPoint_t p, float angle);
extern LIMatrix_t LIMatrixMakeWithXZRotation(LIPoint_t p, float angle);
extern LIMatrix_t LIMatrixMakeWithXYRotation(LIPoint_t p, float angle);
extern LIMatrix_t LIMatrixMakeWithVectorRotation(LIVector_t vector, float angle);
extern LIMatrix_t LIMatrixMakeWithArbitraryRotation(LILine axis, float angle);

#pragma mark - matrix operations

#define LIMatrixTranspose_( _mt_, _m_, _c_ ) do {\
for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
_mt_.i[_c_*_i_ + _j_] = _m_.i[_c_*_j_ + _i_];\
} while(0)

static inline LIMatrix_t LIMatrixTranspose(LIMatrix_t a) {
	LIMatrix_t m;
	LIMatrixTranspose_(m, a, 4);
	return m;
}

extern unsigned LIMatrixSmallestRowOrColumn( bool *isRow, float *m, unsigned n);
extern float LIMatrixMinor( float *m, unsigned row, unsigned column, unsigned n );
extern float LIMatrixDeterminant(LIMatrix_t m);

extern LIMatrix_t LIMatrixInverse(LIMatrix_t m);
extern LIMatrix_t LIMatrixFocus(LIPoint_t eye, LIPoint_t focus);
extern LIMatrix_t LIMatrixConcatenate(LIMatrix_t * const m, LIMatrix_t * const c);

#endif