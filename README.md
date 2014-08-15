## Hack Dalvik VM解决Android 2.3 DEX/LinearAllocHdr超限 ##

[link to my blog](http://viila.info/2014/04/android-2-3-dex-max-function-problem/)

配合[APKCounter](https://github.com/viilaismonster/ApkFuncCounter)使用更佳

当安卓工程庞大到一定程度（代码结构渣到一定程度）的时候，就会遇到诸如最大方法数超过限制导致无法安装，Crash等问题。

相关关键词：Android 2.3 INSTALL_FAILED_DEXOPT 65535
