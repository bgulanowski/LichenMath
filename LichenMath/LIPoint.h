//
//  LIPoint.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
	float x;
	float y;
	float z;
	float w;
} LIPoint4f;

#define LIVector4f LIPoint4f

NS_INLINE LIPoint4f LIPoint4fMake(float x, float y, float z, float w) {
	return (LIPoint4f){.x = x, .y = y, .z = z, .w = w};
}

extern NSString *LIPoint4fToString(LIPoint4f p);
extern LIPoint4f LIPoint4fFromString(NSString *string);

@interface LIPoint : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIPoint4f point4f;

- (instancetype)initWithPoint4f:(LIPoint4f)point4f;
+ (instancetype)pointWithPoint4f:(LIPoint4f)point4f;
+ (instancetype)pointWithX:(float)x y:(float)y z:(float)z w:(float)w;

@end
