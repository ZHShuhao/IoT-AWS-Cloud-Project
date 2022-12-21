# Arduino项目迁移到VSCode+Platformio。

1. Arduino 生成的是.ino文件。需要将ino文件转化成.cpp文件。一种是直接复制代码，重新生成.cpp文件。另外一种是在源文件头部增加#include <Arduino.h>头文件。其实作用就是把.ino文件转换成.cpp文件。

2. 对应生成include，src目录下的文件。暂时只能手动添加。

3. 添加完成后需要根据特定的板子下载对应的库。ioT项目使用的是Heltec的esp32 LoRa WIFI 32 (v2) 的板子。一开始所有配置都设置好后出现一个错误：“collect2:error:ld returned 1 exit status”。网上尝试各种方案都没有解决，然后就想到了没有安装对应的开发库。然后在Platformio的主页面上下载和安装Heltec esp32 LoRa WIFI 32 (v2)对应的依赖库，成功运行。

   ![image-20221129101415817](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20221129101415817.png)