//
//  MT800SampleViewController.swift
//  PrinterDemo
//
//  Created by ios on 2020/12/2.
//  Copyright © 2020 XiamenHY. All rights reserved.
//

import UIKit
import PLPrinterSDK
import SVProgressHUD

class MT800SampleViewController: PDBaseViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func configUI() {
        navigationItem.title = "A4 测试示例"
        view.addSubview(tableView)
        tableView.snp.makeConstraints { $0.edges.equalTo(self.view.usnp.edges) }
        
        loadDataSource()
    }
    
    lazy var tableView : UITableView = {
        let temp = UITableView.init(frame: .zero, style: .plain)
        temp.delegate = self
        temp.dataSource = self
        temp.backgroundColor = .white
        temp.rowHeight = 50.0
        temp.showsVerticalScrollIndicator = false
        temp.separatorStyle = UITableViewCell.SeparatorStyle.singleLine
        return temp
    }()
    
    private var actions = [PDSettingCellItem]()
    var info = [(key: String,value: String)]()
    
    private func loadDataSource() {
        
        actions.removeAll()
        var action : PDSettingCellItem
        action = PDSettingCellItem.init(title: "获取打印机状态", detailTitle: nil, target: self, selector: #selector(self.requestPrinterInfo))
        actions.append(action)
        action = PDSettingCellItem.init(title: "图片打印", detailTitle: nil, target: self, selector: #selector(self.imagePrint))
        actions.append(action)
        action = PDSettingCellItem.init(title: "固件更新", detailTitle: nil, target: self, selector: #selector(self.updateFirmware))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取序列号", detailTitle: nil, target: self, selector: #selector(self.getSN))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取固件版本", detailTitle: nil, target: self, selector: #selector(self.getFirmwareVersion))
        actions.append(action)
        action = PDSettingCellItem.init(title: "清空缓存", detailTitle: nil, target: self, selector: #selector(self.clearPrinterBuffer))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取碳带余量", detailTitle: nil, target: self, selector: #selector(self.getRibbonRemainCount))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取碳带品牌", detailTitle: nil, target: self, selector: #selector(self.getRibbonConsumablesBrandInfo))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取打印机名称", detailTitle: nil, target: self, selector: #selector(self.getPrinterModelName))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取关机时间", detailTitle: nil, target: self, selector: #selector(self.getPrinterShutdownTime))
        actions.append(action)
        action = PDSettingCellItem.init(title: "设置自动关机时间", detailTitle: nil, target: self, selector: #selector(self.setPrinterShutdownTime))
        actions.append(action)
        action = PDSettingCellItem.init(title: "获取浓度", detailTitle: nil, target: self, selector: #selector(self.getPrinterDensity))
        actions.append(action)
        action = PDSettingCellItem.init(title: "设置浓度", detailTitle: nil, target: self, selector: #selector(self.setPrinterDensity))
        actions.append(action)
        
        action = PDSettingCellItem.init(title: "获取纸张类型", detailTitle: nil, target: self, selector: #selector(self.getPrinterPaperType))
        actions.append(action)
        
        action = PDSettingCellItem.init(title: "设置纸张类型", detailTitle: nil, target: self, selector: #selector(self.setPrinterPaperType))
        actions.append(action)
        tableView.reloadData()
    }

}

extension MT800SampleViewController : UITableViewDelegate,UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return actions.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: "iden")
        if cell == nil {
            cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
        }
        cell?.textLabel?.text = actions[indexPath.row].title
        cell?.textLabel?.textColor = UIColor.black
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let action = actions[indexPath.row]
        if let target = action.target {
            if let selector = action.selector {
                target.perform(selector)
            }
        }
    }
}

extension MT800SampleViewController {
    
    private func request(data: Data) {
        
        SVProgressHUD.show()
        PLDataDispatcher.shared().write(data) {
            if $0.fractionCompleted == 1.0 {
                /// 数据发送成功
                SVProgressHUD.dismiss()
            }
        } fail: {
            SVProgressHUD.showError(withStatus: "数据发送失败")
        }
        
        PLDataDispatcher.shared().resolver?.resolvedBlock = { [weak self] in
            guard let self = self else { return }
            guard let model = $0 as? PLMT800ResolverModel else { return }

            switch model.type {
                case .printerInfo:
                    print(model.data.hexString)
                    let info = PLMT800Info.init(data: model.data)
                    if info.state.isEmpty {
                        self.info.append(("打印机状态", "正常"))
                    }else {
                        self.info.append(("打印机状态", "\(info.state)"))
                    }
                    self.info.append(("空闲状态", info.idle ? "空闲" : "正忙"))
                    self.info.append(("电量", "\(info.electricity)"))
                    self.info.append(("自动关机时间", info.shutdownTime == 0 ? "不自动关机" : "\(info.shutdownTime) min"))
                    self.info.append(("浓度", "\(info.density)"))
                    self.info.append(("纸张类型", info.paperType == 0 ? "热敏纸" : "A4纸"))
                    self.info.append(("TPH温度", "\(info.tphTmp)"))
                    self.showInfo()
                    
                case .sn:
                    guard let serialNum = String.init(data: model.data, encoding: .ascii) else { return }
                    self.info.append(("序列号", serialNum))
                    self.showInfo()
                    
                case .firmwareVersion:
                    guard let version = String.init(data: model.data, encoding: .ascii) else { return }
                    self.info.append(("固件版本", version))
                    self.showInfo()
                    
                case .clearBuffer:
                    self.info.append(("清空缓存", model.data[0] == 1 ? "成功" : "失败"))
                    self.showInfo()
                    
                case .carbonRibbonRemainCount:
                    if let count = model.data.read(to: UInt32.self) {
                        self.info.append(("碳带余量", "\(count)mm"))
                        self.showInfo()
                    }
                    
                case .carbonRibbonBrand:
                    guard let version = String.init(data: model.data, encoding: .ascii) else { return }
                    self.info.append(("碳带品牌", version))
                    self.showInfo()
                    
                case .commonGet:
                    print(model.data.hexString)
                    
                    var getName = ""
                    var desc = ""
                    if let byte = model.data.read(to: UInt16.self) {
                        if let key = PLMT800CommonCmdKey.init(rawValue: byte) {
                            if key == .shutdownTime {
                                getName = "自动关机时间"
                                if let time = model.data.read(to: UInt32.self, offset: 3) {
                                    desc = "\(time)"
                                }
                                
                            }else if key == .printDensity {
                                getName = "打印机浓度"
                                desc = "\(model.data[3])"
                            }else if key == .printerName {
                                getName = "打印机型号"
                                model.data.replaceSubrange(0...2, with: Data())
                                if let temp = String.init(data: model.data, encoding: .ascii) {
                                    desc = temp
                                }
                            }else if key == .paperType {
                                getName = "纸张类型"
                                if model.data[3] == 0 {
                                    desc = "连续纸"
                                }
                                if model.data[3] == 1 {
                                    desc = "A4纸"
                                }
                                if model.data[3] == 2 {
                                    desc = "黑标纸"
                                }
                            }
                            
                        }
                    }
                    self.info.append(("获取\(getName)", desc))
                    self.showInfo()
                    
                case .commonSet:
                    print(model.data.hexString)
                    var setName = ""
                    if let byte = model.data.read(to: UInt16.self) {
                        if let key = PLMT800CommonCmdKey.init(rawValue: byte) {
                            if key == .shutdownTime {
                                setName = "自动关机时间"
                            }else if key == .printDensity {
                                setName = "打印机浓度"
                            }
                        }
                    }
                    self.info.append(("设置\(setName)", model.data[2] == 0 ? "成功" : "失败"))
                    self.showInfo()
                default:
                    break
            }
        }
        
    }
    
    private func showInfo() {
        if info.count > 0 {
            let message = info.map({ "\($0.key): \($0.value)" }).joined(separator: "\n")
            self.bk_presentWarningAlertController(title: "接收消息", message: message, style: .default)
        }
        info = []
    }
    
    @objc private func requestPrinterInfo() {
        
        request(data: PLCmdMTGenerator.getPrinterStatusInfo())
    }
    
    //MARK: - 图片范例
    @objc private func imagePrint() {
        
        #if true
        
        /// 这个是通过SDK将PDF转成图片
        var path = Bundle.main.path(forResource: "resource", ofType: "bundle")!
        let bundle = Bundle.init(path: path)!
        path = bundle.path(forResource: "mt800_sample1", ofType: "pdf")!
        let url = URL.init(fileURLWithPath: path)
        
        let pdfConverter = PLPDFConverter.init(path: url, autoRotate: false)
        print(pdfConverter.pageCount)
        guard let image = pdfConverter.image(at: 0, size: A4.size) else { return }
        let vc = PDPreviewImageControllerViewController.init(with: image, printModel: "")
        vc.deviceType = .A4
        self.navigationController?.pushViewController(vc, animated: true)
        
        #else
        
        /// 上海官邸图片测试
        
        guard let testImage = UIImage(named: "a4_test.jpg") else { return }
        let result = PLBitmapManager.drawPrint(testImage, destSize: A4.size, aotuRotate: true)
        let vc = PDPreviewImageControllerViewController.init(with: result, printModel: "")
        vc.deviceType = .A4
        self.navigationController?.pushViewController(vc, animated: true)
        #endif
    }
    
    @objc private func updateFirmware() {
        bk_presentDecisionAlertController(title: "提示", message: "请选择对应的固件进行升级", decisionTitle: nil) { (_) in
            let picker = UIDocumentPickerViewController.init(documentTypes: ["public.data"], in: .import)
            picker.delegate = self
            picker.modalPresentationStyle = .fullScreen
            if #available(iOS 11.0, *) {
                picker.allowsMultipleSelection = false
            } else {
                // Fallback on earlier versions
            }
            self.present(picker, animated: true, completion: nil)
        }
    }
    
    @objc private func getSN() {
        request(data: PLCmdMTGenerator.getPrinterSerialNumber())
    }
    
    @objc private func getFirmwareVersion() {
        request(data: PLCmdMTGenerator.getPrinterFirmwareVersion())
    }
    
    @objc private func clearPrinterBuffer() {
        request(data: PLCmdMTGenerator.clearPrinterBuffer())
    }
    
    @objc private func getRibbonRemainCount() {
        request(data: PLCmdMTGenerator.getRibbonRemainCount())
    }
    
    @objc private func getRibbonConsumablesBrandInfo() {
        request(data: PLCmdMTGenerator.getRibbonConsumablesBrandInfo())
    }
    
    @objc private func getPrinterModelName() {
        request(data: PLCmdMTGenerator.getPrinterName())
    }
    
    @objc private func getPrinterShutdownTime() {
        request(data: PLCmdMTGenerator.getPrinterShutdownTime())
    }
    
    @objc private func setPrinterShutdownTime() {
        self.presentInputAlertController(msg: "设置打印机关机时间", inputDesc: "设置自动关机时间，单位是分钟") {
            if let time = Int.init($0) {
                self.request(data: PLCmdMTGenerator.setPrinterShutdownTime(UInt32(time)))
            }else {
                SVProgressHUD.showInfo(withStatus: "输入错误,请重新输入")
            }
        }
    }
    
    @objc private func getPrinterDensity() {
        request(data: PLCmdMTGenerator.getPrinterDensity())
    }
    
    @objc private func setPrinterDensity() {
        presentInputAlertController(msg: "设置打印机浓度", inputDesc: "请输入打印浓度，范围1~3", closure: {
            if let desity = Int.init($0), desity >= 0, desity <= 3 {
                self.request(data: PLCmdMTGenerator.setPrinterDensity(UInt8(desity)))
            }else {
                SVProgressHUD.showInfo(withStatus: "输入错误,请重新输入")
            }
        })
    }
    
    @objc private func setPrinterPaperType() {
        let picker = GenderPicker.init(with: PDPaperModel.getDatas())
        picker.didSelectedInfoClosure = {[weak self] in
            guard let self = self else { return }
            self.request(data: PLCmdMTGenerator.setPrinterPaper(UInt8($0.id)))
        }
        
    }
    
    @objc private func getPrinterPaperType() {
        request(data: PLCmdMTGenerator.getPrinterPaperType())
        
    }
}

extension MT800SampleViewController: UIDocumentPickerDelegate {
    
    func documentPicker(_ controller: UIDocumentPickerViewController, didPickDocumentAt url: URL) {
        
        sendData(from: url)
    }
    
    func documentPicker(_ controller: UIDocumentPickerViewController, didPickDocumentsAt urls: [URL]) {
        
        sendData(from: urls[0])
    }
    
    func sendData(from url: URL) -> Void {
        
        guard let data = try? Data.init(contentsOf: url) else {
            SVProgressHUD.showError(withStatus: "获取固件失败")
            return
        }
        
        SVProgressHUD.show()
        let resultData = PLCmdMTGenerator.getFirmwareData(data)
        PLDataDispatcher.shared().writeFirmwareData(resultData) { (progress) in
            SVProgressHUD.showProgress(Float(progress.fractionCompleted))
            if progress.fractionCompleted == 1.0 {
                SVProgressHUD.showSuccess(withStatus: "升级成功,请等待打印机重启".localized)
            }
        } fail: {
            SVProgressHUD.showError(withStatus: "升级失败".localized)
        }
        
        PLDataDispatcher.shared().receiveBluetoothDataBlock { (_) in
            
        }
    }
}

/// 这边按照自定义优先级
extension PLMT800PrinterStatus : CustomStringConvertible {
    
    public var description: String {
        var msg = [String]()
        if contains(.highTemperature) {
            msg.append("打印头温度过高")
        }
        if contains(.lowVoltage) {
            msg.append("低电量状态")
        }
        if contains(.headOpened) {
            msg.append("开盖")
        }
        if contains(.carbonRibbonEnd) {
            msg.append("碳带用尽")
        }
        if contains(.paperSmashe) {
            msg.append("装纸异常")
        }
        if contains(.paperAbsent) {
            msg.append("缺纸")
        }
        if contains(.carbonRibbonNotAuthorization) {
            msg.append("RFID验证失败")
        }
        if msg.count > 0 {
            return msg.joined(separator: "-")
        }
        return ""
    }
    
    var buffer : String {
        var message = ""
        if contains(.bufferFull) {
            message = "缓存区不为空"
        }
        return message
    }
}
