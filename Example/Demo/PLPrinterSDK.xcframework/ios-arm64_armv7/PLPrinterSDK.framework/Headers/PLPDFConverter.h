//
//  PLPDFConverter.h
//  PLPrinterSDK
//
//  Created by ios on 2021/8/30.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface PLPDFConverter : NSObject

/// 页数
@property (nonatomic, assign, readonly) NSInteger pageCount;

/// 初始化文件路径
/// @param path 文件路径
/// @param autoRotate 是否需要自动旋转，false表示不用旋转，true表示要自动旋转
- (instancetype)initWithPath:(NSURL *)path autoRotate:(BOOL)autoRotate;

/// 将某页PDF转图片
/// @param index 下标
/// @param size 图片大小
- (UIImage * _Nullable)imageAtIndex:(NSInteger)index size:(CGSize)size;

@end

NS_ASSUME_NONNULL_END
