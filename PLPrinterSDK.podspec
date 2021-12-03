#
# Be sure to run `pod lib lint PrinterSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'PLPrinterSDK'
  s.version          = '0.1.0'
  s.summary          = 'A repository for bluetooth or mfi and printer communications.'
  s.description      = 'A library for bluetooth and printer communication. Bluetooth connection, data processing, and sending data are encapsulated in the library, and the API can be called directly'
                        
  s.homepage         = 'https://github.com/CodeFeel/PLPrinterSDK'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'CodeFeel' => '492262370@qq.com' }
  s.source           = { :git => 'https://github.com/CodeFeel/PLPrinterSDK.git', :tag => "#{s.version}" }
  s.ios.deployment_target = '8.0'

  s.frameworks = 'UIKit', 'CoreBluetooth', 'Foundation', 'CoreGraphics'
  s.ios.vendored_frameworks = 'Framework/PLPrinterSDK.framework'
  s.vendored_frameworks = 'PLPrinterSDK.framework'
end
