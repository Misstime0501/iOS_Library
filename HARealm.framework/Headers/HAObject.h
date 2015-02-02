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

#import <HARealm/HAObjectBase.h>

@class HARealm;
@class HAResults;
@class HAObjectSchema;

/**
 
 In Realm you define your model classes by subclassing HAObject and adding properties to be persisted.
 You then instantiate and use your custom subclasses instead of using the HAObject class directly.
 
     // Dog.h
     @interface Dog : HAObject
     @property NSString *name;
     @property BOOL      adopted;
     @end
 
     // Dog.m
     @implementation Dog
     @end //none needed
 
 ### Supported property types
 
 - `NSString`
 - `NSInteger`, `CGFloat`, `int`, `long`, `float`, and `double`
 - `BOOL` or `bool`
 - `NSDate`
 - `NSData`
 - HAObject subclasses, so you can have many-to-one relationships.
 - `HAArray<X>`, where X is an HAObject subclass, so you can have many-to-many relationships.

 ### Querying
 
 You can query an object directly via the class methods: allObjects, objectsWhere:, objectsOrderedBy:where: and objectForKeyedSubscript:
 These methods allow you to easily query a custom subclass for instances of this class in the
 default Realm. To search in a Realm other than the default Realm use the interface on an HARealm instance.
 
 ### Relationships
 
 See our [Cocoa guide](http://realm.io/docs/cocoa/latest) for more details.
 */


@interface HAObject : HAObjectBase

/**---------------------------------------------------------------------------------------
 *  @name Creating & Initializing Objects
 * ---------------------------------------------------------------------------------------
 */

/**
 Initialize a standalone HAObject
 
 Initialize an unpersisted instance of this object.
 Call addObject: on an HARealm to add standalone object to a realm.
 
 @see [HARealm addObject:]:
 */
- (instancetype)init;


/**
 Initialize a standalone HAObject with values from an NSArray or NSDictionary
 
 Initialize an unpersisted instance of this object.
 Call addObject: on an HARealm to add standalone object to a realm.
 
 @see [HARealm addObject:]:
 */
- (instancetype)initWithObject:(id)object;


/**
 Helper to return the class name for an HAObject subclass.
 
 @return    The class name for the model class.
 */
+ (NSString *)className;

/**
 Create an HAObject in the default Realm with a given object.

 Creates an instance of this object and adds it to the default Realm populating
 the object with the given object.
 
 If nested objects are included in the argument, `createInDefaultRealmWithObject:` will be called
 on them.

 @param object  The object used to populate the object. This can be any key/value coding compliant
                object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                an NSArray with one object for each persisted property. An exception will be
                thrown if any required properties are not present and no default is set.

 When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.

 @see   defaultPropertyValues
 */
+ (instancetype)createInDefaultRealmWithObject:(id)object;

/**
 Create an HAObject in a Realm with a given object.
 
 Creates an instance of this object and adds it to the given Realm populating
 the object with the given object.
 
 If nested objects are included in the argument, `createInRealm:withObject:` will be called
 on them.
 
 @param realm   The Realm in which this object is persisted.
 @param object  The object used to populate the object. This can be any key/value coding compliant
                object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                an NSArray with one object for each persisted property. An exception will be
                thrown if any required properties are not present and no default is set.
                
                When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.
 
 @see   defaultPropertyValues
 */
+ (instancetype)createInRealm:(HARealm *)realm withObject:(id)object;

/**
 Create or update an HAObject in the default Realm with a given object.

 This method can only be called on object types with a primary key defined. If there is already
 an object with the same primary key value in the default HARealm its values are updated and the object
 is returned. Otherwise this creates and populates a new instance of this object in the default Realm.
 
 If nested objects are included in the argument, `createOrUpdateInDefaultRealmWithObject:` will be
 called on them if have a primary key (`createInDefaultRealmWithObject:` otherwise).
 
 This is a no-op if the argument is an HAObject of the same type already backed by the target realm.

 @param object  The object used to populate the object. This can be any key/value coding compliant
                object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                an NSArray with one object for each persisted property. An exception will be
                thrown if any required properties are not present and no default is set.

 When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.

 @see   defaultPropertyValues, primaryKey
 */
+ (instancetype)createOrUpdateInDefaultRealmWithObject:(id)object;

/**
 Create or update an HAObject with a given object.

 This method can only be called on object types with a primary key defined. If there is already
 an object with the same primary key value in the provided HARealm its values are updated and the object
 is returned. Otherwise this creates and populates a new instance of this object in the provided Realm.
 
 If nested objects are included in the argument, `createOrUpdateInRealm:withObject:` will be
 called on them if have a primary key (`createInRealm:withObject:` otherwise).

 This is a no-op if the argument is an HAObject of the same type already backed by the target realm.

 @param realm   The Realm in which this object is persisted.
 @param object  The object used to populate the object. This can be any key/value coding compliant
                object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                an NSArray with one object for each persisted property. An exception will be
                thrown if any required properties are not present and no default is set.

 When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.

 @see   defaultPropertyValues, primaryKey
 */
+ (instancetype)createOrUpdateInRealm:(HARealm *)realm withObject:(id)object;

/**
 The Realm in which this object is persisted. Returns nil for standalone objects.
 */
@property (nonatomic, readonly) HARealm *realm;

/**
 The ObjectSchema which lists the persisted properties for this object.
 */
@property (nonatomic, readonly) HAObjectSchema *objectSchema;

/**
 Indicates if an object can no longer be accessed.
 */
@property (nonatomic, readonly, getter = isInvalidated) BOOL invalidated;

@property (nonatomic, readonly, getter = isDeletedFromRealm) BOOL deletedFromRealm __attribute__((deprecated("Use `invalidated` instead.")));


/**---------------------------------------------------------------------------------------
 *  @name Customizing your Objects
 * ---------------------------------------------------------------------------------------
 */

/**
 Return an array of property names for properties which should be indexed. Only supported
 for string properties.
 @return    NSArray of property names.
 */
+ (NSArray *)indexedProperties;

/**
 Implement to indicate the default values to be used for each property.
 
 @return    NSDictionary mapping property names to their default values.
 */
+ (NSDictionary *)defaultPropertyValues;

/**
 Implement to designate a property as the primary key for an HAObject subclass. Only properties of
 type HAPropertyTypeString and HAPropertyTypeInt can be designated as the primary key. Primary key 
 properties enforce uniqueness for each value whenever the property is set which incurs some overhead.
 Indexes are created automatically for string primary key properties.

 @return    Name of the property designated as the primary key.
 */
+ (NSString *)primaryKey;

/**
 Implement to return an array of property names to ignore. These properties will not be persisted
 and are treated as transient.
 
 @return    NSArray of property names to ignore.
 */
+ (NSArray *)ignoredProperties;


/**---------------------------------------------------------------------------------------
 *  @name Getting & Querying Objects from the Default Realm
 *  ---------------------------------------------------------------------------------------
 */

/**
 Get all objects of this type from the default Realm.
 
 @return    An HAResults of all objects of this type in the default Realm.
 */
+ (HAResults *)allObjects;

/**
 Get objects matching the given predicate for this type from the default Realm.
 
 @param predicateFormat The predicate format string which can accept variable arguments.
 
 @return    An HAResults of objects of the subclass type in the default Realm that match the given predicate
 */
+ (HAResults *)objectsWhere:(NSString *)predicateFormat, ...;


/**
 Get objects matching the given predicate for this type from the default Realm.

 @param predicate   The predicate to filter the objects.

 @return    An HAResults of objects of the subclass type in the default Realm that match the given predicate
 */
+ (HAResults *)objectsWithPredicate:(NSPredicate *)predicate;

/**
 Get the single object with the given primary key from the default Realm.

 Returns the object from the default Realm which has the given primary key, or
 `nil` if the object does not exist. This is slightly faster than the otherwise
 equivalent `[[SubclassName objectsWhere:@"primaryKeyPropertyName = %@", key] firstObject]`.

 This method requires that `primaryKey` be overridden on the receiving subclass.

 @return    An object of the subclass type or nil if an object with the given primary key does not exist.
 @see       -primaryKey
 */
+ (instancetype)objectForPrimaryKey:(id)primaryKey;


/**---------------------------------------------------------------------------------------
 *  @name Querying Specific Realms
 *  ---------------------------------------------------------------------------------------
 */

/**
 Get all objects of this type from the specified Realm.

 @param realm   The Realm instance to query.

 @return        An HAResults of all objects of this type in the specified Realm.
 */
+ (HAResults *)allObjectsInRealm:(HARealm *)realm;

/**
 Get objects matching the given predicate for this type from the specified Realm.

 @param predicateFormat The predicate format string which can accept variable arguments.
 @param realm           The Realm instance to query.

 @return    An HAResults of objects of the subclass type in the specified Realm that match the given predicate
 */
+ (HAResults *)objectsInRealm:(HARealm *)realm where:(NSString *)predicateFormat, ...;

/**
 Get objects matching the given predicate for this type from the specified Realm.

 @param predicate   The predicate to filter the objects.
 @param realm       The Realm instance to query.

 @return    An HAResults of objects of the subclass type in the specified Realm that match the given predicate
 */
+ (HAResults *)objectsInRealm:(HARealm *)realm withPredicate:(NSPredicate *)predicate;

/**
 Get the single object with the given primary key from the specified Realm.

 Returns the object from the specified Realm which has the given primary key, or
 `nil` if the object does not exist. This is slightly faster than the otherwise
 equivalent `[[SubclassName objectsInRealm:realm where:@"primaryKeyPropertyName = %@", key] firstObject]`.

 This method requires that `primaryKey` be overridden on the receiving subclass.

 @return    An object of the subclass type or nil if an object with the given primary key does not exist.
 @see       -primaryKey
 */
+ (instancetype)objectInRealm:(HARealm *)realm forPrimaryKey:(id)primaryKey;

/**
 Get an `NSArray` of objects of type `className` which have this object as the given property value. This can
 be used to get the inverse relatshionship value for `HAObject` and `HAArray` properties.

 @param className   The type of object on which the relationship to query is defined.
 @param property    The name of the property which defines the relationship.

 @return    An NSArray of objects of type `className` which have this object as thier value for the `property` property.
 */
- (NSArray *)linkingObjectsOfClass:(NSString *)className forProperty:(NSString *)property;

/**
 Returns YES if another HAObject points to the same object in an HARealm. For HAObject types
 with a primary, key, `isEqual:` is overridden to use this method (along with a corresponding
 implementation for `hash`.

 @param object  The object to compare to.

 @return    YES if the object represents the same object in the same HARealm.
 */
- (BOOL)isEqualToObject:(HAObject *)object;

#pragma mark -

//---------------------------------------------------------------------------------------
// @name Dynamic Accessors
//---------------------------------------------------------------------------------------
//
// Properties on HAObjects can be accessed and set using keyed subscripting.
// ie. HAObject[@"propertyName"] = object;
//     id object = HAObject[@"propertyName"];
//

- (id)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;

#pragma mark -

@end

/**---------------------------------------------------------------------------------------
 *  @name HAArray Property Declaration
 *  ---------------------------------------------------------------------------------------
 */
/**
 Properties on HAObjects of type HAArray must have an associated type. A type is associated
 with an HAArray property by defining a protocol for the object type which the HAArray will
 hold. To define an protocol for an object you can use the macro HA_ARRAY_TYPE:
 
     HA_ARRAY_TYPE(ObjectType)
     ...
     @property HAArray<ObjectType> *arrayOfObjectTypes;
  */
#define HA_ARRAY_TYPE(HA_OBJECT_SUBCLASS)\
@protocol HA_OBJECT_SUBCLASS <NSObject>   \
@end
