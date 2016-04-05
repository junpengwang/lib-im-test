//
//  WildConversation.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WildCallbackExt.h"
#import "WildCallback.h"

@class WildMessage;

@interface WildConversation : NSObject


- (WildConversation *)init:(WildConversationType)type receiverId:(NSString *)receiverId;

/**
 *  发送消息
 *
 *  @param msg  消息体
 *  @param succ 发送成功时回调
 *  @param fail 发送失败时回调
 *
 *  @return 0 本次操作成功
 */
- (int)sendMessage: (WildMessage*)msg succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  获取会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param succ  成功时回调
 *  @param fail  失败时回调
 *
 *  @return 0 本次操作成功
 */
-(int) getMessage: (int)count last:(WildMessage*)last succ:(WildGetMsgSucc)succ fail:(WildFail)fail;

/**
 *  获取会话消息
 *
 *  @param count 获取数量
 *  @param last  上次最后一条消息
 *  @param cb    回调
 *
 *  @return 0 成功
 */
-(int) getMessage: (int)count last:(WildMessage*)last cb:(id<WildGetMessageCallback>)cb;

/**
 *  设置已读消息
 *
 *  @param readed 会话内最近一条已读的消息
 *
 *  @return 0 表示成功
 */
- (int)setReadMessage:(WildMessage *)readed;

/**
 *  设置会话中所有消息为已读状态
 *
 *  @return 0 表示成功
 */
- (int) setReadMessage;

/**
 *  获取该会话的未读计数
 *
 *  @return 返回未读计数
 */
- (int)getUnReadMessageNum;

/**
 *  获取会话人，单聊为对方账号，群聊为群组Id
 *
 *  @return 会话人
 */
- (NSString *)getReceiver;

/**
 *  获取会话类型
 *
 *  @return 会话类型
 */
- (WildConversationType)getType;

@end
