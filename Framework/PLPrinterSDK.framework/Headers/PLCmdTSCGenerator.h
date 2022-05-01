//
//  PLCmdTSCGenerator.h
//  PLPrinterSDK
//
//  Created by ios on 2021/1/5.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PLBitmapManager.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 *  \~chinese
 *  打印速度
 *
 *  \~english
 *  Print speed
 */
typedef NS_ENUM(NSUInteger, PTTSCPrintSpeed) {
    PTTSCPrintSpeed1        = 1,
    PTTSCPrintSpeed2        = 2,
    PTTSCPrintSpeed3        = 3,
    PTTSCPrintSpeed4        = 4,
    PTTSCPrintSpeed5        = 5,
    PTTSCPrintSpeed6        = 6,
    PTTSCPrintSpeed10       = 10,
    PTTSCPrintSpeed12       = 12
};

/*!
 *  \~chinese
 *  打印方向
 *
 *  \~english
 *  DIRECTION
 */
typedef NS_ENUM(NSUInteger, PTTSCPrintDirection) {
    
    /*! \~chinese 正常方向 \~english normal */
    PTTSCPrintDirectionNormal    = 0,
    
    /*! \~chinese 反向 \~english Reverse */
    PTTSCPrintDirectionReverse   = 1
};

/*!
 *  \~chinese
 *  打印模式
 *
 *  \~english
 *  Print Mode
 */
typedef NS_ENUM(NSUInteger, PTTSCPrintStyle) {
    
    /*! \~chinese 正常模式 \~english normal */
    PTTSCPrintStyleNormal    = 0,
    /*! \~chinese 镜像模式 \~english Mirror */
    PTTSCPrintStyleMirror    = 1
};


/*!
 *  \~chinese
 *  旋转角度
 *
 *  \~english
 *  Rotation
 */
typedef NS_ENUM(NSUInteger, PTTSCStyleRotation) {
    
    /*! \~chinese 正常打印 \~english normal */
    PTTSCStyleRotation0     = 0,
    /*! \~chinese 顺时针旋转90度 \~english rotate 90 degrees (clockwise) */
    PTTSCStyleRotation90    = 90,
    /*! \~chinese 180度旋转 \~english inverted 180 degrees */
    PTTSCStyleRotation180   = 180,
    /*! \~chinese 270度旋转 \~english read from bottom up, 270 degrees */
    PTTSCStyleRotation270   = 270
};

/*!
 *  \~chinese
 *  位图模式
 *
 *  \~english
 *  qrcode mask
 */
typedef NS_ENUM(NSUInteger, PTTSCBitmapMode) {
    
    PTTSCBitmapModeOVERWRITE            = 0,
    PTTSCBitmapModeOR                   = 1,
    PTTSCBitmapModeXOR                  = 2,
    
    /*! *\~chinese 压缩模式，兼容旧的固件，新的固件已经废弃 *\~english Compatible with old models,New firmware has been deprecated */
    PTTSCBitmapModeCompress             = 3,
    PTTSCBitmapModeOVERWRITECompress    = 16,
    PTTSCBitmapModeORCompress           = 17,
    PTTSCBitmapModeXORCompress          = 18
};

@interface PLCmdTSCGenerator : NSObject


/*!
 *  \~chinese
 *
 *  自检，打印打印机信息.
 *
 *  @brief 打印自检页
 *
 *  \~english
 *
 *  printer Print self-test message.
 *
 *  @brief View Printer Message
 */
+ (NSData *)selfTest;

/*!
 *  \~chinese
 *
 *  标签学习功能
 *
 *  @brief 标签学习功能
 *
 *  \~english
 *
 *  label learn
 *
 *  @brief label learn
 */
+ (NSData *)setLabelLearn;

/*!
 *  \~chinese
 *
 *  设置打印纸张范围大小,传的是毫米.1mm == 8 dot
 *
 *  @brief 设置打印区域
 *  @param label_width     标签纸的宽度
 *  @param label_height    标签纸的高度
 *
 *  \~english
 *
 *  This command defines the label width and length(mm).1mm == 8 dot
 *
 *  @brief Set Print Area
 *  @param label_width     Label width
 *  @param label_height    Label length
 *
 */
+ (NSData *)setPrintAreaSizeWithWidth:(NSInteger)label_width height:(NSInteger)label_height;
                           

/*!
 *  \~chinese
 *
 *  设置标签的参考起点.
 *
 *  @brief 设置标签的参考起点
 *  @param x_pos    水平方向的坐标，以点为单位
 *  @param y_pos    垂直方向的坐标，以点为单位
 *
 *  \~english
 *
 *  This command defines the reference point of the label.
 *
 *  @brief Set Label Reference Point
 *  @param x_pos    Horizontal coordinate (in dots)
 *  @param y_pos    Vertical coordinate (in dots)
 *
 */
+ (NSData *)setReferenceXPos:(NSInteger)x_pos yPos:(NSInteger)y_pos;
                    

/*!
 *  \~chinese
 *
 *  将标签定位到下一个标签的起始处.
 *
 *  @brief 定位
 *  \~english
 *
 *  This command feeds label to the beginning of next label.
 *
 *  @brief Form Feed
 */
+ (NSData *)feedToNextLabel;


/*!
 *  \~chinese
 *
 *  设置打印速度.
 *
 *  @brief 设置打印速度
 *  @param speed     打印速度(0~15,默认是6)
 *
 *  \~english
 *
 *  This command defines the print speed.
 *
 *  @brief Print Speed
 *  @param speed     Printing speed in inch per second(0~15,default is 6)
 *
 */
+ (NSData *)setPrintSpeed:(PTTSCPrintSpeed)speed;

/*!
 *  \~chinese
 *
 *  设置打印浓度.
 *
 *  @brief 设置打印浓度
 *  @param density     打印浓度 0~15
 *
 *  \~english
 *
 *  This command sets the printing darkness.
 *
 *  @brief Print Density
 *  @param density     0: specifies the lightest level,15: specifies the darkest level
 *
 */
+ (NSData *)setPrintDensity:(NSInteger)density;

/*!
 *  \~chinese
 *
 *  设置打印的方向和镜像.
 *
 *  @brief 设置打印的方向和镜像
 *  @param direction    正常或者方向打印
 *  @param mirror       正常或者镜像
 *
 *  \~english
 *
 *  This command defines the printout direction and mirror image.
 *
 *  @brief Print Direction And Mirror
 *  @param direction    normal or reverse
 *  @param mirror       normal or mirror
 *
 */
+ (NSData *)setPrintDirection:(PTTSCPrintDirection)direction mirror:(PTTSCPrintStyle)mirror;

/*!
 *  \~chinese
 *
 *  清除图像缓冲区.
 *
 *  @brief 清除图像缓冲区
 *  \~english
 *
 *  This command clears the image buffer.
 *
 *  @brief Clear Buffer
 */
+ (NSData *)setCLS;


/*!
 *  \~chinese
 *
 *  打印数量.
 *
 *  @brief 开始打印，设置打印数量
 *  @param sets      打印份数
 *  @param copies    每份打印的张数
 *
 *  \~english
 *
 *  This command prints the label format currently stored in the image buffer.
 *
 *  @brief Begin Print,Set Print Copies
 *  @param sets     Specifies how many sets of labels will be printed.
 *  @param copies   Specifies how many copies should be printed for each particular label set.
 *
 */
+ (NSData *)printWithSets:(NSInteger)sets copies:(NSInteger)copies;



/*!
 *  \~chinese
 *
 *  开关打印状态回调.
 *
 *  @brief 自动回传状态开关
 *  @note 开启之后，每打印一张都会返回10个字节的数据，格式：指令头4个字节(aa bb cc dd) + 4个字节的打印张数(从开启到关闭的打印总张数) + 1个字节的状态 + 结束符00,
    返回两次数据，第一次表示返回可获取打印总张数和状态，第二次表示打印结束
    比如：1.aabbccdd 03000000 2000
         2.aabbccdd ffffffff 0000 -> 打印结束
           aabbccdd 00000000 0000 -> 关闭自动回传
 *  @param status     true:开启  false:关闭
 *
 *  \~english
 *
 *  Turn on/off print status callback.
 *
 *  @brief Automatic return status switch
 *  @note Returns 10 bytes of data,4-byte instruction header(aa bb cc dd) + 4 bytes of printed sheets + 1 byte status + Terminator(00),Returns twice the data, the first time to return to get the total number of prints and the status, the second time to end the end of printing
 
 *  @param status     true:open  false:close
 *
 */
+ (NSData *)setPrinterStateAutomaticBackWithStatus:(BOOL)status;

/*!
 *  \~chinese
 *
 *  获取打印机状态.
 *
 *  @brief 获取打印机状态
 *
    | 位(返回值) |    状态      |
    | --------- | ----------- |
    |     0     |    开盖      |
    |     1     |    卡纸      |
    |     2     |    缺纸      |
    |     3     |    无碳带    |
    |     4     |    暂停      |
    |     5     |    打印中    |
    |     6     |    开盖      |
    |     7     |    高温      |
 *
 *  \~english
 *
 *  Get print status.
 *  @brief Get Print Status
 *
    | Bit(return value) |    Status     |
    | ----------------- | ------------- |
    |        0          | Head opened   |
    |        1          | Paper jam     |
    |        2          | Out of paper  |
    |        3          | Out of ribbon |
    |        4          | Pause         |
    |        5          | Printing      |
    |        6          | Cover opened  |
    |        7          | High          |
 *
 */
+ (NSData *)getPrinterStatus;

/*!
 *  \~chinese
 *
 *  打印图片.
 *
 *  @brief 打印图片
 *  @param xpos        x起始坐标
 *  @param ypos        y起始坐标
 *  @param mode        图形模式
 *  @param image       打印的图片
 *  @param bitmapMode  打印的图片模式
 *  @param compress    压缩模式
 *  @return            返回false的话，说明下发的图片数据大于打印机缓存区，应禁止下发
 *
 *  \~english
 *
 *  Print Bitmap.
 *
 *  @brief Print Bitmap
 *  @param xpos        Specify the x-coordinate
 *  @param ypos        Specify the y-coordinate
 *  @param mode        Graphic modes
 *  @param image       Image
 *  @param bitmapMode  Bitmap mpde:binary/dithering
 *  @param compress    Compress mode:TIFF/ZPL2/LZO/None
 *  @return            The data is less than the cache and can be printed NO:The data exceeds the cache and cannot be printed
 *
 */
+ (NSData *)addBitmapWithXPos:(NSInteger)xpos yPos:(NSInteger)ypos mode:(PTTSCBitmapMode)mode image:(UIImage *)image bitmapMode:(PLBitmapMode)bitmapMode compress:(PLBitmapCompressMode)compress;
                     
                     
                    
               
                 

@end

NS_ASSUME_NONNULL_END
