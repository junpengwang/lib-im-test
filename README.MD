### WildIMLib 集成

#### 使用 CocoaPods 
野狗建议使用 [CocoaPods](https://cocoapods.org/) 管理工程的依赖。关于 CocoaPods 的入门，请参考： [CocoaPods getting started](https://guides.cocoapods.org/using/getting-started.html)。 


打开工程目录，新建一个 Podfile 文件

	$ cd your-project-directory
	$ pod init
	$ open -a Xcode Podfile # opens your Podfile in XCode

然后在 Podfile 文件中添加以下语句

	target 'your-target-name' do
	pod 'Wilddog'
	pod 'WildChatLib'
	end
	
最后安装 SDK

	$ pod install
	$ open your-project.xcworkspace



####1 引入头文件

	#import <WildIMLib/WildIMLib.h>
	
####2 初始化

WildIMLib 以野狗 SDK 为基础，所以初始化之前需要一个野狗的 APPID，通过 initSDK: 初始化。原型为：

````
/**
 *  初始化SDK
 *
 * @param sdkAppId    用户标识接入SDK的应用ID
 *
 *  @return 0 成功
 */
- (int)initSDK:(NSString *)sdkAppId;
 
```` 

######示例
	[[WildIMLib sharedInstance] initSDK:@"your-appid"];

####3 登陆

用户登陆野狗服务器后才能正常收发消息，登陆接口需要提供三个参数，

userId 用户 Id，唯一表示用户身份;

name 用户昵称，推送的时候需要用到;

token 使用用户 id 和 野狗的超级密钥生产的 jwt token;
######登陆结构原型
````
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

````

######示例

````
[[WildIMLib sharedInstance] login:uid customeToken:token userName:uid succ:^{
                NSLog(@"login succ);              
            } fail:^(int code, NSString *msg) {
                NSLog(@"login failed:%@",msg);
            }];
````

####4 新消息通知
在多数情况下，用户需要感知新消息的通知，这时只需注册新消息通知回调 WildMessageListener，在用户登录状态下，会拉取离线消息，为了不漏掉消息通知，需要在登录之后注册新消息通知。

######原型

````
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
````

####5 消息收发

a. 会话获取

会话是指面向一个人或者一个群组的对话，通过与单个人或群组之间会话收发消息，发消息时首先需要先获取会话，获取会话需要指定会话类型（群组&单聊），以及会话对方标志（对方帐号或者群号）。获取会话由 getConversation 实现：
######原型

````
/**
 *  获取会话
 *
 *  @param type 会话类型，Wild_C2C 表示单聊 Wild_GROUP 表示群聊
 *  @param receiver C2C 为对方用户 identifier， GROUP 为群组Id
 *
 *  @return 会话对象
 */
- (WildConversation *)getConversation:(WildConversationType)type receiver:(NSString *)receiver;
````

######参数说明
type：
会话类型，如果是单聊，填写 TIM_C2C，如果是群聊，填写TIM_GROUP
receiver：
会话标识，单聊情况下，receiver为对方帐号identifier，群聊情况下，receiver为群组Id

b. 消息发送

获取会话后，可以通过 sendMessage: 发送消息

######原型
````
@interface WildConversation : NSObject

-(int) sendMessage: (WildMessage*)msg succ:(WildSucc)succ fail:(WildFail)fail;

-(int) sendMessage: (WildMessage*)msg cb:(id)cb;

@end

````
