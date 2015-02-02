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

@class HAProperty;

#import <Foundation/Foundation.h>

/**
 This class represents Realm model object schemas persisted to Realm in an HASchema.

 When using Realm, HAObjectSchema objects allow performing migrations and
 introspecting the database's schema.

 Object schemas map to tables in the core database.
 */
@interface HAObjectSchema : NSObject<NSCopying>

/**
 Array of persisted HAProperty objects for an object.
 
 @see HAProperty
 */
@property (nonatomic, readonly, copy) NSArray *properties;

/**
 The name of the class this schema describes.
 */
@property (nonatomic, readonly) NSString *className;

/**
 The property which is the primary key for this object (if any).
 */
@property (nonatomic, readonly) HAProperty *primaryKeyProperty;

/**
 Retrieve an HAProperty object by name.
 
 @param propertyName The property's name.
 
 @return HAProperty object or nil if there is no property with the given name.
 */
- (HAProperty *)objectForKeyedSubscript:(id <NSCopying>)propertyName;

/**
 Returns YES if equal to objectSchema
*/
- (BOOL)isEqualToObjectSchema:(HAObjectSchema *)objectSchema;

@end
