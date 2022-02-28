//
//  PLResolverCentral.h
//  PLPrinterSDK
//
//  Created by ios on 2020/12/1.
//

#import <Foundation/Foundation.h>
#import "PLDataDispatcher.h"

NS_ASSUME_NONNULL_BEGIN


@interface PLResolverCentral : NSObject

@end


@interface PLCommonResolveModel : NSObject

///< \~chinese 是否丢弃 \~english discardable
@property (nonatomic, assign) BOOL isDiscardable;

///< \~chinese 数据内容 \~english content
@property (nonatomic, strong) NSData *data;

///< \~chinese 消耗的数据量 \~english data length costed
@property (nonatomic, assign) NSInteger cost;

///< \~chinese 源数据 \~english raw data
@property (nonatomic, strong) NSData *rawData;

@end


@interface PLDataRouterBlock : NSObject

@property (nonatomic, assign) NSInteger minDataLength;
@property (nonatomic, copy) PLCommonResolveModel * _Nullable (^ handleBlock)(NSData *);

@end


@interface PLDataRouter : NSObject

- (void)registerHandle:(NSData *)key block:(PLDataRouterBlock *)block;

- (PLDataRouterBlock * _Nullable)handle:(NSData *)key;

@end

@interface PLCommonResolver : NSObject <PLDataResolver>

@property (nonatomic, strong) PLDataRouter *router;

@property (nonatomic, copy) void (^ _Nullable handleFailBlock)(NSData *);

- (void)registerHandle;

@end

NS_ASSUME_NONNULL_END
