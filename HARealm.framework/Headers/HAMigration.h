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

@class HASchema;
@class HAArray;
@class HAObject;

typedef void (^HAObjectMigrationBlock)(HAObject *oldObject, HAObject *newObject);

/**---------------------------------------------------------------------------------------
 *  @name Realm Migrations
 *  ---------------------------------------------------------------------------------------
 */
/**
 HAMigration is the object passed into a user defined HAMigrationBlock when updating the version
 of an HARealm instance.
 
 This object provides access to the HASchema current to this migration.
 */
@interface HAMigration : NSObject

/**
 Get the new HASchema for the migration. This is the schema which describes the HARealm before the
 migration is applied.
 */
@property (nonatomic, readonly) HASchema *oldSchema;

/**
 Get the new HASchema for the migration. This is the schema which describes the HARealm after applying
 a migration.
 */
@property (nonatomic, readonly) HASchema *newSchema;


/**---------------------------------------------------------------------------------------
 *  @name Altering Objects during a Migration
 *  ---------------------------------------------------------------------------------------
 */
/**
 Enumerates objects of a given type in this Realm, providing both the old and new versions of each object.
 Objects properties can be accessed using keyed subscripting.
 
 @param className   The name of the HAObject class to enumerate.
 
 @warning   All objects returned are of a type specific to the current migration and should not be casted
            to className. Instead you should access them as HAObjects and use keyed subscripting to access
            properties.
 */
- (void)enumerateObjects:(NSString *)className block:(HAObjectMigrationBlock)block;

/**
 Create an HAObject of type `className` in the Realm being migrated.

 @param className   The name of the HAObject class to create.
 @param object      The value used to populate the created object. This can be any key/value coding compliant
                    object, or a JSON object such as those returned from the methods in NSJSONSerialization, or
                    an NSArray with one object for each persisted property. An exception will be
                    thrown if any required properties are not present and no default is set.

                    When passing in an NSArray, all properties must be present, valid and in the same order as the properties defined in the model.
 */
-(HAObject *)createObject:(NSString *)className withObject:(id)object;

/**
 Delete an object from a Realm during a migration. This can be called within `enumerateObjects:block:`.

 @param object  Object to be deleted from the Realm being migrated.
 */
- (void)deleteObject:(HAObject *)object;

@end


