//
//  LIMatrix.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIVector.h>
#import <LichenMath/LIPoint.h>

// All angles are in radians

#pragma mark - macro definitions

#define sine sinf
#define cosine cosf
#define absolute fabsf

#define LIMatrixIdentity { { {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} } }

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

#define LIVectorTransform( _v_, _a_, _m_, _c_ ) do {\
	float *_pv_ = (float *)&_v_;\
	float *_pa_ = (float *)&_a_;\
		for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
			for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
				_pv_[_i_] += _pa_[_j_] * _m_.i[_c_*_j_ + _i_];\
} while(0)

NS_INLINE LIPoint_t LITransformPoint(LIPoint_t a, LIMatrix_t m) {
	LIPoint_t v = {};
	LIVectorTransform(v, a, m, 4);
	return v;
}

#pragma mark - matrix creation

NS_INLINE LIMatrix_t LIMatrixMake(float elements[16]) {
	LIMatrix_t matrix;
	for (NSUInteger i=0; i<16; ++i) {
		matrix.i[i] = elements[i];
	}
	return matrix;
}

// Normally you would want to make column-major matrices, but the Row function makes visualization easier in code

NS_INLINE LIMatrix_t LIMatrixMakeWithRowElements(float a00, float a01, float a02, float a03,
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

NS_INLINE LIMatrix_t LIMatrixMakeWithColumnElements(float a00, float a01, float a02, float a03,
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

NS_INLINE LIMatrix_t LIMatrixMakeWithTranslation(LIVector_t v) {
	LIMatrix_t m = LIMatrixIdentity;
	m.v[3] = LIPointMake(v.x, v.y, v.z, 1.0f);
	return m;
}

NS_INLINE LIMatrix_t LIMatrixMakeWithXAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements(1.0f,    0,    0,    0,
									      0, cosa, -sina,   0,
									      0, sina,  cosa,   0,
									      0,    0,    0, 1.0f);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithYAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements( cosa,    0, sina,    0,
							               0, 1.0f,    0,    0,
									   -sina,    0, cosa,    0,
							               0,    0,    0, 1.0f);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithZAxisRotation(float angle) {
	float cosa = cosine(angle), sina = sine(angle);
	return LIMatrixMakeWithRowElements(cosa, -sina,    0,    0,
							           sina,  cosa,    0,    0,
							           0,     0,    1.0f,    0,
							           0,     0,       0, 1.0f);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithYZRotation(LIPoint_t p, float angle) {
	
//	if(LIPointIsOrigin(p)) return LIXAxisRotationMatrix(angle);
	
	float b = p.y, c = p.z;
	float cosa = cosine(angle), ccosa = 1-cosa, sina = sine(angle);
	
	/*	return LIMatrixMakeWithRowElements(1 + 0*cosa,      0 - 0,      0 + 0, (a*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
	 0 + 0, 0 + 1*cosa,   0 - sina, (b*1 - 0*(a + 0))*ccosa + (c - 0)*sina,
	 0 - 0,   0 + sina, 0 + 1*cosa, (c*1 - 0*(a + 0))*ccosa + (b - 0)*sina,
	 0,          0,          0,                                      1);*/
	
	return LIMatrixMakeWithRowElements(1,    0,     0,                0,
									   0, cosa, -sina, b*ccosa + c*sina,
									   0, sina,  cosa, c*ccosa + b*sina,
									   0,    0,     0,                1);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithXZRotation(LIPoint_t p, float angle) {
	
//	if(LIPointIsOrigin(p)) return LIYAxisRotationMatrix(angle);
	
	float a = p.x, c = p.z;
	float cosa = cosine(angle), ccosa = 1-cosa, sina = sine(angle);
	
	/*	return LIMatrixMakeWithRowElements(0 + 1*cosa,      0 - 0,   0 + sina, (a*1 - 0*(1 + 0))*ccosa + (0 - c)*sina,
	 0 + 0, 1 + 0*cosa,      0 - 0, (b*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
	 0 - sina,      0 + 0, 0 + 1*cosa, (c*1 - 0*(0 + 1))*ccosa + (0 - a)*sina,
	 0,          0,          0,                                      1);*/
	
	return LIMatrixMakeWithRowElements( cosa, 0, sina, a*ccosa - c*sina,
									       0, 1,    0,                0,
									   -sina, 0, cosa, c*ccosa - a*sina,
									       0, 0,    0,              1);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithXYRotation(LIPoint_t p, float angle) {
	
//	if(LIPointIsOrigin(p)) return LIZAxisRotationMatrix(angle);
	
	float a = p.x, b = p.y;
	float cosa = cosine(angle), ccosa = 1-cosa, sina = sine(angle);
	
	/*	return LIMatrixMakeWithRowElements(0 + 1*cosa,   0 - sina,      0 + 0, (a*1 - 0*(0 + c))*ccosa + (b - 0)*sina,
										     0 + sina, 0 + 1*cosa,      0 - 0, (b*1 - 0*(0 + c))*ccosa + (0 - a)*sina,
										        0 - 0,      0 + 0, 1 + 0*cosa, (c*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
										            0,          0,          0,                                      1);*/
	
	return LIMatrixMakeWithRowElements(cosa, -sina, 0, a*ccosa + b*sina,
									   sina,  cosa, 0, b*ccosa - a*sina,
									      0,     0, 1,                0,
									      0,     0, 0,                1);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithVectorRotation(LIVector_t vector, float angle) {
	
	LIVector_t nv = LIVectorNormalize(vector);
	
	float u = nv.x, v = nv.y, w = nv.z;
	float uu = u*u, vv = v*v, ww = w*w, uv = u*v, uw = u*w, vw = v*w;
	float cosa = cosine(angle), ccosa = 1-cosa, sina = sine(angle);
	float usina = u*sina, vsina = v*sina, wsina = w*sina, uvccosa = uv*ccosa, uwccosa = uw*ccosa, vwccosa = vw*ccosa;
	
	/*	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina,       (0 - u*(0 + 0))*ccosa + (0 - 0)*sina,
										   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, (0*uu_ww - v*(0 + 0))*ccosa + (0 - 0)*sina,
										   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, (0*uu_vv - w*(0 + 0))*ccosa + (0 - 0)*sina,
														 0,               0,               0,                                          1);*/
	/*	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina, 0,
										   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, 0,
										   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, 0,
										                 0,               0,               0, 1);*/
	/*	uu + vv_ww*cosa => uu + (1-uu)*cosa => uu + cosa - uu*cosa => cosa + uu - uu*cosa => cosa + uu*(1-cosa) => cosa + uu*ccosa */
	
	return LIMatrixMakeWithRowElements(cosa + uu*ccosa, uvccosa - wsina, uwccosa + vsina, 0,
									   uvccosa + wsina, cosa + vv*ccosa, vwccosa - usina, 0,
									   uwccosa - vsina, vwccosa + usina, cosa + ww*ccosa, 0,
 									                 0,               0,               0, 1);
}

NS_INLINE LIMatrix_t LIMatrixMakeWithArbitraryRotation(LILine axis, float angle) {
	
	if(angle == 0.0f) return (LIMatrix_t)LIMatrixIdentity;
	
	if(LIPointIsOrigin(axis.p)) return LIMatrixMakeWithVectorRotation(axis.v, angle);
	
	if(LIVectorIsXAligned(axis.v)) return LIMatrixMakeWithYZRotation(axis.p, angle);
	if(LIVectorIsYAligned(axis.v)) return LIMatrixMakeWithXZRotation(axis.p, angle);
	if(LIVectorIsZAligned(axis.v)) return LIMatrixMakeWithXYRotation(axis.p, angle);
	
	LIVector_t nv = LIVectorNormalize(axis.v);
	
	float a = axis.p.x, b = axis.p.y, c = axis.p.z, u = nv.x, v = nv.y, w = nv.z;
	float uu = u*u, vv = v*v, ww = w*w, uv = u*v, uw = u*w, vw = v*w;
	float uu_vv = uu + vv, uu_ww = uu + ww, vv_ww = vv + ww;
	float cosa = cosine(angle), ccosa = 1-cosa, sina = sine(angle);
	float usina = u*sina, vsina = v*sina, wsina = w*sina, uvccosa = uv*ccosa, uwccosa = uw*ccosa, vwccosa = vw*ccosa;
	float au = a*u, av = a*v, aw = a*w, bu = b*u, bv = b*v, bw = b*w, cu = c*u, cv = c*v, cw = c*w;
	
	// See http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/
	
	/*
	 uu + vv_ww*cosa,  uvccosa - wsina,  uwccosa + vsina,  (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
	 uvccosa + wsina,  vv + uu_ww*cosa,  vwccosa - usina,  (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
	 uwccosa - vsina,  vwccosa + usina,  ww + uu_vv*cosa,  (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
	               0,                0,                0,                                               1
	 */
	
	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina, (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
									   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
									   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
									                 0,               0,               0,                                              1);
}

#pragma mark - matrix operations

#define LIMatrixTranspose_( _mt_, _m_, _c_ ) do {\
	for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
		for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
			_mt_.i[_c_*_i_ + _j_] = _m_.i[_c_*_j_ + _i_];\
} while(0)

NS_INLINE LIMatrix_t LIMatrixTranspose(LIMatrix_t a) {
	LIMatrix_t m;
	LIMatrixTranspose_(m, a, 4);
	return m;
}

extern NSUInteger LIMatrixSmallestRowOrColumn( BOOL *isRow, float *m, NSUInteger n);
extern float LIMatrixDeterminantN(float *m, NSUInteger n);
extern float LIMatrixMinor( float *m, NSUInteger row, NSUInteger column, NSUInteger n );


static inline float LIMatrixDeterminant(LIMatrix_t m) {
    return LIMatrixDeterminantN(m.i, 4);
}

extern LIMatrix_t LIMatrixInverse(LIMatrix_t m);
extern LIMatrix_t LIMatrixFocus(LIPoint_t eye, LIPoint_t focus);

#pragma mark - string encoding

extern NSString *LIMatrixToString(LIMatrix_t m);
extern LIMatrix_t LIMatrixFromString(NSString *string);

@interface LIMatrix : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIMatrix_t matrix;

- (instancetype)initWithMatrix:(LIMatrix_t)matrix;
+ (instancetype)matrixWithMatrix:(LIMatrix_t)matrix;
+ (instancetype)matrixWithElements:(float *)elements;

@end
