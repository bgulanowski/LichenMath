//
//  LIMatrixTest.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-09-27.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "LIMatrix.h"
#import "LIPoint.h"
#import "LIVector.h"

@interface LIMatrixTest : XCTestCase

@end

@implementation LIMatrixTest {
    LIPoint_t x;
    LIPoint_t y;
    LIPoint_t z;
    
    LIPoint_t nx;
    LIPoint_t ny;
    LIPoint_t nz;
}

- (id)initWithInvocation:(NSInvocation *)invocation {
    self = [super initWithInvocation:invocation];
    if (self) {
        x = LIPointFromVector(LIVectorUnitX, 1);
        y = LIPointFromVector(LIVectorUnitY, 1);
        z = LIPointFromVector(LIVectorUnitZ, 1);
        
        nx = LIPointFromVector(LIVectorScale(LIVectorUnitX, -1), 1);
        ny = LIPointFromVector(LIVectorScale(LIVectorUnitY, -1), 1);
        nz = LIPointFromVector(LIVectorScale(LIVectorUnitZ, -1), 1);
    }
    return self;
}

- (void)testMatrixEntry {
    
    LIMatrix_t m = {};
    float elements[16];
    for (unsigned int i = 0; i<16; ++i) {
        elements[i] = (float)i;
    }
    LIMatrixInit(&m, elements);
    
    unsigned int i=0;
    for (unsigned int r=0; r<4; ++r) {
        for (unsigned int c=0; c<4; ++c) {
            LIMatrixEntry_t entry = LIMatrixEntryMake(r, c);
            float e = elements[i++];
            float a = LIMatrixGetEntry(&m, entry);
            XCTAssertEqual(e, a, @"Entry %@ does not match [%i:%i]", LIMatrixEntryToString(entry), r, c);
        }
    }
    
    float e = 100.0f;
    const int row = 4, col = 3, element = row * 4 + col;
    LIMatrixEntry_t entry = LIMatrixEntryMake(row, col);
    LIMatrixSetEntry(&m, entry, e);
    float a = LIMatrixGetElement(&m, element);
    XCTAssertEqual(e, a, @"Element %i does not match %@", element, LIMatrixEntryToString(entry));
}

- (void)testLIMatrixEquality {
    
}

- (void)testLIMatrixTranslation {
    
    LIPoint_t o = LIPointOrigin;

    LIVector_t v = LIVectorMake(1, -2, 30000000);
    LIMatrix_t m = LIMatrixMakeWithTranslation(v);
    LIPoint_t e = LIPointFromVector(v, 1);
    LIPoint_t a = LIMatrixTransformPoint(&o, &m);
    
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Translate point failed: %@ != %@", LIPointToString(a), LIPointToString(e));
}
// Even these simple transformations have rounding errors, so align the points
- (void)testLIMatrixMakeWithXAxisRotation {

    LIMatrix_t m = LIMatrixMakeWithXAxisRotation(M_PI_2);
    LIPoint_t a = LIPointAlign(LIMatrixTransformPoint(&x, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  x), @"Rotate  X about X failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nx, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nx), @"Rotate -X about X failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&y, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  z), @"Rotate  Y about X failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&ny, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nz), @"Rotate -Y about X failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&z, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, ny), @"Rotate  Z about X failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nz, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  y), @"Rotate -Z about X failed: %@", LIPointToString(a));
}

- (void)testLIMatrixMakeWithYAxisRotation {
    
    LIMatrix_t m = LIMatrixMakeWithYAxisRotation(M_PI_2);
    LIPoint_t a = LIPointAlign(LIMatrixTransformPoint(&x, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nz), @"Rotate  X about Y failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nx, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  z), @"Rotate -X about Y failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&y, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  y), @"Rotate  Y about Y failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&ny, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, ny), @"Rotate -Y about Y failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&z, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  x), @"Rotate  Z about Y failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nz, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nx), @"Rotate -Z about Y failed: %@", LIPointToString(a));
}

- (void)testLIMatrixMakeWithZAxisRotation {
    
    LIMatrix_t m = LIMatrixMakeWithZAxisRotation(M_PI_2);
    LIPoint_t a = LIPointAlign(LIMatrixTransformPoint(&x, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  y), @"Rotate  X about Z failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nx, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, ny), @"Rotate -X about Z failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&y, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nx), @"Rotate  Y about Z failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&ny, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  x), @"Rotate -Y about Z failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&z, &m));
    XCTAssertTrue(LIPointEqualToPoint(a,  z), @"Rotate  Z about Z failed: %@", LIPointToString(a));
    
    a = LIPointAlign(LIMatrixTransformPoint(&nz, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, nz), @"Rotate -Z about Z failed: %@", LIPointToString(a));
}

- (void)testLIMatrixFocus {
    
    LIMatrix_t m = LIMatrixFocus(LIPointOrigin, z);
    LIPoint_t f = LIPointOrigin;
    LIPoint_t e = LIPointOrigin;
    LIPoint_t a = LIPointAlign(LIMatrixTransformPoint(&f, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));

    f = z;
    e = z;
    a = LIPointAlign(LIMatrixTransformPoint(&f, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));
    
    
    m = LIMatrixFocus(LIPointOrigin, nz);
    
    f = LIPointOrigin;
    e = LIPointOrigin;
    a = LIPointAlign(LIMatrixTransformPoint(&f, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));
    
    f = LIPointMake(1, 1, 1, 1);
    e = LIPointMake(-1, 1, -1, 1);
    a = LIPointAlign(LIMatrixTransformPoint(&f, &m));
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));
    
    
    m = LIMatrixFocus(LIPointMake(10, 2, -3, 1), LIPointMake(-10, 2, -3, 1));
    f = LIPointMake(0, 2, -3, 1);
    e = LIPointMake(0, 0, 10, 1);
    a = LIMatrixTransformPoint(&f, &m);
    XCTAssertTrue(LIPointEqualToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));
    
    
    LIPoint_t l = LIPointMake(1, 1, 1, 1);
    m = LIMatrixFocus(LIPointOrigin, l);
    e = LIPointMake(0, 0, sqrtf(3.0), 1);
    a = LIMatrixTransformPoint(&l, &m);
    XCTAssertTrue(LIPointCloseToPoint(a, e), @"Failed to transform point: %@", LIPointToString(a));
}

@end
