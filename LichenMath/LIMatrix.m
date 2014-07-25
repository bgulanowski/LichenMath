//
//  LIMatrix.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIMatrix.h"

//#import "LichenMacros.h"

static NSString * const matrixKey = @"_matrix";

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

float LIMatrixDeterminantN(float *m, NSUInteger n) {
    
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

static float *LIMatrixInverseN(float *m, NSUInteger n) {
    
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

@end
