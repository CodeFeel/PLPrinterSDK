//
//  PLConnectInterface.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef NS_ENUM(NSInteger, PLConnectMode) {
    /// 未知类型
    PLConnectModeUnconnect  = 0,
    /// BLE
    PLConnectModeBLE        = 1,
};

typedef NS_ENUM(NSInteger, PLBluetoothState) {
    PLBluetoothStateUnknown = 0,
    /// 未授权，请前往系统设置授权
    PLBluetoothStateUnauthorized  = 1,
    /// 蓝牙未开
    PLBluetoothStatePoweredOff  = 2,
    /// 正常
    PLBluetoothStatePoweredOn  = 3,
};

/// 连接错误类型
typedef NS_ENUM(NSUInteger,PLConnectError){
    PLConnectErrorTimeout = 0,
    PLConnectErrorNoPeripheral,
    PLConnectErrorValidateTimeout,
    PLConnectErrorUnknownDevice,
    PLConnectErrorSystemFailed,
    PLConnectErrorValidateFailed,
    PLConnectErrorCodeCheckFailed,
};

typedef void(^PLAccessoryPickerCompletion)(NSError *error);

#pragma mark - 打印机属性类
@interface PLPrinterMessage : NSObject

@property (nonatomic, copy) NSString        *name;          ///< 外设的唯一标识符
@property (nonatomic, copy) NSString        *mac;           ///< mfi和ble的可能不一样
@property (nonatomic, copy) NSString        *identifier;    ///< 外设的唯一标识符
@property (nonatomic, strong) NSNumber      *distance;      ///< 距离
@property (nonatomic, strong) CBPeripheral  *peripheral;    ///< ble连接对象
@property (nonatomic, assign) PLConnectMode  mode;          ///< 连接类型

@end

#pragma mark - 蓝牙连接协议
@protocol PLPrinterInterfaceDelegate <NSObject>

@optional
/** BLE:发现附近蓝牙设备 */
- (void)didDiscoverBLEPrints:(NSArray<PLPrinterMessage *> *)devices;

/** 连接失败 */
- (void)didConnectFail:(NSError *)error;

/** 连接成功 */
- (void)didConnectSuccess;

/** 断开连接 */
- (void)didDisconnect:(BOOL)active;

@end

@interface PLConnectInterface : NSObject

@property (nonatomic, weak) id<PLPrinterInterfaceDelegate>  delegate;           ///< 协议
@property (nonatomic, assign) BOOL                          isConnected;        ///< 是否连接
@property (nonatomic, strong) PLPrinterMessage              *deviceConnected;   ///< 是否连接，连接后对象不为nil
@property (nonatomic, assign) PLConnectMode                 mode;               ///< 连接方式

/** 单例对象 */
+ (PLConnectInterface *)shared;

/** 开启扫描 ble */
- (void)scanBluetooth;

/** 停止扫描，连接成功会自动停止扫描 */
- (void)stopScanBluetooth;

/**
 * 连接打印机
 * @param printer 外设对象
 */
- (void)connectPrinter:(PLPrinterMessage *)printer;

- (void)connectDeviceWithIdentifier:(NSString *)identifier;

/** 断开打印机 */
- (void)disconnect;

- (void)cancelConnect;

/** 获取手机的蓝牙状态 */
- (PLBluetoothState)getBluetoothStatus;

@end
