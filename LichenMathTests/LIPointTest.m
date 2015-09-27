//
//  LIPointTest.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-26.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "LIPoint.h"
#import "LIVector.h"

@interface LIPointTest : XCTestCase

@end

@implementation LIPointTest

//- (void)setUp {
//    [super setUp];
//}
//
//- (void)tearDown {
//    [super tearDown];
//}

- (void)testLIPointZero {
    XCTAssertEqual(LIPointZero.x, 0);
    XCTAssertEqual(LIPointZero.y, 0);
    XCTAssertEqual(LIPointZero.z, 0);
    XCTAssertEqual(LIPointZero.w, 0);
}

- (void)testLIPointOrigin {
    XCTAssertEqual(LIPointOrigin.x, 0);
    XCTAssertEqual(LIPointOrigin.y, 0);
    XCTAssertEqual(LIPointOrigin.z, 0);
    XCTAssertEqual(LIPointOrigin.w, 1.0f);
}

- (void)testLIPointIsNormal {
    XCTAssertFalse(LIPointIsNormal(LIPointZero));
    XCTAssertTrue(LIPointIsNormal(LIPointOrigin));
}

- (void)testLIPointMake {
    float x = 0, y = 1e16, z = -7.0f/23.0f, w = 1.0f;
    LIPoint_t p = LIPointMake(x, y, z, w);
    XCTAssertEqual(x, p.x);
    XCTAssertEqual(y, p.y);
    XCTAssertEqual(z, p.z);
    XCTAssertEqual(w, p.w);
}

- (void)testLIPointEqualToPoint {
    
    XCTAssertTrue(LIPointEqualToPoint(LIPointZero, LIPointZero));
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, LIPointOrigin));
    XCTAssertFalse(LIPointEqualToPoint(LIPointZero, LIPointOrigin));
    
    LIPoint_t p = LIPointMake(1, 0, 0, 1);
    XCTAssertFalse(LIPointEqualToPoint(p, LIPointOrigin));
    p = LIPointMake(0, 1, 0, 1);
    XCTAssertFalse(LIPointEqualToPoint(p, LIPointOrigin));
    p = LIPointMake(0, 0, 1, 1);
    XCTAssertFalse(LIPointEqualToPoint(p, LIPointOrigin));
}

- (void)testLIPointIsOrigin {
    XCTAssertTrue(LIPointIsOrigin(LIPointOrigin));
    XCTAssertFalse(LIPointIsOrigin(LIPointZero));
    LIPoint_t p = LIPointMake(0, 0, 0, 1.0f);
    XCTAssertTrue(LIPointIsOrigin(p));
    p = LIPointMake(0, .000001, 0, 1.0f);
    XCTAssertFalse(LIPointIsOrigin(p));
}

- (void)testLIPointTranslate {
    LIPoint_t p = LIPointTranslate(LIPointOrigin, LIVectorZero);
    XCTAssertTrue(LIPointEqualToPoint(p, LIPointOrigin));
}

- (void)testLIPointAlign {
    
    LIPoint_t p = LIPointMake(0.1f, -0.000125f, M_PI_4 * 2e20, 1.0f);
    LIPoint_t a = LIPointAlign(p);
    LIVector_t v = LIVectorSubtract(LIVectorFromPoint(p), LIVectorFromPoint(a));
    
    XCTAssertFalse(LIVectorIsZero(v), @"remainders should not all be zero: %@", LIVectorToString(v));
    
    float const scale = (float)0x1p+20;
    LIPoint_t r = LIPointMap(a, ^(float e) { return truncf(e * scale) - e * scale; });
    v = LIVectorFromPoint(r);
    
    XCTAssertTrue(LIVectorIsZero(v), @"remainders should all be zero: %@", LIVectorToString(v));
}

@end
