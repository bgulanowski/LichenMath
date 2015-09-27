//
//  LIVectorTest.m
//  LichenMath
//
//  Created by Brent Gulanowski on 2015-08-11.
//  Copyright © 2015 Lichen Labs. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "LichenMath.h"

#import <objc/runtime.h>

@interface LIVectorTest : XCTestCase

@end

static const float LARGE_VAL = 2e12 + 9879.0f;
static const float DECIMAL_VAL = 1.0f/10.0f;

static const LIVector_t TEST_VECTOR = (LIVector_t) { 0, LARGE_VAL, DECIMAL_VAL };

@interface VectorInfo : NSObject {
@public
    LIVector_t _vector;
    LIVector_t _squares;
    float _length;
    float _square;
}

- (instancetype)initWithX:(float)x y:(float)y z:(float)z;

@end

NSSet *sumsOfSquares( BOOL uniques, const float max_root );

@implementation LIVectorTest {
    NSSet *_vectorInfos;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _vectorInfos = sumsOfSquares(YES, 32.f);
    }
    return self;
}

#if 0
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
#endif

- (void)testVectorZero {
    XCTAssertEqual(LIVectorZero.x, 0.0f);
    XCTAssertEqual(LIVectorZero.y, 0.0f);
    XCTAssertEqual(LIVectorZero.z, 0.0f);
}

- (void)testVectorIsZero {
    LIVector_t v = { 0, 0, 0 };
    XCTAssertTrue(LIVectorIsZero(v));
}

- (void)testVectorMake {
    LIVector_t v = LIVectorMake(0, LARGE_VAL, DECIMAL_VAL);
    XCTAssertEqual(v.x, 0);
    XCTAssertEqual(v.y, LARGE_VAL);
    XCTAssertEqual(v.z, DECIMAL_VAL);
}

- (void)testVectorCopy {
    LIVector_t v = LIVectorCopy(TEST_VECTOR);
    XCTAssertEqual(v.x, TEST_VECTOR.x);
    XCTAssertEqual(v.y, TEST_VECTOR.y);
    XCTAssertEqual(v.z, TEST_VECTOR.z);
    XCTAssertNotEqual(&TEST_VECTOR, &v);
}

- (void)testVectorHash {

    float const max = 32;
    unsigned long count = max*max*max;

#define USE_DICT 1
#if USE_DICT
    // Using a dictionary means no size limits on the hash, but 5x slower or worse
    NSMutableDictionary *hashes = [NSMutableDictionary dictionary];
#else
    NSUInteger size = (unsigned long) count*4 - 1;
    NSUInteger *table = calloc(size, sizeof(NSUInteger));
#endif
    
    NSUInteger collisions = 0;
    NSUInteger worstCollision = 0;
    
    for (float i=0; i<max; ++i) {
        for (float j=0; j<max; ++j) {
            for (float k=0; k<max; ++k) {
                NSUInteger hashi = LIVectorHash(LIVectorMake(i, j + 501, k + 2871));
#if USE_DICT
                NSNumber *hash = @(hashi);
                NSUInteger hashCount = [hashes[hash] unsignedIntegerValue] + 1;
                hashes[hash] = @(hashCount);
#else
                NSUInteger index = hashi%size;
                NSUInteger hashCount = ++table[index];
#endif
                if (hashCount > 1) {
                    ++collisions;
                    if (hashCount > worstCollision) {
                        worstCollision = hashCount;
                    }
                }
            }
        }
    }
    
#if USE_DICT
#else
    free(table), table = NULL;
#endif
    
    NSLog(@"Hashed %lu vectors; got %td collisions (worst: %td)", count, collisions, worstCollision);
    XCTAssertTrue(collisions < 256, @"Too many collisions: %td", collisions);
}


- (void)testVectorEqual {
    LIVector_t v = LIVectorMake(0, LARGE_VAL, DECIMAL_VAL);
    XCTAssertTrue(LIVectorEqualToVector(TEST_VECTOR, v));
}

- (void)testVectorInverse {
    LIVector_t v = LIVectorInverse(TEST_VECTOR);
    XCTAssertEqual(v.x, -TEST_VECTOR.x);
    XCTAssertEqual(v.x, -TEST_VECTOR.x);
    XCTAssertEqual(v.y, -TEST_VECTOR.y);
    XCTAssertEqual(v.z, -TEST_VECTOR.z);
}

- (void)testVectorRotate {
    LIVector_t v = LIVectorRotate(TEST_VECTOR);
    XCTAssertEqual(v.x, LARGE_VAL);
    XCTAssertEqual(v.y, DECIMAL_VAL);
    XCTAssertEqual(v.z, 0);
}

- (void)testVectorDominantElement {
    XCTAssertEqual(LIVectorDominantElement(TEST_VECTOR), LIVectorElementY);
    XCTAssertEqual(LIVectorDominantElement(LIVectorInverse(TEST_VECTOR)), LIVectorElementY);
    
    LIVector_t v = LIVectorRotate(TEST_VECTOR);
    XCTAssertEqual(LIVectorDominantElement(v), LIVectorElementX);
    XCTAssertEqual(LIVectorDominantElement(LIVectorInverse(v)), LIVectorElementX);
    
    v = LIVectorRotate(v);
    XCTAssertEqual(LIVectorDominantElement(v), LIVectorElementZ);
    XCTAssertEqual(LIVectorDominantElement(LIVectorInverse(v)), LIVectorElementZ);
}

- (void)testVectorClosestAxis {
    LIVector_t a = LIVectorClosestAxis(TEST_VECTOR);
    LIVector_t e = LIVectorUnitY;
    XCTAssertTrue(LIVectorEqualToVector(a, e), @"%@ != %@", LIVectorToString(a), LIVectorToString(e));
}

- (void)testVectorSortedElements {
    LIVector_t v = LIVectorMake(3, 2, 1);
    LIVector_t e = LIVectorMake(1, 2, 3);
    XCTAssertTrue(LIVectorEqualToVector(LIVectorSortedElements(v), e));
}

- (void)testVectorAdd {
    LIVector_t v = LIVectorAdd(LIVectorZero, LIVectorZero);
    XCTAssertTrue(LIVectorIsZero(v))
    ;
    v = LIVectorAdd(LIVectorZero, TEST_VECTOR);
    XCTAssertTrue(LIVectorEqualToVector(v, TEST_VECTOR));
    
    v = LIVectorAdd(TEST_VECTOR, LIVectorZero);
    XCTAssertTrue(LIVectorEqualToVector(v, TEST_VECTOR));
    
    v = LIVectorAdd(TEST_VECTOR, LIVectorRotate(TEST_VECTOR));
    XCTAssertEqual(v.x, LARGE_VAL);
    XCTAssertEqual(v.y, LARGE_VAL + DECIMAL_VAL);
    XCTAssertEqual(v.z, DECIMAL_VAL);
}

- (void)testVectorSubtract {
    LIVector_t v = LIVectorSubtract(LIVectorZero, LIVectorZero);
    XCTAssertTrue(LIVectorEqualToVector(v, LIVectorZero));
    
    v = LIVectorSubtract(TEST_VECTOR, TEST_VECTOR);
    XCTAssertTrue(LIVectorEqualToVector(v, LIVectorZero));
    v = LIVectorSubtract(LIVectorZero, TEST_VECTOR);
    XCTAssertTrue(LIVectorEqualToVector(v, LIVectorInverse(TEST_VECTOR)));
}

- (void)testVectorLength {
    XCTAssertEqual(0, LIVectorLength(LIVectorZero));
    XCTAssertEqual(1.0f, LIVectorLength(LIVectorUnitX));
    XCTAssertEqual(1.0f, LIVectorLength(LIVectorUnitY));
    XCTAssertEqual(1.0f, LIVectorLength(LIVectorUnitZ));
    
    for (VectorInfo *vectorInfo in _vectorInfos) {
        XCTAssertEqual(vectorInfo->_length, LIVectorLength(vectorInfo->_vector));
    }
}

- (void)testVectorNormalize {
    XCTAssertTrue(LIVectorEqualToVector(LIVectorZero, LIVectorNormalize(LIVectorZero)));
    XCTAssertEqual(1.0f, LIVectorLength(LIVectorNormalize(TEST_VECTOR)));
}

- (void)testVectorCrossProduct {
    LIVector_t units[] = { LIVectorUnitX, LIVectorUnitY, LIVectorUnitZ };
    for (int i=0; i<3; ++i) {
        XCTAssertTrue(LIVectorIsZero(LIVectorCrossProduct(units[i], units[i])));
        XCTAssertTrue(LIVectorEqualToVector(LIVectorCrossProduct(units[i%3], units[(i+1)%3]), units[(i+2)%3]));
    }
    
//    LIVector_t e = LIVectorMake(1.f, 1.f, 1.f);
//    LIVector_t v1 =
//    LIVector_t v = LIVectorCrossProduct(LIVectorMake(1, 1, 1), LIVectorMake(-1, 1, 1));
//    LIVectorLength(v);
}

@end

@implementation VectorInfo

- (NSUInteger)hash {
    return LIVectorHash(_vector);
}

- (BOOL)isEqual:(VectorInfo *)object {
    return object == self || (object_getClass(self) == object_getClass(object) && LIVectorEqualToVector(_vector, object->_vector));
}

- (NSComparisonResult)compare:(VectorInfo *)other
{
    return _length == other->_length ? NSOrderedSame : _length < other->_length ? NSOrderedAscending : NSOrderedDescending;
}

- (instancetype)initWithX:(float)x y:(float)y z:(float)z {
    self = [super init];
    if (self) {
        _vector = LIVectorSortedElements(LIVectorMake(x, y, z));
        _squares = LIVectorMake(_vector.x*_vector.x, _vector.y*_vector.y, _vector.z*_vector.z);
        _square = _squares.x + _squares.y + _squares.z;
        _length = sqrtf(_square);
    }
    return self;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"%01.f: %1.f, %1.f, %1.f (%1.f = %1.f + %1.f + %1.f)", _length, _vector.x, _vector.y, _vector.z, _square, _squares.x, _squares.y, _squares.z];
}

@end

NSSet *sumsOfSquares( BOOL uniques, const float max_root ) {
    
    NSMutableSet *vectorInfos = [NSMutableSet set];

    for (float root=1.0f; root<max_root; ++root) {
        float const square = root * root;
        
        for (float z=1.0f; z<max_root; ++z) {
            for (float y=1.0f; y<max_root; ++y) {
                if (z == y) {
                    continue;
                }
                for (float x=1.0f; x<max_root; ++x) {
                    
                    if (uniques && (y == x || x == z)) {
                        continue;
                    }
                    
                    VectorInfo *vectorInfo = [[VectorInfo alloc] initWithX:x y:y z:z];
                    
                    if (square == vectorInfo->_square) {
                        [vectorInfos addObject:vectorInfo];
                    }
                }
            }
        }
    }
    
    return vectorInfos;
}

/* initial output of above:
 
 "7: 2, 3, 6 (49 = 4 + 9 + 36)",
 "9: 1, 4, 8 (81 = 1 + 16 + 64)",
 "11: 2, 6, 9 (121 = 4 + 36 + 81)",
 "13: 3, 4, 12 (169 = 9 + 16 + 144)",
 "14: 4, 6, 12 (196 = 16 + 36 + 144)",
 "15: 2, 5, 14 (225 = 4 + 25 + 196)",
 "15: 2, 10, 11 (225 = 4 + 100 + 121)",
 "17: 8, 9, 12 (289 = 64 + 81 + 144)",
 "18: 2, 8, 16 (324 = 4 + 64 + 256)",
 "19: 1, 6, 18 (361 = 1 + 36 + 324)",
 "19: 6, 10, 15 (361 = 36 + 100 + 225)",
 "21: 4, 5, 20 (441 = 16 + 25 + 400)",
 "21: 4, 8, 19 (441 = 16 + 64 + 361)",
 "21: 4, 13, 16 (441 = 16 + 169 + 256)",
 "21: 6, 9, 18 (441 = 36 + 81 + 324)",
 "21: 8, 11, 16 (441 = 64 + 121 + 256)",
 "22: 4, 12, 18 (484 = 16 + 144 + 324)",
 "23: 3, 6, 22 (529 = 9 + 36 + 484)",
 "23: 3, 14, 18 (529 = 9 + 196 + 324)",
 "23: 6, 13, 18 (529 = 36 + 169 + 324)",
 "25: 9, 12, 20 (625 = 81 + 144 + 400)",
 "25: 12, 15, 16 (625 = 144 + 225 + 256)",
 "26: 6, 8, 24 (676 = 36 + 64 + 576)",
 "27: 2, 7, 26 (729 = 4 + 49 + 676)",
 "27: 2, 10, 25 (729 = 4 + 100 + 625)",
 "27: 2, 14, 23 (729 = 4 + 196 + 529)",
 "27: 3, 12, 24 (729 = 9 + 144 + 576)",
 "27: 7, 14, 22 (729 = 49 + 196 + 484)",
 "28: 8, 12, 24 (784 = 64 + 144 + 576)",
 "29: 3, 16, 24 (841 = 9 + 256 + 576)",
 "29: 11, 12, 24 (841 = 121 + 144 + 576)",
 "29: 12, 16, 21 (841 = 144 + 256 + 441)",
 "30: 4, 10, 28 (900 = 16 + 100 + 784)",
 "30: 4, 20, 22 (900 = 16 + 400 + 484)",
 "31: 5, 6, 30 (961 = 25 + 36 + 900)",
 "31: 6, 14, 27 (961 = 36 + 196 + 729)",
 "31: 6, 21, 22 (961 = 36 + 441 + 484)",
 "31: 14, 18, 21 (961 = 196 + 324 + 441)"

 */
