//
//  LIVector.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIVector.h"

#define scanGLfloat scanFloat
#define BAPointf LIVector3f

static NSString * const vector3fKey = @"_vector3f";

NSString *LIVectorToString(LIVector3f v) {
	return [NSString stringWithFormat:@"{%.20f,%.20f,%.20f}", v.x, v.y, v.z];
}

LIVector3f LIVectorFromString(NSString *s) {
	
	LIVector3f result = {0,0,0};
	NSScanner *scanner = [NSScanner scannerWithString:s];
	
	[scanner scanString:@"{" intoString:nil];
	[scanner scanGLfloat:&(result.x)];
	[scanner scanString:@"," intoString:nil];
	[scanner scanGLfloat:&(result.y)];
	[scanner scanString:@"," intoString:nil];
	[scanner scanGLfloat:&(result.z)];
	
	return result;
}

@implementation LIVector

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] vectorWithVector3f:_vector3f];
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_vector3f, [aDecoder decodeBytesForKey:vector3fKey returnedLength:NULL], sizeof(_vector3f));
		}
		else {
			memcpy(&_vector3f, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(_vector3f));
		}
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(const uint8_t *)&_vector3f length:sizeof(_vector3f) forKey:vector3fKey];
	}
	else {
		[aCoder encodeBytes:&_vector3f length:sizeof(_vector3f)];
	}
}

#pragma mark - LIVector

- (instancetype)initWithVector3f:(LIVector3f)vector3f {
	self = [super init];
	if (self) {
		_vector3f = vector3f;
	}
	return self;
}

+ (instancetype)vectorWithVector3f:(LIVector3f)vector3f {
	return [[self alloc] initWithVector3f:vector3f];
}

+ (instancetype)vectorWithX:(float)x y:(float)y z:(float)z {
	return [self vectorWithVector3f:LIVector3fMake(x, y, z)];
}

@end
