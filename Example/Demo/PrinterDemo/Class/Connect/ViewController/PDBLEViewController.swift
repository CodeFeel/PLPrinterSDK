//
//  PDBLEViewController.swift
//  PrinterDemo
//
//  Created by ios on 2019/9/9.
//  Copyright © 2019 XiamenHY. All rights reserved.
//

import UIKit
import PLPrinterSDK

extension UIScrollView {
    
    var tHead: MJRefreshHeader {
        get { return mj_header! }
        set { mj_header = newValue }
    }
    
    var tFoot: MJRefreshFooter {
        get { return mj_footer! }
        set { mj_footer = newValue }
    }
}

class PDBLEViewController: PDBaseViewController {
    
    private var dataSources = [PLPrinterMessage]()
    
    private lazy var tableView : UITableView = {
        let temp = UITableView.init(frame: .zero, style: .grouped)
        temp.delegate = self
        temp.dataSource = self
        temp.backgroundColor = .white
        temp.rowHeight = 60.0
        temp.showsVerticalScrollIndicator = false
        temp.separatorStyle = UITableViewCell.SeparatorStyle.singleLine
        temp.tHead = MJRefreshNormalHeader(refreshingBlock: {[weak self] in self?.searchNearDevices() })
        return temp
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
    }
    
    override func configUI() {
        navigationItem.title = "打印机列表".localized
        PLConnectInterface.shared()?.delegate = self
        
        view.addSubview(tableView)
        tableView.snp.makeConstraints { $0.edges.equalTo(self.view.usnp.edges) }
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        searchNearDevices()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        PLConnectInterface.shared()?.stopScanBluetooth()
    }
    
    @objc private func searchNearDevices() {
        
        if PLConnectInterface.shared()?.getBluetoothStatus() == PLBluetoothState.poweredOn {
            PLConnectInterface.shared()?.stopScanBluetooth()
            PLConnectInterface.shared()?.scanBluetooth()
            
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 3) {
                self.tableView.tHead.endRefreshing()
            }
        }else if PLConnectInterface.shared()?.getBluetoothStatus() == PLBluetoothState.poweredOff {
            SVProgressHUD.showInfo(withStatus: "请打开蓝牙".localized)
        }else {
            SVProgressHUD.showInfo(withStatus: "请前往系统设置中找到您的APP开启蓝牙权限".localized)
        }
    }
}

/// 实现代理协议
extension PDBLEViewController : PLPrinterInterfaceDelegate {
    
    func didDiscoverBLEPrints(_ devices: [PLPrinterMessage]!) {
        self.tableView.tHead.endRefreshing()
        self.dataSources = devices.sorted(by: { return $0.distance.floatValue < $1.distance.floatValue })
        self.tableView.reloadData()
    }
    
    func didConnectSuccess() {
        SVProgressHUD.showSuccess(withStatus: "连接成功".localized)
        self.navigationController?.popToRootViewController(animated: true)
    }
    
    func didConnectFail(_ error: Error!) {
        SVProgressHUD.showError(withStatus: error.localizedDescription)
    }
    
}

extension PDBLEViewController : UITableViewDelegate,UITableViewDataSource {
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataSources.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: "iden")
        if cell == nil {
            cell = UITableViewCell.init(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "iden")
        }
        cell?.textLabel?.text = dataSources[indexPath.row].name
        cell?.detailTextLabel?.text = dataSources[indexPath.row].mac
        
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
        PLConnectInterface.shared()?.connectPrinter(dataSources[indexPath.row])
        #warning("A4这边需要初始化")
        PLDataDispatcher.shared().resolver = PLMT800Resolver()
    }
}






