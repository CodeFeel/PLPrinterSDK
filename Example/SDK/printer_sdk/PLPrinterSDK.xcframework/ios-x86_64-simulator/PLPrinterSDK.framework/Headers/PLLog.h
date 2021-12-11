//
//  PLLog.h
//  PLPrinterSDK
//
//  Created by ios on 2021/11/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define PLLOG(text) [[PLLog shareInstance] writeFile:text];

@interface PLLog : NSObject

/// 默认false,不写入数据  要写入日志，先将设置为true
@property (nonatomic, assign) BOOL isWrite;

+ (PLLog *)shareInstance;

/// 文件在沙盒Docuemnts/pl_log txt文件
- (void)writeFile:(NSString *)file;

- (NSString *)readFile;

/// 如果返回false，一般是文件已经不存在
- (BOOL)removeFile;

@end

NS_ASSUME_NONNULL_END
