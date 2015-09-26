//
//  LILineTest.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-26.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "LILine_t.h"
#import "LIPoint.h"

@interface LILineTest : XCTestCase

@end

@implementation LILineTest

/*
- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}
 */

- (void)testLILineLineIntersection {
    
    // test the co-ordinate axes intersection at the origin
    LILine_t l1 = LILineMake(LIPointOrigin, LIVectorUnitX);
    LILine_t l2 = LILineMake(LIPointOrigin, LIVectorUnitY);
    LILine_t l3 = LILineMake(LIPointOrigin, LIVectorUnitZ);
    
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, LILineLineIntersection(l1, l2)));
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, LILineLineIntersection(l2, l3)));
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, LILineLineIntersection(l3, l1)));
    
    // redefine the co-ordinate axes with offset points and scaled vectors
    l1 = LILineMake(LIPointTranslate(LIPointOrigin, LIVectorUnitX), LIVectorScale(LIVectorUnitX, 2.0f));
    l2 = LILineMake(LIPointTranslate(LIPointOrigin, LIVectorUnitY), LIVectorScale(LIVectorUnitY, -1.0f));
    l3 = LILineMake(LIPointTranslate(LIPointOrigin, LIVectorUnitZ), LIVectorScale(LIVectorUnitZ, 0.5f));
    
    LIPoint_t p = LILineLineIntersection(l1, l2);
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, p), @"%@ != %@", LIPointToString(LIPointOrigin), LIPointToString(p));
    p = LILineLineIntersection(l2, l3);
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, p), @"%@ != %@", LIPointToString(LIPointOrigin), LIPointToString(p));
    p = LILineLineIntersection(l3, l1);
    XCTAssertTrue(LIPointEqualToPoint(LIPointOrigin, p), @"%@ != %@", LIPointToString(LIPointOrigin), LIPointToString(p));
    
    // test for parallel lines
    l1 = LILineMake(LIPointOrigin, LIVectorUnitX);
    l2 = LILineMake(LIPointTranslate(LIPointOrigin, LIVectorMake(1, 1, 1)), LIVectorUnitX);
    XCTAssertTrue(LIPointEqualToPoint(LIPointZero, LILineLineIntersection(l1, l2)));
}

@end
