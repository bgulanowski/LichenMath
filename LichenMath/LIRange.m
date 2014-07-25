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
	return [NSString stringWithFormat:@"range{%.5f, %.5f}", _range.p, _range.d];
}

- (BOOL)isEqual:(id)object {
	if (![object isKindOfClass:[LIRange class]]) {
		return NO;
	}
	return LIRangeEquals(_range, ((LIRange *)object)->_range);
}

#pragma mark - NSCopying

- (id)copyWithZone:(NSZone *)zone {
	return [[self class] rangeWithRange:_range];
}

#pragma mark - NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder {
	if ([aCoder allowsKeyedCoding]) {
		[aCoder encodeBytes:(uint8_t *)&_range length:sizeof(LIRange_t) forKey:@"r"];
	}
	else {
		[aCoder encodeBytes:&_range length:sizeof(LIRange_t)];
	}
}

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super init];
	if (self) {
		if ([aDecoder allowsKeyedCoding]) {
			memcpy(&_range, [aDecoder decodeBytesForKey:@"r" returnedLength:NULL], sizeof(LIRange_t));
		}
		else {
			memcpy(&_range, [aDecoder decodeBytesWithReturnedLength:NULL], sizeof(LIRange_t));
		}
	}
	return self;
}

#pragma mark - LIRange

- (instancetype)initWithRange:(LIRange_t)range {
	self = [super init];
	if (self) {
		_range = range;
	}
	return self;
}

+ (instancetype)rangeWithRange:(LIRange_t)range {
	return [[self alloc] initWithRange:range];
}

+ (instancetype)rangeWithPosition:(float)position distance:(float)distance {
	return [self rangeWithRange:LIRangeMake(position, distance)];
}

@end
