////////////////////////////////////////////////////////////////////////////
//
// Copyright 2014 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <HARealm/HACollection.h>

@class HAObject, HARealm;

/**
 HAResults is an auto-updating container type in Realm returned from object
 queries.

 HAResults can be queried with the same predicates as HAObject and HAArray
 and you can chain queries to further filter query results.

 HAResults cannot be created directly.
 */

@interface HAResults : NSObject<HACollection, NSFastEnumeration>

/**---------------------------------------------------------------------------------------
 *  @name HAResults Properties
 *  ---------------------------------------------------------------------------------------
 */

/**
 Number of objects in the results.
 */
@property (nonatomic, readonly, assign) NSUInteger count;

/**
 The class name (i.e. type) of the HAObjects contained in this HAResults.
 */
@property (nonatomic, readonly, copy) NSString *objectClassName;

/**
 The Realm this `HAResults` is associated with.
 */
@property (nonatomic, readonly) HARealm *realm;

#pragma mark -

/**---------------------------------------------------------------------------------------
 *  @name Accessing Objects from an HAResults
 * ---------------------------------------------------------------------------------------
 */

/**
 Returns the object at the index specified.

 @param index   The index to look up.

 @return An HAObject of the class contained by this HAResults.
 */
- (id)objectAtIndex:(NSUInteger)index;

/**
 Returns the first object in the results.

 Returns `nil` if called on an empty HAResults.

 @return An HAObject of the class contained by this HAResults.
 */
- (id)firstObject;

/**
 Returns the last object in the results.

 Returns `nil` if called on an empty HAResults.

 @return An HAObject of the class contained by this HAResults.
 */
- (id)lastObject;



#pragma mark -


/**---------------------------------------------------------------------------------------
 *  @name Querying Results
 *  ---------------------------------------------------------------------------------------
 */
/**
 Gets the index of an object.

 Returns NSNotFound if the object is not found in this HAResults.

 @param object  An object (of the same type as returned from the objectClassName selector).
 */
- (NSUInteger)indexOfObject:(HAObject *)object;

/**
 Gets the index of the first object matching the predicate.

 @param predicateFormat The predicate format string which can accept variable arguments.

 @return    Index of object or NSNotFound if the object is not found in this HAResults.
 */
- (NSUInteger)indexOfObjectWhere:(NSString *)predicateFormat, ...;

/**
 Gets the index of the first object matching the predicate.

 @param predicate   The predicate to filter the objects.

 @return    Index of object or NSNotFound if the object is not found in this HAResults.
 */
- (NSUInteger)indexOfObjectWithPredicate:(NSPredicate *)predicate;

/**
 Get objects matching the given predicate in the HAResults.

 @param predicateFormat The predicate format string which can accept variable arguments.

 @return                An HAResults of objects that match the given predicate
 */
- (HAResults *)objectsWhere:(NSString *)predicateFormat, ...;

/**
 Get objects matching the given predicate in the HAResults.

 @param predicate   The predicate to filter the objects.

 @return            An HAResults of objects that match the given predicate
 */
- (HAResults *)objectsWithPredicate:(NSPredicate *)predicate;

/**
 Get a sorted `HAResults` from an existing `HAResults` sorted by a property.

 @param property    The property name to sort by.
 @param ascending   The direction to sort by.

 @return    An HAResults sorted by the specified property.
 */
- (HAResults *)sortedResultsUsingProperty:(NSString *)property ascending:(BOOL)ascending;

/**
 Get a sorted `HAResults` from an existing `HAResults` sorted by an `NSArray`` of `HASortDescriptor`s.

 @param properties  An array of `HASortDescriptor`s to sort by.

 @return    An HAResults sorted by the specified properties.
 */
- (HAResults *)sortedResultsUsingDescriptors:(NSArray *)properties;

#pragma mark -


/**---------------------------------------------------------------------------------------
 *  @name Aggregating Property Values
 *  ---------------------------------------------------------------------------------------
 */

/**
 Returns the minimum (lowest) value of the given property

 NSNumber *min = [results minOfProperty:@"age"];

 @warning You cannot use this method on HAObject, HAArray, and NSData properties.

 @param property The property to look for a minimum on. Only properties of type int, float, double and NSDate are supported.

 @return The minimum value for the property amongst objects in an HAResults.
 */
-(id)minOfProperty:(NSString *)property;

/**
 Returns the maximum (highest) value of the given property of objects in an HAResults

 NSNumber *max = [results maxOfProperty:@"age"];

 @warning You cannot use this method on HAObject, HAArray, and NSData properties.

 @param property The property to look for a maximum on. Only properties of type int, float, double and NSDate are supported.

 @return The maximum value for the property amongst objects in an HAResults
 */
-(id)maxOfProperty:(NSString *)property;

/**
 Returns the sum of the given property for objects in an HAResults.

 NSNumber *sum = [results sumOfProperty:@"age"];

 @warning You cannot use this method on HAObject, HAArray, and NSData properties.

 @param property The property to calculate sum on. Only properties of type int, float and double are supported.

 @return The sum of the given property over all objects in an HAResults.
 */
-(NSNumber *)sumOfProperty:(NSString *)property;

/**
 Returns the average of a given property for objects in an HAResults.

 NSNumber *average = [results averageOfProperty:@"age"];

 @warning You cannot use this method on HAObject, HAArray, and NSData properties.

 @param property The property to calculate average on. Only properties of type int, float and double are supported.

 @return    The average for the given property amongst objects in an HAResults. This will be of type double for both
 float and double properties.
 */
-(NSNumber *)averageOfProperty:(NSString *)property;

#pragma mark -

- (id)objectAtIndexedSubscript:(NSUInteger)index;

#pragma mark -

/**---------------------------------------------------------------------------------------
 *  @name Unavailable Methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 -[HAResults init] is not available because HAResults cannot be created directly.
 HAResults can be obtained by querying a Realm.
 */
- (instancetype)init __attribute__((unavailable("HAResults cannot be created directly")));

/**
 +[HAResults new] is not available because HAResults cannot be created directly.
 HAResults can be obtained by querying a Realm.
 */
+ (instancetype)new __attribute__((unavailable("HAResults cannot be created directly")));

@end

