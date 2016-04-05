//
//  WildCallback.h
//  WildIMLib
//
//  Created by junpengwang on 16/3/26.
//  Copyright © 2016年 www.wilddog.com. All rights reserved.
//

#ifndef WildCallback_h
#define WildCallback_h

#import "WildCommon.h"

/**
 *  回调
 */
@protocol WildCallback <NSObject>

/**
 *  成功
 */
- (void) onSucc;

/**
 *  消息发送失败
 *
 *  @param errCode 失败错误码
 *  @param errMsg  失败错误描述
 */
- (void)onErr:(int)errCode errMsg:(NSString*)errMsg;
@end

/**
 *  消息读取回调
 */
@protocol WildGetMessageCallback <NSObject>

/**
 *  消息读取成功
 *
 *  @param msgs 消息列表，WildMessage 数组
 */
- (void) onSucc:(NSArray *) msgs;

/**
 *  消息发送失败
 *
 *  @param errCode 失败错误码
 *  @param errMsg  失败错误描述
 */
- (void)onErr:(int)errCode errMsg:(NSString*)errMsg;

@end


/**
 *  资源(图片/声音等)回调
 */
@protocol WildResourceCallback <NSObject>

/**
 *  资源二进制信息
 *
 *  @param data 二进制
 */
- (void) onSucc:(NSData *) data;

/**
 *  消息发送失败
 *
 *  @param errCode 失败错误码
 *  @param errMsg  失败错误描述
 */
- (void)onErr:(int)errCode errMsg:(NSString*)errMsg;

@end


/**
 *  日志监听回调
 */
@protocol WildLogListener <NSObject>

/**
 *  回调日志接口
 *
 *  @param lvl 日志级别
 *  @param content 日志内容
 */
- (void) log:(WildLogLevel)lvl content:(NSString*)content;

@end



/**
 *  连接通知回调
 */
@protocol WildConnListener <NSObject>
@optional

/**
 *  网络连接成功
 */
- (void)onConnSucc;

/**
 *  网络连接断开（断线只是通知用户，不需要重新登陆，重连以后会自动上线）
 *
 *  @param code 错误码
 *  @param err  错误描述
 */
- (void)onDisconnect:(int)code err:(NSString*)err;


@end


/**
 *  用户在线状态通知（用户需要重新登陆）
 */
@protocol WildUserStatusListener <NSObject>
@optional
/**
 *  踢下线通知
 */
- (void)onForceOffline;

/**
 *  断线重连失败
 */
- (void)onReConnFailed:(int)code err:(NSString*)err;
@end

/**
 *  页面刷新接口（如有需要未读计数刷新，会话列表刷新等）
 */
@protocol WildRefreshListener <NSObject>
@optional
/**
 *  刷新会话
 */
- (void) onRefresh;
@end


/**
 *  APNs 配置
 */
@interface WildAPNSConfig : NSObject
/**
 *  是否开启推送：0-不进行设置 1-开启推送 2-关闭推送
 */
@property(nonatomic,assign) uint32_t openPush;
/**
 *  C2C消息声音,不设置传入nil
 */
@property(nonatomic,retain) NSString * c2cSound;

/**
 *  Group消息声音,不设置传入nil
 */
@property(nonatomic,retain) NSString * groupSound;

/**
 *  Video声音,不设置传入nil
 */
@property(nonatomic,retain) NSString * videoSound;

@end

/**
 *  APNs推送配置更新成功回调
 *
 *  @param config 配置
 */
typedef void (^WildAPNSConfigSucc)(WildAPNSConfig* config);

#endif /* WildCallback_h */
