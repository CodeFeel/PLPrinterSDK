//
//  PDMFIViewController.swift
//  PrinterDemo
//
//  Created by ios on 2020/12/2.
//  Copyright © 2020 XiamenHY. All rights reserved.
//

import UIKit

class PDMFIViewController: PDBaseViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func configUI() {
        navigationItem.title = "打印机列表"
        PLConnectInterface.shared()?.delegate = self
              
        view.addSubview(tableView)
        view.addSubview(tableView)
        tableView.snp.makeConstraints {
            $0.left.right.top.equalTo(0)
            $0.bottom.equalTo(-(kSafeAreaBottomHeight + 55))
        }
        
        view.addSubview(searchBtn)
        searchBtn.snp.makeConstraints {
            $0.left.equalTo(11)
            $0.right.equalTo(-11)
            $0.bottom.equalTo(-(kSafeAreaBottomHeight + 15))
            $0.height.equalTo(40)
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        PLConnectInterface.shared()?.scanAccessory()
        PLConnectInterface.shared()?.registerEAAccessoryManagerNotifications()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        PLConnectInterface.shared()?.removeEAAccessoryManagerNotifications()
    }

    private var mfiDevices = [PLPrinterMessage]()
    
    private lazy var tableView : UITableView = {
        let temp = UITableView.init(frame: .zero, style: .grouped)
        temp.delegate = self
        temp.dataSource = self
        temp.backgroundColor = .white
        temp.rowHeight = 60.0
        temp.showsVerticalScrollIndicator = false
        temp.separatorStyle = UITableViewCell.SeparatorStyle.singleLine
        return temp
    }()

    lazy var searchBtn: UIButton = {
        let temp = UIButton.init(type: UIButton.ButtonType.custom)
        temp.backgroundColor = UIColor.theme
        temp.setTitle("查找设备".localized, for: UIControl.State.normal)
        temp.setTitleColor(UIColor.white, for: UIControl.State.normal)
        temp.setTitleColor(UIColor.yellow, for: UIControl.State.highlighted)
        temp.titleLabel?.font = UIFont.systemFont(ofSize: 15)
        temp.layer.masksToBounds = true
        temp.layer.cornerRadius = 20
        temp.addTarget(self, action: #selector(addNewEquiptement), for: .touchUpInside)
        return temp
    }()
        
    @objc private func addNewEquiptement() {
        #warning("这边过滤机型")
        DispatchQueue.main.async {
            PLConnectInterface.shared()?.showBluetoothAccessorys("MT", completion: {
                guard let error = $0 as NSError? else { return }
                switch error.code {
                    case 0:
                        SVProgressHUD.showInfo(withStatus: "已经连接")
                    case 1:
                        SVProgressHUD.showInfo(withStatus: "未找到设")
                    case 2:
                        SVProgressHUD.showInfo(withStatus: "取消连接")
                    case 3:
                        SVProgressHUD.showInfo(withStatus: "连接失败")
                    default:
                        break
                }
            })
        }
    }
    
}

/// 实现代理协议
extension PDMFIViewController : PLPrinterInterfaceDelegate {
    
    func didDiscoverMFIPrints(_ devices: [PLPrinterMessage]!) {
        self.mfiDevices = devices
        self.tableView.reloadData()
    }
    
    func didConnectSuccess() {
        SVProgressHUD.showSuccess(withStatus: "连接成功".localized)
        self.navigationController?.popToRootViewController(animated: true)
    }
    
    func didConnectFail(_ error: Error!) {
        SVProgressHUD.dismiss()
        bk_presentWarningAlertController(title: "提示", message: error.localizedDescription, style: .default)
    }
    
    func observerAccessoryDidConnectedNotification(_ device: PLPrinterMessage!) {

        let index = self.mfiDevices.firstIndex { (temp) -> Bool in
            return temp.name == device.name
        }
        if let index = index {
            if index == NSNotFound {
                self.mfiDevices.append(device)
            }else {
                self.mfiDevices[index] = device
            }
        }else {
            self.mfiDevices.append(device)
        }
        self.tableView.reloadData()
    }
    
    func observerAccessoryDidDisconnectNotification(_ device: PLPrinterMessage!) {
        if let index = self.mfiDevices.firstIndex(where: { (temp) -> Bool in
            return temp.name == device.name
        }), index != NSNotFound {
            self.mfiDevices.remove(at: index)
            self.tableView.reloadData()
        }
        
    }
    
}

extension PDMFIViewController : UITableViewDelegate,UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return mfiDevices.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: "iden")
        if cell == nil {
            cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
        }
        cell?.textLabel?.text = mfiDevices[indexPath.row].name
        cell?.detailTextLabel?.text = mfiDevices[indexPath.row].mac
        
        cell?.textLabel?.textColor = UIColor.black
        cell?.detailTextLabel?.textColor = UIColor.titleColor
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "附近的蓝牙设备".localized
    }
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 45.0
    }
    
    func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.01
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        SVProgressHUD.show(withStatus: "连接中，请稍等".localized)
        PLConnectInterface.shared()?.connectPrinter(mfiDevices[indexPath.row])
        #warning("A4这边需要初始化")
        PLDataDispatcher.shared().resolver = PLMT800Resolver()
    }
}
