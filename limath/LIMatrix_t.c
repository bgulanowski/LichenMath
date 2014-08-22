//
//  LIMatrix_t.c
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-08-02.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#include <stdio.h>

#include "LIMatrix_t.h"

#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

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
	
	// See https://sites.google.com/site/glennmurray/Home/rotation-matrices-and-formulas
	
	/* uu + vv_ww*cosa,  uvccosa - wsina,  uwccosa + vsina,  (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
	 * uvccosa + wsina,  vv + uu_ww*cosa,  vwccosa - usina,  (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
	 * uwccosa - vsina,  vwccosa + usina,  ww + uu_vv*cosa,  (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
	 *               0,                0,                0,                                               1  */
	
	return LIMatrixMakeWithRowElements(uu + vv_ww*cosa, uvccosa - wsina, uwccosa + vsina, (a*vv_ww - u*(bv + cw))*ccosa + (bw - cv)*sina,
									   uvccosa + wsina, vv + uu_ww*cosa, vwccosa - usina, (b*uu_ww - v*(au + cw))*ccosa + (cu - aw)*sina,
									   uwccosa - vsina, vwccosa + usina, ww + uu_vv*cosa, (c*uu_vv - w*(au + bv))*ccosa + (bu - av)*sina,
									                 0,               0,               0,                                              1);
}

unsigned LIMatrixSmallestRowOrColumn( bool *isRow, float *m, unsigned n) {
    
    unsigned index = 0;
	
    unsigned b = 0; // best count of zeros
    
    *isRow = false;
    
    // check the jth row and the jth column at the same time
    for(unsigned j=0; j<n; ++j) {
        
        unsigned r = 0; // row count
        unsigned c = 0; // col count
        
        for(unsigned k=0; k<n; ++k) {
            if(0.0f == m[k*n+j]) r++; // jth row
            if(0.0f == m[j*n+k]) c++; // jth column
            if (c > b || r > b) {
                if(r > c) {
                    *isRow = true;
                    b = r;
                    index = j;
                }
                else {
                    *isRow = false;
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

static inline float LIMatrixDeterminantN(float *m, unsigned n) {
    
    float result = 0;
    
    if(2 == n) {
        result = m[0]*m[3]-m[1]*m[2];
    }
    else {
        // find the row/column with the most zeros
        bool isRow = false;
        unsigned rc = LIMatrixSmallestRowOrColumn(&isRow, m, n);
        int rccf = -(rc&1)*2+1;
        
        // indirect recursion
        if(isRow) {
            for(unsigned i=0; i<n; ++i) {
                unsigned index = i*n+rc;
                if(0.0f != m[index]) {
                    int icf = -(i&1)*2+1;
                    float minor = LIMatrixMinor(m, rc, i, n);
                    result += icf * rccf * m[index] * minor;
                }
            }
        }
        else {
            for(int i=0; i<n; ++i) {
                unsigned index = rc*n+i;
                if(0.0f != m[index]) {
                    int icf = -(i&1)*2+1;
                    float minor = LIMatrixMinor(m, i, rc, n);
                    result += icf * rccf * m[index] * minor;
                }
            }
        }
    }
    
    return result;
}

float LIMatrixMinor( float *m, unsigned row, unsigned column, unsigned n ) {
    
    assert(n > 2);
	
    float *minorMatrix = malloc(sizeof(float)*(n-1)*(n-1));
	
    // copy elements
    for(unsigned i=0; i<n-1; ++i) {     // columns
        unsigned skip = i >= column;
        for(unsigned j=0; j<n-1; ++j) { // rows
            unsigned c = i+skip;
            unsigned r = j + (j>=row);
            unsigned index = c*n + r;
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

static inline float *LIMatrixInverseN(float *m, unsigned n) {
    
    float *r = malloc(sizeof(float)*n*n);
    
    float dinv = 1.0f/LIMatrixDeterminantN(m, n);
    
    for(unsigned i=0; i<n; ++i) {     // columns
        int rcf = -(i&1)*2+1;
        for(unsigned j=0; j<n; ++j) { // rows
            int ccf = -(j&1)*2+1;
            // transpose and divide as we go -- swap rows/columns
            r[i*n+j] = rcf * ccf * LIMatrixMinor(m, i, j, n) * dinv;
        }
    }
    
    return r;
}

LIMatrix_t LIMatrixInverse(LIMatrix_t m) {
    
    LIMatrix_t result;
    float *temp = LIMatrixInverseN(m.i, 4);
    
    for(unsigned i=0; i<16; ++i)
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
	
	for (unsigned i = 0; i < 4; ++i) {
		LIVectorTransform(r.v[i], &(c->v[i]), m->i, 4);
	}
	
	return r;
}


