//
//  LIRegion.h
//  LichenMath
//
//  Created by Brent Gulanowski on 2014-07-24.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LichenMath/LIPoint_t.h>
#import <LichenMath/LIRegion_t.h>

@interface LIRegion : NSObject<NSCopying, NSCoding>

@property (nonatomic) LIRegion_t region;

- (instancetype)initWithRegion:(LIRegion_t)region;
+ (instancetype)regionWithRegion:(LIRegion_t)region;
+ (instancetype)regionWithOrigin:(LIPoint_t)origin size:(LISize_t)size;
+ (instancetype)regionWithX:(float)x y:(float)y z:(float)z width:(float)width height:(float)height depth:(float)depth;

@end
