//
//  GenderPicker.swift
//  KangXin
//
//  Created by ios on 2021/11/23.
//

import Foundation
import UIKit

struct PDPaperModel {
    var id = 0
    var name = ""
    
    static func getDatas() -> [PDPaperModel] {
        var models = [PDPaperModel]()
        models.append(PDPaperModel(id: 0, name: "连续纸"))
        models.append(PDPaperModel(id: 1, name: "A4纸"))
        models.append(PDPaperModel(id: 2, name: "黑标纸"))
        return models
    }
}

class GenderPicker: UIView {
    
    private lazy var bgView: UIView = {
        let temp = UIView()
        temp.backgroundColor = UIColor.white
        temp.isUserInteractionEnabled = true
        self.addSubview(temp)
        return temp
    }()
    
    private lazy var pickerView: UIPickerView = {
        let temp = UIPickerView.init()
        temp.backgroundColor = UIColor.white
        temp.delegate = self
        temp.dataSource = self
        bgView.addSubview(temp)
        return temp
    }()
    
    
    private var toolBar = UIToolbar()
    
    lazy var cancelButton: UIButton = {
        let temp = UIButton(type: .custom)
        temp.setTitle("取消", for: .normal)
        temp.setTitleColor(UIColor.black, for: .normal)
        temp.titleLabel?.font = UIFont.systemFont(ofSize: 17)
        temp.addTarget(self, action: #selector(self.dismiss), for: .touchUpInside)
        bgView.addSubview(temp)
        return temp
    }()
    
    lazy var okButton: UIButton = {
        let temp = UIButton(type: .custom)
        temp.setTitle("确定", for: .normal)
        temp.setTitleColor(UIColor.black, for: .normal)
        temp.titleLabel?.font = UIFont.systemFont(ofSize: 17)
        temp.addTarget(self, action: #selector(self.pickItemAction), for: .touchUpInside)
        bgView.addSubview(temp)
        return temp
    }()
    
    private var options = [PDPaperModel]()
    var didSelectedInfoClosure: ((_ info: PDPaperModel) -> Void)?
    
    init(with options: [PDPaperModel]) {
        super.init(frame: PDAppWindow.bounds)
        self.options = options
        makeConstraints()
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func makeConstraints()  {
        PDAppWindow.addSubview(self)
        self.backgroundColor = .clear
        
        bgView.snp.makeConstraints {
            $0.left.right.equalToSuperview()
            $0.bottom.equalTo(kScreenHeight)
            $0.height.equalTo(180 + 44 + kSafeAreaBottomHeight)
        }
        
        cancelButton.snp.makeConstraints {
            $0.left.equalTo(15)
            $0.top.equalToSuperview()
        }
        
        okButton.snp.makeConstraints {
            $0.right.equalTo(-15)
            $0.top.equalToSuperview()
        }
        
        pickerView.snp.makeConstraints {
            $0.left.right.equalToSuperview()
            $0.bottom.equalToSuperview()
            $0.height.equalTo(180 + kSafeAreaBottomHeight)
        }
        UIView.animate(withDuration: 0.25, animations: {
            self.backgroundColor = UIColor.black.withAlphaComponent(0.5)
            self.bgView.transform = CGAffineTransform(translationX: 0, y: -(kScreenHeight))
        })
    }
        
    @objc func pickItemAction() {
        if options.count > pickerView.selectedRow(inComponent: 0) {
            guard let closure = didSelectedInfoClosure else { return }
            closure(options[pickerView.selectedRow(inComponent: 0)])
        }
        dismiss()
    }
    
    @objc func dismiss() {
        UIView.animate(withDuration: 0.3) {
            self.backgroundColor = UIColor.clear
            self.bgView.transform = CGAffineTransform.identity
        } completion: { _ in
            self.bgView.removeFromSuperview()
            self.removeFromSuperview()
        }
    }
}

extension GenderPicker : UIPickerViewDelegate, UIPickerViewDataSource {
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return options.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return options[row].name
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
                subview.backgroundColor = UIColor.lightText
            }
        }
        var pickLabel = view as? UILabel
        if pickLabel == nil {
            pickLabel = UILabel()
            pickLabel?.font = UIFont.systemFont(ofSize: 20)
            pickLabel?.textAlignment = .center
            pickLabel?.backgroundColor = UIColor.white
        }
        
        pickLabel?.text = options[row].name
        pickLabel?.textColor = UIColor.black
        return pickLabel!
    }
    
}
