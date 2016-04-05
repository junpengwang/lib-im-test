//
//  WildCallbackExt.h
//  WildIMLib
//
//  Created by junpengwang on 16/3/26.
//  Copyright © 2016年 www.wilddog.com. All rights reserved.
//

#ifndef WildCallbackExt_h
#define WildCallbackExt_h
#import "WildCommon.h"

/////////////////////////////////////////////////////////
///  回调协议
/////////////////////////////////////////////////////////

@class WildMessage;
@class WildGroupTipsElem;


/**
 *  消息回调
 */
@protocol WildMessageListener <NSObject>
@required
/**
 *  新消息回调通知
 *
 *  @param msgs 新消息列表，WildMessage 类型数组
 */
- (void)onNewMessage:(NSArray*) msgs;
@end



/**
 *  消息修改回调
 */
@protocol WildMessageUpdateListener <NSObject>
@optional
/**
 *  消息修改通知
 *
 *  @param msgs 修改的消息列表，WildMessage 类型数组
 */
- (void)onMessageUpdate:(NSArray*) msgs;
@end



/**
 *  图片上传进度回调
 */
@protocol WildUploadProgressListener <NSObject>
@optional
/**
 *  消息修改通知
 *
 *  @param msgs 修改的消息列表，WildMessage 类型数组
 */
- (void) onUploadProgressCallback:(WildMessage *)msg elemidx:(uint32_t)elemidx taskid:(uint32_t)taskid progress:(uint32_t)progress;
@end


/**
 *  群组成员变更通知
 */
@protocol WildGroupMemberListener <NSObject>
@optional
/**
 *  群成员数量变更通知回调
 *  @param group   群组Id
 *  @param tipType 提示类型
 *  @param members 变更的成员列表
 */
- (void)onMemberUpdate:(NSString*)group tipType:(WildGroupTipsType)tipType members:(NSArray*)members;

/**
 *  群成员资料变更通知回调
 *  @param groupId     群组Id
 *  @param memberInfos 成员资料变更列表,WildGroupTipsElemMemberInfo类型数组
 */
- (void)onMemberInfoUpdate:(NSString*)group  memberInfos:(NSArray*)memberInfos;
@end

/**
 *  群事件通知回调
 */
@protocol WildGroupEventListener <NSObject>
@optional
/**
 *  群tips回调
 *
 *  @param elem  群tips消息
 */
- (void)onGroupTipsEvent:(WildGroupTipsElem*)elem;
@end


#endif /* WildCallbackExt_h */
