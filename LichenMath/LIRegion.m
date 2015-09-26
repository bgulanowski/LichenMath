//
//  LIRegion.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIRegion.h"

#import "LIPoint.h"
#import "LIVector.h"

static NSString * const regionKey = @"_region";

NSString *LIRegionToString(LIRegion_t region) {
    NSString *o = LIPointToString(region.origin.p);
    NSString *v = LIVectorToString(LIVectorFromSize(region.volume.s));
    return [NSString stringWithFormat:@"{%@,%@}", o, v];
}

LIRegion_t LIRegionFromString(NSString *string) {
    LIRegion_t r;
    NSRange range = NSMakeRange(1, string.length - 2);
    NSArray *comps = [[string substringWithRange:range] componentsSeparatedByString:@","];
    r.origin.p = LIPointFromString(comps[0]);
    r.volume.s = LIVectorToSize(LIVectorFromString(comps[1]));
    return r;
}

@implementation LIRegion

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] regionWithRegion:_region];
}

#pragma mark - NSCoding

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_region, [aDecoder decodeBytesForKey:regionKey returnedLength:NULL], sizeof(_region));
		}
		else {
            NSUInteger length = 0;
			memcpy(&_region, [aDecoder decodeBytesWithReturnedLength:&length], sizeof(_region));
		}
	}
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(const uint8_t *)&_region length:sizeof(_region) forKey:regionKey];
	}
	else {
		[aCoder encodeBytes:&_region length:sizeof(_region)];
	}
}

#pragma mark - LIRegion

- (instancetype)initWithRegion:(LIRegion_t)region {
	self = [super init];
	if (self) {
		_region = region;
	}
	return self;
}

+ (instancetype)regionWithRegion:(LIRegion_t)region {
	return [[self alloc] initWithRegion:region];
}

+ (instancetype)regionWithOrigin:(LIPoint_t)origin size:(LISize_t)size {
	return [self regionWithRegion:(LIRegion_t) { .origin.p = origin, .volume.s = size }];
}

+ (instancetype)regionWithX:(float)x y:(float)y z:(float)z width:(float)width height:(float)height depth:(float)depth {
	return [self regionWithRegion:LIRegionMake(x, y, z, width, height, depth)];
}

- (NSString *)debugDescription {
    return LIRegionToString(_region);
}

@end
