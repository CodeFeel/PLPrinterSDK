//
//  PLCmdCPCLGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2021/1/5.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PLBitmapManager.h"

NS_ASSUME_NONNULL_BEGIN

/// rfid存储区域
typedef NS_ENUM(NSUInteger, PTRFIDMemory) {
    PTRFIDMemoryReserved = 0,     /// 保留区, 起始地址 + length <= 4 (length指的是数据长度的一半,下同)
    PTRFIDMemoryEPC = 1,         /// EPC, 起始地址 >= 2 且 起始地址 + length <= 8
    PTRFIDMemoryTID = 2,         /// TID,只读区域, 起始地址 + length <= 6
    PTRFIDMemoryUser = 3         /// 用户区, 起始地址 + length < 128
};

@interface PTRFIDInfoSlice : NSObject

@property (nonatomic, copy) NSString *_Nonnull content;
@property (nonatomic, assign) PTRFIDMemory memory;
@property (nonatomic, assign) NSUInteger startAddr;

@end

/*!
 *  \~chinese
 *  纸张类型
 *
 *  \~english
 *  Paper type
 */
typedef NS_ENUM(NSUInteger, PTCPCLPaperType) {
    PTCPCLPaperContinuoue          = 0,  ///< continuous paper
    PTCPCLPaperLabel               = 1,  ///< label paper
    PTCPCLPaperBackBlackMark       = 2,  ///< back black mark
    PTCPCLPaperFrontBlackMark      = 3,  ///< front black mark
    PTCPCLPaperBlackMarkInch3      = 4,  ///< 3 inch black mark
    PTCPCLPaperBlackMarkInch2      = 5   ///< 2 inch black mark
};

/*!
 *  \~chinese
 *  标签分辨率
 *
 *  \~english
 *  Label resolution
 */
typedef NS_ENUM(NSUInteger, PTCPCLLabelResolution) {
    PTCPCLLabelResolution100   = 100,  ///< 100
    PTCPCLLabelResolution200   = 200   ///< 200
};

/*!
 *  \~chinese
 *  条码类型
 *
 *  \~english
 *  Barcode style
 */
typedef NS_ENUM(NSUInteger, PTCPCLBarcodeStyle) {
    PTCPCLBarcodeStyleUPCA      = 0,
    PTCPCLBarcodeStyleUPCE      = 1,
    PTCPCLBarcodeStyleEAN13     = 2,
    PTCPCLBarcodeStyleEAN8      = 3,
    PTCPCLBarcodeStyleCode39    = 4,
    PTCPCLBarcodeStyleCode93    = 5,
    PTCPCLBarcodeStyleCode128   = 6,
    PTCPCLBarcodeStyleCodeBAR   = 7
};

/*!
 *  \~chinese
 *  条码宽窄条比例
 *
 *  \~english
 *  The ratio of wide to narrow bars
 */
typedef NS_ENUM(NSUInteger, PTCPCLBarcodeBarRatio) {
    PTCPCLBarcodeBarRatio0     = 0,
    PTCPCLBarcodeBarRatio1     = 1,
    PTCPCLBarcodeBarRatio2     = 2,
    PTCPCLBarcodeBarRatio3     = 3,
    PTCPCLBarcodeBarRatio4     = 4,
    PTCPCLBarcodeBarRatio20    = 20,
    PTCPCLBarcodeBarRatio21    = 21,
    PTCPCLBarcodeBarRatio22    = 22,
    PTCPCLBarcodeBarRatio23    = 23,
    PTCPCLBarcodeBarRatio24    = 24,
    PTCPCLBarcodeBarRatio25    = 25,
    PTCPCLBarcodeBarRatio26    = 26,
    PTCPCLBarcodeBarRatio27    = 27,
    PTCPCLBarcodeBarRatio28    = 28,
    PTCPCLBarcodeBarRatio29    = 29,
    PTCPCLBarcodeBarRatio30    = 30
};

/*!
 *  \~chinese
 *  规范编号
 *
 *  \~english
 *  QRCode model number
 */
typedef NS_ENUM(NSUInteger, PTCPCLQRCodeModel) {
    PTCPCLQRCodeModel1      = 1,
    PTCPCLQRCodeModel2      = 2   ///< default
};

/*!
 *  \~chinese
 *  二维码单元宽度
 *
 *  \~english
 *  Unit-width of the barcode in dots. 1-32,default: 6
 */
typedef NS_ENUM(NSUInteger, PTCPCLQRCodeUnitWidth) {
    PTCPCLQRCodeUnitWidth_1 = 1,
    PTCPCLQRCodeUnitWidth_2,
    PTCPCLQRCodeUnitWidth_3,
    PTCPCLQRCodeUnitWidth_4,
    PTCPCLQRCodeUnitWidth_5,
    PTCPCLQRCodeUnitWidth_6,        ///< default
    PTCPCLQRCodeUnitWidth_7,
    PTCPCLQRCodeUnitWidth_8,
    PTCPCLQRCodeUnitWidth_9,
    PTCPCLQRCodeUnitWidth_10,
    PTCPCLQRCodeUnitWidth_11,
    PTCPCLQRCodeUnitWidth_12,
    PTCPCLQRCodeUnitWidth_13,
    PTCPCLQRCodeUnitWidth_14,
    PTCPCLQRCodeUnitWidth_15,
    PTCPCLQRCodeUnitWidth_16,
    PTCPCLQRCodeUnitWidth_17,
    PTCPCLQRCodeUnitWidth_18,
    PTCPCLQRCodeUnitWidth_19,
    PTCPCLQRCodeUnitWidth_20,
    PTCPCLQRCodeUnitWidth_21,
    PTCPCLQRCodeUnitWidth_22,
    PTCPCLQRCodeUnitWidth_23,
    PTCPCLQRCodeUnitWidth_24,
    PTCPCLQRCodeUnitWidth_25,
    PTCPCLQRCodeUnitWidth_26,
    PTCPCLQRCodeUnitWidth_27,
    PTCPCLQRCodeUnitWidth_28,
    PTCPCLQRCodeUnitWidth_29,
    PTCPCLQRCodeUnitWidth_30,
    PTCPCLQRCodeUnitWidth_31,
    PTCPCLQRCodeUnitWidth_32
};

/*!
 *  \~chinese
 *  二维码纠错水平
 *
 *  \~english
 *  QRCode Error Correction Level
 */
typedef NS_ENUM(NSUInteger, PTCPCLQRCodeCorrectionLevel) {
    PTCPCLQRCodeCorrectionLevelH      = 0,  ///< Ultra high reliability level
    PTCPCLQRCodeCorrectionLevelQ      = 1,  ///< High reliability level
    PTCPCLQRCodeCorrectionLevelM      = 2,  ///< Standard level
    PTCPCLQRCodeCorrectionLevelL      = 3 ///< High density level
};

/*!
 *  \~chinese
 *  二维码字符类型
 *
 *  \~english
 *  QRCode Character mode symbols
 */
typedef NS_ENUM(NSUInteger, PTCPCLQRCodeDataInputMode) {
    PTCPCLQRCodeDataInputModeA      = 0,  ///< Automatic(default)
    PTCPCLQRCodeDataInputModeM      = 1  ///< manual
};

/*!
 *  \~chinese
 *  文本字体名称
 *
 *  \~english
 *  Text Font Name
 */
typedef NS_ENUM(NSUInteger, PTCPCLTextFontName) {
    PTCPCLTextFont1       = 1,  ///< chinese:24x24   english:9x17
    PTCPCLTextFont2       = 2,  ///< chinese:24x24   english:12x24
    PTCPCLTextFont3       = 3,  ///< chinese:20x20   english:10x20
    PTCPCLTextFont4       = 4,  ///< chinese:32x32   english:16x32
    PTCPCLTextFont5       = 5,  ///< chinese:24x24   english:12x24
    PTCPCLTextFont7       = 7,  ///< chinese:24x24   english:12x24
    PTCPCLTextFont8       = 8,  ///< chinese:24x24   english:12x24
    PTCPCLTextFont20      = 20, ///< chinese:16x16   english:8x16
    PTCPCLTextFont28      = 28, ///< chinese:28x28   english:14x28
    PTCPCLTextFont55      = 55 ///< chinese:16x16   english:8x16
};


/*!
 *  \~chinese
 *  字体加粗
 *
 *  \~english
 *  Text bold
 */
typedef NS_ENUM(NSUInteger, PTCPCLTextBold) {
    PTCPCLTextBold0    = 0, ///< default,not bold
    PTCPCLTextBold1    = 1,
    PTCPCLTextBold2    = 2,
    PTCPCLTextBold3    = 3,
    PTCPCLTextBold4    = 4,
    PTCPCLTextBold5    = 5
};

/*!
 *  \~chinese
 *  旋转角度
 *
 *  \~english
 *  Rotation:Counterclockwise rotation
 */
typedef NS_ENUM(NSUInteger, PTCPCLStyleRotation) {
    PTCPCLStyleRotation0    = 0,    ///< Counterclockwise rotation,default
    PTCPCLStyleRotation90   = 90,   ///< Counterclockwise rotation 90
    PTCPCLStyleRotation180  = 180,  ///< Counterclockwise rotation 180
    PTCPCLStyleRotation270  = 270   ///< Counterclockwise rotation 270
};

/*!
 *  \~chinese
 *  字体放大系数
 *
 *  \~english
 *  Font scale
 */
typedef NS_ENUM(NSUInteger, PTCPCLFontScale) {
    PTCPCLFontScale_1  = 1,
    PTCPCLFontScale_2,
    PTCPCLFontScale_3,
    PTCPCLFontScale_4,
    PTCPCLFontScale_5,
    PTCPCLFontScale_6,
    PTCPCLFontScale_7,
    PTCPCLFontScale_8,
    PTCPCLFontScale_9,
    PTCPCLFontScale_10,
    PTCPCLFontScale_11,
    PTCPCLFontScale_12,
    PTCPCLFontScale_13,
    PTCPCLFontScale_14,
    PTCPCLFontScale_15,
    PTCPCLFontScale_16
};

/*!
 *  \~chinese
 *  PDF417码的纠错等级
 *
 *  \~english
 *  The error recovery level.
 */
typedef NS_ENUM(NSUInteger, PTCPCLPDF417ErrLevel) {
    PTCPCLPDF417ErrLevel_0  = 0,
    PTCPCLPDF417ErrLevel_1  = 1,   //default
    PTCPCLPDF417ErrLevel_2,
    PTCPCLPDF417ErrLevel_3,
    PTCPCLPDF417ErrLevel_4,
    PTCPCLPDF417ErrLevel_5,
    PTCPCLPDF417ErrLevel_6,
    PTCPCLPDF417ErrLevel_7,
    PTCPCLPDF417ErrLevel_8
};

/*!
 *  \~chinese
 *  PDF417码是水平还是垂直
 *
 *  \~english
 *  The PDF417 code horizontal or vertical.
 */
typedef NS_ENUM(NSUInteger, PTCPCLPDF417Direction) {
    PTCPCLPDF417DirectionH    = 0,    ///< horizontal
    PTCPCLPDF417DirectionV    = 1    ///< vertical
};

/*!
 *  \~chinese
 *  PDF417数据压缩是自动还是二进制
 *
 *  \~english
 *  The compaction of data in the barcode is automatic, or explicitly set to binary.
 */
typedef NS_ENUM(NSUInteger, PTCPCLPDF417Binary) {
    PTCPCLPDF417BinaryA    = 0,    ///< automatic
    PTCPCLPDF417BinaryF    = 1    ///< forced
};



/*!
 * \~chinese
 *
 * @brief CPCL指令数据生成类
 *
 * \~english
 *
 * @brief CPCL Command Data Generate Class.
 *
 */
@interface PLCmdCPCLGenerator : NSObject

/*!
 *  \~chinese
 *
 *  下发给打印机的数据.
 *
 *  \~english
 *
 *  Data sent to the printer.
 *
 */
@property(strong,nonatomic,readwrite) NSMutableData * _Nonnull cmdData;

/*!
 *  \~chinese
 *
 *  指令使用的编码，默认是GBK.
 *
 *  \~english
 *
 *  encode，default is GBK.
 *
 */
@property (nonatomic, assign) NSStringEncoding encoding;



/*!
 *  \~chinese
 *
 *  添加指令.
 *
 *  @brief 添加指令.
 *  @param cmd 指令文本.使用encoding属性进行编码.
 *
 *  \~english
 *
 *  append command.
 *
 *  @brief append command.
 *  @param cmd command text. encode with encoding property.
 *
 */
- (void)appendCommand:(NSString * _Nonnull)cmd;

/*!
 *  \~chinese
 *
 *  添加指令.
 *
 *  @brief 添加指令.
 *  @param cmd 指令数据.
 *
 *  \~english
 *
 *  append command.
 *
 *  @brief append command.
 *  @param cmd command data.
 *
 */
- (void)appendCommandData:(NSData * _Nonnull)data;

/*!
 *  \~chinese
 *
 *  打印自检页.
 *
 *  @brief 打印自检页.
 *
 *  \~english
 *
 *  selfTest.
 *
 *  @brief selfTest.
 *
 */
- (void)printSelfInspectionPage;

/*!
 *  \~chinese
 *
 *  获取打印机状态.
 *
 *  @brief 获取打印机状态
 *
 | 位(返回值)  |    1        |     0     |
 | --------- | ----------- |-----------|
 |     0     |    忙碌      |  准备就绪  |
 |     1     |    缺纸      |   纸充足   |
 |     2     |    开盖      |   合盖     |
 |     3     |    低电量    |  电量正常   |

 *
 *  \~english
 *
 *  Get print status.
 *
 *  @brief Get Print Status
 *
 | Bit(return value) |          1          |      0                 |
 | ----------------- | ------------------- |---------------------   |
 |        0          | Printer is Busy     | Printer is Ready       |
 |        1          | Paper is Out        | Paper is OK            |
 |        2          | Head Latch is Open  | Head Latch is Closed   |
 |        3          | Battery is Low      | Battery is OK          |
 *
 */
- (void)cpclGetPaperStatus;

/*!
 *  \~chinese
 *
 *  获取固件版本号
 *
 *  @brief 获取固件版本号
 *
 *  \~english
 *
 *  firmware version.
 *
 *  @brief firmware version.
 *
 */
- (void)getFirmwareVersion;

/*!
 *  \~chinese
 *
 *  开关打印状态回调.
 *
 *  @brief 开关打印状态回调.
 *
 *  \~english
 *
 *  Turn on/off print status callback.
 *
 *  @brief Turn on/off print status callback.
 *
 */
- (void)cpclTurnOnPrintStatusCallBack:(BOOL)flag;

/*!
 *  \~chinese
 *
 *  获取打印机SN号
 *
 *  @brief 获取打印机SN号
 *
 *  \~english
 *
 *  get printer serial number.
 *
 *  @brief get printer serial number.
 *
 */
- (void)cpclGetPrinterSN;

/*!
 *  \~chinese
 *
 *  设置纸张类型1
 *
 *  @brief 设置纸张类型1
 *  @param type 纸张类型
 *
 *  \~english
 *
 *  set the paper type1.
 *
 *  @brief set the paper type1.
 *  @param type paper type.
 *
 */
- (void)cpclPaperTypeWithType:(PTCPCLPaperType)type;

/*!
 *  \~chinese
 *
 *  开始标签会话.
 *
 *  @brief 开始标签会话.
 *  @param offset   标签的横向偏移量.
 *  @param hRes     标签横向分辨率(点/英寸). 100 或 200
 *  @param vRes     标签纵向分辨率(点/英寸). 100 或 200
 *  @param height   标签点高. 0-65535
 *  @param quantity 标签打印份数. 0-1024
 *
 *  \~english
 *
 *  start label session.
 *
 *  @brief start label session.
 *  @param offset   The number of units to offset all fields from the left side of the label horizontally. 0-65535
 *  @param hRes     The horizontal resolution of this label, expressed in dots per inch. 100 or 200
 *  @param vRes     The vertical resolution of this label, expressed in dots per inch. 100 or 200
 *  @param height   The height of the label in units. 0-65535
 *  @param quantity The number of copies of the label to print.  0-1024
 *
 */
- (void)cpclLabelWithOffset:(NSInteger)offset
                       hRes:(PTCPCLLabelResolution)hRes
                       vRes:(PTCPCLLabelResolution)vRes
                     height:(NSInteger)height
                   quantity:(NSInteger)quantity;

/*!
 *  \~chinese
 *
 *  指定标签宽度.
 *
 *  @brief 指定标签宽度.
 *  @param pageWidth 标签宽度(点)
 *
 *  \~english
 *
 *  used to specify the width a label session.
 *
 *  @brief used to specify the width a label session.
 *  @param pageWidth width of a label session in dots.
 *
 */
- (void)cpclPageWidth:(NSInteger)pageWidth;

/*!
 *  \~chinese
 *
 *  横向条码打印.
 *
 *  @brief 横向条码打印.
 *  @param type     条码类型. UPCA/UPCE/EAN13/EAN8/39/93/128/CODABAR
 *  @param width    窄条宽度.
 *  @param ratio    宽窄条比例. 0-4，20-30
 *  @param height   条码高度.
 *  @param x        横向起始位置.
 *  @param y        纵向起始位置.
 *  @param barcode  条码内容.
 *
 *  \~english
 *
 *  horizonal barcode.
 *
 *  @brief horizonal barcode.
 *  @param type     The type of barcode to print. UPCA/UPCE/EAN13/EAN8/39/93/128/CODABAR
 *  @param width    The width of a narrow bar.
 *  @param ratio    The ratio of wide to narrow bars. 0-4，20-30
 *  @param height   The height of the barcode.
 *  @param x        The X position where the barcode begins
 *  @param y        The Y position where the barcode begins
 *  @param barcode  The data to be encoded into a barcode
 *
 */
- (void)cpclBarcode:(PTCPCLBarcodeStyle)type
              width:(NSInteger)width
              ratio:(PTCPCLBarcodeBarRatio)ratio
             height:(NSInteger)height
                  x:(NSInteger)x
                  y:(NSInteger)y
            barcode:(NSString * _Nonnull)barcode;

/*!
 *  \~chinese
 *
 *  纵向条码打印.
 *
 *  @brief 纵向条码打印.
 *  @param type     条码类型.
 *  @param width    窄条宽度.
 *  @param ratio    宽窄条比例. 0-4，20-30
 *  @param height   条码高度.
 *  @param x        横向起始位置.
 *  @param y        纵向起始位置.
 *  @param barcode  条码内容.
 *
 *  \~english
 *
 *  vertical barcode.
 *
 *  @brief vertical barcode.
 *  @param type     The type of barcode to print.
 *  @param width    The width of a narrow bar.
 *  @param ratio    The ratio of wide to narrow bars. 0-4，20-30
 *  @param height   The height of the barcode.
 *  @param x        The X position where the barcode begins
 *  @param y        The Y position where the barcode begins
 *  @param barcode  The data to be encoded into a barcode
 *
 */
- (void)cpclBarcodeVertical:(PTCPCLBarcodeStyle)type
                      width:(NSInteger)width
                      ratio:(PTCPCLBarcodeBarRatio)ratio
                     height:(NSInteger)height
                          x:(NSInteger)x
                          y:(NSInteger)y
                    barcode:(NSString * _Nonnull)barcode;

/*!
 *  \~chinese
 *
 *  指定条码下方文字格式.
 *
 *  @brief 指定条码下方文字格式.
 *  @param font         字体名.
 *  @param fontSize     字体大小, 0-999.
 *  @param offset       文本距离条码的偏移量，0-999.
 *
 *  \~english
 *
 *  used to specify if a human-readable text representation of barcode data should be printed below 1D barcodes.
 *
 *  @brief Specify the barcode below the text format
 *  @param font         A font name or number to create the representation
 *  @param fontSize     The size of the font: 0-999
 *  @param offset       How far in units the text is from the barcode:0-999
 *
 */
- (void)cpclBarcodeTextWithFont:(PTCPCLTextFontName)font
                       fontSize:(NSInteger)fontSize
                         offset:(NSInteger)offset;

/*!
 *  \~chinese
 *
 *  指定条码下方文字格式.
 *
 *  @brief 指定条码下方文字格式.
 *  @param font     字体文件名.
 *  @param xScale   字符横向大小(点).
 *  @param yScale   字符纵向大小(点).
 *  @param offset   文本距离条码的偏移量，0-999.
 *
 *  \~english
 *
 *  used to specify if a human-readable text representation of barcode data should be printed below 1D barcodes.
 *
 *  @brief Specify the barcode below the text format
 *  @param font     The filename of the TTF font with extension.
 *  @param xScale   The X size of the font, in dots: 0-999.
 *  @param yScale   The Y size of the font, in dots: 0-999.
 *  @param offset   How far in units the text is from the barcode:0-999.
 *
 */
- (void)cpclBarcodeTextWithTrueTypeFont:(PTCPCLTextFontName)font
                                 xScale:(NSInteger)xScale
                                 yScale:(NSInteger)yScale
                                 offset:(NSInteger)offset;

/*!
 *  \~chinese
 *
 *  结束条码底部文字展示.
 *
 *  @brief 结束条码底部文字展示.
 *
 *  \~english
 *
 *  turn off the addition of the text representation.
 *
 *  @brief turn off the addition of the text representation.
 */
- (void)cpclBarcodeTextOff;

/*!
 *  \~chinese
 *
 *  横向QR码打印
 *
 *  @brief 横向QR码打印
 *  @param xPos        横向开始点.
 *  @param yPos        纵向开始点.
 *  @param model       规范编号, 1 或 2.
 *  @param unitWidth   单元宽度. 范围是1-32,默认是6
 *
 *  \~english
 *
 *  horizonal QR barcode.
 *
 *  @brief horizonal QR barcode.
 *  @param xPos        The X position where the barcode begins
 *  @param yPos        The Y position where the barcode begins
 *  @param model       Specifies the model of QR code to print.1 or 2
 *  @param unitWidth   Unit-width of the barcode in dots. 1-32,default: 6.
 *
 */
- (void)cpclBarcodeQRcodeWithXPos:(NSInteger)xPos
                             yPos:(NSInteger)yPos
                            model:(PTCPCLQRCodeModel)model
                        unitWidth:(PTCPCLQRCodeUnitWidth)unitWidth;

/*!
 *  \~chinese
 *
 *  纵向QR码打印
 *
 *  @brief 纵向QR码打印
 *  @param xPos        横向开始点.
 *  @param yPos        纵向开始点.
 *  @param model       规范编号, 1 或 2.
 *  @param unitWidth   单元宽度. 范围是1-32,默认是6
 *
 *  \~english
 *
 *  vertical QR barcode.
 *
 *  @brief vertical QR barcode.
 *  @param xPos        The X position where the barcode begins
 *  @param yPos        The Y position where the barcode begins
 *  @param model       Specifies the model of QR code to print.1 or 2
 *  @param unitWidth   Unit-width of the barcode in dots. 1-32,default: 6.
 *
 */
- (void)cpclBarcodeVerticalQRcodeWithXPos:(NSInteger)xPos
                                     yPos:(NSInteger)yPos
                                    model:(PTCPCLQRCodeModel)model
                                unitWidth:(PTCPCLQRCodeUnitWidth)unitWidth;

/*!
 *  \~chinese
 *
 *  添加QR码数据.
 *
 *  @brief 添加QR码数据.
 *  @param level            纠错级别
 *  @param characterMode    输入的字符模式符号
 *  @param context          数据
 *
 *  \~english
 *
 *  QR Data.
 *
 *  @brief QR Data.
 *  @param level            Error Correction
 *  @param characterMode    Data Input Mode
 *  @param context          Data for barcode
 *
 */
- (void)cpclBarcodeQRCodeCorrectionLecel:(PTCPCLQRCodeCorrectionLevel)level characterMode:(PTCPCLQRCodeDataInputMode)characterMode context:(NSString *_Nonnull)context;

/*!
 *  \~chinese
 *
 *  QR码结束.
 *
 *  @brief QR码结束.
 *
 *  \~english
 *
 *  The QR code terminator.
 *
 *  @brief The QR code terminator.
 *
 */
- (void)cpclBarcodeQRcodeEnd;


/*!
 *  \~chinese
 *
 *  配置PDF417码的参数
 *
 *  @brief 配置PDF417码的参数
 *  @param directon         水平还是垂直
 *  @param xPos             条形码开始的X位置 (0 to 65535 units)
 *  @param yPos             条形码开始的Y位置 (0 to 65535 units)
 *  @param xDot             单个元素的X大小（以点为单位）,默认是2 (0 to 65535)
 *  @param yDot             单个元素的Y大小（以点为单位）,默认是6 (0 to 65535)
 *  @param columns          指定要使用的列数 (1 to 30),默认是3
 *  @param rows             指定要使用的行数 (0 to 90),默认是0
 *  @param ecc              指定错误恢复级别 (0 to 8),默认是1
 *  @param binaryModel      强制二进制压缩模式 (0 or 1),默认是0
 *
 *  \~english
 *
 *  Config PDF417 parameters
 *
 *  @brief Config PDF417 parameters
 *  @param directon         horizontal or vertical
 *  @param xPos             The X position where the barcode begins (0 to 65535 units)
 *  @param yPos             The Y position where the barcode begins (0 to 65535 units)
 *  @param xDot             The X size of a single element in dots,the default value is 2 (0 to 65535)
 *  @param yDot             The Y size of a single element in dots,the default value is 6(0 to 65535)
 *  @param columns          Specifies the number of columns to use,the default value is 3 (1 to 30)
 *  @param rows             Specifies the number of rows to use,the default value is 0 (0 to 90)
 *  @param ecc              Specifies the error recovery level,the default value is 1 (0 to 8)
 *  @param binaryModel      Force binary compaction mode,the default value is 0 (0 or 1)
 */
- (void)cpclPDF417CodeWithDirection:(PTCPCLPDF417Direction)directon
                               xPos:(NSInteger)xPos
                               yPos:(NSInteger)yPos
                               xDot:(NSInteger)xDot
                               yDot:(NSInteger)yDot
                            columns:(NSInteger)columns
                               rows:(NSInteger)rows
                                ecc:(PTCPCLPDF417ErrLevel)ecc
                        binaryModel:(PTCPCLPDF417Binary)binaryModel;


/*!
 *  \~chinese
 *
 *  添加PDF417码数据.
 *
 *  @brief 添加PDF417码数据.
 *  @param context          数据
 *
 *  \~english
 *
 *  PDF417 Data.
 *
 *  @brief PDF417 Data.
 *  @param context          data
 *
 */
- (void)cpclPDF417CodeAddContext:(NSString *_Nullable)context;

/*!
 *  \~chinese
 *
 *  PDF417码结束.
 *
 *  @brief PDF417码结束.
 *
 *  \~english
 *
 *  The PDF417 code terminator.
 *
 *  @brief The PDF417 code terminator.
 *
 */
- (void)cpclPDF417codeEnd;


/*!
 *  \~chinese
 *
 *  绘制矩形.
 *
 *  @brief 绘制矩形.
 *  @param xPos      横向开始点(0~65535)
 *  @param yPos      纵向开始点(0~65535)
 *  @param xEnd      横向结束点(0~65535)
 *  @param yEnd      纵向结束点(0~65535)
 *  @param thickness 线条宽度.(0~65535)
 *
 *  \~english
 *
 *  draw box.
 *
 *  @brief draw box.
 *  @param xPos      The X origin of the box.(0~65535)
 *  @param yPos      The Y origin of the box.(0~65535)
 *  @param xEnd      The X coordinate where the box ends.(0~65535)
 *  @param yEnd      The Y coordinate where the box ends.(0~65535)
 *  @param thickness The thickness of the lines in the box.(0~65535)
 *
 */
- (void)cpclBoxWithXPos:(NSInteger)xPos
                   yPos:(NSInteger)yPos
                   xEnd:(NSInteger)xEnd
                   yEnd:(NSInteger)yEnd
              thickness:(NSInteger)thickness;

/*!
 *  \~chinese
 *
 *  画线条.
 *
 *  @brief 画线条.
 *  @param xPos         起点的x坐标
 *  @param yPos         起点的y坐标
 *  @param xEnd         终点的x坐标
 *  @param yEnd         终点的y坐标
 *  @param thickness    线条的单位宽度
 *
 *  \~english
 *
 *  draw line.
 *
 *  @brief draw line.
 *  @param xPos         The X origin of the line.
 *  @param yPos         The Y origin of the line.
 *  @param xEnd         The X coordinate where the line ends.
 *  @param yEnd         The Y coordinate where the line ends.
 *  @param thickness    The thickness of the line.
 *
 */
- (void)cpclLineWithXPos:(NSInteger)xPos
                    yPos:(NSInteger)yPos
                    xEnd:(NSInteger)xEnd
                    yEnd:(NSInteger)yEnd
               thickness:(NSInteger)thickness;

/*!
 *  \~chinese
 *
 *  反白线条.
 *
 *  @brief 反白线条.
 *  @param xPos      横向开始点(0~65535)
 *  @param yPos      纵向开始点(0~65535)
 *  @param xEnd      横向结束点(0~65535)
 *  @param yEnd      纵向结束点(0~65535)
 *  @param thickness 线条宽度.(0~65535)
 *
 *  \~english
 *
 *  draw inverse line.
 *
 *  @brief draw inverse line.
 *  @param xPos      The X origin of the box.(0~65535)
 *  @param yPos      The Y origin of the box.(0~65535)
 *  @param xEnd      The X coordinate where the box ends.(0~65535)
 *  @param yEnd      The Y coordinate where the box ends.(0~65535)
 *  @param thickness The thickness of the lines in the box.(0~65535)
 *
 */
- (void)cpclInverseLineWithXPos:(NSInteger)xPos
                           yPos:(NSInteger)yPos
                           xEnd:(NSInteger)xEnd
                           yEnd:(NSInteger)yEnd
                      thickness:(NSInteger)thickness;

/*!
 *  \~chinese
 *
 *  打印图片
 *
 *  @brief 打印图片
 *  @param Xpos         横向开始打印位置
 *  @param Ypos         纵向开始打印位置
 *  @param image        需要打印的图片
 *  @param bitmapMode   位图的类型，黑白和灰阶抖动
 *  @param compress     打印机支持的压缩类型
 *
 *  \~english
 *
 *  Print Image
 *
 *  @brief Print Image
 *  @param Xpos         Horizontal starting position.
 *  @param Ypos         Vertical starting position.
 *  @param image        Print image
 *  @param bitmapMode   Bitmap type
 *  @param compress     The type of compression supported by the printer
 *
 */
- (void)cpclPrintBitmapWithXPos:(NSInteger)xPos
                           yPos:(NSInteger)yPos
                          image:(UIImage *_Nullable )image
                     bitmapMode:(PLBitmapMode)bitmapMode
                       compress:(PLBitmapCompressMode)compress
                      isPackage:(BOOL)isPackage;


/*!
 *  \~chinese
 *
 *  标签会话结束，打印标签.
 *
 *  @brief 标签会话结束，打印标签.
 *
 *  \~english
 *
 *  terminate a CPCL label session, and create the resulting print out.
 *
 *  @brief The tag end of the session
 *
 */
- (void)cpclPrint;

/*!
 *  \~chinese
 *
 *  反向打印,将整个标签旋转180.
 *
 *  @brief 反向打印,将整个标签旋转180.
 *
 *  \~english
 *
 *  Reverse print,Rotate the label 180.
 *
 *  @brief Reverse print,Rotate the label 180.
 *
 */
- (void)cpclPoPrint;



/*!
 *  \~chinese
 *
 *  居中
 *
 *  @brief 居中
 *  @param range 居中区域宽度.
 *
 *  \~english
 *
 *  center justification.
 *
 *  @brief center justification.
 *  @param range The width of the area to center on from the left side.
 *
 */
- (void)cpclCenterWithRange:(NSInteger)range;

/*!
 *  \~chinese
 *
 *  居中
 *
 *  @brief  居中
 *
 *  \~english
 *
 *  center justification.
 *
 *  @brief center justification.
 *
 */
- (void)cpclCenter;

/*!
 *  \~chinese
 *
 *  左对齐.
 *
 *  @brief 左对齐.
 *  @param range 用于为FONT-GROUP指令指定文字区域
 *
 *  \~english
 *
 *  left justification.
 *
 *  @brief left justification.
 *  @param range When used with LEFT, the only function Range performs is a field specification function for FONT-GROUP.
 *
 */
- (void)cpclLeft:(NSInteger)range;


/*!
 *  \~chinese
 *
 *  左对齐.
 *
 *  @brief 左对齐.
 *
 *  \~english
 *
 *  left justification.
 *
 *  @brief left justification.
 *
 */
- (void)cpclLeft;

/*!
 *  \~chinese
 *
 *  右对齐.
 *
 *  @brief 右对齐.
 *  @param right 要对齐的右边界位置.
 *
 *  \~english
 *
 *  right justification.
 *
 *  @brief right justification.
 *  @param right the location of the right side to justify to.
 *
 */
- (void)cpclRight:(NSInteger)right;

/*!
 *  \~chinese
 *
 *  右对齐.
 *
 *  @brief 右对齐.
 *
 *  \~english
 *
 *  right justification.
 *
 *  @brief right justification.
 *
 */
- (void)cpclRight;

/*!
 *  \~chinese
 *
 *  字体加粗.
 *
 *  @brief 字体加粗.
 *  @param boldness 加粗程度.
 *
 *  \~english
 *
 *  add a faux bolding effect to pre-scaled fonts.
 *
 *  @brief add a faux bolding effect to pre-scaled fonts.
 *  @param boldness the boldness of the text.
 *
 */
- (void)cpclSetBold:(PTCPCLTextBold)boldness;

/*!
 *  \~chinese
 *
 *  设置字间距.
 *
 *  @brief 设置字间距.
 *  @param spacing 字间距.
 *
 *  \~english
 *
 *  set the horizontal spacing between characters.
 *
 *  @brief set the horizontal spacing between characters.
 *  @param spacing the spacing between characters of a font.
 *
 */
- (void)cpclSetSpacing:(NSInteger)spacing;

/*!
 *  \~chinese
 *
 *  设置字体放大倍数
 *
 *  @brief 设置字体放大倍数
 *  @param width    宽度放大系数, 1-16.
 *  @param height   高度放大系数, 1-16.
 *
 *  \~english
 *
 *  set the output scaling of pre-scaled fonts
 *
 *  @brief set the output scaling of pre-scaled fonts
 *  @param width    the width multiplier of the font, 1-16.
 *  @param height   the height multiplier of the font, 1-16.
 *
 */
- (void)cpclSetMagWithWidth:(PTCPCLFontScale)width height:(PTCPCLFontScale)height;

/*!
 *  \~chinese
 *
 *  打印自动换行文本.
 *
 *  @brief 打印自动换行文本.
 *  @param rotate       文字旋转方向
 *  @param font         字体
 *  @param fontSize     字体大小
 *  @param x            起始位置x
 *  @param y            起始位置y
 *  @param safeHeight   打印区域高度,超过高度部分不会打印
 *  @param width        打印区域宽度,宽度为0表示不自动换行
 *  @param lineSpacing  行间隔
 *  @param fontScale    字体放大倍数
 *  @param text         打印内容
 *  @return             自动换行后的实际打印高度
 *
 *  \~english
 *
 *  print text that feed line automatically.
 *
 *  @brief print text that feed line automatically.
 *  @param rotate       text rotate.
 *  @param font         text font.
 *  @param fontSize     text font size.
 *  @param x            orgin x of text.
 *  @param y            origin y of text.
 *  @param safeHeight   height of text field.Part will not print more than height
 *  @param width        width of text field.if width is 0,not auto line
 *  @param lineSpacing  line space.
 *  @param fontScale    Font magnification factor
 *  @param text         text.
 *  @return             Actual print height after automatic line feed
 */
- (NSInteger)cpclAutoTextWithRotate:(PTCPCLStyleRotation)rotate
                               font:(PTCPCLTextFontName)font
                           fontSize:(NSInteger)fontSize
                                  x:(NSInteger)x
                                  y:(NSInteger)y
                         safeHeight:(NSInteger)safeHight
                              width:(NSInteger)width
                        lineSpacing:(NSInteger)lineSpacing
                          fontScale:(PTCPCLFontScale)fontScale
                               text:(NSString * _Nonnull)text;

/*!
 *  \~chinese
 *
 *  打印自动换行文本,此接口解决旋转90后打印居中文本,旋转90\270后，cpclCenter接口无效
 *
 *  @brief 打印自动换行文本.
 *  @param rotate       文字旋转方向
 *  @param font         字体
 *  @param fontSize     字体大小
 *  @param xPos         起始位置x
 *  @param yPos         起始位置y
 *  @param center       是否居中
 *  @param safeHeight   打印区域高度,超过高度部分不会打印
 *  @param width        打印区域宽度,宽度为0表示不自动换行
 *  @param lineSpacing  行间隔
 *  @param fontScale    字体放大倍数
 *  @param text         打印内容
 *  @return             自动换行后的实际打印高度
 *
 *  \~english
 *
 *  print text that feed line automatically.rotate 90\270,the cpclCenter interface is invalid
 *
 *  @brief print text that feed line automatically
 *  @param rotate       text rotate.
 *  @param font         text font.
 *  @param fontSize     text font size.
 *  @param xPos         orgin x of text.
 *  @param yPos         origin y of text.
 *  @param center       Whether in the middle
 *  @param safeHeight   height of text field.Part will not print more than height
 *  @param width        width of text field.if width is 0,not auto line
 *  @param lineSpacing  line space.
 *  @param fontScale    Font magnification factor.
 *  @param text         text.
 *  @return             Actual print height after automatic line feed
 */
- (NSInteger)cpclAutoTextWithRotate:(PTCPCLStyleRotation)rotate
                               font:(PTCPCLTextFontName)font
                           fontSize:(NSInteger)fontSize
                               xPos:(NSInteger)xPos
                               yPos:(NSInteger)yPos
                             center:(BOOL)center
                         safeHeight:(NSInteger)safeHight
                              width:(NSInteger)width
                        lineSpacing:(NSInteger)lineSpacing
                          fontScale:(PTCPCLFontScale)fontScale
                               text:(NSString * _Nonnull)text;

/*!
 *  \~chinese
 *
 *  打印居中文本
 *
 *  @brief 打印居中文本
 *  @param rotate       文字旋转方向
 *  @param font         字体
 *  @param fontSize     字体大小
 *  @param x            起始位置x
 *  @param y            起始位置y
 *  @param width        打印区域宽度
 *  @param text         打印内容
 *
 *  \~english
 *
 *  Print center text
 *
 *  @brief Print center text
 *  @param rotate       text rotate.
 *  @param font         text font.
 *  @param fontSize     text font size.
 *  @param x            orgin x of text.
 *  @param y            origin y of text.
 *  @param width        width of textbox
 *  @param text         content of text.
 */
- (void)cpclCenterTextWithRotate:(PTCPCLStyleRotation)rotate
                            font:(PTCPCLTextFontName)font
                        fontSize:(NSInteger)fontSize
                               x:(NSInteger)x
                               y:(NSInteger)y
                           width:(NSInteger)width
                            text:(NSString * _Nonnull)text;

/*!
 *  \~chinese
 *
 *  打印文本.
 *
 *  @brief 打印文本.
 *  @param rotate       文字旋转方向
 *  @param font         字体
 *  @param fontSize     字体大小
 *  @param x            起始位置x
 *  @param y            起始位置y
 *  @param text         打印内容
 *
 *  \~english
 *
 *  print text.
 *
 *  @brief print text.
 *  @param rotate       text rotate.
 *  @param font         text font.
 *  @param fontSize     text font size.
 *  @param x            orgin x of text.
 *  @param y            origin y of text.
 *  @param text         text.
 */
- (void)cpclTextWithRotate:(PTCPCLStyleRotation)rotate
                      font:(PTCPCLTextFontName)font
                  fontSize:(NSInteger)fontSize
                         x:(NSInteger)x
                         y:(NSInteger)y
                      text:(NSString * _Nonnull)text;

/*!
 *  \~chinese
 *
 *  打印反白加粗文本.
 *
 *  @brief 打印反白加粗文本.
 *  @param font         字体
 *  @param rotate       文字旋转方向
 *  @param fontSize     字体大小
 *  @param reverse      是否反白
 *  @param bold         加粗
 *  @param x            起始位置x
 *  @param y            起始位置y
 *  @param text         打印内容
 *
 *  \~english
 *
 *  print reverse bold text.
 *
 *  @brief print reverse bold text.
 *  @param font         text font.
 *  @param rotate       text rotate.
 *  @param fontSize     text font size.
 *  @param reverse      Whether it is reversed
 *  @param bold         bold
 *  @param x            origin x of text.
 *  @param y            origin y of text.
 *  @param text         text.
 */
- (void)appendTextWithFont:(PTCPCLTextFontName)font
                    rotate:(PTCPCLStyleRotation)rotate
                  fontSize:(NSInteger)fontSize
                   reverse:(BOOL)reverse
                      bold:(PTCPCLTextBold)bold
                         x:(NSInteger)x
                         y:(NSInteger)y
                      text:(NSString * _Nonnull)text;

/////////////////////////////////////////////////////////////////////
/***************** Background Text Commands *******************/
/////////////////////////////////////////////////////////////////////

/*!
 *  \~chinese
 *
 *  设置背景黑度值.(0-255) 0：normal
 *
 *  @brief 设置背景黑度值
 *  @param value 黑度值.
 *
 *  \~english
 *
 *  Set the background blackness value.(0-255) 0：normal
 *
 *  @brief Set the background blackness value
 *  @param value Set the background blackness value
 *
 */
- (void)cpclSetBackgroundBlacknessValue:(NSInteger)value;

/*!
 *  \~chinese
 *
 *  设置背景文字.
 *
 *  @brief 设置背景文字.
 *  @param font         字体
 *  @param rotate       文字旋转方向
 *  @param fontSize     字体大小
 *  @param xPos         起始位置xPos
 *  @param yPos         起始位置yPos
 *  @param text         打印内容
 *
 *  \~english
 *
 *  set back text.
 *
 *  @brief set back text.
 *  @param font         text font.
 *  @param rotate       text rotate.
 *  @param fontSize     Size identifier for the font
 *  @param xPos         x-coordinate of start point
 *  @param yPos         y-coordinate of start point
 *  @param text         The text data to be  printed
 */
- (void)cpclBackTextWithFont:(PTCPCLTextFontName)font
                      rotate:(PTCPCLStyleRotation)rotate
                    fontSize:(NSInteger)fontSize
                        xPos:(NSInteger)xPos
                        yPos:(NSInteger)yPos
                        text:(NSString *_Nonnull)text;

/////////////////////////////////////////////////////////////////////
/***************** Line Print Commands *******************/
/////////////////////////////////////////////////////////////////////

/*!
 *  \~chinese
 *
 *  设置左边距
 *
 *  @brief 设置左边距
 *  @param offset   距离左边的偏移量.
 *
 *  \~english
 *
 *  Set margin
 *
 *  @brief Set margin
 *  @param offset   Specifics the distance from the left edge in units
 *
 */
- (void)cpclLineMargin:(NSInteger)offset;

/*!
 *  \~chinese
 *
 *  走纸一行
 *
 *  @brief 走纸一行
 *
 *  \~english
 *
 *  feed
 *
 *  @brief feed
 *
 */
- (void)cpclLineFeed;

/*!
 *  \~chinese
 *
 *  设置走纸
 *
 *  @brief 设置走纸
 *  @param amount   走纸多少个点. -4000~4000dots
 *
 *  \~english
 *
 *  Set feed
 *
 *  @brief Set feed
 *  @param amount   How much to feed in units.-4000~4000dots
 *
 */
- (void)cpclFeed:(NSInteger)amount;


/*!
 *  \~chinese
 *
 *  设置打印速度.
 *
 *  @brief 设置打印速度.
 *  @param value 打印速度,0-5.
 *
 *  \~english
 *
 *  set the maximum speed at which printout occurs.
 *
 *  @brief set the maximum speed at which printout occurs.
 *  @param value speed to print in an arbitrary scale,0-5.
 *
 */
- (void)cpclSpeed:(NSInteger)value;

/*!
 *  \~chinese
 *
 *  打印结束后定位至下个黑标或标签缝.
 *
 *  @brief 定位下个标签.
 *
 *  \~english
 *
 *  the printer should attempt to synchronize to a mark or gap on the media after the label is printed.
 *
 *  @brief Positioning label
 *
 */
- (void)cpclForm;

/*!
 *  \~chinese
 *
 *  设置打印浓度.
 *
 *  @brief 设置打印浓度.
 *  @param value 输出浓度, -100~200.默认是0
 *
 *  \~english
 *
 *  set the darkness of the printout from the printer.default:0
 *
 *  @brief set the darkness of the printout from the printer
 *  @param value darkness of the printout, -100~300.
 *
 */
- (void)cpclTone:(NSInteger)value;


/*!
 *  \~chinese
 *
 *  设置打印浓度.
 *
 *  @brief 设置打印浓度.
 *  @param value 输出浓度, 0-3.默认是0
 *
 *  \~english
 *
 *  set the darkness of the printout from the printer.default:0
 *
 *  @brief set the darkness of the printout from the printer
 *  @param value darkness of the printout, 0-3.
 *
 */
- (void)cpclContrast:(NSInteger)value;

/////////////////////////////////////////////////////////////////////
/***************** CPCL260 *******************/
/////////////////////////////////////////////////////////////////////
/** T260 35 55 75 95 */
- (void)setPrinterDensity:(NSInteger)density;

/// T260标签学习
- (void)labelPositionLearn;
 
/**
 T260 纸张类型，设置成功返回4f4b 失败返回4e4f
 
 @param type 0：连续纸 1：标签纸
 */
- (void)setPrinterPaperType:(NSInteger)type;


/////////////////////////////////////////////////////////////////////
///////////////////////RFID 具体看协议////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/// RFID 校准
- (void)rfidCalibrate;

/// RFID 打印
- (void)rfidPrint;

/// 单条写入RFID标签
/// @param content 数据内容
/// @param startAddr 起始地址
/// @param memory 存储区域
- (BOOL)rfidWriteData:(NSString *_Nonnull)content startAddr:(NSInteger)startAddr memory:(PTRFIDMemory)memory;

/// 读取RFID标签
/// @param length 读取的数据长度，只能是偶数,
/// @param startAddr 读取的起始地址
/// @param memory 读取的存储区域
- (BOOL)rfidReadDataWithLength:(NSInteger)length startAddr:(NSInteger)startAddr memory:(PTRFIDMemory)memory;

/// 用户区多条写入
/// @param slices 数组
- (void)rfidMultiWriteData:(NSMutableArray <PTRFIDInfoSlice *> *_Nonnull)slices;

@end

NS_ASSUME_NONNULL_END



