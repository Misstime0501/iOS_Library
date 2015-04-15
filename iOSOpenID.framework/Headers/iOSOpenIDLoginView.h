//
//  iOSOpenIDLoginView.h
//  iOSOpenID
//
//  Created by HRWY on 15/4/14.
//  Copyright (c) 2015年 HRWY. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol iOSOpenIDLoginViewDelegate <NSObject>

/// 获取Token成功的响应事件
- (void)iOSOpenIDFetchTokenSucc:(NSString *)token;
/// 获取Token失败的响应事件
- (void)iOSOpenIDFetchTokenFail;
/// 获取Token出现异常的响应事件
- (void)iOSOpenIDFetchTokenError:(NSError *)error;

@end

@interface iOSOpenIDLoginView : UIView
{
    __unsafe_unretained id<iOSOpenIDLoginViewDelegate> _delegate;
}

@property (nonatomic, assign) id<iOSOpenIDLoginViewDelegate> delegate;
@property (nonatomic, retain) NSString *iOSOpenIDToken;


- (id)init:(id<iOSOpenIDLoginViewDelegate>)delegate;

- (id)initWithURL:(NSString *)serverURL
         delegate:(id<iOSOpenIDLoginViewDelegate>)delegate;

- (void)getOpenID;

@end
