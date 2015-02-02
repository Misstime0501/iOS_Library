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
#import <HARealm/HAConstants.h>

/**
 This class models properties persisted to Realm in an HAObjectSchema.
 
 When using Realm, HAProperty objects allow performing migrations and 
 introspecting the database's schema.
 
 These properties map to columns in the core database.
 */
@interface HAProperty : NSObject

/**
 Property name.
 */
@property (nonatomic, readonly) NSString *name;

/**
 Property type.
 
 @see HAPropertyType
 */
@property (nonatomic, readonly) HAPropertyType type;

/**
 Indicates if this property is indexed.
 
 @see HAObject
 */
@property (nonatomic, readonly) BOOL indexed;

/**
 Object class name - specify object types for HAObject and HAArray properties.
 */
@property (nonatomic, readonly, copy) NSString *objectClassName;

@end
