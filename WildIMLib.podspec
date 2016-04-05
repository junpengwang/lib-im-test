





Pod::Spec.new do |spec|
spec.name         = 'WildIMLib'
spec.version      = '0.0.1'
spec.license      = { :type => 'MIT' }
spec.homepage     = 'http://www.wilddog.com'
spec.authors      = { 'Wilddog' => 'www.wilddog.com' }
spec.summary      = '野狗 IM 通信能力库'
spec.source       = { :git => 'https://github.com/tonymillion/Reachability.git', :tag => 'v3.1.0' }
spec.source_files = 'Reachability.{h,m}'
spec.framework    = 'SystemConfiguration'
end