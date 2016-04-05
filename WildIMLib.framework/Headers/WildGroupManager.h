//
//  WildGroupManager.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WildCommon.h"

/**
 * 群成员角色
 */
typedef NS_ENUM(NSInteger, WildGroupMemberRole) {
    /**
     *  群成员
     */
    Wild_GROUP_MEMBER_ROLE_MEMBER              = 0,
    
    /**
     *  群管理员
     */
    Wild_GROUP_MEMBER_ROLE_ADMIN               = 1,
    
    /**
     *  群主
     */
    Wild_GROUP_MEMBER_ROLE_SUPER               = 2,
};

/**
 * 加群选项
 */
typedef NS_ENUM(NSInteger, WildGroupAddOpt) {
    /**
     *  禁止加群
     */
    Wild_GROUP_ADD_FORBID                    = 0,
    
    /**
     *  需要管理员审批
     */
    Wild_GROUP_ADD_AUTH                      = 1,
    
    /**
     *  任何人可以加入
     */
    Wild_GROUP_ADD_ANY                       = 2,
};

/**
 * 群消息接受选项
 */
typedef NS_ENUM(NSInteger, WildGroupReceiveMessageOpt) {
    /**
     *  接收消息
     */
    Wild_GROUP_RECEIVE_MESSAGE                       = 0,
    /**
     *  不接收消息，服务器不进行转发
     */
    Wild_GROUP_NOT_RECEIVE_MESSAGE                   = 1,
    /**
     *  接受消息，不进行iOS APNs 推送
     */
    Wild_GROUP_RECEIVE_NOT_NOTIFY_MESSAGE            = 2,
};


@interface WildGroupManager : NSObject

/**
 *  获取群管理器实例
 *
 *  @return 管理器实例
 */
+ (WildGroupManager *)sharedInstance;

/**
 *  创建私有群
 *
 *  @param members   群成员，NSString* 数组
 *  @param groupName 群名
 *  @param callback  回调
 *
 *  @return 0 成功
 */
-(int)createPrivateGroup:(NSArray*)members groupName:(NSString*)groupName succ:(WildCreateGroupSucc)succ fail:(WildFail)fail;

/**
 *  创建公有群
 *
 *  @param members   群成员，NSString* 数组
 *  @param groupName 群名
 *  @param succ      成功回调
 *  @param fail      失败回调
 *
 *  @return 0 成功
 */
-(int)createPublicGroup:(NSArray*)members groupName:(NSString*)groupName succ:(WildCreateGroupSucc)succ fail:(WildFail)fail;


/**
 *  解散群组
 *
 *  @param groupId 群组Id
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)deleteGroup:(NSString *)groupId succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  邀请好友入群
 *
 *  @param groupId   群组Id
 *  @param members 要加入的成员列表（NSString* 类型数组）
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)inviteGroupMember:(NSString *)groupId members:(NSArray *)members succ:(WildGroupMemberSucc)succ fail:(WildFail)fail;


/**
 *  删除群成员
 *
 *  @param groupId   群组Id
 *  @param members 要删除的成员列表
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)deleteGroupMember:(NSString *)groupId members:(NSArray *)members succ:(WildGroupMemberSucc)succ fail:(WildFail)fail;


/**
 *  删除群成员
 *
 *  @param groupId   群组Id
 *  @param reason  删除原因
 *  @param members 要删除的成员列表
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)deleteGroupMemberWithReason:(NSString *)groupId reason:(NSString *)reason members:(NSArray *)members succ:(WildGroupMemberSucc)succ fail:(WildFail)fail;


/**
 *  申请加群
 *
 *  @param groupId 申请加入的群组Id
 *  @param msg   申请消息
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)joinGroup:(NSString *)groupId msg:(NSString *)msg succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  主动退出群组
 *
 *  @param groupId 群组Id
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)quitGroup:(NSString *)groupId succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  获取群列表
 *
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)getGroupList:(WildGroupListSucc)succ fail:(WildFail)fail;

/**
 *  获取群信息
 *
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)getGroupInfo:(NSArray *)groupIds succ:(WildGroupListSucc)succ fail:(WildFail)fail;


/**
 *  获取群成员列表
 *
 *  @param groupId 群组Id
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)getGroupMembers:(NSString *)groupId succ:(WildGroupMemberSucc)succ fail:(WildFail)fail;


/**
 *  修改群名
 *
 *  @param groupId     群组Id
 *  @param groupName 新群名
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupName:(NSString *)groupId groupName:(NSString *)groupName succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  修改群简介
 *
 *  @param groupId          群组Id
 *  @param introduction     群简介（最长120字节）
 *  @param callback  回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupIntroduction:(NSString *)groupId introduction:(NSString *)introduction succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  修改群公告
 *
 *  @param group            群组Id
 *  @param notification     群公告（最长150字节）
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupNotification:(NSString*)group notification:(NSString*)notification succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  修改接受消息选项
 *
 *  @param group            群组Id
 *  @param opt              接受消息选项，详见 TIMGroupReceiveMessageOpt
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyReciveMessageOpt:(NSString*)group opt:(WildGroupReceiveMessageOpt)opt succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  修改加群选项
 *
 *  @param group            群组Id
 *  @param opt              加群选项，详见 TIMGroupAddOpt
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupAddOpt:(NSString*)group opt:(WildGroupAddOpt)opt succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  禁言用户（只有管理员或群主能够调用）
 *
 *  @param group            群组Id
 *  @param identifier       被禁言的用户identifier
 *  @param stime            禁言时间
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupMemberInfoSetSilence:(NSString*)group user:(NSString*)identifier stime:(uint32_t)stime succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  修改群成员角色
 *
 *  @param group            群组Id
 *  @param identifier       被修改角色的用户identifier
 *  @param opt              角色（注意：不能修改为群主），详见 TIMGroupMemberRole
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupMemberInfoSetRole:(NSString*)group user:(NSString*)identifier role:(WildGroupMemberRole)role succ:(WildSucc)succ fail:(WildFail)fail;


/**
 *  修改群头像
 *
 *  @param group            群组Id
 *  @param url              群头像地址（最长100字节）
 *  @param succ             成功回调
 *  @param fail             失败回调
 *
 *  @return 0 成功
 */
- (int)modifyGroupFaceUrl:(NSString*)group url:(NSString*)url succ:(WildSucc)succ fail:(WildFail)fail;


@end



/**
 *  成员操作返回值
 */
@interface WildGroupMemberInfo : NSObject

/**
 *  被操作成员
 */
@property(nonatomic,retain) NSString* member;

/**
 *  群名片
 */
@property(nonatomic,retain) NSString* nameCard;

/**
 *  加入群组时间
 */
@property(nonatomic,assign) time_t joinTime;

/**
 *  成员类型
 */
@property(nonatomic,assign) WildGroupMemberRole role;

/**
 *  禁言时间（剩余秒数）
 */
@property(nonatomic,assign) uint32_t silentUntil;

/**
 *  自定义字段集合,key是NSString*类型,value是NSData*类型
 */
@property(nonatomic,retain) NSDictionary* customInfo;

@end

