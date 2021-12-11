//
//  PDMainViewController.swift
//  PrinterDemo
//
//  Created by ios on 2019/9/6.
//  Copyright © 2019 XiamenHY. All rights reserved.
//

import UIKit

enum PDSectionIndex : Int {
    case device = 0
    case command
    case appendix
}

public struct PDSettingCellItem {
    var title: String
    var detailTitle: String?
    weak var target: NSObject?
    var selector: Selector?
}

class PDMainViewController: PDBaseViewController {

    private lazy var tableView : UITableView = {
        let tw = UITableView(frame: CGRect.zero, style: UITableView.Style.grouped)
        tw.delegate = self
        tw.dataSource = self
        tw.rowHeight = 50
        tw.backgroundColor = UIColor.white
        tw.showsVerticalScrollIndicator = false
        tw.separatorStyle = UITableViewCell.SeparatorStyle.singleLine
        return tw
    }()
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        navigationItem.title = "iOS SDK"
        navigationItem.leftBarButtonItem = UIBarButtonItem.init(title: "断开".localized, style: UIBarButtonItem.Style.plain, target: self, action: #selector(disconnectDevice))
    }
    
    
    @objc private func disconnectDevice() {
        PLConnectInterface.shared()?.disconnect()
    }
    
    override func configUI() {
        
        view.addSubview(tableView)
        tableView.snp.makeConstraints {
            $0.edges.equalTo(self.view.usnp.edges).priority(.low)
            $0.top.equalToSuperview()
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        tableView.reloadData()
        /// 遵循代理，目的是在主界面调用断开连接的方法
        PLConnectInterface.shared()?.delegate = self
    }
    
}

extension PDMainViewController : PLPrinterInterfaceDelegate {

    func didDisconnect() {
        SVProgressHUD.showInfo(withStatus: "设备已断开".localized)
        self.navigationController?.popToRootViewController(animated: true)
        self.tableView.reloadData()
    }
}

extension PDMainViewController : UITableViewDelegate,UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return PDSectionIndex.appendix.rawValue + 1
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        var title = ""
        
        switch PDSectionIndex.init(rawValue: section)?.rawValue {
        case PDSectionIndex.device.rawValue:
            title = "目标设备".localized
        case PDSectionIndex.command.rawValue:
            title = "打印机指令".localized
        case PDSectionIndex.appendix.rawValue:
            title = "附录".localized
        case .none:
            title = ""
        case .some(_):
            title = ""
        }
         return title
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == PDSectionIndex.device.rawValue {
            return 1
        }
        if section == PDSectionIndex.command.rawValue {
            return 1
        }
        if section == PDSectionIndex.appendix.rawValue {
            return 1
        }
        return 1
    }
    
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 40
    }
    
    func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.01
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "iden")
        
        if indexPath.section == 0 {
            if cell == nil {
                cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
            }
            if cell != nil {
                if PLConnectInterface.shared()?.deviceConnected == nil {
                    cell?.backgroundColor = UIColor(red: 0.8, green: 0.9, blue: 1.0, alpha: 1.0)
                    
                    cell?      .textLabel!.text = "未连接".localized
                    cell?.detailTextLabel!.text = ""
                    
                    cell?      .textLabel!.textColor = UIColor.theme
                    cell?.detailTextLabel!.textColor = UIColor.theme
                    
                    UIView.beginAnimations(nil, context: nil)
                    
                    cell?      .textLabel!.alpha = 0.0
                    cell?.detailTextLabel!.alpha = 0.0
                    
                    UIView.setAnimationDelay             (0.0)                             // 0mS!!!
                    UIView.setAnimationDuration          (0.6)                             // 600mS!!!
                    UIView.setAnimationRepeatCount       (Float(UINT32_MAX))
                    UIView.setAnimationRepeatAutoreverses(true)
                    UIView.setAnimationCurve             (UIView.AnimationCurve.easeIn)
                    
                    cell?      .textLabel!.alpha = 1.0
                    cell?.detailTextLabel!.alpha = 1.0
                    
                    UIView.commitAnimations()
                }else {
                    cell?.textLabel?.text = PLConnectInterface.shared()?.deviceConnected.name
                    cell?.textLabel?.textColor = UIColor.black
                }
                cell?.accessoryType = UITableViewCell.AccessoryType.disclosureIndicator
                cell?.isUserInteractionEnabled = true
            }
        }else {
            
            let cmdTypes = ["A4机型"]
            if indexPath.section == 1 {
                
                if cell == nil {
                    cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
                }
                cell?      .textLabel!.text = cmdTypes[indexPath.row]
                cell?.detailTextLabel!.text = ""
                
                cell?      .textLabel!.textColor = UIColor.titleColor
                cell?.detailTextLabel!.textColor = UIColor.titleColor
                cell?.accessoryType = UITableViewCell.AccessoryType.disclosureIndicator
            }
            
            let appdixs = ["日志".localized]
            if indexPath.section == 2 {
                
                if cell == nil {
                    cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
                }
                
                cell?      .textLabel!.text = appdixs[indexPath.row]
                cell?.detailTextLabel!.text = ""
                
                cell?      .textLabel!.textColor = UIColor.black
                cell?.detailTextLabel!.textColor = UIColor.black
            }
            
        }
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let selectedSection = PDSectionIndex.init(rawValue: indexPath.section)!
        switch (selectedSection,indexPath.row) {
        case (PDSectionIndex.device,0):
            showConnectType()
        case (PDSectionIndex.command, _):
            if PLConnectInterface.shared()?.deviceConnected == nil {
                bk_presentWarningAlertController(title: "提示", message: "打印机未连接，请先连接", style: .default) { (_) in
                    self.showConnectType()
                }
            }else {
                self.navigationController?.pushViewController(MT800SampleViewController(), animated: true)
            }
        case (PDSectionIndex.appendix,let row):
            
            if row == 0 {
                self.navigationController?.pushViewController(PDLogViewController(), animated: true)
            }
            
        default:
            break
        }
    }
}

//connect
extension PDMainViewController {
    
    private func showConnectType() {
                
        let bleAction = UIAlertAction(title: "BLE", style: .default) { (_) in
            self.pushBleController()
        }
        let mfiAction = UIAlertAction(title: "MFI", style: .default) { (_) in
            self.pushMFIController()
        }
        let cancel = UIAlertAction(title: "取消", style: .cancel, handler: nil)
        bk_presentAlertController(title: "提示", message: "请选择一种连接方式", preferredStyle: .alert, actions: [bleAction, mfiAction, cancel])
    }
    
    @objc private func pushBleController() {
        navigationController?.pushViewController(PDBLEViewController(), animated: true)
    }
    
    @objc private func pushMFIController() {
        navigationController?.pushViewController(PDMFIViewController(), animated: true)
    }
}


