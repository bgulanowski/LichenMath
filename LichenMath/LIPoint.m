//
//  LIPoint.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIPoint.h"

NSString *LIPoint4fToString(LIPoint4f p) {
	return [NSString stringWithFormat:@"{%.8f,%.8f,%.8f,%.8f}", p.x, p.y, p.z, p.w];
}

LIPoint4f LIPoint4fFromString(NSString *string) {
	LIPoint4f r;
	sscanf([string cStringUsingEncoding:NSASCIIStringEncoding],
           "{%f,%f,%f,%f}",
           &(r.x), &(r.y), &(r.z), &(r.w));
	return r;
}

@implementation LIPoint

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [LIPoint pointWithPoint4f:_point4f];
}

#pragma mark - NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(uint8_t *)&_point4f length:sizeof(LIPoint4f) forKey:@"r"];
	}
	else {
		[aCoder encodeBytes:&_point4f length:sizeof(LIPoint4f)];
	}
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_point4f, [aDecoder decodeBytesForKey:@"r" returnedLength:NULL], sizeof(LIPoint4f));
		}
		else {
			memcpy(&_point4f, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(LIPoint4f));
		}
	}
	return self;
}

- (instancetype)initWithPoint4f:(LIPoint4f)point4f {
	self = [super init];
	if (self) {
		_point4f = point4f;
	}
	return self;
}

+ (instancetype)pointWithPoint4f:(LIPoint4f)point4f {
	return [[self alloc] initWithPoint4f:point4f];
}

+ (instancetype)pointWithX:(float)x y:(float)y z:(float)z w:(float)w {
	return [self pointWithPoint4f:LIPoint4fMake(x, y, z, w)];
}

@end
