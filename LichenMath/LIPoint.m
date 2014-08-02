//
//  LIPoint_t.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIPoint.h"

#import "LIMatrix.h"
#import "LichenMath_Private.h"

NSString *LIPointToString(LIPoint_t p) {
	return [NSString stringWithFormat:@"{%.8f,%.8f,%.8f,%.8f}", p.x, p.y, p.z, p.w];
}

LIPoint_t LIPointFromString(NSString *string) {
	LIPoint_t r;
	sscanf([string cStringUsingEncoding:NSASCIIStringEncoding],
           "{%f,%f,%f,%f}",
           &(r.x), &(r.y), &(r.z), &(r.w));
	return r;
}

@implementation LIPoint

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [LIPoint pointWithPoint:_point];
}

#pragma mark - NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(uint8_t *)&_point length:sizeof(LIPoint_t) forKey:@"r"];
	}
	else {
		[aCoder encodeBytes:&_point length:sizeof(LIPoint_t)];
	}
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_point, [aDecoder decodeBytesForKey:@"r" returnedLength:NULL], sizeof(LIPoint_t));
		}
		else {
			memcpy(&_point, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(LIPoint_t));
		}
	}
	return self;
}

- (instancetype)initWithPoint:(LIPoint_t)point {
	self = [super init];
	if (self) {
		_point = point;
	}
	return self;
}

+ (instancetype)pointWithPoint:(LIPoint_t)point {
	return [[self alloc] initWithPoint:point];
}

+ (instancetype)pointWithX:(float)x y:(float)y z:(float)z w:(float)w {
	return [self pointWithPoint:LIPointMake(x, y, z, w)];
}

- (LIPoint *)pointWithMatrix:(LIMatrix *)transform {
//	LIPoint_t r;
	return nil;
}

- (void)applyMatrix:(LIMatrix *)matrix {
	_point = LIMatrixTransformPoint(&(_point), &(matrix->_matrix));
}

@end
