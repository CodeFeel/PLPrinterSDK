//
//  PLCmdBBJGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PLBitmapManager.h"

NS_ASSUME_NONNULL_BEGIN

/// 打印机信息
@interface PLBBJDeviceInfo : NSObject

@property (nonatomic, copy) NSString *deviceName;
@property (nonatomic, copy) NSString *mode;
@property (nonatomic, copy) NSString *sn;
@property (nonatomic, copy) NSString *firmware_version;
@property (nonatomic, copy) NSString *hardware_version;
@property (nonatomic, copy) NSString *bleName;
@property (nonatomic, copy) NSString *ble_version;
@property (nonatomic, copy) NSString *mac;
@property (nonatomic, copy) NSString *pin;

- (instancetype)initWithData:(NSData *)data;

@end

@interface PLCmdBBJGenerator : NSObject

/** 打印自检页 */
+ (NSData *)printSelfPage;

/**
 获取打印机信息
 返回数据格式：
 设备名 ： 32 byte
 设备模式 ： 24 byte
 SN号 ： 32 byte
 固件版本 ： 3~4 byte
 硬件版本 ： 3 byte
 蓝牙名称 ： 18 byte
 蓝牙固件版本 ： 12 byte
 蓝牙mac地址 ： 12 byte
 蓝牙PIN ： 4 byte
 + END
 */
+ (NSData *)getPrinterInfo;

/** 设置纸张学习指令,该指令在合盖无纸张的情况下调用 */
+ (NSData *)setPaperLearn;

/** 获取打印机机型名称 */
+ (NSData *)getPrinterModelName;

/**
 * 修改打印机名称
 * @param printerName 长度小于32
 */
+ (NSData *)setPrinterName:(NSString *)printerName;

/**  获取打印机固件版本号 */
+ (NSData *)getPrinterFirmwareVersion;

/** 获取打印机的SN号 */
+ (NSData *)getPrinterSN;

/** 获取纸张类型 0->连续纸  1->标签纸 */
+ (NSData *)getPrinterPaperType;

/**
 * 设置纸张类型 暂时无法设置 默认就是连续纸
 * @param type 0->连续纸  2->标签纸
 */
+ (NSData *)setPrinterPaperType:(Byte)type;

/** 获取设备休眠时间，单位分钟 */
+ (NSData *)getPrinterSleepTime;

/**
 * 设置设备休眠时间
 * @param time 单位分钟 , 0,10,20,30,40,50,60
 */
+ (NSData *)setPrinterSleepTime:(uint32_t)time;

/** 获取设备关机时间，单位：分钟 */
+ (NSData *)getPrinterShutdownTime;

/**
 * 设置关机时间
 * @param time 单位分钟  0,60,120,180,240,300,360
 */
+ (NSData *)setPrinterShutdownTime:(uint32_t)time;

/** 获取打印机浓度 0-2 */
+ (NSData *)getPrinterDensity;

/**
 * 设置打印机浓度
 * @param density 0-2
 */
+ (NSData *)setPrinterDensity:(Byte)density;

/** 获取电量 */
+ (NSData *)getPrinterBattery;

/**
 * 设置滚动文字
 * @param textArray 字符串数组,数组个数小于10，每条文字的长度不能超过32
 */
+ (NSData *)setScrollingTextForPrinterWithTextArray:(NSArray <NSString *> *)textArray;

/** 删除打印机上的滚动文字 */
+ (NSData *)removeScrollingTextAtScreen;

/**
 * 打印位图
 * @param image 图片
 * @param mode 效果
 * @param compress 选LZO压缩
 * @param package 是否分包，不分包 传NO
 * @param copies 打印份数
 * @return data 如果data大小为nil，则说明图片太大
 */
+ (NSData *)appendBitmapDataWithImage:(UIImage *)image
                                 mode:(PLBitmapMode)mode
                             compress:(PLBitmapCompressMode)compress
                              package:(BOOL)package
                               copies:(Byte)copies;

/**
 * 自定义位图打印(自定义算法)
 * @param data 算法处理后的图片数据
 * @param imageWidth 图片宽度
 * @param copies 打印份数
 * @return data 如果data大小为nil，则说明图片太大
 */
+ (NSData *)customImageWithBinaryData:(NSData *)data
                           imageWidth:(NSInteger)imageWidth
                               copies:(Byte)copies;

/**
 * 储存图片到打印机缓存区
 * @param image 图片
 * @param mode 效果
 * @param compress 选LZO压缩
 * @return data 如果data大小为nil，则说明图片太大
 */
+ (NSData *)storageImageToPrinterBufferWithImage:(UIImage *)image
                                            mode:(PLBitmapMode)mode
                                        compress:(PLBitmapCompressMode)compress;

/**
 * 自定义存储位图(自定义算法)
 * @param data 算法处理后的图片数据
 * @param imageWidth 图片宽度
 * @return data 如果data大小为nil，则说明图片太大
 */
+ (NSData *)customStorageImageToCacheWithData:(NSData *)data
                                   imageWidth:(NSInteger)imageWidth;



@end

NS_ASSUME_NONNULL_END
