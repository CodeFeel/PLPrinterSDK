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
    /// MFI
    PLConnectModeMFI        = 2,
};

typedef NS_ENUM(NSInteger, PLBluetoothState) {
    /// 未授权，请前往系统设置授权
    PLBluetoothStateUnauthorized  = 0,
    /// 蓝牙未开
    PLBluetoothStatePoweredOff  = 1,
    /// 正常
    PLBluetoothStatePoweredOn  = 2,
};

/// 连接错误类型
typedef NS_ENUM(NSUInteger,PLConnectError){
    PLConnectErrorTimeout = 0,
    PLConnectErrorNoAccessory,
    PLConnectErrorNoPeripheral,
    PLConnectErrorValidateTimeout,
    PLConnectErrorUnknownDevice,
    PLConnectErrorSystemFailed,
    PLConnectErrorValidateFailed,
    PLConnectErrorCodeCheckFailed
};

typedef void(^PLAccessoryPickerCompletion)(NSError *error);

#pragma mark - 打印机属性类
@interface PLPrinterMessage : NSObject

@property (nonatomic, copy) NSString        *name;  ///< 外设的唯一标识符
@property (nonatomic, copy) NSString        *mac;   ///< mfi和ble的可能不一样
@property (nonatomic, copy) NSString        *identifier; ///< 外设的唯一标识符
@property (nonatomic, strong) NSNumber      *distance;  ///< 距离
@property (nonatomic, strong) EAAccessory   *accessory; ///< mfi连接对象
@property (nonatomic, strong) CBPeripheral  *peripheral; ///< ble连接对象
@property (nonatomic, assign) PLConnectMode  mode;      ///< 连接类型

@end

#pragma mark - 蓝牙连接协议
@protocol PLPrinterInterfaceDelegate <NSObject>

@optional
/** BLE:发现附近蓝牙设备 */
- (void)didDiscoverBLEPrints:(NSArray<PLPrinterMessage *> *)devices;

/** MFI:发现附近配件 */
- (void)didDiscoverMFIPrints:(NSArray<PLPrinterMessage *> *)devices;

/** 连接失败 */
- (void)didConnectFail:(NSError *)error;

/** 连接成功 */
- (void)didConnectSuccess;

/** 断开连接 */
- (void)didDisconnect;

/** 监听系统设置有配件连接，注册mfi通知后才会回调 */
- (void)observerAccessoryDidConnectedNotification:(PLPrinterMessage *)device;

/** 监听系统设置有配件断开，注册mfi通知后才会回调 */
- (void)observerAccessoryDidDisconnectNotification:(PLPrinterMessage *)device;

@end

@interface PLConnectInterface : NSObject

@property (nonatomic, weak) id<PLPrinterInterfaceDelegate>  delegate;           ///< 协议
@property (nonatomic, assign) BOOL                          isConnected;        ///< 是否连接
@property (nonatomic, strong) PLPrinterMessage              *deviceConnected;   ///< 是否连接，连接后对象不为nil
@property (nonatomic, assign) PLConnectMode                 mode;               ///< 连接方式 ble还是mfi

/** 单例对象 */
+ (PLConnectInterface *)shared;

/** 开启扫描 ble */
- (void)scanBluetooth;

/** 开启扫描 mfi */
- (void)scanAccessory;

/** 停止扫描，连接成功会自动停止扫描 */
- (void)stopScanBluetooth;

/**
 * 连接打印机
 * @param printer 外设对象(请使用mfi搜索到的外设对象连接，ble只是快速搜索展示，无法用于连接)
 */
- (void)connectPrinter:(PLPrinterMessage *)printer;

/** 断开打印机 */
- (void)disconnect;

/** 获取手机的蓝牙状态 */
- (PLBluetoothState)getBluetoothStatus;

/** 注册MFI通知 */
- (void)registerEAAccessoryManagerNotifications;

/** 移除MFI通知 */
- (void)removeEAAccessoryManagerNotifications;

/** 展示可连接的配件列表，该方法会弹出连接窗口 */
- (void)showBluetoothAccessorys:(NSString *)name completion:(PLAccessoryPickerCompletion)completion;

@end
