//
//  PDPreviewImageControllerViewController.swift
//  PrinterDemo
//
//  Created by ios on 2019/9/11.
//  Copyright © 2019 XiamenHY. All rights reserved.
//

import UIKit
import SVProgressHUD

struct A4 {
    static let size = CGSize(width: 2336, height: 3288)
}

public extension CGRect {
    
    func contentRect(ratio: CGFloat, margin: CGFloat = 0) -> CGRect {
        
        let tempFrame = self.insetBy(dx: margin, dy: margin)
        if tempFrame.width/tempFrame.height > ratio {
            
            let contentWidth = ratio*tempFrame.height
            let result = tempFrame.insetBy(dx: (tempFrame.width - contentWidth)/2, dy: 0)
            return result
        }else {
            
            let contentHeight = tempFrame.width/ratio
            let result = tempFrame.insetBy(dx: 0, dy: (tempFrame.height - contentHeight)/2)
            return result
        }
    }
    
    func insetBy(edgeInset: UIEdgeInsets) -> CGRect {
        
        return CGRect.init(
            x: self.origin.x + edgeInset.left,
            y: self.origin.y + edgeInset.top,
            width: self.size.width - edgeInset.left - edgeInset.right,
            height: self.size.height - edgeInset.top - edgeInset.bottom
        )
    }
}

class PDPreviewImageControllerViewController: PDBaseViewController {
    
    lazy var previewImageView: UIImageView = {
        let temp = UIImageView.init()
        temp.image = self.selectedImage
        temp.backgroundColor = UIColor.white
        return temp
    }()
    
    var selectedImage : UIImage?
    var imageMode = PLBitmapMode.dithering
    var printImage = UIImage()
    
    lazy var bottomView: UIView = {
        let temp = UIView.init()
        temp.backgroundColor = UIColor.white
        temp.translatesAutoresizingMaskIntoConstraints = false
        return temp
    }()
    
    lazy var segmentImageMode = UISegmentedControl.init()
    lazy var segmentDpiMode = UISegmentedControl.init()
    
    lazy var copiesLabel:UILabel = {
        let temp = UILabel.init()
        temp.text = "\(printCopiesCount)"
        temp.textAlignment = .center
        temp.textColor = UIColor.titleColor
        temp.backgroundColor = UIColor.lightDividing
        temp.font = UIFont.systemFont(ofSize: 13)
        temp.adjustsFontSizeToFitWidth = true
        return temp
    }()
    
    lazy var lessCopiesView: UIView = {
        let temp = UIView()
        temp.backgroundColor = UIColor.white
        let tap = UITapGestureRecognizer.init(target: self, action: #selector(lessPrintCopies))
        temp.isUserInteractionEnabled = true
        temp.addGestureRecognizer(tap)
        return temp
    }()
    
    lazy var addCopiesView: UIView = {
        let temp = UIView()
        temp.backgroundColor = UIColor.white
        let tap = UITapGestureRecognizer.init(target: self, action: #selector(addPrintCopies(_:)))
        temp.isUserInteractionEnabled = true
        temp.addGestureRecognizer(tap)
        return temp
    }()
    
    lazy var printBtn : UIButton = {
        let temp = UIButton.init(type: UIButton.ButtonType.custom)
        temp.backgroundColor = UIColor.theme
        temp.setTitle("打印".localized, for: UIControl.State.normal)
        temp.setTitleColor(UIColor.white, for: UIControl.State.normal)
        temp.setTitleColor(UIColor.black, for: UIControl.State.highlighted)
        temp.layer.cornerRadius = PDWidth_pt(x: 18)
        temp.translatesAutoresizingMaskIntoConstraints = false
        temp.addTarget(self, action: #selector(self.startPrint), for: UIControl.Event.touchUpInside)
        return temp
    }()
    
    var printCopiesCount = 1
    var isPackage = false
    var PDPrintDots: CGFloat = 576
    
    var bottomViewHeight : CGFloat = 200.0
    /// 默认压缩LZO
//    var imagePressMode = HYBitmapCompressMode.LZO
    var printerName = ""
    
    var deviceType = PDPrinterType.A4
    var dispatcher : PDPrintDispatcher? // A4打印
    
    init(with previewImage: UIImage, printModel:String) {
        self.selectedImage = previewImage
        self.printerName = printModel
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        navigationItem.title = "打印预览".localized
        view.backgroundColor = UIColor.darkDividing
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
    }
    
    override func configUI() {
        
        view.addSubview(bottomView)
        bottomView.snp.makeConstraints {
            $0.left.right.equalToSuperview()
            $0.bottom.equalTo(self.view.usnp.bottom)
            $0.height.equalTo(PDWidth_pt(x: bottomViewHeight))
        }
        
        //设置imageView的frame
        let willRect = CGRect(x: 20, y: 20 , width: kScreenWidth - 40, height: kScreenHeight - PDWidth_pt(x: bottomViewHeight) - kSafeAreaBottomHeight - 40 - kNavgationHeight)
        let newRect = willRect.contentRect(ratio: selectedImage!.size.width / selectedImage!.size.height)
        previewImageView.frame = newRect
        view.addSubview(previewImageView)
        
        configBottomView()
    }
    
    func configBottomView() {
        
        segmentDpiMode = UISegmentedControl(items: ["2336"])
        segmentDpiMode.selectedSegmentIndex = 0
        if #available(iOS 13, *) {
            segmentDpiMode.selectedSegmentTintColor = UIColor.theme
        }else {
            segmentDpiMode.tintColor = UIColor.theme
        }
        segmentDpiMode.setTitleTextAttributes([NSAttributedString.Key.font:UIFont.systemFont(ofSize: 14),NSAttributedString.Key.foregroundColor:UIColor.black], for: UIControl.State.normal)
        segmentDpiMode.setTitleTextAttributes([NSAttributedString.Key.font:UIFont.systemFont(ofSize: 14),NSAttributedString.Key.foregroundColor:UIColor.white], for: UIControl.State.selected)
        bottomView.addSubview(segmentDpiMode)
        segmentDpiMode.snp.makeConstraints {
            $0.left.equalToSuperview().offset(10)
            $0.right.equalToSuperview().offset(-10)
            $0.top.equalToSuperview().offset(PDWidth_pt(x: 15))
            $0.height.equalTo(PDWidth_pt(x: 40))
        }
        
        segmentImageMode = UISegmentedControl(items: ["二值".localized,"增强扩散".localized, "增强聚集".localized])
        
        segmentImageMode.selectedSegmentIndex = 1
        if #available(iOS 13, *) {
            segmentImageMode.selectedSegmentTintColor = UIColor.theme
        }else {
            segmentImageMode.tintColor = UIColor.theme
        }
        segmentImageMode.setTitleTextAttributes([NSAttributedString.Key.font:UIFont.systemFont(ofSize: 14),NSAttributedString.Key.foregroundColor:UIColor.black], for: UIControl.State.normal)
        segmentImageMode.setTitleTextAttributes([NSAttributedString.Key.font:UIFont.systemFont(ofSize: 14),NSAttributedString.Key.foregroundColor:UIColor.white], for: UIControl.State.selected)
        segmentImageMode.addTarget(self, action: #selector(selectedImageMode), for: UIControl.Event.valueChanged)
        bottomView.addSubview(segmentImageMode)
        segmentImageMode.snp.makeConstraints {
            $0.left.equalToSuperview().offset(10)
            $0.right.equalToSuperview().offset(-10)
            $0.top.equalTo(segmentDpiMode.snp.bottom).offset(PDWidth_pt(x: 15))
            $0.height.equalTo(PDWidth_pt(x: 40))
        }
        
        let printCopiesLb = UILabel()
        printCopiesLb.text = "份数".localized
        printCopiesLb.textAlignment = .left
        printCopiesLb.textColor = UIColor.titleColor
        printCopiesLb.font = UIFont.systemFont(ofSize: 13)
        printCopiesLb.backgroundColor = UIColor.white
        printCopiesLb.adjustsFontSizeToFitWidth = true
        bottomView.addSubview(printCopiesLb)
        printCopiesLb.snp.makeConstraints {
            $0.left.equalTo(10)
            $0.top.equalTo(segmentImageMode.snp.bottom).offset(PDWidth_pt(x: 20))
            $0.width.equalTo(50)
            $0.height.equalTo(PDWidth_pt(x: 50))
        }
        
        bottomView.addSubview(lessCopiesView)
        lessCopiesView.snp.makeConstraints {
            $0.left.equalTo(printCopiesLb.snp.right).offset(0)
            $0.top.equalTo(printCopiesLb)
            $0.width.equalTo(50)
            $0.height.equalTo(PDWidth_pt(x: 50))
        }
        
        bottomView.addSubview(copiesLabel)
        copiesLabel.snp.makeConstraints {
            $0.left.equalTo(lessCopiesView.snp.right).offset(0)
            $0.top.equalTo(printCopiesLb)
            $0.width.equalTo(50)
            $0.height.equalTo(PDWidth_pt(x: 50))
        }
        
        bottomView.addSubview(addCopiesView)
        addCopiesView.snp.makeConstraints {
            $0.left.equalTo(copiesLabel.snp.right).offset(0)
            $0.top.equalTo(printCopiesLb)
            $0.width.equalTo(50)
            $0.height.equalTo(PDWidth_pt(x: 50))
        }
        
        let lessImage = UIImageView.init()
        lessImage.image = UIImage(named: "jian")
        lessCopiesView.addSubview(lessImage)
        lessImage.snp.makeConstraints {
            $0.center.equalToSuperview()
            $0.width.height.equalTo(PDWidth_pt(x: 16))
        }
        
        let addImage = UIImageView.init()
        addImage.image = UIImage(named: "jia")
        addCopiesView.addSubview(addImage)
        addImage.snp.makeConstraints {
            $0.center.equalToSuperview()
            $0.width.height.equalTo(PDWidth_pt(x: 16))
        }
        
        bottomView.addSubview(printBtn)
        printBtn.snp.makeConstraints {
            $0.right.equalToSuperview().offset(-10)
            $0.centerY.equalTo(copiesLabel.snp.centerY)
            $0.width.equalTo(kScreenWidth - 200 - 40)
            $0.height.equalTo(PDWidth_pt(x: 40))
        }
    }
    
    deinit {
        print("PDPreviewImageControllerViewController------")
    }
}

extension PDPreviewImageControllerViewController {
    
    @objc private func lessPrintCopies() {
        
        if printCopiesCount <= 1 {
            return
        }
        printCopiesCount -= 1
        copiesLabel.text = "\(printCopiesCount)"
    }
    
    @objc private func addPrintCopies(_ sender:UITapGestureRecognizer) {
        
        if printCopiesCount >= 100 {
            return
        }
        printCopiesCount += 1
        copiesLabel.text = "\(printCopiesCount)"
    }
    
    @objc private func selectedImageMode() {
        
        if deviceType == .A4 {
            if segmentImageMode.selectedSegmentIndex == 0 {
                imageMode = PLBitmapMode.binary
            }else if segmentImageMode.selectedSegmentIndex == 1 {
                imageMode = PLBitmapMode.dithering
            }else if segmentImageMode.selectedSegmentIndex == 2 {
                imageMode = PLBitmapMode.cluster
            }
        }else {
            
        }
        
    }
    
    @objc private func startPrint() {
        
        if deviceType == .A4 {
            guard let temp = selectedImage else { return }
            printImage = PDResetImage.scaleSourceImage(image: temp, width: A4.size.width, height: A4.size.height)!
            self.printA4Image()
        }
        
    }
}

/// A4
extension PDPreviewImageControllerViewController {
    
    private func printA4Image() {
        
        let infoData = PLCmdMTGenerator.getPrinterStatusInfo()
        PLDataDispatcher.shared().write(infoData, progress: {
            if $0.fractionCompleted == 1.0 {
                /// 数据发送成功
                SVProgressHUD.dismiss()
            }
        }, fail: nil)
        
        PLDataDispatcher.shared().resolver?.resolvedBlock = { [weak self] in
            guard let self = self else { return }
            guard let model = $0 as? PLMT800ResolverModel else { return }

            switch model.type {
                case .printerInfo:
                    print(model.data.hexString)
                    let info = PLMT800Info.init(data: model.data)
                    if !info.state.buffer.isEmpty {
                        self.bk_presentDecisionAlertController(title: "提示", message: "打印机有缓存数据，建议先清缓存", decisionTitle: nil) { (_) in
                            let clearData = PLCmdMTGenerator.clearPrinterBuffer()
                            PLDataDispatcher.shared().write(clearData)
                        }
                        return
                    }
                    let deviceStatus = info.state.description
                    if info.paperType == 0 {
                        UserDefaults.standard.set(false, forKey: PDPaperType)
                    }else {
                        UserDefaults.standard.set(true, forKey: PDPaperType)
                    }
                    self.managerPrintTask(deviceStatus)
                case .clearBuffer:
                    SVProgressHUD.showSuccess(withStatus: "缓存清理成功")
                default:
                    break
            }
        }
                
    }
    
    /// 锐化  --- 增加   扩散/聚集
    func managerPrintTask(_ state: String) {
        
        SVProgressHUD.show()
        DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 0.1) {
            var tasks = [PDImageMode]()
            switch self.imageMode {
                case .binary:
                    let temp = PDImageMode.binary(image: self.printImage)
                    tasks = [PDImageMode].init(repeating: temp, count: self.printCopiesCount)
                case .dithering:
                    let shapeImage = PLBitmapManager.image(toSharpen: self.printImage)
                    guard let procImage = ImgProc.enhanceFilter(shapeImage) else { return }
                    let temp = PDImageMode.dithering(image: procImage)
                    tasks = [PDImageMode].init(repeating: temp, count: self.printCopiesCount)
                case .cluster:
                    let shapeImage = PLBitmapManager.image(toSharpen: self.printImage)
                    guard let procImage = ImgProc.enhanceFilter(shapeImage) else { return }
                    let temp = PDImageMode.cluster(image: procImage)
                    tasks = [PDImageMode].init(repeating: temp, count: self.printCopiesCount)
                case .gray:
                    break
                @unknown default:
                fatalError()
            }
            
            self.dispatcher = PDPrintDispatcher.init(with: tasks)
            if state.isEmpty {
                self.dispatcher?.beginPrint()
            }else {
                let temp = PDShowStatusView.init(with: state)
                temp.callBackCancelBlock {
                    self.dispatcher?.stopPrint(true)
                }
            }
        }
    }
    
}

enum PDImageMode {
    case binary(image:UIImage)
    case dithering(image:UIImage)
    case cluster(image:UIImage)
}

extension PDImageMode : PDPrintTask {
    func bitmapData() -> (Data, UInt16) {
        switch self {
            case .binary(let image):
                let image = PLBitmapManager.image(toSharpen: image)
                let data = PLBitmapManager.generateGenralData(with: image, watermark: false, mode: .binary, compress: .none, package: false)
                return (data,UInt16(image.size.height))
            case .dithering(let image):
                let data = PLBitmapManager.generateGenralData(with: image, watermark: false, mode: .dithering, compress: .none, package: false)
                return (data,UInt16(image.size.height))
            case .cluster(let image):
                let data = PLBitmapManager.generateGenralData(with: image, watermark: false, mode: .cluster, compress: .none, package: false)
                return (data,UInt16(image.size.height))
        
        }
    }
}

 
 
