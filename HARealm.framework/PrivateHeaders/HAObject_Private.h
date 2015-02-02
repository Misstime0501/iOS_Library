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

#import <HARealm/HAObject.h>

// HAObject accessor and read/write realm
@interface HAObjectBase () {
  @public
    HARealm *_realm;
    // objectSchema is a cached pointer to an object stored in the HASchema
    // owned by _realm, so it's guaranteed to stay alive as long as this object
    // without retaining it (and retaining it makes iteration slower)
    __unsafe_unretained HAObjectSchema *_objectSchema;
}

- (instancetype)initWithRealm:(__unsafe_unretained HARealm *)realm
                       schema:(__unsafe_unretained HAObjectSchema *)schema
                defaultValues:(BOOL)useDefaults;
- (instancetype)initWithObject:(id)object schema:(HASchema *)schema;

// namespace properties to prevent collision with user properties
@property (nonatomic, readwrite) HARealm *realm;
@property (nonatomic, readwrite) HAObjectSchema *objectSchema;

// shared schema for this class
+ (HAObjectSchema *)sharedSchema;

@end

