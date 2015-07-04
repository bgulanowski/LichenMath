//
//  LIMatrix.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIMatrix.h"

#import <LichenMath/LIVector.h>
#import <LichenMath/LIPoint.h>

#import "LichenMath_Private.h"

static NSString * const matrixKey = @"_matrix";

NSString *LIMatrixToString(LIMatrix_t m) {
	LIMatrix_t t = LIMatrixTranspose(m);
	return [NSString stringWithFormat:@"{\n%@,\n%@,\n%@,\n%@\n}",
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

@implementation LIMatrix

- (LIMatrix_t *const)r_matrix { return &_matrix; }

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
            NSUInteger length = 0;
			memcpy(&_matrix, [aDecoder decodeBytesWithReturnedLength:&length], sizeof(_matrix));
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

+ (instancetype)identity
{
	return [self matrixWithMatrix:LIMatrixIdentity];
}

- (void)concatenate:(LIMatrix *)matrix {
	_matrix = LIMatrixConcatenate(&_matrix, &(matrix->_matrix));
}

- (LIPoint *)transformPoint:(LIPoint *)point {
	return [LIPoint pointWithPoint:LIMatrixTransformPoint(&(point->_point), &_matrix)];
}

- (void)setValue:(float)v forElement:(intptr_t)e {
	_matrix.i[e] = v;
}

- (float)valueForElement:(intptr_t)e {
	return _matrix.i[e];
}

- (void)setValues:(float *)v forElements:(intptr_t *)elements count:(NSUInteger)count {
	for (NSUInteger i=0; i<count; ++i) {
		_matrix.i[elements[i]] = v[i];
	}
}

- (NSString *)debugDescription {
	return LIMatrixToString(_matrix);
}

@end
