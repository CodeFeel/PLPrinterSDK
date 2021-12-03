//
//  PLCmdMTGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>
#import "PLBitmapManager.h"
#import "PLEnumList.h"

NS_ASSUME_NONNULL_BEGIN

/// 状态信息类
@interface PLMT800Info : NSObject

@property (nonatomic, assign) PLMT800PrinterStatus state;
@property (nonatomic, assign) BOOL idle;
@property (nonatomic, assign) Byte electricity;
@property (nonatomic, assign) uint32_t shutdownTime;
@property (nonatomic, assign) Byte density;
@property (nonatomic, assign) Byte paperType;
@property (nonatomic, assign) uint16_t tphTmp;

- (instancetype)initWithData:(NSData *)data;

@end

/// 指令类
@interface PLCmdMTGenerator : NSObject

/**
 获取打印机信息
 2个字节状态 1个字节空闲 1个字节电池百分比 4个字节自动关机时间 1个浓度 1个纸张类型(1:A4) 2个温度
 */
+ (NSData *)getPrinterStatusInfo;

/** 获取碳带耗材品牌，字符串，以00结尾 */
+ (NSData *)getRibbonConsumablesBrandInfo;

/** 获取碳带剩余量，4个字节，int类型 单位mm */
+ (NSData *)getRibbonRemainCount;

/** 获取打印机序列号，字符串，以00结尾 */
+ (NSData *)getPrinterSerialNumber;

/** 获取打印机固件版本，字符串，以00结尾 */
+ (NSData *)getPrinterFirmwareVersion;

/** 获取打印浓度 */
+ (NSData *)getPrinterDensity;

/**
 设置打印浓度

 @param density 1 2 3
 */
+ (NSData *)setPrinterDensity:(Byte)density;

/** 获取关机时间 */
+ (NSData *)getPrinterShutdownTime;

/**
 设置关机时间

 @param time 关机时间
 */
+ (NSData *)setPrinterShutdownTime:(uint32_t)time;

/** 清除打印机缓存 */
+ (NSData *)clearPrinterBuffer;

/** 获取打印机型号 */
+ (NSData *)getPrinterName;

/**
 * 图片分包数组
 * @param data 图片数据 2336x3288
 * @param height 图片高度 3288
 */
+ (NSMutableArray<PLMT800BitmapSlice *> *)sliceImageBitmap:(NSData *)data height:(uint16_t)height;


/**
 * 图片分包数组(自定义算法)
 * @param data 算法处理后的图片数据，2336x3288
 * @param height 图片高度 3288
 * @param compress 图片是否要压缩,该版本暂不支持压缩
 * @param package 是否要分包，该版本暂不支持分包
 */
+ (NSMutableArray<PLMT800BitmapSlice *> *)customSliceImageBitmap:(NSData *)data
                                                          height:(uint16_t)height
                                                        compress:(PLBitmapCompressMode)compress
                                                         package:(BOOL)package;

/**
 * 封装好的固件数据
 * @param data 固件数据
 */
+ (NSData *)getFirmwareData:(NSData *)data;


/**
 设置纸张类型

 @param type 0~2: 0：连续纸 1：A4纸 2：黑标纸
 */
+ (NSData *)setPrinterPaper:(Byte)type;

@end

NS_ASSUME_NONNULL_END

