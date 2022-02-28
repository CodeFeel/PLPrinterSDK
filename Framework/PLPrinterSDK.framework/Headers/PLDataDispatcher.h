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
typedef void(^PLAutoMT800StateAction)(PLMT800PrinterStatus state);
typedef void(^PLImagePrintCompleteAction)(PLPoooliImageCompleteStatus state);

@interface PLDataDispatcher : NSObject

@property (nonatomic, strong) id<PLDataResolver>        _Nullable  resolver; ///< 协议属性
@property (nonatomic, copy) PLReceiveDataAction         _Nullable  receiveDataBlock; ///< 接收蓝牙数据
@property (nonatomic, copy) PLAutoPoooliStateAction     _Nullable  autoPoooliStateBlock; ///< L系列自动回传状态
@property (nonatomic, copy) PLAutoMT800StateAction      _Nullable  autoA4StateBlock; ///< A4系列自动回传状态
@property (nonatomic, copy) PLImagePrintCompleteAction  _Nullable  printImageCompleteBlock; ///< 图片打印完成回调，暂时只有打印高清灰阶有效

+ (PLDataDispatcher *)shared;

/** 清空缓存数据 */
- (void)clearBufferData;

/** 发送数据 */
- (void)writeData:(NSData *)data;

/** 发送数据 */
- (void)writeData:(NSData *)data progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** 发送含有灰阶高清的图片数据 */
- (void)writeGrayHDImageData:(NSData *)data progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** A4 打印图片 */
- (void)writeA4ImageDatas:(NSMutableArray *)datas progress:(void(^_Nullable)(NSProgress *))block fail:(void(^_Nullable)(void))failBlock;

/** 固件升级数据 */
- (void)writeFirmwareData:(NSMutableArray *)slices progress:(void(^)(NSProgress *))block fail:(void(^)(void))failBlock;

/** 接收蓝牙返回数据回调 A4机型不需要使用这个回调 */
- (void)receiveBluetoothDataBlock:(PLReceiveDataAction)receiveDataBlock;

/** Poooli自动返回异常状态回调 */
- (void)autoPoooliDeviceStateBlock:(PLAutoPoooliStateAction)automaticStateBlock;

/** A4自动返回异常状态回调 */
- (void)autoA4DeviceStateBlock:(PLAutoMT800StateAction)automaticStateBlock;

/** 图片打印完成的回调 poooli */
- (void)imagePrintCompleteBlock:(PLImagePrintCompleteAction)imagePrintBlock;

@end


NS_ASSUME_NONNULL_END








