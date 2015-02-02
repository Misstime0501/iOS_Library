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

/**
 Property types supported in Realm models.

 See [Realm Models](http://realm.io/docs/cocoa/latest/#models)
 */
// Make sure numbers match those in <tightdb/data_type.hpp>
typedef NS_ENUM(int32_t, HAPropertyType) {
    ////////////////////////////////
    // Primitive types
    ////////////////////////////////

    /** Integer type: NSInteger, int, long, Int (Swift) */
    HAPropertyTypeInt    = 0,
    /** Boolean type: BOOL, bool, Bool (Swift) */
    HAPropertyTypeBool   = 1,
    /** Float type: CGFloat (32bit), float, Float (Swift) */
    HAPropertyTypeFloat  = 9,
    /** Double type: CGFloat (64bit), double, Double (Swift) */
    HAPropertyTypeDouble = 10,

    ////////////////////////////////
    // Object types
    ////////////////////////////////

    /** String type: NSString, String (Swift) */
    HAPropertyTypeString = 2,
    /** Data type: NSData */
    HAPropertyTypeData   = 4,
    /** Any type: id, **not supported in Swift** */
    HAPropertyTypeAny    = 6,
    /** Date type: NSDate */
    HAPropertyTypeDate   = 7,

    ////////////////////////////////
    // Array/Linked object types
    ////////////////////////////////

    /** Object type. See [Realm Models](http://realm.io/docs/cocoa/latest/#models) */
    HAPropertyTypeObject = 12,
    /** Array type. See [Realm Models](http://realm.io/docs/cocoa/latest/#models) */
    HAPropertyTypeArray  = 13,
};

// Appledoc doesn't support documenting externed globals, so document them as an
// enum instead
#ifdef APPLEDOC
typedef NS_ENUM(NSString, HARealmNotification) {
/**
 Posted by HARealm when the data in the realm has changed.

 DidChange are posted after a realm has been refreshed to reflect a write
 transaction, i.e. when an autorefresh occurs, [refresh]([HARealm refresh]) is
 called, after an implicit refresh from [beginWriteTransaction]([HARealm beginWriteTransaction]),
 and after a local write transaction is committed.
 */
    HARealmDidChangeNotification,
/**
 Posted by HARealm when a write transaction has been committed to an HARealm on
 a different thread for the same file. This is not posted if
 [autorefresh]([HARealm autorefresh]) is enabled or if the HARealm is
 refreshed before the notifcation has a chance to run.

 Realms with autorefresh disabled should normally have a handler for this
 notification which calls [refresh]([HARealm refresh]) after doing some work.
 While not refreshing is allowed, it may lead to large Realm files as Realm has
 to keep an extra copy of the data for the un-refreshed HARealm.
 */
    HARealmRefreshRequiredNotification,
};
#else
// See comments above
extern NSString * const HARealmRefreshRequiredNotification;
extern NSString * const HARealmDidChangeNotification;
#endif

typedef NS_ENUM(NSInteger, HAError) {
    /** Retuned by HARealm if no other specific error is returned when a realm is opened. */
    HAErrorFail                  = 1,
    /** Returned by HARealm for any I/O related exception scenarios when a realm is opened. */
    HAErrorFileAccessError       = 2,
    /** Returned by HARealm if the user does not have permission to open or create
        the specified file in the specified access mode when the realm is opened. */
    HAErrorFilePermissionDenied  = 3,
    /** Returned by HARealm if no_create was specified and the file did already exist when the realm is opened. */
    HAErrorFileExists            = 4,
    /** Returned by HARealm if no_create was specified and the file was not found when the realm is opened. */
    HAErrorFileNotFound          = 5,
    /** Returned by HARealm if the database file is currently open in another
        process which cannot share with the current process due to an
        architecture mismatch. */
    HAErrorIncompatibleLockFile  = 8,
};

// Schema version used for unitialized Realms
extern const NSUInteger HANotVersioned;

extern NSString * const HAErrorDomain;

extern NSString * const HAExceptionName;

extern NSString * const HARealmVersionKey;

extern NSString * const HARealmCoreVersionKey;
