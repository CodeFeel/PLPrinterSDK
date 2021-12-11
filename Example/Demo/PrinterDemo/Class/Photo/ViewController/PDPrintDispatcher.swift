//
//  PDPrintDispatcher.swift
//  PrinterDemo
//
//  Created by ios on 2020/12/3.
//  Copyright © 2020 XiamenHY. All rights reserved.
//

import UIKit

protocol PDPrintTask {
    func bitmapData() -> (Data,UInt16)
}

enum HPPrinterState {
    case printBefore
    case printing
    case printEnd
}

class PDPrintDispatcher: NSObject {
    
    var tasks = [PDPrintTask]()
    var printer_state = HPPrinterState.printBefore
    var searchTimer : Timer?
    let totalTaskCount: Int
    
    lazy var stateView: PDShowStatusView = {
        let temp = PDShowStatusView.init(with: "")
        return temp
    }()
    
    init(with tasks:[PDPrintTask]) {
        
        self.tasks = tasks
        self.totalTaskCount = tasks.count
        super.init()
        autoPrinterStatus()
    }
    
    func beginPrint() {
        
        printer_state = .printing
        resumeNextTask()
    }
    
    func resumeNextTask() -> Void {
        
        self.searchTimer?.invalidate()
        if self.tasks.count == 0 {
            updateUIToTaskCompleted()
            return
        }
//        SVProgressHUD.show(withStatus: "\(totalTaskCount - tasks.count + 1)/\(totalTaskCount)")
        SVProgressHUD.show()
        let component = self.tasks[0].bitmapData()
        let arrays = PLCmdMTGenerator.sliceImageBitmap(component.0, height: component.1)
        
        PLDataDispatcher.shared().writeA4ImageDatas(arrays) { [weak self](progress) in
            guard let self = self else { return }
            SVProgressHUD.showProgress(Float(progress.fractionCompleted))
            if progress.fractionCompleted == 1.0 {
                SVProgressHUD.show(withStatus: "数据发送成功，打印中。。。")
                /// 发送成功，移除第一个任务
                self.tasks.remove(at: 0)
                /// 这边发送结尾指令
                if UserDefaults.standard.bool(forKey: PDPaperType) {
                    PLDataDispatcher.shared().write(Data.init([0x0c]))
                }else {
                    PLDataDispatcher.shared().write(Data.init(repeating: 0x0a, count: 13))
                }
                
                DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 0.5) {
                    /// 轮询查状态
                    self.searchTimer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(self.searchPrinterBuffer), userInfo: nil, repeats: true)
                }
            }
        } fail: {[weak self] in
            guard let self = self else { return }
            SVProgressHUD.showError(withStatus: "数据发送失败")
            self.stopPrint(false)
        }
    }
    
    @objc func searchPrinterBuffer() {
        
        let infoData = PLCmdMTGenerator.getPrinterStatusInfo()
        PLDataDispatcher.shared().write(infoData)
        
        PLDataDispatcher.shared().resolver?.resolvedBlock = { [weak self] in
            guard let self = self else { return }
            guard let model = $0 as? PLMT800ResolverModel else { return }
            switch model.type {
                case .printerInfo:
                    print(model.data.hexString)
                    let info = PLMT800Info.init(data: model.data)
                    if !info.state.buffer.isEmpty || !info.idle {
                        return
                    }
                    let deviceStatus = info.state.description
                    if deviceStatus.isEmpty {
                        self.resumeNextTask()
                    }else {
                        if self.tasks.count == 0 {
                            self.searchTimer?.invalidate()
                            self.updateUIToTaskCompleted()
                        }
                    }
                default:
                    break
            }
        }
    }
    
    private func autoPrinterStatus() {
        PLDataDispatcher.shared().autoA4DeviceStateBlock { [weak self](state) in
            guard let self = self else { return }
            let message = state.description
            if message.isEmpty {
                self.stateView.dismiss()
                if self.printer_state == HPPrinterState.printBefore {
                    self.beginPrint()
                }
            }else {
                ///打印完成不显示异常状态
                if self.printer_state == .printEnd {
                    return
                }
                ///任务量为0，缓存数据空，不显示异常状态
                if self.printer_state == .printing && self.tasks.count == 0 && state.buffer.isEmpty {
                    return
                }
                self.stateView.configUI(message)
                self.stateView.callBackCancelBlock {[weak self] in
                    guard let self = self else { return }
                    self.stopPrint(true)
                    SVProgressHUD.dismiss()
                }
            }
        }
    }
    
    func updateUIToTaskCompleted() -> Void {
        
        self.printer_state = HPPrinterState.printEnd
        self.stateView.dismiss()
        SVProgressHUD.showSuccess(withStatus: "打印完成".localized)
    }
    
    func stopPrint(_ isRet:Bool) {
        
        if let temp = searchTimer {
            temp.invalidate()
        }
        printer_state = HPPrinterState.printEnd
        PLDataDispatcher.shared().write(PLCmdMTGenerator.clearPrinterBuffer())
        PLDataDispatcher.shared().resolver?.resolvedBlock = { [weak self] in
            guard let _ = self else { return }
            guard let model = $0 as? PLMT800ResolverModel else { return }
            switch model.type {
                case .clearBuffer:
                    print("---清理成功--------")
                default:
                    break
            }
        }
    }

}
