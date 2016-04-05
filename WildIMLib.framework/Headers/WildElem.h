//
//  WildElem.h
//  WildIMLib
//
//  Created by Garin on 16/3/3.
//  Copyright © 2016年 wilddog. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WildCommon.h"
#import "WildCallback.h"

/**
 *  图片压缩选项
 */
typedef NS_ENUM(NSInteger, Wild_IMAGE_COMPRESS_TYPE){
    /**
     *  原图(不压缩）
     */
    Wild_IMAGE_COMPRESS_ORIGIN              = 0x00, //1
    /**
     *  高压缩率：图片较小，默认值
     */
    Wild_IMAGE_COMPRESS_HIGH                = 0x01, //0.6
    /**
     *  低压缩：高清图发送(图片较大)
     */
    Wild_IMAGE_COMPRESS_LOW                 = 0x02, //0.8
};

/**
 *  图片类型
 */
typedef NS_ENUM(NSInteger, Wild_IMAGE_TYPE){
    /**
     *  原图
     */
    Wild_IMAGE_TYPE_ORIGIN              = 0x01,
    /**
     *  缩略图
     */
    Wild_IMAGE_TYPE_THUMB               = 0x02,
    /**
     *  大图
     */
    Wild_IMAGE_TYPE_LARGE               = 0x04,
};

/**
 *  图片格式
 */
typedef NS_ENUM(NSInteger, Wild_IMAGE_FORMAT){
    /**
     *  JPG格式
     */
    Wild_IMAGE_FORMAT_JPG            = 0x1,
    /**
     *  GIF格式
     */
    Wild_IMAGE_FORMAT_GIF            = 0x2,
    /**
     *  PNG格式
     */
    Wild_IMAGE_FORMAT_PNG            = 0x3,
    /**
     *  BMP格式
     */
    Wild_IMAGE_FORMAT_BMP            = 0x4,
    /**
     *  未知格式
     */
    Wild_IMAGE_FORMAT_UNKNOWN        = 0xff,
};



/**
 *  消息Elem基类
 */
@interface WildElem : NSObject

@end


/**
 *  文本消息Elem
 */
@interface WildTextElem : WildElem

/**
 *  消息文本
 */
@property (nonatomic,retain) NSString * text;
@end



@interface WildMentionElem : WildElem

@property (nonatomic,retain) NSString *mentionId;
@end



@interface WildTipElem : WildElem
/**
 *  提示文本
 */
@property (nonatomic,retain) NSString *text;
@end



@interface WildCardElem : WildElem

@property (nonatomic,retain) NSString *name;
@property (nonatomic,retain) NSString *headUrl;
@property (nonatomic,retain) NSString *cardId;
@property (nonatomic,retain) NSString *desc;
@end


@interface WildImage : NSObject
/**
 *  图片ID，内部标识，可用于外部缓存key
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  图片类型
 */
@property(nonatomic,assign) Wild_IMAGE_TYPE type;
/**
 *  图片大小
 */
@property(nonatomic,assign) int size;
/**
 *  图片宽度
 */
@property(nonatomic,assign) int width;
/**
 *  图片高度
 */
@property(nonatomic,assign) int height;
/**
 *  下载URL
 */
@property(nonatomic, retain) NSString * url;

/**
 *  获取图片
 *
 *  @param path 图片保存路径
 *  @param succ 成功回调，返回图片数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void)getImage:(NSString *)path succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  获取图片
 *
 *  @param path 图片保存路径
 *  @param cb 图片获取回调
 */
- (void)getImage:(NSString *)path cb:(id<WildCallback>)cb;

@end


/**
 *  图片消息Elem
 */
@interface WildImageElem : WildElem

/**
 *  要发送的图片路径，必须是本地路径
 */
@property(nonatomic,retain) NSString * path;

/**
 *  所有类型图片，只读
 */
@property(nonatomic,retain) NSArray * imageList;

/**
 * 上传时任务Id，可用来查询上传进度
 */
@property(nonatomic,assign) uint32_t taskId;

/**
 *  图片压缩等级，详见 Wild_IMAGE_COMPRESS_TYPE
 */
@property(nonatomic,assign) Wild_IMAGE_COMPRESS_TYPE level;

/**
 *  图片格式，详见 Wild_IMAGE_FORMAT
 */
@property(nonatomic,assign) Wild_IMAGE_FORMAT format;

/**
 *  查询上传进度
 */
- (uint32_t) getUploadingProgress;

@end


@interface WildVoiceElem : WildElem

/**
 *  存储语音数据
 */
@property(nonatomic,retain) NSData * data;
/**
 *  语音消息内部ID
 */
@property(nonatomic,retain) NSString * uuid;
/**
 *  语音数据大小
 */
@property(nonatomic,assign) int dataSize;
/**
 *  语音长度（秒），发送消息时设置
 */
@property(nonatomic,assign) int second;

@property(nonatomic,strong) NSString *url;

/**
 *  获取语音数据
 *
 *  @param succ 成功回调，返回语音数据
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) getSound:(WildGetResourceSucc)succ fail:(WildFail)fail;

/**
 *  获取语音数据
 *
 *  @param cb 资源获取回调
 */
- (void) getSound:(id<WildResourceCallback>)cb;

@end



/**
 *  地理位置Elem
 */
@interface WildLocationElem : WildElem
/**
 *  地理位置描述信息，发送消息时设置
 */
@property(nonatomic,retain) NSString * desc;
/**
 *  纬度，发送消息时设置
 */
@property(nonatomic,assign) double latitude;
/**
 *  精度，发送消息时设置
 */
@property(nonatomic,assign) double longitude;
@end


/**
 *  扩展Elem
 */
@interface WildExtElem : WildElem
/**
 *
 */
@property (nonatomic,retain) NSData * data;
@end


/**
 *  群tips，成员变更信息
 */
@interface WildGroupTipsElemMemberInfo : NSObject

/**
 *  变更用户
 */
@property(nonatomic,retain) NSString * identifier;
/**
 *  禁言时间（秒，表示还剩多少秒可以发言）
 */
@property(nonatomic,assign) uint32_t shutupTime;

@end



/**
 *  群Tips类型
 */
typedef NS_ENUM(NSInteger, Wild_GROUP_INFO_CHANGE_TYPE){
    /**
     *  群名修改
     */
    Wild_GROUP_INFO_CHANGE_GROUP_NAME                    = 0x01,
    /**
     *  群简介修改
     */
    Wild_GROUP_INFO_CHANGE_GROUP_INTRODUCTION            = 0x02,
    /**
     *  群公告修改
     */
    Wild_GROUP_INFO_CHANGE_GROUP_NOTIFICATION            = 0x03,
    /**
     *  群头像修改
     */
    Wild_GROUP_INFO_CHANGE_GROUP_FACE                    = 0x04,
    /**
     *  群主变更
     */
    Wild_GROUP_INFO_CHANGE_GROUP_OWNER                   = 0x05,
};

/**
 *  群tips，群变更信息
 */
@interface WildGroupTipsElemGroupInfo : NSObject

/**
 *  变更类型
 */
@property(nonatomic, assign) Wild_GROUP_INFO_CHANGE_TYPE type;

/**
 *  根据变更类型表示不同含义
 */
@property(nonatomic,retain) NSString * value;
@end

/**
 *  群Tips类型
 */
typedef NS_ENUM(NSInteger, Wild_GROUP_TIPS_TYPE){
    /**
     *  邀请加入群 (opUser & groupName & userList)
     */
    Wild_GROUP_TIPS_TYPE_INVITE              = 0x01,
    /**
     *  退出群 (opUser & groupName & userList)
     */
    Wild_GROUP_TIPS_TYPE_QUIT_GRP            = 0x02,
    /**
     *  踢出群 (opUser & groupName & userList)
     */
    Wild_GROUP_TIPS_TYPE_KICKED              = 0x03,
    /**
     *  设置管理员 (opUser & groupName & userList)
     */
    Wild_GROUP_TIPS_TYPE_SET_ADMIN           = 0x04,
    /**
     *  取消管理员 (opUser & groupName & userList)
     */
    Wild_GROUP_TIPS_TYPE_CANCEL_ADMIN        = 0x05,
    /**
     *  群资料变更 (opUser & groupName & introduction & notification & faceUrl & owner)
     */
    Wild_GROUP_TIPS_TYPE_INFO_CHANGE         = 0x06,
    /**
     *  群成员资料变更 (opUser & groupName & memberInfoList)
     */
    Wild_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE         = 0x07,
};
/**
 *  群Tips
 */
@interface WildGroupTipsElem : WildElem

/**
 *  群组Id
 */
@property(nonatomic,retain) NSString * group;

/**
 *  群Tips类型
 */
@property(nonatomic,assign) Wild_GROUP_TIPS_TYPE type;

/**
 *  操作人用户名
 */
@property(nonatomic,retain) NSString * opUser;

/**
 *  被操作人列表 NSString* 数组
 */
@property(nonatomic,retain) NSArray * userList;

/**
 *  在群名变更时表示变更后的群名，否则为 nil
 */
@property(nonatomic,retain) NSString * groupName;

/**
 *  群信息变更： Wild_GROUP_TIPS_TYPE_INFO_CHANGE 时有效，为 WildGroupTipsElemGroupInfo 结构体列表
 */
@property(nonatomic,retain) NSArray * groupChangeList;

/**
 *  成员变更： Wild_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE 时有效，为 WildGroupTipsElemMemberInfo 结构体列表
 */
@property(nonatomic,retain) NSArray * memberChangeList;

/**
 *  变更成员资料
 */
@property(nonatomic,retain) NSDictionary * changedUserInfo;
/**
 *  变更成员群内资料
 */
@property(nonatomic,retain) NSDictionary * changedGroupMemberInfo;

@end


/**
 *  群系统消息类型
 */
typedef NS_ENUM(NSInteger, Wild_GROUP_SYSTEM_TYPE){
    /**
     *  申请加群请求（只有管理员会收到）
     */
    Wild_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE              = 0x01,
    /**
     *  申请加群被同意（只有申请人能够收到）
     */
    Wild_GROUP_SYSTEM_ADD_GROUP_ACCEPT_TYPE               = 0x02,
    /**
     *  申请加群被拒绝（只有申请人能够收到）
     */
    Wild_GROUP_SYSTEM_ADD_GROUP_REFUSE_TYPE               = 0x03,
    /**
     *  被管理员踢出群（只有被踢的人能够收到）
     */
    Wild_GROUP_SYSTEM_KICK_OFF_FROM_GROUP_TYPE            = 0x04,
    /**
     *  群被解散（全员能够收到）
     */
    Wild_GROUP_SYSTEM_DELETE_GROUP_TYPE                   = 0x05,
    /**
     *  创建群消息（创建者能够收到）
     */
    Wild_GROUP_SYSTEM_CREATE_GROUP_TYPE                   = 0x06,
    /**
     *  邀请入群通知(被邀请者能够收到)
     */
    Wild_GROUP_SYSTEM_INVITED_TO_GROUP_TYPE               = 0x07,
    /**
     *  主动退群（主动退群者能够收到）
     */
    Wild_GROUP_SYSTEM_QUIT_GROUP_TYPE                     = 0x08,
    /**
     *  设置管理员(被设置者接收)
     */
    Wild_GROUP_SYSTEM_GRANT_ADMIN_TYPE                    = 0x09,
    /**
     *  取消管理员(被取消者接收)
     */
    Wild_GROUP_SYSTEM_CANCEL_ADMIN_TYPE                   = 0x0a,
    /**
     *  群已被回收(全员接收)
     */
    Wild_GROUP_SYSTEM_REVOKE_GROUP_TYPE                   = 0x0b,
    /**
     *  邀请入群请求(被邀请者接收)
     */
    Wild_GROUP_SYSTEM_INVITE_TO_GROUP_REQUEST_TYPE        = 0x0c,
    /**
     *  邀请加群被同意(只有发出邀请者会接收到)
     */
    Wild_GROUP_SYSTEM_INVITE_TO_GROUP_ACCEPT_TYPE         = 0x0d,
    /**
     *  邀请加群被拒绝(只有发出邀请者会接收到)
     */
    Wild_GROUP_SYSTEM_INVITE_TO_GROUP_REFUSE_TYPE         = 0x0e,
    /**
     *  用户自定义通知(默认全员接收)
     */
    Wild_GROUP_SYSTEM_CUSTOM_INFO                         = 0xff,
};
/**
 *  群系统消息
 */
@interface WildGroupSystemElem : WildElem

/**
 * 操作类型
 */
@property (nonatomic,assign) Wild_GROUP_SYSTEM_TYPE type;

/**
 * 群组Id
 */
@property (nonatomic,retain) NSString * group;

/**
 * 操作人
 */
@property (nonatomic,retain) NSString * user;

/**
 * 操作理由
 */
@property (nonatomic,retain) NSString * msg;


/**
 *  消息标识，客户端无需关心
 */
@property (nonatomic,assign) uint64_t msgKey;

/**
 *  消息标识，客户端无需关心
 */
@property (nonatomic,retain) NSData * authKey;

/**
 *  用户自定义透传消息体（type＝TIM_GROUP_SYSTEM_CUSTOM_INFO时有效）
 */
@property (nonatomic,retain) NSDictionary * userData;

@property (nonatomic,strong) NSArray *receivers;

///**
// *  操作人资料
// */
//@property(nonatomic,retain) WildUserProfile * opUserInfo;
//
///**
// *  操作人群成员资料
// */
//@property(nonatomic,retain) WildGroupMemberInfo * opGroupMemberInfo;

/**
 *  同意申请，目前只对申请加群和被邀请入群消息生效
 *
 *  @param msg  同意理由，选填
 *  @param succ 成功回调
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) accept:(NSString*)msg succ:(WildSucc)succ fail:(WildFail)fail;

/**
 *  拒绝申请，目前只对申请加群和被邀请入群消息生效
 *
 *  @param msg  拒绝理由，选填
 *  @param succ 成功回调
 *  @param fail 失败回调，返回错误码和错误描述
 */
- (void) refuse:(NSString*)msg succ:(WildSucc)succ fail:(WildFail)fail;

@end


