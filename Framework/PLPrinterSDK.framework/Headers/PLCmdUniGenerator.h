//
//  PLCmdUniGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2021/1/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PLFirmwareSlice : NSObject

@property (nonatomic, assign) uint32_t offset;
@property (nonatomic, strong) NSData *data;

@end

/// wifi安全加密协议方式
typedef NS_ENUM (NSUInteger, PTWiFiAuthMode) {
    PTWiFiAuthModeOPEN         = 0,
    PTWiFiAuthModeWEP,
    PTWiFiAuthModeWPA2_PSK,
    PTWiFiAuthModeWPA_WPA2_PSK,
    PTWiFiAuthModeWPA_PSK,
    PTWiFiAuthModeWPA,
    PTWiFiAuthModeWPA2,
    PTWiFiAuthModeSAE,
    PTWiFiAuthModeUNKNOW
};

@interface PLCmdUniGenerator : NSObject

/////////////////////////////////////////////////////////////////////
/***************** 机型和版本 SN接口 *******************/
/////////////////////////////////////////////////////////////////////
///
/// 获取打印机型号,回的数据格式：51333142 5400，最后一个字节00前面的是有效数据
+ (NSData *)getPrinterModelName;

/// 获取打印机固件版本号,版本号返回格式为 X.XX.XX或X.X.X【如1.01.01或1.0.3】
+ (NSData *)getPrinterFirmwareVersion;

/// 获取SN
+ (NSData *)getPrinterSerialNumber;

/////////////////////////////////////////////////////////////////////
/***************** wifi 配网接口 *******************/
/////////////////////////////////////////////////////////////////////

/// 0:STA 1:AP
+ (NSData *)setPrinterWifiMode:(NSInteger)mode;

/// 设置ssid,ssid
+ (NSData *)setPrinterWifiSSID:(NSString *)ssid;

/// 设置ip
+ (NSData *)setPrinterWifiIP:(NSString *)ip;

/// 设置pwd
+ (NSData *)setPrinterWifiPassword:(NSString *)pwd;

/// 设置wifi安全加密协议方式
+ (NSData *)setPrinterWifiAuth:(PTWiFiAuthMode)mode;

/// wifi重新配置并开启UDP广播,该条指令等上面四条指令发送完后再发送这条指令
+ (NSData *)configureWifi;

/// 获取wifi信息
+ (NSData *)getPrinterWifiInfo;

/////////////////////////////////////////////////////////////////////
/***************** 固件升级 *******************/
/////////////////////////////////////////////////////////////////////

+ (NSMutableArray<PLFirmwareSlice *> *)generateFirmwarePacksWithData:(NSData *)data;


@end

NS_ASSUME_NONNULL_END
