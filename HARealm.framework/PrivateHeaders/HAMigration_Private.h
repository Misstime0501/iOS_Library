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

#import <HARealm/HAMigration.h>
#import <HARealm/HARealm.h>
#import <HARealm/HAObjectBase.h>

typedef void (^HAObjectBaseMigrationBlock)(HAObjectBase *oldObject, HAObjectBase *newObject);

@interface HAMigration ()

@property (nonatomic, strong) HARealm *oldRealm;
@property (nonatomic, strong) HARealm *realm;

- (instancetype)initWithRealm:(HARealm *)realm key:(NSData *)key error:(NSError **)error;

- (void)execute:(HAMigrationBlock)block;

@end
