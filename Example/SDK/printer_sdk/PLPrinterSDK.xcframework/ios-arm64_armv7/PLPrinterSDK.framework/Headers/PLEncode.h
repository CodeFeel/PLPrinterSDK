//
//  PLEncode.h
//  PLPrinterSDK
//
//  Created by ios on 2020/11/30.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PLEncode : NSObject

/** 编码 */
+ (NSData *)encodeDataWithString:(NSString *)string;
/** 解码 */
+ (NSString *)decodeStringWithData:(NSData *)data;

/** 支持多种编码 */
+ (NSData *)encodeDataWithString:(NSString *)string encodingType:(CFStringEncodings)encodeType;
/** 支持多种解码 */
+ (NSString *)decodeDataWithString:(NSData *)data encodingType:(CFStringEncodings)encodeType;

@end

NS_ASSUME_NONNULL_END
