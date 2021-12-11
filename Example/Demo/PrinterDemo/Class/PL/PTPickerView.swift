//
//  PTPickerView.swift
//  iOSPrinterDemo
//
//  Created by ios on 2019/2/14.
//  Copyright © 2019 Mellow. All rights reserved.
//

import UIKit

class PTPickerView: UIView {

    lazy var pickerView: UIPickerView = {
        let temp = UIPickerView.init()
        temp.backgroundColor = UIColor.white
        temp.delegate = self
        temp.dataSource = self
        return temp
    }()
    
    var toolBar = UIToolbar()
    var options = [String]()
    var selectItemClosure : ((_ selectedItem:String) -> Void)?
    
    init(with options:[String]) {
        
        super.init(frame: PDAppWindow.bounds)
        self.options = options
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func layoutSubviews() {
        
        configUI()
        configToolBar()
    }
    
    lazy var cancelBtn: UIButton = {
        let temp = UIButton(type: .custom)
        temp.backgroundColor = .clear
        temp.setTitle("取消", for: .normal)
        temp.setTitleColor(UIColor.theme, for: .normal)
        temp.addTarget(self, action: #selector(self.dismiss), for: .touchUpInside)
        return temp
    }()
    
    lazy var okBtn: UIButton = {
        let temp = UIButton(type: .custom)
        temp.backgroundColor = .clear
        temp.setTitle("确定", for: .normal)
        temp.setTitleColor(UIColor.theme, for: .normal)
        temp.addTarget(self, action: #selector(self.pickItemAction), for: .touchUpInside)
        return temp
    }()
    
    func configUI()  {
        
        self.backgroundColor = UIColor.black.withAlphaComponent(0.5)
        
        self.addSubview(pickerView)
        pickerView.snp.makeConstraints {
            $0.left.right.equalToSuperview()
            $0.bottom.equalTo(-kSafeAreaBottomHeight)
            $0.height.equalTo(180)
        }
        
        self.addSubview(toolBar)
        toolBar.snp.makeConstraints {
            $0.left.right.equalToSuperview()
            $0.bottom.equalTo(pickerView.snp.top).offset(0)
            $0.height.equalTo(44)
        }
    }
    
    private func configToolBar() {
        let fixedSpace = UIBarButtonItem.init(barButtonSystemItem: .fixedSpace,
                                              target: nil,
                                              action: nil)
        fixedSpace.width = 20
        let cancelItem = UIBarButtonItem(customView: cancelBtn)
        let confirmItem = UIBarButtonItem(customView: okBtn)
        let space = UIBarButtonItem.init(barButtonSystemItem: .flexibleSpace,
                                         target: nil,
                                         action: nil)
        toolBar.items = [fixedSpace,cancelItem,space,confirmItem,fixedSpace]
    }
    
    @objc func pickItemAction() {
        if options.count > pickerView.selectedRow(inComponent: 0) {
            guard let closure = selectItemClosure else { return }
            closure(options[pickerView.selectedRow(inComponent: 0)])
        }
        self.removeFromSuperview()
    }
    
    @objc func dismiss() {
        self.removeFromSuperview()
    }
    
}

extension PTPickerView : UIPickerViewDelegate,UIPickerViewDataSource {
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return options.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return options[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, rowHeightForComponent component: Int) -> CGFloat {
        return 30.0
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        
//        print(options[row])
    }
    
    func pickerView(_ pickerView: UIPickerView, viewForRow row: Int, forComponent component: Int, reusing view: UIView?) -> UIView {
        
        for subview in pickerView.subviews {
            if subview.frame.size.height < 1 {
                subview.backgroundColor = UIColor.lightGray
            }
        }
        
        var pickLabel = view as? UILabel
        
        if pickLabel == nil {
            pickLabel = UILabel.init()
            pickLabel?.font = UIFont.systemFont(ofSize: 25)
            pickLabel?.textAlignment = .center
            pickLabel?.backgroundColor = UIColor.white
        }
        
        pickLabel?.text = options[row]
        pickLabel?.textColor = UIColor.black
        
        return pickLabel!
    }
    
}
