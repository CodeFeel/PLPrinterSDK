//
//  PLMT800Resolver.h
//  PLPrinterSDK
//
//  Created by ios on 2020/12/2.
//

#import <Foundation/Foundation.h>
#import "PLResolverCentral.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PLMT800CmdType) {
    PLMT800CmdTypePrinterInfo,              ///< 打印机信息
    PLMT800CmdTypeCarbonRibbonBrand,        ///< 碳带品牌
    PLMT800CmdTypeCarbonRibbonRemainCount,  ///< 碳带余量
    PLMT800CmdTypeSn,                       ///< 序列号
    PLMT800CmdTypeFirmwareVersion,          ///< 固件版本
    PLMT800CmdTypeClearBuffer,              ///< 清空缓存
    PLMT800CmdTypeAutoStatus,               ///< 自动回传状态
    PLMT800CmdTypeImageSliceAck,            ///< 图片分包ACK
    PLMT800CmdTypeFirmwareSliceAck,         ///< 固件分包ACK
    PLMT800CmdTypeCommonSet,                ///< 设置指令（浓度 关机时间指令 打印机型号）
    PLMT800CmdTypeCommonGet,                ///< 获取指令（浓度 关机时间指令 打印机型号）
    PLMT800CmdTypeAuthorizedKey,            ///< 授权key获取，暂用不上
    PLMT800CmdTypeAuthorizedRibbon,         ///< 授权里程，暂用不上
    PLMT800CmdTypeCarbonRibbonProperty,     ///< 碳带相关信息，暂用不上
    PLMT800CmdTypeNotResolvedData = 0xff,   ///< 失败
};

@interface PLMT800Resolver : PLCommonResolver

@end

@interface PLMT800ResolverModel : PLCommonResolveModel

@property (nonatomic, copy) NSString *_Nullable key;
@property (nonatomic, assign) PLMT800CmdType type;

@end


NS_ASSUME_NONNULL_END
