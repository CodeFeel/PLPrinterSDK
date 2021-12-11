//
//  AppDelegate.swift
//  PrinterDemo
//
//  Created by ios on 2019/9/5.
//  Copyright © 2019 XiamenHY. All rights reserved.
//

import UIKit
import PLPrinterSDK
import SVProgressHUD

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        
        
        /// a04813
//        PLDataDispatcher.shared().start(withAuthKey: "Xe8T6JTT6wVVqk58nZgH8aD+1cCaYSZqyO6lznsaz5QGvL6Xtvl0kV01BWpwjCF7zVYUluArwRPKaE1TVNQGrNLxjDWYDLSDz0vIPq3Vgw4/Tofw3M+aV0Njc0iEyRVl1ipe8IF91RWprq9aMG7hcKtW3tcuyFOWIOffUqfyPLs=")
        
        /// qudao
        PLDataDispatcher.shared().start(withAuthKey: "UJE+lt9zrR1o1IfxJyu085iK26IlMnn+HyGfXVbZCeOwx75IaRoJU4CsmzVms8Xlw/uPo1cM+3exfZXCydPTkTZx6VW95Chp2AmLCf0Aq0pBVQpb3tEs/TkVHQbRBCdJMEJiyKv8JufnBe1XO0Jjfmrmz10+Z7AtZW8qYq/WRBk=")
        
        
        /// 开启日志 写入
        PLLog.shareInstance().isWrite = true
        
        window = UIWindow.init(frame: UIScreen.main.bounds)
        window?.backgroundColor = UIColor.white
        let vc = PDMainViewController.init()
        let nvc = PDBaseNavigationController.init(rootViewController: vc)
        window?.rootViewController = nvc
        if #available(iOS 13.0, *) {
            window?.overrideUserInterfaceStyle = .light
        }
        window?.makeKeyAndVisible()
                
        SVProgressHUD.setDefaultStyle(SVProgressHUDStyle.dark)
        SVProgressHUD.setDefaultMaskType(SVProgressHUDMaskType.clear)
        SVProgressHUD.setDefaultAnimationType(SVProgressHUDAnimationType.native)
        SVProgressHUD.setMinimumDismissTimeInterval(0.5)
        SVProgressHUD.setMaximumDismissTimeInterval(2)
        
        
        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

