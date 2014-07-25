//
//  LIMatrix.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIMatrix.h"

//#import "LichenMacros.h"

static NSString * const matrix4fKey = @"_matrix4f";

NSString *LIMatrix4fToString(LIMatrix4f m) {
	LIMatrix4f t = BATransposeMatrix4x4f(m);
	return [NSString stringWithFormat:@"{%@,%@,%@,%@}",
			LIPoint4fToString(t.v[0]), LIPoint4fToString(t.v[1]), LIPoint4fToString(t.v[2]), LIPoint4fToString(t.v[3])];
}

LIMatrix4f LIMatrix4fFromString(NSString *string) {
	LIMatrix4f r;
	sscanf([string cStringUsingEncoding:NSASCIIStringEncoding],
           "{{%f,%f,%f,%f},{%f,%f,%f,%f},{%f,%f,%f,%f}}",
           &(r.v[0].x), &(r.v[0].y), &(r.v[0].z), &(r.v[0].w),
		   &(r.v[1].x), &(r.v[1].y), &(r.v[1].z), &(r.v[1].w),
		   &(r.v[2].x), &(r.v[2].y), &(r.v[2].z), &(r.v[2].w));
	return r;
}

@implementation LIMatrix

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] matrixWithMatrix4f:_matrix4f];
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_matrix4f, [aDecoder decodeBytesForKey:matrix4fKey returnedLength:NULL], sizeof(_matrix4f));
		}
		else {
			memcpy(&_matrix4f, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(_matrix4f));
		}
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(const uint8_t *)&_matrix4f length:sizeof(_matrix4f) forKey:matrix4fKey];
	}
	else {
		[aCoder encodeBytes:&_matrix4f length:sizeof(_matrix4f)];
	}
}

#pragma mark - LIMatrix

- (instancetype)initWithMatrix4f:(LIMatrix4f)matrix4f {
	self = [super init];
	if (self) {
		_matrix4f = matrix4f;
	}
	return self;
}

+ (instancetype)matrixWithMatrix4f:(LIMatrix4f)matrix4f {
	return [[self alloc] initWithMatrix4f:matrix4f];
}

+ (instancetype)matrixWithElements:(float *)elements {
	return [self matrixWithMatrix4f:LIMatrix4fMake(elements)];
}

@end
