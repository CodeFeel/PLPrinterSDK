//
//  PLBitmapManager.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/// MT800位图模型
@interface PLMT800BitmapSlice : NSObject

@property (nonatomic, assign) uint16_t serial;
@property (nonatomic, strong) NSData *data;

@end

/// Poooli位图模型
@interface PLBitmapSlice : NSObject

@property (nonatomic, assign) uint16_t serial; ///< 包序号
@property (nonatomic, strong) NSData *data; ///< 包数据

@end

typedef NS_ENUM(NSInteger,PLBitmapCompressMode) {
    ///图片不压缩
    PLBitmapCompressModeNone = 0,
    ///图片压缩
    PLBitmapCompressModeLZO = 48
};

typedef NS_ENUM(NSInteger, PLBitmapMode) {
    /// 黑白图片，二值算法
    PLBitmapModeBinary = 0,
    /// 扩散抖动算法
    PLBitmapModeDithering = 1,
    /// 聚集抖动
    PLBitmapModeCluster = 2,
    /// 灰阶算法
    PLBitmapModeGray = 3
};

@interface PLBitmapManager : NSObject

/// 生成二值抖动图片数据
/// @param image 图片
/// @param watermark 是否增加水印
/// @param mode 图片效果，这边如果选择灰阶模式，那么则默认SDK处理图片
/// @param compress 压缩模式
/// @param package 是否需要分包，一般都需要分包
+ (NSData *)generateGenralDataWithImage:(UIImage *)image watermark:(BOOL)watermark mode:(PLBitmapMode)mode compress:(PLBitmapCompressMode)compress package:(BOOL)package;


/// 灰阶高清数据，PLCmdPoooliGenerator再调用appendGrayHDImageBitmap
/// @param image 图片，图片高度不能超过5000
/// @param watermark 是否需要增加水印
/// @param gamma 伽码系数，调节明暗度
/// @param factor 锐化程度，默认14，取值1-20，值越大锐化程度越低
/// @param gammaType 是否需要调节伽马系数，YES表示需要，NO表示不需要，200dpi的机型建议选择NO
+ (NSData *)generateHDDataWithImage:(UIImage *)image watermark:(BOOL)watermark fGamma:(CGFloat)gamma factor:(NSInteger)factor gammaType:(BOOL)gammaType;


/// 预览图
/// @param image 原图图片
/// @param mode 预览的图片模式
/// @param gamma 伽码系数，调节明暗度,范围：0.6-2.4，默认值1.2，只对灰阶图起作用
/// @param gammaType 是否需要调节伽马系数，YES表示需要，NO表示不需要，只对灰阶图起作用
+ (UIImage *)generateRenderingWithImage:(UIImage *)image mode:(PLBitmapMode)mode fGamma:(CGFloat)gamma gammaType:(BOOL)gammaType;


/// 生成位图数据(该数据需要指令类的对应接口再处理，不可直接下发)
/// @param image 图片
/// @param watermark 是否增加白色水印
/// @param mode 图片效果
+ (NSData *)generateBitmapDataWithImage:(UIImage *)image watermark:(BOOL)watermark mode:(PLBitmapMode)mode;

/// 锐化后的图片
/// @param image 原图图片
+ (UIImage *)imageToSharpen:(UIImage *)image;


/// 生成透明图片
/// @param image 原图图片
+ (UIImage *)imageToTransparent:(UIImage *)image;


/// 自定义阈值的黑白图数据
+ (NSData *)printableBinaryData:(UIImage *)image threshold:(Byte)threshold compress:(PLBitmapCompressMode)compress;


@end

NS_ASSUME_NONNULL_END








