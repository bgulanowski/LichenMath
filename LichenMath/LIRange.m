//
//  LIRange.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import "LIRange.h"

@implementation LIRange

#pragma mark - NSObject

- (NSString *)description {
	return [NSString stringWithFormat:@"range{%.5f, %.5f}", _range2f.p, _range2f.d];
}

- (BOOL)isEqual:(id)object {
	if (![object isKindOfClass:[LIRange class]]) {
		return NO;
	}
	return LIRange2fEquals(_range2f, ((LIRange *)object)->_range2f);
}

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] rangeWithRange:_range2f];
}

#pragma mark - NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(uint8_t *)&_range2f length:sizeof(LIRange2f) forKey:@"r"];
	}
	else {
		[aCoder encodeBytes:&_range2f length:sizeof(LIRange2f)];
	}
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_range2f, [aDecoder decodeBytesForKey:@"r" returnedLength:NULL], sizeof(LIRange2f));
		}
		else {
			memcpy(&_range2f, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(LIRange2f));
		}
	}
	return self;
}

#pragma mark - LIRange

- (instancetype)initWithRange:(LIRange2f)range {
	self = [super init];
	if (self) {
		_range2f = range;
	}
	return self;
}

+ (instancetype)rangeWithRange:(LIRange2f)range {
	return [[self alloc] initWithRange:range];
}

+ (instancetype)rangeWithPosition:(float)position distance:(float)distance {
	return [self rangeWithRange:LIRange2fMake(position, distance)];
}

@end
