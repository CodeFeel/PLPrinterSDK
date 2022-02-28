//
//  PLCmdPoooliGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>
#import "PLEnumList.h"

NS_ASSUME_NONNULL_BEGIN

/// 打印机信息
@interface PLDeviceInfo : NSObject

@property (nonatomic, copy) NSString *modelSeries;
@property (nonatomic, copy) NSString *deviceName;
@property (nonatomic, copy) NSString *sn;
@property (nonatomic, copy) NSString *firmware_version;
@property (nonatomic, copy) NSString *hardware_version;
@property (nonatomic, copy) NSString *bleName;
@property (nonatomic, copy) NSString *ble_version;
@property (nonatomic, copy) NSString *mac;
@property (nonatomic, copy) NSString *pin;

- (instancetype)initWithData:(NSData *)data;

@end

/// 状态信息
@interface PLDeviceStateInfo : NSObject

@property (nonatomic, assign) PLPoooliPrinterStatus state;
@property (nonatomic, assign) BOOL idle;
@property (nonatomic, assign) Byte electricity;
@property (nonatomic, assign) uint16_t shutdownTime;
@property (nonatomic, assign) Byte density;
@property (nonatomic, assign) Byte paperType;
@property (nonatomic, assign) Byte ledType;
@property (nonatomic, assign) Byte red;
@property (nonatomic, assign) Byte green;
@property (nonatomic, assign) Byte blue;
@property (nonatomic, assign) uint16_t tphTmp;

- (instancetype)initWithData:(NSData *)data;

@end


@interface PLCmdPoooliGenerator : NSObject

/** 获取打印机信息 */
+ (NSData *)getPrinterInfo;

/** 获取状态信息 */
+ (NSData *)getPrinterStatusInfo;

/** 恢复出厂设置 */
+ (NSData *)resetPrinterFactory;

/** 打印自检页 */
+ (NSData *)printSelfCheckingPage;

/** 打印模块 */
+ (NSData *)printModule;

/** 打印黑块 */
+ (NSData *)printBlackPiece;

/** 打印斜线 */
+ (NSData *)printSlash;

/** 设置浓度 0-99 */
+ (NSData *)setPrinterDensity:(Byte)density;

/** 设置关机时间 */
+ (NSData *)setPrinterShutdownTime:(uint32_t)time;

/** 设置纸张类型 0->连续纸  1->标签纸 */
+ (NSData *)setPrinterPaperType:(Byte)type;

/** 设置走纸 1行 == 0.125mm */
+ (NSData *)setFeedLine:(uint16_t)line;

/**
 * 设置LED颜色类型
 * @param type 0~5：GREEN,BLUE,RED,YELLOW,PINK,All
 */
+ (NSData *)setPrinterLEDColorWithType:(Byte)type;

/**
 * 自定义LED颜色
 * @param red 0-100
 * @param green 0-100
 * @param blue 0-100
 */
+ (NSData *)setPrinterLEDBrightnessWithRed:(Byte)red green:(Byte)green blue:(Byte)blue;

/**
 * 走纸定位指令，一般用于打印完数据后定位缝标，在标签纸打印的时候使用，可拼接在图片数据的结尾
 * @param line 1行高度为0.125mm,注：如果传0的话直接定位到下个缝标
 */
+ (NSData *)setPrinterPositionForLabelPaperWithLine:(uint16_t)line;

/** 设置打印速度 */
+ (NSData *)setPrinterSpeed:(Byte)speed;

/** 设置纸张宽度 648 912 1248 */
+ (NSData *)setPrinterPrintWidthForL3:(uint16_t)width;


/**
 * 生成机器识别的高清数据
 * @param data 数据
 * @param imageWidth 图片实际宽度
 */
+ (NSData *)appendGrayHDImageBitmap:(NSData *)data imageWidth:(NSInteger)imageWidth;

/**
 * 生成机器识别的高清数据,256阶数据(自定义算法)
 * @param data 256阶图片数据(算法处理后的图片数据,图片高度不能超过5000)
 * @param imageWidth 图片实际宽度
 */
+ (NSData *)customGrayImageWith256LevelData:(NSData *)data imageWidth:(NSInteger)imageWidth;

/**
 * 生成机器识别的高清数据，16阶数据(自定义算法)
 * @param data 16阶图片数据(算法处理后的图片数据,图片高度不能超过5000)
 * @param imageWidth 图片实际宽度
 */
+ (NSData *)customGrayImageWith16LevelData:(NSData *)data imageWith:(NSInteger)imageWidth;

/**
 * 生成机器识别的(二值、抖动)数据(自定义算法)
 * @param data 算法处理后的图片数据
 * @param imageWidth 图片实际宽度
 */
+ (NSData *)customImageWithBinaryData:(NSData *)data imageWidth:(NSInteger)imageWidth;


/// 纸张学习
+ (NSData *)devicePaperLearn;

/**
 *  设置对齐方式 0 1 2
 *  @param position
 */
+ (NSData *)setJustification:(NSInteger)position;

/** 清除打印机缓存 */
+ (NSData *)clearPrinterBuffer;

@end

NS_ASSUME_NONNULL_END




