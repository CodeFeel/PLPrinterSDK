//
//  UIImageView+add.swift
//  PrinterDemo
//
//  Created by ios on 2019/9/11.
//  Copyright © 2019 XiamenHY. All rights reserved.
//

import Foundation
import Photos

extension UIImageView {
    
    func loadImage(with asset:PHAsset) {
        self.loadImage(with: asset, targetSize: CGSize.init(width: self.bounds.width, height: self.bounds.height))
    }
    
    func loadImage(with asset:PHAsset,targetSize:CGSize) {
        let imageRequest = PHImageRequestOptions()
        imageRequest.isSynchronous = false
        imageRequest.resizeMode = .exact
        imageRequest.deliveryMode = .highQualityFormat
        PHImageManager.default().requestImage(for: asset, targetSize: CGSize.init(width: targetSize.width * kMainScreenScale, height: targetSize.height * kMainScreenScale), contentMode: .aspectFill, options: imageRequest) { (requestImage, info) in
            self.image = requestImage
        }
    }
    
}

extension UITextField {
    // MARK: - 在键盘上添加完成按钮
    func addBackView() {
        let toolView = UIView(frame: CGRect(x: 0, y: 0, width: kScreenWidth, height: 40))
        toolView.backgroundColor = .white
        let finishBtn = UIButton(frame: CGRect(x: kScreenWidth - 60, y: 5, width: 50, height: 30))
        finishBtn.setTitleColor(UIColor.theme, for: .normal)
        finishBtn.setTitle("完成", for: UIControl.State.normal)
        finishBtn.addTarget(self, action: #selector(self.resignFirstResponder), for: UIControl.Event.touchUpInside)
        toolView.addSubview(finishBtn)
        self.inputAccessoryView = toolView
    }
}

extension UITextView {
    // MARK: - 在键盘上添加完成按钮
    func addBackView() {
        let toolView = UIView(frame: CGRect(x: 0, y: 0, width: kScreenWidth, height: 40))
        toolView.backgroundColor = .white
        let finishBtn = UIButton(frame: CGRect(x: kScreenWidth - 60, y: 5, width: 50, height: 30))
        finishBtn.setTitleColor(UIColor.theme, for: .normal)
        finishBtn.setTitle("完成", for: UIControl.State.normal)
        finishBtn.addTarget(self, action: #selector(self.resignFirstResponder), for: UIControl.Event.touchUpInside)
        toolView.addSubview(finishBtn)
        self.inputAccessoryView = toolView
    }
    
}
