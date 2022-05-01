# PLPrinterSDK




#### CocoaPods

To integrate PLPrinterSDK into your Xcode project using CocoaPods, specify it to a target in your Podfile:

```swift
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '9.0'
use_frameworks!

target 'MyApp' do
  # your other pod
  # ...
  pod 'PLPrinterSDK ','~> 0.2.1'
end
```

Then, run the following command:

```swift
$ pod install
```

> If you cannot find the latest version, you can execute `pod repo update` first



#### Warning

If it is a Bluetooth connection, you need to add Bluetooth privacy permissions in Info.plist

```swift
Privacy - Bluetooth Always Usage Description
```

```swift
Privacy - Bluetooth Peripheral Usage Description
```



### Document

```swift
请查看Example的文档说明
```

支持任何机型
