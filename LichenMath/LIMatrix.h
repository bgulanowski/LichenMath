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

typedef union {
	LIVector4f v[4];
	float i[16];
} LIMatrix4f;

#define LIMatrixTranspose( _mt_, _m_, _c_ ) do {\
	for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
		for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
			_mt_.i[_c_*_i_ + _j_] = _m_.i[_c_*_j_ + _i_];\
} while(0)

static inline LIMatrix4f BATransposeMatrix4x4f(LIMatrix4f a) {
	LIMatrix4f m;
	LIMatrixTranspose(m, a, 4);
	return m;
}

#define LIVectorTransform( _v_, _a_, _m_, _c_ ) do {\
	float *_pv_ = (float *)&_v_;\
	float *_pa_ = (float *)&_a_;\
		for(unsigned _i_ = 0; _i_ < _c_; ++_i_)\
			for(unsigned _j_ = 0; _j_ < _c_; ++_j_)\
				_pv_[_i_] += _pa_[_j_] * _m_.i[_c_*_j_ + _i_];\
} while(0)

static inline LIPoint4f BATransformPoint4f(LIPoint4f a, LIMatrix4f m) {
	LIPoint4f v = {};
	LIVectorTransform(v, a, m, 4);
	return v;
}

NS_INLINE LIMatrix4f LIMatrix4fMake(float elements[16]) {
	LIMatrix4f matrix;
	for (NSUInteger i=0; i<16; ++i) {
		matrix.i[i] = elements[i];
	}
	return matrix;
}

extern NSString *LIMatrix4fToString(LIMatrix4f m);
extern LIMatrix4f LIMatrix4fFromString(NSString *string);

@interface LIMatrix : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIMatrix4f matrix4f;

- (instancetype)initWithMatrix4f:(LIMatrix4f)matrix4f;
+ (instancetype)matrixWithMatrix4f:(LIMatrix4f)matrix4f;
+ (instancetype)matrixWithElements:(float *)elements;

@end
