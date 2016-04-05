//
//  WildIMLib.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WildConversation.h"
#import "WildGroupManager.h"
#import "WildMessage.h"
#import "WildCommon.h"
#import "WildGroupManager.h"
#import "WildElem.h"
#import "WildGroupInfo.h"
#import "WildCallbackExt.h"
#import "WildUserInfo.h"

@protocol WildBlackListDataSource;

@interface WildIMLib : NSObject

/**
 *  当前登陆的用户uid
 */
@property (nonatomic, strong) NSString *userUid;

/**
 *  获取管理器实例
 *
 *  @return 管理器实例
 */
+ (instancetype)sharedInstance;

/**
 *  初始化SDK
 *
 * @param sdkAppId    用户标识接入SDK的应用ID
 *
 *  @return 0 成功
 */
- (int)initSDK:(NSString *)sdkAppId;


/**
 *  登陆
 *
 *  @param userId 用户Id
 *  @param token  根据用户ID 和 野狗超级密钥生成的 Token。
 *  @param name   用户昵称
 *  @param succ   成功回调
 *  @param fail   失败回调
 *  @return 0 登陆请求发送成功，等待回调
 */
- (int)login:(NSString *)userId customeToken:(NSString *)token userName:(NSString *)name succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  获取当前登陆的用户
 *
 *  @return 如果登陆返回用户的identifier，如果未登录返回nil
 */
- (NSString*) getLoginUser;

/**
 *  设置 DeviceToken
 *
 *  @param token 苹果推送服务注册成功返回的 DeviceToken，用于推送服务
 */
- (void)setDeviceToken:(NSString *)token;


/**
 *  获取会话数量
 *
 *  @return 会话数量
 */
- (int)conversationCount;

/**
 *  获取会话
 *
 *  @param type 会话类型，Wild_C2C 表示单聊 Wild_GROUP 表示群聊
 *  @param receiver C2C 为对方用户 identifier， GROUP 为群组Id
 *
 *  @return 会话对象
 */
- (WildConversation *)getConversation:(WildConversationType)type receiver:(NSString *)receiver;

/**
 *  通过索引获取会话
 *
 *  @param index 索引
 *
 *  @return 返回对应的会话
 */
- (WildConversation *)getConversationByIndex:(int)index;


/**
 *  删除会话
 *
 *  @param type 会话类型，Wild_C2C 表示单聊 TIM_GROUP 表示群聊

 *  @param receiver    用户identifier 或者 群组Id
 *
 *  @return TRUE:删除成功  FALSE:删除失败
 */
- (BOOL)deleteConversation:(WildConversationType)type receiver:(NSString *)receiver;

/**
 *  删除会话和消息
 *
 *  @param type 会话类型，TIM_C2C 表示单聊 TIM_GROUP 表示群聊
 *  @param receiver    用户identifier 或者 群组Id
 *
 *  @return TRUE:删除成功  FALSE:删除失败
 */
- (BOOL) deleteConversationAndMessages:(WildConversationType)type receiver:(NSString*)receiver;

/**
 *  设置连接通知回调
 *
 *  @param listener 回调
 *
 *  @return 0 成功
 */
- (int)setMessageListener: (id<WildMessageListener>)listener;

/**
 *  设置连接通知回调
 *
 *  @param listener 回调
 *
 *  @return 0 成功
 */
-(int) setConnListener: (id<WildConnListener>)listener;



/**
 *  加入黑名单
 *
 *  @param userId     用户id
 */
- (void)addToBlacklist:(NSString *)userId;


/**
 *  移出黑名单
 *
 *  @param userId     用户id
 */
- (void)removeFromBlacklist:(NSString *)userId;


/**
 *  用户黑名单信息提供者
 */
@property(nonatomic, weak) id <WildBlackListDataSource> blackListDataSource;


/**
 *  获取用户黑名单状态
 *
 *  @param userId     用户id
 *  @param successBlock 获取用户黑名单状态成功。bizStatus：0-在黑名单，101-不在黑名单
 *  @param errorBlock      获取用户黑名单状态失败。
 */
- (void)getBlacklistStatus:(NSString *)userId
                   success:(void (^)(int bizStatus))successBlock
                     error:(void (^)(WildError *error))errorBlock;

@end


@protocol WildBlackListDataSource <NSObject>

/**
 *  获取黑名单列表
 *
 *  @param userId     用户id
 *  @param successBlock 黑名单列表，多个id以回车分割
 *  @param errorBlock      获取用户黑名单状态失败
 */

- (void)getBlacklistWithUserId:(NSString *)userId
                       success:(void (^)(NSArray *blockUserIds))successBlock
                         error:(void (^)(WildError *error))errorBlock;


/**
 *  创建系统角色 小秘书、小助手等。
 *
 *  @param name 系统角色名称
 *  @param url  头像
 *  @param suss 成功
 *  @param fail 失败
 */
- (void)createSystemUser:(NSString *)name avatar:(NSString *)url sussucc:(void(^)(NSString *roomId))suss fail:(void(^)(NSError *error))fail;
@end






