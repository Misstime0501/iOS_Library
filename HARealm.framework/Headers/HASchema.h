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

@class HAObjectSchema;

/**
 This class represents the collection of model object schemas persisted to Realm.

 When using Realm, HASchema objects allow performing migrations and
 introspecting the database's schema.

 Schemas map to collections of tables in the core database.
 */
@interface HASchema : NSObject<NSCopying>

/**
 An NSArray containing HAObjectSchema's for all object types in this Realm. Meant
 to be used during migrations for dynamic introspection.
 
 @see HAObjectSchema
 */
@property (nonatomic, readonly, copy) NSArray *objectSchema;

/**
 Returns an HAObjectSchema for the given class name in this HASchema.
 
 @param className   The object class name.
 @return            HAObjectSchema for the given class in this HASchema.
 
 @see               HAObjectSchema
 */
- (HAObjectSchema *)schemaForClassName:(NSString *)className;

/**
 Look up an HAObjectSchema for the given class name in this Realm. Throws if there
 is no object of type className in this HASchema instance.
 
 @param className   The object class name.
 @return            HAObjectSchema for the given class in this Realm.
 
 @see               HAObjectSchema
 */
- (HAObjectSchema *)objectForKeyedSubscript:(id <NSCopying>)className;

/**
 Returns YES if schema are equal
 */
- (BOOL)isEqualToSchema:(HASchema *)schema;

@end
