//
//  LichenMathTests.m
//  LichenMathTests
//
//  Created by Brent Gulanowski on 2014-07-22.
//  Copyright (c) 2014 Lichen Labs. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "LIMathUtilities.h"
#import "LILine_t.h"

@interface LichenMathTests : XCTestCase

@end

@implementation LichenMathTests

- (void)testFloatBetweenFloats {
    
    XCTAssertFalse(LIFloatBetweenFloats(0, 0, 0), @"Zero between zero and zero");
    XCTAssertTrue(LIFloatBetweenFloats(0, 0, 1.0f), @"Zero not between zero and one");
    XCTAssertTrue(LIFloatBetweenFloats(0, 1.0f, 0), @"Zero not between one and zero (reversed)");
    XCTAssertFalse(LIFloatBetweenFloats(1.0f, 0, 1.0f), @"One between zero and one (exclusive)");
}

- (void)testFloatAlign {
    
    NSLog(@"Test align unit: %f; inverse: %f", ALIGN_UNIT, ALIGN_UNIT_INV);
    XCTAssertEqual(1.0/ALIGN_UNIT, ALIGN_UNIT_INV, @"Align unit inverse is not inverse of align unit");

    float f = 1.0f;
    
    for (int i=0; i<32; ++i) {
        float r = LIFloatAlign(f);
        XCTAssertTrue(r >= ALIGN_UNIT_INV || r == 0.0, @"Failed: f->r: %f -> %f", f, r);
        f *= 0.5f;
    }
}

@end
