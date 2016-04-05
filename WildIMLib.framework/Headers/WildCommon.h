//
//  WildCommon.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#ifndef WildCommon_h
#define WildCommon_h

@class WildError;

#define kWildSuccessStr @"成功"

/**
 * 网络连接状态
 */
typedef NS_ENUM(NSInteger, WildNetworkStatus) {
    /**
     * 已连接
     */
    Wild_NETWORK_STATUS_CONNECTED             = 1,
    /**
     * 链接断开
     */
    Wild_NETWORK_STATUS_DISCONNECTED          = 2,
};


/**
 * 日志级别
 */
typedef NS_ENUM(NSInteger, WildLogLevel) {
    Wild_LOG_NONE                = 0,
    Wild_LOG_ERROR               = 1,
    Wild_LOG_WARN                = 2,
    Wild_LOG_INFO                = 3,
    Wild_LOG_DEBUG               = 4,
};

/////////////////////////////////////////////////////////
///  回调Block
/////////////////////////////////////////////////////////

/**
 *  获取消息回调
 *
 *  @param NSArray 消息列表
 */
typedef void (^WildGetMsgSucc)(NSArray * msgs);

/**
 *  一般操作成功回调
 */
typedef void (^WildSucc)();

/**
 *  操作失败回调
 *
 *  @param code 错误码
 *  @param msg  错误描述，配合错误码使用，如果问题建议打印信息定位
 */
typedef void (^WildFail)(int code, NSString * msg);

/**
 *  登陆成功回调
 */
typedef void (^WildLoginSucc)();

/**
 *  获取资源
 *
 *  @param NSData 资源二进制
 */
typedef void (^WildGetResourceSucc)(NSData * data);



/**
 *  群创建成功
 *
 *  @param NSString 群组Id
 */
typedef void (^WildCreateGroupSucc)(NSString * groupId);

/**
 *  群成员列表回调
 *
 *  @param NSArray 群成员列表
 */
typedef void (^WildGroupMemberSucc)(NSArray * members);

/**
 *  群成员列表回调（分页使用）
 *
 *  @param NSArray 群成员（WildGroupMemberInfo*）列表
 */
typedef void (^WildGroupMemberSuccV2)(uint64_t nextSeq, NSArray * members);

/**
 *  群列表回调
 *
 *  @param NSArray 群列表
 */
typedef void (^WildGroupListSucc)(NSArray * arr);


/**
 *  日志回调
 *
 *  @param lvl      输出的日志级别
 *  @param NSString 日志内容
 */
typedef void (^WildLogFunc)(WildLogLevel lvl, NSString * msg);


@class WildImageElem;
/**
 *  上传图片成功回调
 *
 *  @param elem 上传图片成功后elem
 */
typedef void (^WildUploadImageSucc)(WildImageElem * elem);

/////////////////////////////////////////////////////////
///  基本类型
/////////////////////////////////////////////////////////

/**
 *  登陆信息
 */

@interface WildLoginParam : NSObject{
    NSString*       accountType;        // 用户的账号类型
    NSString*       identifier;         // 用户名
    NSString*       userSig;            // 鉴权Token
    NSString*       appidAt3rd;          // App用户使用OAuth授权体系分配的Appid
    
    int             sdkAppId;           // 用户标识接入SDK的应用ID
}

/**
 *  用户的账号类型
 */
@property(nonatomic,retain) NSString* accountType;

/**
 * 用户名
 */
@property(nonatomic,retain) NSString* identifier;

/**
 *  鉴权Token
 */
@property(nonatomic,retain) NSString* userSig;

/**
 *  App用户使用OAuth授权体系分配的Appid
 */
@property(nonatomic,retain) NSString* appidAt3rd;


/**
 *  用户标识接入SDK的应用ID
 */
@property(nonatomic,assign) int sdkAppId;

@end



/**
 * 会话类型：
 *      C2C     双人聊天
 *      GROUP   群聊
 */
typedef NS_ENUM(NSInteger, WildConversationType) {
    /**
     *  C2C 类型
     */
    Wild_C2C              = 1,
    
    /**
     *  群聊 类型
     */
    Wild_GROUP            = 2,
    
    /**
     *  系统消息
     */
    Wild_SYSTEM           = 3,
};



/**
 *  消息状态
 */
typedef NS_ENUM(NSInteger, WildMessageStatus){
    /**
     *  消息发送中
     */
    Wild_MSG_STATUS_SENDING              = 1,
    /**
     *  消息发送成功
     */
    Wild_MSG_STATUS_SEND_SUCC            = 2,
    /**
     *  消息发送失败
     */
    Wild_MSG_STATUS_SEND_FAIL            = 3,
    /**
     *  消息被删除
     */
    Wild_MSG_STATUS_HAS_DELETED          = 4,
};


/**
 *  群组提示类型
 */
typedef NS_ENUM(NSInteger, WildGroupTipsType){
    /**
     *  成员加入
     */
    Wild_GROUP_TIPS_JOIN              = 1,
    /**
     *  成员离开
     */
    Wild_GROUP_TIPS_QUIT              = 2,
    /**
     *  成员被踢
     */
    Wild_GROUP_TIPS_KICK              = 3,
    /**
     *  成员设置管理员
     */
    Wild_GROUP_TIPS_SET_ADMIN         = 4,
    /**
     *  成员取消管理员
     */
    Wild_GROUP_TIPS_CANCEL_ADMIN      = 5,
};

#endif /* WildCommon_h */



