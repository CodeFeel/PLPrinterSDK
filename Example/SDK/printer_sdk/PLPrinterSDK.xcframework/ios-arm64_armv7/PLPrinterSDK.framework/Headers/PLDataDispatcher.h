//
//  PLDataDispatcher.h
//  PLPrinterSDK
//
//  Created by ios on 2020/12/1.
//

#import <Foundation/Foundation.h>
#import "PLEnumList.h"

NS_ASSUME_NONNULL_BEGIN

/// MT800解析协议
@protocol PLDataResolver <NSObject>

@property (nonatomic, copy) void (^_Nullable resolvedBlock)(id result);

- (void)readDeviceInput:(NSData *)data;

@end

typedef void(^PLReceiveDataAction)(NSData *data);
typedef void(^PLAutoMT800StateAction)(PLMT800PrinterStatus state);

@interface PLDataDispatcher : NSObject

@property (nonatomic, strong) id<PLDataResolver>        _Nullable  resolver; ///< 协议属性
@property (nonatomic, copy) PLReceiveDataAction         _Nullable  receiveDataBlock; ///< 接收蓝牙数据，A4机型不需要使用这block
@property (nonatomic, copy) PLAutoMT800StateAction      _Nullable  autoA4StateBlock; ///< A4系列自动回传状态

+ (PLDataDispatcher *)shared;

/// 初始化授权key，不然无法连接打印机，建议在AppDelegate中调用
/// @param authKey 授权key
- (void)startWithAuthKey:(NSString *)authKey;

/// 取消发送
- (void)cancelSendData;

/** 发送数据 */
- (void)writeData:(NSData *)data;

/** 发送数据 */
- (void)writeData:(NSData *)data progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** A4 打印图片 */
- (void)writeA4ImageDatas:(NSMutableArray *)datas progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** 固件升级数据 */
- (void)writeFirmwareData:(NSData *)data progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** 接收蓝牙返回数据回调 A4机型不需要使用这个回调 */
- (void)receiveBluetoothDataBlock:(PLReceiveDataAction)receiveDataBlock;

/** A4自动返回异常状态回调 */
- (void)autoA4DeviceStateBlock:(PLAutoMT800StateAction)automaticStateBlock;


@end


NS_ASSUME_NONNULL_END








