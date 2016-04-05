//
//  WildUserInfo.h
//  WildIMLib
//
//  Created by Garin on 16/3/17.
//  Copyright © 2016年 www.wilddog.com. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  用户信息类
 */
@interface WildUserInfo : NSObject

/** 用户ID */
@property(nonatomic, strong) NSString *userId;
/** 用户名*/
@property(nonatomic, strong) NSString *name;
/** 头像URL*/
@property(nonatomic, strong) NSString *portraitUri;

+ (void)saveUserInfo:(WildUserInfo *)userInfo;

+ (BOOL)hasUserInfo:(NSString *)userId;

+ (WildUserInfo *)getUserInfo:(NSString *)userId;

@end
