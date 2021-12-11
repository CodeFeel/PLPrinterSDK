//
//  PDShowStatusView.swift
//  PrinterDemo
//
//  Created by ios on 2020/3/27.
//  Copyright © 2020 XiamenHY. All rights reserved.
//

import UIKit

class PDShowStatusView: UIView {

    lazy var titleLb: UILabel = {
        let temp = UILabel.init()
        temp.text = "打印机状态"
        temp.font = UIFont.boldSystemFont(ofSize: 18)
        temp.textAlignment = .center
        temp.backgroundColor = UIColor.lightDividing
        temp.textColor = UIColor.black
        return temp
    }()
    
    lazy var stateLb: UILabel = {
        let temp = UILabel.init()
        temp.text = "正常"
        temp.font = UIFont.systemFont(ofSize: 15)
        temp.textAlignment = .center
        temp.backgroundColor = UIColor.white
        temp.textColor = UIColor.black
        temp.numberOfLines = 0
        return temp
    }()

    lazy var bgView: UIView = {
        let temp = UIView()
        temp.backgroundColor = UIColor.white
        temp.layer.cornerRadius = PDWidth_pt(x: 16)
        temp.clipsToBounds = true
        return temp
    }()
    
    lazy var bottomView: UIView = {
        let temp = UIView()
        temp.backgroundColor = UIColor.lightDividing
        return temp
    }()
    
    lazy var confirmBtn: UIButton = {
        let temp = UIButton.init(type: .custom)
        temp.backgroundColor = UIColor.lightDividing
        temp.setAttributedTitle(NSAttributedString.init(string: "取消任务", attributes: [NSAttributedString.Key.font:UIFont.boldSystemFont(ofSize: 16),NSAttributedString.Key.foregroundColor:UIColor.blue]), for: UIControl.State.normal)
        temp.addTarget(self, action: #selector(PDShowStatusView.cancelPrintTask), for: UIControl.Event.touchUpInside)
        return temp
    }()
    
    init(with status: String) {
        super.init(frame: PDAppWindow.bounds)
        
        configUI(status)
    }
    
    typealias cancelQueueBlock = () -> Void
    var cancelClosure : cancelQueueBlock?
    
    func callBackCancelBlock(_ block: @escaping cancelQueueBlock) {
        cancelClosure = block
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func configUI(_ printerStatus:String) {
        
        dismiss()
        if printerStatus.isEmpty {
            return
        }
        self.backgroundColor = UIColor.black.withAlphaComponent(0.3)
        self.tag = 1001
        PDAppWindow.addSubview(self)
        
        self.addSubview(bgView)
        bgView.snp.makeConstraints {
            $0.center.equalToSuperview()
            $0.width.equalTo(PDWidth_pt(x: 270))
        }
        
        bgView.addSubview(titleLb)
        titleLb.snp.makeConstraints {
            $0.left.top.right.equalTo(0)
            $0.height.equalTo(55)
        }
        
        bgView.addSubview(confirmBtn)
        confirmBtn.snp.makeConstraints {
            $0.left.right.bottom.equalToSuperview()
            $0.height.equalTo(45)
        }
        
        stateLb.text = printerStatus
        bgView.addSubview(stateLb)
        stateLb.snp.makeConstraints {
            $0.left.equalTo(5)
            $0.right.equalTo(-5)
            $0.top.equalTo(titleLb.snp.bottom).offset(35)
            $0.bottom.equalTo(confirmBtn.snp.top).offset(-35)
        }
    }
}

extension PDShowStatusView {
    
    @objc func cancelPrintTask() {
        guard let tempBlock = cancelClosure else { return }
        tempBlock()
        dismiss()
    }
    
    func dismiss() {
        self.removeFromSuperview()
        PDAppWindow.viewWithTag(1001)?.removeFromSuperview()
    }
}
