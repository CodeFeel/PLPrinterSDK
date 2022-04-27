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
typedef void(^PLAutoPoooliStateAction)(PLPoooliPrinterStatus state);
typedef void(^PLImagePrintCompleteAction)(PLPoooliImageCompleteStatus state);

@interface PLDataDispatcher : NSObject

@property (nonatomic, strong) id<PLDataResolver>        _Nullable  resolver; ///< 协议属性
@property (nonatomic, copy) PLReceiveDataAction         _Nullable  receiveDataBlock; ///< 接收蓝牙数据
@property (nonatomic, copy) PLAutoPoooliStateAction     _Nullable  autoPoooliStateBlock; ///< L系列自动回传状态
@property (nonatomic, copy) PLImagePrintCompleteAction  _Nullable  printImageCompleteBlock; ///< 图片打印完成回调，暂时只有打印高清灰阶有效

+ (PLDataDispatcher *)shared;

/** 清空缓存数据 */
- (void)clearBufferData;

/** 发送数据 */
- (void)writeData:(NSData *)data;

/** 发送数据 */
- (void)writeData:(NSData *)data progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** 固件升级数据 */
- (void)writeFirmwareData:(NSMutableArray *)slices progress:(void(^)(NSProgress *))block fail:(void(^)(void))failBlock;

/** 接收蓝牙返回数据回调 A4机型不需要使用这个回调 */
- (void)receiveBluetoothDataBlock:(PLReceiveDataAction)receiveDataBlock;

/** 自动返回异常状态回调 */
- (void)autoPoooliDeviceStateBlock:(PLAutoPoooliStateAction)automaticStateBlock;

/** 图片打印完成的回调 */
- (void)imagePrintCompleteBlock:(PLImagePrintCompleteAction)imagePrintBlock;

@end


NS_ASSUME_NONNULL_END








