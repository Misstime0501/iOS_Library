//
//  funcMacroDefine.h
//  iOSOpenID
//
//  Created by HRWY on 15/4/14.
//  Copyright (c) 2015年 HRWY. All rights reserved.
//

#ifndef iOSOpenID_funcMacroDefine_h
#define iOSOpenID_funcMacroDefine_h

#define OIDLog(fmt, ...) NSLog((@"%s [%d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#define Zero                0
#define ScreenWidth         [[UIScreen mainScreen] bounds].size.width
#define ScreenHeight        [[UIScreen mainScreen] bounds].size.height

#endif
