//
//  WildMessage.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>

@class WildElem;
@class WildConversation;

@interface WildMessage : NSObject

/**
 *  增加Elem
 *
 *  @param elem elem结构
 *
 *  @return 0       表示成功
 *          1       禁止添加Elem（文件或语音多于两个Elem）
 *          2       未知Elem
 */
- (int)addElem:(WildElem *)elem;


/**
 *  获取对应索引的Elem
 *
 *  @param index 对应索引
 *
 *  @return 返回对应Elem
 */
- (WildElem *)getElem:(int)index;


/**
 *  删除消息：注意这里仅修改状态
 *
 *  @return TRUE 成功
 */
- (BOOL)remove;


/**
 *  获取Elem数量
 *
 *  @return elem数量
 */
- (int)elemCount;


/**
 *  获取会话
 *
 *  @return 该消息所对应会话
 */
- (WildConversation *)getConversation;


/**
 *  消息Id
 */
- (NSString *)msgId;


/**
 *  是否发送方
 *
 *  @return TRUE 表示是发送消息    FALSE 表示是接收消息
 */
- (BOOL) isSelf;

/**
 *  获取发送方
 *
 *  @return 发送方标识
 */
- (NSString *) sender;


/**
 *  消息状态
 *
 *  @return WildMessageStatus 消息状态
 */
- (WildMessageStatus)status;


/**
 *  当前消息的时间戳
 *
 *  @return 时间戳
 */
- (NSString *)timestamp;


@end
