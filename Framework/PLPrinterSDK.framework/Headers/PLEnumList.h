//
//  PLEnumList.h
//  PLPrinterSDK
//
//  Created by ios on 2020/12/3.
//

#ifndef PLEnumList_h
#define PLEnumList_h

/// 设置指令返回状态
typedef NS_ENUM(uint16_t, PLPoooliSetStatus) {
    PLPoooliSetStatusOK = 0x4b4f,
    PLPoooliSetStatusFailed = 0x4f4e,
};

typedef NS_OPTIONS(uint16_t, PLPoooliPrinterStatus) {
    /// 正常
    PLPoooliPrinterStatusOK     = 0,
    /// 缺纸
    PLPoooliPrinterStatusOutOfPaper = 1 << 0,
    /// 高温
    PLPoooliPrinterStatusHighTmp    = 1 << 1,
    /// 低温
    PLPoooliPrinterStatusLowTmp     = 1 << 2,
    /// 低电量
    PLPoooliPrinterStatusLowVoltage = 1 << 3,
    /// 未关闭纸舱盖
    PLPoooliPrinterStatusHeadOpened = 1 << 4,
    /// 电压过低，将关机
    PLPoooliPrinterStatusShutdown = 1 << 5,
    /// 定位失败
    PLPoooliPrinterStatusPositionFail = 1 << 6
};

typedef NS_ENUM(NSInteger, PLPoooliImageCompleteStatus) {
    PLPoooliImageCompleteStatusSuccesss = 0
};

/// 判断设置和读取指令
typedef NS_ENUM(uint16_t, PLMT800CommonCmdKey) {
    PLMT800CommonCmdKeyShutdownTime = 0x191,    ///< 关机时间
    PLMT800CommonCmdKeyPrintDensity = 0xcb,     ///< 打印机浓度
    PLMT800CommonCmdKeyPrinterName = 0x4,       ///< 打印机型号
};

typedef NS_OPTIONS(uint16_t, PLMT800PrinterStatus) {
    PLMT800PrinterStatusOK = 0,
    PLMT800PrinterStatusPaperAbsent = 1 << 0,///缺纸
    PLMT800PrinterStatusHighTemperature = 1 << 1,///高温
    PLMT800PrinterStatusLowTemperature = 1 << 2,///低温
    PLMT800PrinterStatusLowVoltage = 1 << 3,///低电量
    PLMT800PrinterStatusHeadOpened = 1 << 4,///开盖
    PLMT800PrinterStatusCarbonRibbonEnd = 1 << 5,///碳带用尽
    PLMT800PrinterStatusPaperSmashe = 1 << 6,///纸装歪
    PLMT800PrinterStatusCarbonRibbonNotAuthorization = 1 << 7,///碳带未授权
    PLMT800PrinterStatusBufferFull = 1 << 8,///缓存已满
//    PLMT800PrinterStatusNoMileage = 1 << 9,///里程不足
};


#endif /* PLEnumList_h */
