//
//  img.h
//  img
//
//  Created by DQA on 2019/11/29.
//  Copyright © 2019 hprt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//! Project version number for img.
FOUNDATION_EXPORT double imgVersionNumber;

//! Project version string for img.
FOUNDATION_EXPORT const unsigned char imgVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <img/PublicHeader.h>

@interface ImgProc : NSObject

+ (UIImage *)enhanceFilter:(UIImage *)image;

@end


