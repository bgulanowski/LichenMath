//
//  LIVector.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
	float x;
	float y;
	float z;
} LIVector3f;

NS_INLINE LIVector3f LIVector3fMake(float x, float y, float z) {
	return (LIVector3f){.x = x, .y = y, .z = z};
}

extern NSString *LIVectorToString(LIVector3f v);
extern LIVector3f LIVectorFromString(NSString *s);

@interface LIVector : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIVector3f vector3f;

- (instancetype)initWithVector3f:(LIVector3f)vector3f;
+ (instancetype)vectorWithVector3f:(LIVector3f)vector3f;
+ (instancetype)vectorWithX:(float)x y:(float)y z:(float)z;

@end
