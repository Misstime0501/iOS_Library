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

#import <HARealm/HARealm.h>
#import <HARealm/HAObjectSchema.h>
#import <HARealm/HAProperty.h>

@class HAResults;

@interface HARealm (Dynamic)

// full constructor
+ (instancetype)realmWithPath:(NSString *)path
                          key:(NSData *)key
                     readOnly:(BOOL)readonly
                     inMemory:(BOOL)inMemory
                      dynamic:(BOOL)dynamic
                       schema:(HASchema *)customSchema
                        error:(NSError **)outError;

/**---------------------------------------------------------------------------------------
 *  @name Getting Objects from a Realm
 * ---------------------------------------------------------------------------------------
 */
/**
 Get all objects of a given type in this Realm.

 @param className   The name of the HAObject subclass to retrieve on e.g. `MyClass.className`.

 @return    An HAResults of all objects in this realm of the given type.

 @see       HAObject allObjects
 */
- (HAResults *)allObjects:(NSString *)className;

/**
 Get objects matching the given predicate from the this Realm.

 The preferred way to get objects of a single class is to use the class methods on HAObject.

 @param className       The type of objects you are looking for (name of the class).
 @param predicateFormat The predicate format string which can accept variable arguments.

 @return    An HAResults of results matching the given predicate.

 @see       HAObject objectsWhere:
 */
- (HAResults *)objects:(NSString *)className where:(NSString *)predicateFormat, ...;

/**
 Get objects matching the given predicate from the this Realm.

 The preferred way to get objects of a single class is to use the class methods on HAObject.

 @param className   The type of objects you are looking for (name of the class).
 @param predicate   The predicate to filter the objects.

 @return    An HAResults of results matching the given predicate.

 @see       HAObject objectsWhere:
 */
- (HAResults *)objects:(NSString *)className withPredicate:(NSPredicate *)predicate;

/**
 Create an HAObject of type `className` in the Realm with a given object.

 @param object  The object used to populate the object. This can be any key/value coding compliant
                object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                an NSArray with one object for each persisted property. An exception will be
                thrown if any required properties are not present and no default is set.

 When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.
 */
-(HAObject *)createObject:(NSString *)className withObject:(id)object;

@end

@interface HAObjectSchema (Dynamic)
/**
 Initialize an HAObjectSchema with classname, objectClass, and an array of properties

 @param objectClassName     The name of the class used to refer to objects of this type.
 @param objectClass         The objective-c class used when creating instances of this type.
 @param properties          An array HAProperty describing the persisted properties for this type.

 @return    An initialized instance of HAObjectSchema.
 */
- (instancetype)initWithClassName:(NSString *)objectClassName objectClass:(Class)objectClass properties:(NSArray *)properties;
@end

@interface HAProperty (Dynamic)
/**
 Initialize an HAProperty

 @param name            The property name.
 @param type            The property type.
 @param objectClassName The object type used for Object and Array types.
 @param attributes      A bitmask of attributes for this property.

 @return    An initialized instance of HAProperty.
 */
- (instancetype)initWithName:(NSString *)name
                        type:(HAPropertyType)type
             objectClassName:(NSString *)objectClassName
                     indexed:(BOOL)indexed;
@end
