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

#ifdef __cplusplus
extern "C" {
#endif

@class HARealm, HASchema, HAObjectSchema, HAObjectBase, HAResults;

//
// Table modifications
//

// updates a Realm to a given target schema/version
// creates tables as necessary
// optionally runs migration block if schema is out of date
//
// NOTE: the schema passed in will be set on the Realm and may later be mutated. sharing a targetSchema accross
// even the same Realm with different column orderings will cause issues
NSError *HAUpdateRealmToSchemaVersion(HARealm *realm, NSUInteger version, HASchema *targetSchema, NSError *(^migrationBlock)());

// sets a realm's schema to a copy of targetSchema
// caches table accessors on each objectSchema
//
// NOTE: the schema passed in will be set on the Realm and may later be mutated. sharing a targetSchema accross
// even the same Realm with different column orderings will cause issues
void HARealmSetSchema(HARealm *realm, HASchema *targetSchema, bool verifyAndAlignColumns);

// create or get cached accessors for the given schema
void HARealmCreateAccessors(HASchema *schema);

// Clear the cache of created accessor classes
void HAClearAccessorCache();

//
// Options for object creation
//
typedef NS_OPTIONS(NSUInteger, HACreationOptions) {
    // Normal object creation
    HACreationOptionsNone = 0,
    // Verify that no existing row has the same value for this property
    HACreationOptionsEnforceUnique = 1 << 0,
    // If the property is a link or array property, upsert the linked objects
    // if they have a primary key, and insert them otherwise.
    HACreationOptionsUpdateOrCreate = 1 << 1,
    // If a link or array property links to an object persisted in a different
    // realm from the object, copy it into the object's realm rather than throwing
    // an error
    HACreationOptionsAllowCopy = 1 << 2,
};


//
// Adding, Removing, Getting Objects
//

// add an object to the given realm
void HAAddObjectToRealm(HAObjectBase *object, HARealm *realm, HACreationOptions options);

// delete an object from its realm
void HADeleteObjectFromRealm(HAObjectBase *object);

// deletes all objects from a realm
void HADeleteAllObjectsFromRealm(HARealm *realm);

// get objects of a given class
HAResults *HAGetObjects(HARealm *realm, NSString *objectClassName, NSPredicate *predicate);

// get an object with the given primary key
id HAGetObject(HARealm *realm, NSString *objectClassName, id key);

// create object from array or dictionary
HAObjectBase *HACreateObjectInRealmWithValue(HARealm *realm, NSString *className, id value, HACreationOptions options);


//
// Accessor Creation
//

// Create accessors
HAObjectBase *HACreateObjectAccessor(__unsafe_unretained HARealm *realm,
                                       __unsafe_unretained HAObjectSchema *objectSchema,
                                       NSUInteger index);


#ifdef __cplusplus
}
#endif
