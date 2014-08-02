//
//  LIMatrix.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIMatrix.h"
#import "LichenMath_Private.h"

static NSString * const matrixKey = @"_matrix";

LIMatrix_t LIMatrixMakeWithYZRotation(LIPoint_t p, float angle) {
	
	if(LIPointIsOrigin(p)) return LIMatrixMakeWithXAxisRotation(angle);
	
	float b = p.y;
	float c = p.z;
	float sina = sine(angle);
	float cosa = cosine(angle);
	float ccosa = 1-cosa;
	
	/*	return LIMatrixMakeWithRowElements(1 + 0*cosa,      0 - 0,      0 + 0, (a*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
										        0 + 0, 0 + 1*cosa,   0 - sina, (b*1 - 0*(a + 0))*ccosa + (c - 0)*sina,
										        0 - 0,   0 + sina, 0 + 1*cosa, (c*1 - 0*(a + 0))*ccosa + (b - 0)*sina,
										            0,          0,          0,                                      1);*/
	
	return LIMatrixMakeWithRowElements(1,    0,     0,                0,
									   0, cosa, -sina, b*ccosa + c*sina,
									   0, sina,  cosa, c*ccosa + b*sina,
									   0,    0,     0,                1);
}

LIMatrix_t LIMatrixMakeWithXZRotation(LIPoint_t p, float angle) {
	
	if(LIPointIsOrigin(p)) return LIMatrixMakeWithYAxisRotation(angle);
	
	float a = p.x;
	float c = p.z;
	float sina = sine(angle);
	float cosa = cosine(angle);
	float ccosa = 1-cosa;
	
	/*	return LIMatrixMakeWithRowElements(0 + 1*cosa,      0 - 0,   0 + sina, (a*1 - 0*(1 + 0))*ccosa + (0 - c)*sina,
	 *											0 + 0, 1 + 0*cosa,      0 - 0, (b*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
	 *										 0 - sina,      0 + 0, 0 + 1*cosa, (c*1 - 0*(0 + 1))*ccosa + (0 - a)*sina,
	 *												0,          0,          0,                                      1); */
	
	return LIMatrixMakeWithRowElements( cosa, 0, sina, a*ccosa - c*sina,
									       0, 1,    0,                0,
									   -sina, 0, cosa, c*ccosa - a*sina,
									       0, 0,    0,              1);
}

LIMatrix_t LIMatrixMakeWithXYRotation(LIPoint_t p, float angle) {
	
	if(LIPointIsOrigin(p)) return LIMatrixMakeWithZAxisRotation(angle);
	
	float a = p.x;
	float b = p.y;
	float sina = sine(angle);
	float cosa = cosine(angle);
	float ccosa = 1-cosa;
	
	/*	return LIMatrixMakeWithRowElements(0 + 1*cosa,   0 - sina,      0 + 0, (a*1 - 0*(0 + c))*ccosa + (b - 0)*sina,
	 *									     0 + sina, 0 + 1*cosa,      0 - 0, (b*1 - 0*(0 + c))*ccosa + (0 - a)*sina,
	 *									        0 - 0,      0 + 0, 1 + 0*cosa, (c*0 - 1*(0 + 0))*ccosa + (0 - 0)*sina,
	 *									            0,          0,          0,                                      1); */
	
	return LIMatrixMakeWithRowElements(cosa, -sina, 0, a*ccosa + b*sina,
									   sina,  cosa, 0, b*ccosa - a*sina,
									      0,     0, 1,                0,
									      0,     0, 0,                1);
}

LIMatrix_t LIMatrixMakeWithVectorRotation(LIVector_t vector, float angle) {
	
	LIVector_t nv = LIVectorNormalize(vector);
	
	float u = nv.x;
	float v = nv.y;
	float w = nv.z;
	
	float uu = u*u;
	float vv = v*v;
	float ww = w*w;
	
	float uv = u*v;
	float uw = u*w;
	float vw = v*w;
	
	float sina = sine(angle);

	float usina = u*sina;
	float vsina = v*sina;
	float wsina = w*sina;
	
	float cosa = cosine(angle);
	float ccosa = 1-cosa;

	float uvccosa = uv*ccosa;
	float uwccosa = uw*ccosa;
	float vwccosa = vw*ccosa;
	
	/*	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina,       (0 - u*(0 + 0))*ccosa + (0 - 0)*sina,
	 *									   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, (0*uu_ww - v*(0 + 0))*ccosa + (0 - 0)*sina,
	 *									   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, (0*uu_vv - w*(0 + 0))*ccosa + (0 - 0)*sina,
	 *													 0,               0,               0,                                           1); */
	/*	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina, 0,
	 *									   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, 0,
	 *									   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, 0,
	 *													 0,               0,               0, 1); */
	/*	uu + vv_ww*cosa => uu + (1-uu)*cosa => uu + cosa - uu*cosa => cosa + uu - uu*cosa => cosa + uu*(1-cosa) => cosa + uu*ccosa */
	
	return LIMatrixMakeWithRowElements(cosa + uu*ccosa, uvccosa - wsina, uwccosa + vsina, 0,
									   uvccosa + wsina, cosa + vv*ccosa, vwccosa - usina, 0,
									   uwccosa - vsina, vwccosa + usina, cosa + ww*ccosa, 0,
									                 0,               0,               0, 1);
}

LIMatrix_t LIMatrixMakeWithArbitraryRotation(LILine axis, float angle) {
	
	if(angle == 0.0f) return (LIMatrix_t)LIMatrixIdentity;
	
	if(LIPointIsOrigin(axis.p)) return LIMatrixMakeWithVectorRotation(axis.v, angle);
	
	if(LIVectorIsXAligned(axis.v)) return LIMatrixMakeWithYZRotation(axis.p, angle);
	if(LIVectorIsYAligned(axis.v)) return LIMatrixMakeWithXZRotation(axis.p, angle);
	if(LIVectorIsZAligned(axis.v)) return LIMatrixMakeWithXYRotation(axis.p, angle);
	
	LIVector_t nv = LIVectorNormalize(axis.v);
	
	float a = axis.p.x;
	float b = axis.p.y;
	float c = axis.p.z;
	
	float u = nv.x;
	float v = nv.y;
	float w = nv.z;
	
	float uu = u*u;
	float vv = v*v;
	float ww = w*w;
	
	float uv = u*v;
	float uw = u*w;
	float vw = v*w;
	
	float uu_vv = uu + vv;
	float uu_ww = uu + ww;
	float vv_ww = vv + ww;
	
	float sina = sine(angle);
	
	float usina = u*sina;
	float vsina = v*sina;
	float wsina = w*sina;
	
	float cosa = cosine(angle);
	float ccosa = 1-cosa;
	
	float uvccosa = uv*ccosa;
	float uwccosa = uw*ccosa;
	float vwccosa = vw*ccosa;

	float au = a*u;
	float av = a*v;
	float aw = a*w;
	float bu = b*u;
	float bv = b*v;
	float bw = b*w;
	float cu = c*u;
	float cv = c*v;
	float cw = c*w;
	
	// See http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/
	
	/* uu + vv_ww*cosa,  uvccosa - wsina,  uwccosa + vsina,  (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
	 * uvccosa + wsina,  vv + uu_ww*cosa,  vwccosa - usina,  (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
	 * uwccosa - vsina,  vwccosa + usina,  ww + uu_vv*cosa,  (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
	 *               0,                0,                0,                                               1  */
	
	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina, (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
									   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
									   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
									                 0,               0,               0,                                              1);
}

NSString *LIMatrixToString(LIMatrix_t m) {
	LIMatrix_t t = LIMatrixTranspose(m);
	return [NSString stringWithFormat:@"{%@,%@,%@,%@}",
			LIPointToString(t.v[0]), LIPointToString(t.v[1]), LIPointToString(t.v[2]), LIPointToString(t.v[3])];
}

LIMatrix_t LIMatrixFromString(NSString *string) {
	LIMatrix_t r;
	sscanf([string cStringUsingEncoding:NSASCIIStringEncoding],
           "{{%f,%f,%f,%f},{%f,%f,%f,%f},{%f,%f,%f,%f}}",
           &(r.v[0].x), &(r.v[0].y), &(r.v[0].z), &(r.v[0].w),
		   &(r.v[1].x), &(r.v[1].y), &(r.v[1].z), &(r.v[1].w),
		   &(r.v[2].x), &(r.v[2].y), &(r.v[2].z), &(r.v[2].w));
	return r;
}

NSUInteger LIMatrixSmallestRowOrColumn( BOOL *isRow, float *m, NSUInteger n) {
    
    NSUInteger index = 0;
	
    NSUInteger b = 0; // best count of zeros
    
    *isRow = NO;
    
    // check the jth row and the jth column at the same time
    for(NSUInteger j=0; j<n; ++j) {
        
        NSUInteger r = 0; // row count
        NSUInteger c = 0; // col count
        
        for(NSUInteger k=0; k<n; ++k) {
            if(0.0f == m[k*n+j]) r++; // jth row
            if(0.0f == m[j*n+k]) c++; // jth column
            if (c > b || r > b) {
                if(r > c) {
                    *isRow = YES;
                    b = r;
                    index = j;
                }
                else {
                    *isRow = NO;
                    b = c;
                    index = j;
                }
                // this row or column is already the winner; skip the rest
                continue;
            }
        }
    }
    
    return index;
}

NS_INLINE float LIMatrixDeterminantN(float *m, NSUInteger n) {
    
    float result = 0;
    
    if(2 == n) {
        result = m[0]*m[3]-m[1]*m[2];
    }
    else {
        // find the row/column with the most zeros
        BOOL isRow = NO;
        NSUInteger rc = LIMatrixSmallestRowOrColumn(&isRow, m, n);
        NSInteger rccf = -(rc&1)*2+1;
        
        // indirect recursion
        if(isRow) {
            for(NSUInteger i=0; i<n; ++i) {
                NSUInteger index = i*n+rc;
                if(0.0f != m[index]) {
                    NSInteger icf = -(i&1)*2+1;
                    float minor = LIMatrixMinor(m, rc, i, n);
                    result += icf * rccf * m[index] * minor;
                }
            }
        }
        else {
            for(NSInteger i=0; i<n; ++i) {
                NSUInteger index = rc*n+i;
                if(0.0f != m[index]) {
                    NSInteger icf = -(i&1)*2+1;
                    float minor = LIMatrixMinor(m, i, rc, n);
                    result += icf * rccf * m[index] * minor;
                }
            }
        }
    }
    
    return result;
}

float LIMatrixMinor( float *m, NSUInteger row, NSUInteger column, NSUInteger n ) {
    
    assert(n > 2);
	
    float *minorMatrix = malloc(sizeof(float)*(n-1)*(n-1));
	
    // copy elements
    for(NSUInteger i=0; i<n-1; ++i) {     // columns
        NSUInteger skip = i >= column;
        for(NSUInteger j=0; j<n-1; ++j) { // rows
            NSUInteger c = i+skip;
            NSUInteger r = j + (j>=row);
            NSUInteger index = c*n + r;
            minorMatrix[i*(n-1)+j] = m[index];
        }
    }
    
    float det = LIMatrixDeterminantN(minorMatrix, n-1);
	
    free(minorMatrix);
	
    return det;
}

float LIMatrixDeterminant(LIMatrix_t m) {
    return LIMatrixDeterminantN(m.i, 4);
}

NS_INLINE float *LIMatrixInverseN(float *m, NSUInteger n) {
    
    float *r = malloc(sizeof(float)*n*n);
    
    float dinv = 1.0f/LIMatrixDeterminantN(m, n);
    
    for(NSUInteger i=0; i<n; ++i) {     // columns
        NSInteger rcf = -(i&1)*2+1;
        for(NSUInteger j=0; j<n; ++j) { // rows
            NSInteger ccf = -(j&1)*2+1;
            // transpose and divide as we go -- swap rows/columns
            r[i*n+j] = rcf * ccf * LIMatrixMinor(m, i, j, n) * dinv;
        }
    }
    
    return r;
}

LIMatrix_t LIMatrixInverse(LIMatrix_t m) {
    
    LIMatrix_t result;
    float *temp = LIMatrixInverseN(m.i, 4);
    
    for(NSUInteger i=0; i<16; ++i)
        result.i[i] = temp[i];
    
    free(temp);
    
    return result;
}

LIMatrix_t LIMatrixFocus(LIPoint_t eye, LIPoint_t focus) {
	
	LIVector_t e3 = LIVectorMake(eye.x - focus.x, eye.y - focus.y, eye.z - focus.z);
	LIVector_t Z = LIVectorNormalize(e3);
	LIVector_t X = LIVectorNormalize(LICrossProductVectors3(LIVectorMake(0, 1, 0), Z));
	LIVector_t Y = LIVectorNormalize(LICrossProductVectors3(Z, X));
	
	LIMatrix_t m;
	m.v[0] = LIPointMake(X.x, Y.x, Z.x, 0);
	m.v[1] = LIPointMake(X.y, Y.y, Z.y, 0);
	m.v[2] = LIPointMake(X.z, Y.z, Z.z, 0);
	m.v[3] = LIPointMake(-LIDotProductVectors3(X, e3), -LIDotProductVectors3(Y, e3), -LIDotProductVectors3(Z, e3), 1);
	return m;
}

LIMatrix_t LIMatrixConcatenate(LIMatrix_t *m, LIMatrix_t *c) {
	
	LIMatrix_t r;
	
	for (NSUInteger i = 0; i < 4; ++i) {
		LIVectorTransform(r.v[i], &(c->v[i]), m->i, 4);
	}
	
	return r;
}

@implementation LIMatrix

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] matrixWithMatrix:_matrix];
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_matrix, [aDecoder decodeBytesForKey:matrixKey returnedLength:NULL], sizeof(_matrix));
		}
		else {
			memcpy(&_matrix, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(_matrix));
		}
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(const uint8_t *)&_matrix length:sizeof(_matrix) forKey:matrixKey];
	}
	else {
		[aCoder encodeBytes:&_matrix length:sizeof(_matrix)];
	}
}

#pragma mark - LIMatrix

- (instancetype)initWithMatrix:(LIMatrix_t)matrix {
	self = [super init];
	if (self) {
		_matrix = matrix;
	}
	return self;
}

+ (instancetype)matrixWithMatrix:(LIMatrix_t)matrix {
	return [[self alloc] initWithMatrix:matrix];
}

+ (instancetype)matrixWithElements:(float *)elements {
	return [self matrixWithMatrix:LIMatrixMake(elements)];
}

- (void)concatenate:(LIMatrix *)matrix {
	_matrix = LIMatrixConcatenate(&_matrix, &(matrix->_matrix));
}

- (LIPoint *)transformPoint:(LIPoint *)point {
	return [LIPoint pointWithPoint:LIMatrixTransformPoint(&(point->_point), &_matrix)];
}

@end
