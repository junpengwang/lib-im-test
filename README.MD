## 新手指引

####1 总览
开发者的应用接入野狗 IM SDK，需要经过如下几个简单的步骤:

<img src="总览.jpg" width="700">

####2 注册野狗实时后端云帐号

注册野狗实时后端云帐号请访问 [野狗注册页面](https://www.wilddog.com/my-account/signup)。

<img src="注册.png" width="300">

####3 创建应用

注册后登陆帐号，会进入野狗控制面板，在这里创业您的第一个应用。填入应用名和应用 ID，应用 ID 在初始化 SDK 时需要用到。,更多信息请访问 [如何创建野狗应用](https://z.wilddog.com/overview/app)


<img src="创建应用.png" width="850">

####4 生成 Token

<img src="生成Token.png" width="850">

App 开发都有自己的帐户系统，野狗使用 [JWT token](https://jwt.io) 结合超级密钥生成 Token 来集成 APP 用户 ID 和 昵称。在野狗帐号控制面板中进入应用中，在左侧功能栏中找到超级密钥。用户可以自行生成token，只需符合格式约定。token采用标准的jwt格式，payload部分中，必须包含的字段如下：[更多信息请参考](https://z.wilddog.com/rule/guide) 中第五节自定义 token。

| 字段 | 描述 |
| --- | --- |
| v | token的版本，默认是数字0  |
| iat | token的颁发时间，Unix时间秒数 |
| d | 认证数据。token的payload，必须包含uid字段，对应规则表达式中的`auth`变量|

下面是可选参数：

| 字段 | 描述 |
| --- | --- |
| nbf | token在之前（缩写"not before"）时间不会生效|
| exp | token过期的时间戳，以秒为单位 |
| admin | 如果设置为true，将获得完全的读写权限|
| debug | 如果设置为true，将在安全和规则表达式失败时提供详细的错误信息|


一个示例的token payload：

``` 
{
    "v" : 0,
    "iat" : 1437520447,
    "d" : {
        "uid" : "sampleId"
    },
    "admin" : true,
    "exp" :  1437845927
}
```

使用SHA-256 HMAC签名，生成标准的jwt即可。



## WildIMLib iOS 集成

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

	#import <WildIMLib/WildIMSDK.h>
	
####2 初始化

WildIMLib 以野狗 SDK 为基础，所以初始化之前需要一个野狗的 AppID，通过 initSDK: 初始化。原型为：

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
 *  @param token  根据用户 ID、昵称和野狗超级密钥生成的 Token。
 *  @param succ   成功回调
 *  @param fail   失败回调
 *  @return 0 登陆请求发送成功，等待回调
 */
- (int)loginWithcustomeToken:(NSString *)token succ:(WildSucc)succ fail:(WildFail)fail;

````

######示例

````
[[WildManager sharedInstance] login:uid customeToken:token userName:uid succ:^{
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

#####a. 会话获取

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
会话类型，如果是单聊，填写 Wild_C2C，如果是群聊，填写 Wild_GROUP
receiver：
会话标识，单聊情况下，receiver为对方帐号identifier，群聊情况下，receiver为群组Id

######示例
以下示例获取对方 uid 为“10086”的单聊会话：

```
WildConversation * c2c_conversation = [[WildManager sharedInstance] getConversation:Wild_C2C receiver:@"10086"];
```
以下示例获取群组Id为"-KFS5puUyvyyDNsryJaY"的群聊会话：

```
WildConversation * group_conversation = [[WildManager sharedInstance] getConversation:Wild_GROUP receiver:@"-KFS5puUyvyyDNsryJaY"];
```

#####b. 消息发送

获取会话后，可以通过 sendMessage: 发送消息

######原型
````
@interface WildConversation : NSObject

-(int) sendMessage: (WildMessage*)msg succ:(WildSucc)succ fail:(WildFail)fail;

@end

````

#####5.1 文本消息发送
文本消息由 WildTextElem 定义：

```
@interface WildTextElem : WildElem {
    NSString * text;
}
```
text 传递需要发送的文本消息：
######示例

```
WildTextElem * text_elem = [[WildTextElem alloc] init];

[text_elem setText:@"this is a text message"];

WildMessage * msg = [[WildMessage alloc] init];
[msg addElem:text_elem];

[conversation sendMessage:msg succ:^(){
    NSLog(@"SendMsg Succ");
}fail:^(int code, NSString * err) {
    NSLog(@"SendMsg Failed:%d->%@", code, err);
}];

```
#####5.2 图片消息发送
图片消息由 WildImageElem 定义。它是 WildElem 的一个子类，也就是说图片也是消息的一种内容。 发送图片的过程，就是将 WildImageElem 加入到 WildMessage 中，然后随消息一起发送出去。详细如下：

######原型

```
/**
 *  存储要发送的图片路径，必须是本地路径，可参考下面示例
 */
@interface WildImageElem : WildElem

/**
 *  要发送的图片路径
 */
@property(nonatomic,retain) NSString * path;


/**
 *  图片压缩等级，详见 Wild_IMAGE_COMPRESS_TYPE
 */
@property(nonatomic,assign) Wild_IMAGE_COMPRESS_TYPE level;

@end
```
######参数说明
path ：存储要发送的图片路径，必须是本地路径，可参考下面示例

level : 发送图片前对图片进行压缩，level 表示压缩等级，详见 Wild_IMAGE_COMPRESS_TYPE 定义

发送图片时，只需要设置图片路径 path。

######图片发送示例：

```
/**
*  获取聊天会话, 以同用户iOS-001的单聊为例，群聊可参见4.1节a部分
*/
WildConversation * c2c_conversation = [[WildManager sharedInstance] getConversation:Wild_C2C receiver:@"iOS-001"];

/**
*  构造一条消息
*/
WildMessage * msg = [[WildMessage alloc] init];

/**
*  构造图片内容
*/
WildImageElem * image_elem = [[WildImageElem alloc] init];
image_elem.path = @"/xxx/imgPath.jpg";

/**
*  将图片内容添加到消息容器中
*/
[msg addElem:image_elem];

/**
*  发送消息
*/
[conversation sendMessage:msg succ:^(){  //成功
       NSLog(@"SendMsg Succ");
}fail:^(int code, NSString * err) {  //失败
       NSLog(@"SendMsg Failed:%d->%@", code, err);
}];
```
##### 5.3 语音消息发送
语音消息由 WildSoundElem 定义，其中data存储语音数据，语音数据需要提供时长信息，以秒为单位，注意，一条消息只能有一个语音Elem，添加多条语音Elem时，AddElem函数返回错误1，添加不生效，另外，语音和文件elem不一定会按照添加时的顺序获取，建议逐个判断elem类型展示。

```
@interface WildSoundElem : WildElem {
   NSData * data;
   int second;
}
```
######示例

```
NSData *data = /* 语音数据 */;

WildSoundElem * sound_elem = [[WildSoundElem alloc] init];

[sound_elem setData:data];
[sound_elem setSecond:10];

WildMessage * msg = [[WildMessage alloc] init];
[msg addElem:sound_elem];

[conversation sendMessage:msg succ:^(){
    NSLog(@"SendMsg Succ");
}fail:^(int code, NSString * err) {
    NSLog(@"SendMsg Failed:%d->%@", code, err);
}];
```
###6 获取消息
ImSDK 会在本地进行消息存储，可通过 WildConversation 方法的 getMessage 获取，此方法为异步方法，需要通过设置回调得到消息数据，对于群组，登录后可以获取漫游消息，对于C2C，开通漫游服务后可以获取漫游消息，ImSDK提供了两种方式，一种通过闭包回调，另一种通过protocol接口回调：

######原型

```
@interface WildConversation : NSObject

// 闭包回调
- (int)getMessage:(int)count last:(WildMessage*)last succ:(WildGetMsgSucc)succ fail:(WildFail)fail;
```
######参数说明：
count 指定获取消息的数量

last 指定上次获取的最后一条消息，如果last传nil，从最新的消息开始读取

succ 成功回调

fail 失败回调

######示例

```
[conversation getMessage:10 last:nil succ:^(NSArray * msgList) {
    for (WildMessage * msg in msgList) {
        if ([msg isKindOfClass:[WildMessage class]]) {
            NSLog(@"GetOneMessage:%@", msg);
        }
    }
}fail:^(int code, NSString * err) {
    NSLog(@"Get Message Failed:%d->%@", code, err);
}];
```

###7 获取所有会话
SDK会保存用户的会话和消息，可以通过 ConversationCount 获取当前会话数量，从而得到所有本地会话：

######原型：

```
-(int) ConversationCount;
-(WildConversation*) getConversationByIndex:(int)index;

示例：

int cnt = [[WildManager sharedInstance] ConversationCount];

for (int i = 0; i < cnt; i++) {
 WildConversation * conversation = [[WildManager sharedInstance] getConversationByIndex:i];
}
```

###8 删除会话
存在本地的最近联系会话，可以删除，需要注意的是，此处仅删除会话记录，会话中的消息并未删除。

######原型

```
@protocol WildMessageListener
/**
 *  删除会话
 *
 *  @param type 会话类型，Wild_C2C 表示单聊 Wild_GROUP 表示群聊
 *  @param receiver    用户identifier 或者 群组Id
 *
 *  @return TRUE:删除成功  FALSE:删除失败
 */
-(BOOL) deleteConversation:(WildConversationType)type receiver:(NSString*) receiver;

@end
```
######参数解释
type：

会话类型，如果是单聊，填写 Wild_C2C，如果是群聊，填写Wild_GROUP

receiver：

会话标识，单聊情况下，receiver为对方用户identifier，群聊情况下，receiver为群组Id
######示例

```
WildConversation * conversation = [[WildManager sharedInstance] deleteConversation:Wild_C2C receiver:@"10086"];
```
###9 消息解析
收到消息后，可用过 getElem 从 WildMessage 中获取所有的 Elem 节点：

遍历 Elem 原型:

```
@interface WildMessage : NSObject

-(int) elemCount;
-(WildElem*) getElem:(int)index;

@end
```
######示例：

```
WildMessage * message = /* 消息 */

int cnt = [message elemCount];

for (int i = 0; i < cnt; i++) {
 WildElem * elem = [message getElem:i];

 if ([elem isKindOfClass:[WildTextElem class]]) {
     WildTextElem * text_elem = (WildTextElem * )elem;
 }
 else if ([elem isKindOfClass:[WildImageElem class]]) {
     WildImageElem * image_elem = (WildImageElem * )elem;
 }
}
```
###10 未读计数
#####10.1 获取当前未读消息数量
可通过 WildConversation 的 getUnReadMessageNum 方法获取当前会话中未读消息的数量：
######原型:

```
-(int) getUnReadMessageNum;
```
######示例

```
WildConversation * conversation = [[WildManager sharedInstance] getConversation:Wild_C2C receiver:@"iOS_002"];

[conversation getUnReadMessageNum];
```

#####10.2 已读上报

当用户阅读某个会话的数据后，需要进行会话消息的已读上报，SDK根据会话中最后一条阅读的消息，设置会话中之前所有消息为已读。

######原型:

```
@interface WildConversation : NSObject

-(int) setReadMessage: (WildMessage*)readed;
-(int) setReadMessage;

@end
```
######参数说明
readed：

为当前会话中最后一条读过的消息，ImSDK会把比readed时间更早的消息标记为已读消息。无参数的版本设置一个会话中所有消息为已读状态，大多数情况下使用无参数版本即可。

######示例1

```
WildConversation * conversation = [[WildManager sharedInstance] getConversation:Wild_C2C receiver:@"iOS_002"];

WildMessage * msg = [[WildMessage alloc] init];
[conversation setReadMessage:msg];
```
此示例设置C2C会话内的所有消息为已读。
######示例2

```
WildConversation * conversation = [[WildManager sharedInstance] getConversation:Wild_GROUP receiver:@"TGID1JYSZEAEQ"];

[conversation setReadMessage];
```
此示例设置群组@"TGID1JYSZEAEQ"内所有消息为已读，C2C 和群组设置已读用法相同，区别在于会话类型。

###群组管理

###离线推送

