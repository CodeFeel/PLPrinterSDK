//
//  PLBarcodeEncodeVerify.h
//  ZHPrint
//
//  Created by ios on 2022/4/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PLBarcodeSlice : NSObject
@property (nonatomic, assign) BOOL isVerify;
@property (nonatomic, copy) NSString *content;
@end

@interface PLBarcodeEncodeVerify : NSObject

+ (PLBarcodeSlice *)verifyEan8Encoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyEan13Encoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyUpcaEncoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyUpceEncoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyCode128Encoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyCode39Encoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyCode93Encoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyCodaBarEncoding:(NSString *)contents;

+ (PLBarcodeSlice *)verifyItf25Encoding:(NSString *)contents;

@end

NS_ASSUME_NONNULL_END
