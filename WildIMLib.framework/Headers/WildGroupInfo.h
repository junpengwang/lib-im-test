//
//  WildGroup.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface WildGroupInfo : NSObject

/**
 *  群组Id
 */
@property(nonatomic,retain) NSString* group;
/**
 *  群名
 */
@property(nonatomic,retain) NSString* groupName;
/**
 *  群创建人/管理员
 */
@property(nonatomic,retain) NSString * owner;
/**
 *  群类型：Private,Public,Chatroom
 */
@property(nonatomic,retain) NSString* groupType;
/**
 *  群创建时间
 */
@property(nonatomic,assign) uint32_t createTime;
/**
 *  最近一次群资料修改时间
 */
@property(nonatomic,assign) uint32_t lastInfoTime;
/**
 *  最近一次发消息时间
 */
@property(nonatomic,assign) uint32_t lastMsgTime;
/**
 *  群成员数量
 */
@property(nonatomic,assign) uint32_t memberNum;
/**
 *  最大成员数
 */
@property(nonatomic,assign) uint32_t maxMemberNum;
/**
 *  群公告
 */
@property(nonatomic,retain) NSString* notification;
/**
 *  群简介
 */
@property(nonatomic,retain) NSString* introduction;


@end
