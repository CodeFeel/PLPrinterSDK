//
//  PLCmdESCGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2021/1/5.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PLBitmapManager.h"

NS_ASSUME_NONNULL_BEGIN

@interface PLCmdESCGenerator : NSObject

/// 自检，打印打印机信息.
+ (NSData *)printSelfTest;

/// 获取打印机状态.
+ (NSData *)getPrinterStatus;

/// 标签学习功能
+ (NSData *)setLabelLearn;

/// 打印并走纸一行.
+ (NSData *)printAndLineFeed;

/// 打印并向前走纸.
/// @param lines 走纸行数
+ (NSData *)printAndFeedLines:(NSInteger)lines;

/// 初始化打印机.
+ (NSData *)initializePrinter;

/// 打印图片
/// @param image 原图
/// @param mode 图片效果
/// @param compress 压缩模式，LZO：压缩；None：不压缩
/// @param package 是否分包，压缩的时候一般要分包
+ (NSData *)appendRasterImage:(UIImage *)image mode:(PLBitmapMode)mode compress:(PLBitmapCompressMode)compress package:(BOOL)package;

/// 设置对齐方式.
/// @param justification 0：居左  1:居中  2:居右
+ (NSData *)setJustification:(NSInteger)justification;

/// 设置打印速度.
/// @param speed 打印速度(0~11)
+ (NSData *)setSpeed:(NSInteger)speed;

/// 设置打印浓度.
/// @param density 打印浓度(0~3)
+ (NSData *)setDensity:(NSInteger)density;

/// 设置标准模式.
+ (NSData *)setStandardMode;

/// 设置左边空白宽度(行模式).
/// @param left 距离
+ (NSData *)setLeftMargin:(NSInteger)left;

/// 设置打印区域宽度(行模式)
/// @param width 宽度
+ (NSData *)setPrintAreaWidth:(NSInteger)width;

/// 设置页模式.
+ (NSData *)setPageMode;

/// 在页模式下设置打印区域
/// @param xPos 横向开始点
/// @param yPos 纵向开始点
/// @param width 指定区域宽度
/// @param height 指定区域高度
+ (NSData *)pageSetPrintAreaWithXPos:(NSInteger)xPos yPos:(NSInteger)yPos width:(NSInteger)width height:(NSInteger)height;

/// 在页模式下设置打印方向.
/// @param direction 0：从左到右  1:下到上  2:右到左 3：上到下
+ (NSData *)pageSetPrintDirection:(NSInteger)direction;

/// 在页模式下设置水平运动单位.
/// @param position 运动单位
+ (NSData *)setAbsolutePosition:(NSInteger)position;

/// 在页模式下设置垂直运动单位.
/// @param yPos 运动单位
+ (NSData *)pageSetAbsoluteYPos:(NSInteger)yPos;

/// 设置相对打印位置.
/// @param position 运动单位
+ (NSData *)setRelativePosition:(NSInteger)position;

/// 在页模式下设置相对垂直打印位置.
/// @param yPos 运动单位
+ (NSData *)pageSetRelativeYPos:(NSInteger)yPos;

/// 打印并回到标准模式.
+ (NSData *)printAndReturnStandardMode;

/// 在页面模式下取消打印数据.
+ (NSData *)cancelPrint;

/// 清除缓存.
+ (NSData *)clearBuffer;

/// 定位到下个缝标，行模式下使用
+ (NSData *)feedToNextLabelForLineMode;

/// 定位到下个缝标，页模式下使用
+ (NSData *)feedToNextLabelForPageMode;

/// 在页模式下打印数据
+ (NSData *)printDataInPageMode;

/// 获取打印机的速率
+ (NSData *)getPrintSpeed;

/// 更改打印机的打印速率
/// @param speed 0-40
+ (NSData *)changePrintSpeed:(NSInteger)speed;

@end

NS_ASSUME_NONNULL_END
