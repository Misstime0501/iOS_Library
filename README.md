# iOS_Library
    iOSOpenID.framework 
        是 OpenID 的 SDK 调用方法：
            import <iOSOpenID/iOSOpenID.h>
            继承 iOSOpenIDLoginViewDelegate
            
            iOSOpenIDLoginView *loginView = [[iOSOpenIDLoginView alloc] init:self];
            [loginView getOpenID];

            回调函数分别为：
            /// token 获取成功，并返回 token
            - (void)iOSOpenIDFetchTokenSucc:(NSString *)token;

            /// token 获取失败
            - (void)iOSOpenIDFetchTokenFail

            /// 获取 token 出现异常 并返回异常信息
            - (void)iOSOpenIDFetchTokenError:(NSError *)error
