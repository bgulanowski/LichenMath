//
//  LIVector.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIVector.h"

#define LIPointf LIVector_t

static NSString * const vectorKey = @"_vector";

NSString *LIVectorToString(LIVector_t v) {
	return [NSString stringWithFormat:@"{%.20f,%.20f,%.20f}", v.x, v.y, v.z];
}

LIVector_t LIVectorFromString(NSString *s) {
	
	LIVector_t result = {0,0,0};
	NSScanner *scanner = [NSScanner scannerWithString:s];
	
	[scanner scanString:@"{" intoString:nil];
	[scanner scanFloat:&(result.x)];
	[scanner scanString:@"," intoString:nil];
	[scanner scanFloat:&(result.y)];
	[scanner scanString:@"," intoString:nil];
	[scanner scanFloat:&(result.z)];
	
	return result;
}

@implementation LIVector

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] vectorWithVector:_vector];
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_vector, [aDecoder decodeBytesForKey:vectorKey returnedLength:NULL], sizeof(_vector));
		}
		else {
			memcpy(&_vector, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(_vector));
		}
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(const uint8_t *)&_vector length:sizeof(_vector) forKey:vectorKey];
	}
	else {
		[aCoder encodeBytes:&_vector length:sizeof(_vector)];
	}
}

#pragma mark - LIVector

- (instancetype)initWithVector:(LIVector_t)vector {
	self = [super init];
	if (self) {
		_vector = vector;
	}
	return self;
}

+ (instancetype)vectorWithVector:(LIVector_t)vector {
	return [[self alloc] initWithVector:vector];
}

+ (instancetype)vectorWithX:(float)x y:(float)y z:(float)z {
	return [self vectorWithVector:LIVectorMake(x, y, z)];
}

@end
