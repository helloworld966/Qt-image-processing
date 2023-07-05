# Qt-image-processing

## 1. 声明介绍
### 简介
简单记录在图像处理的学习上使用的算法，主要对图像预处理、图像滤波、边缘检测、噪声处理、特征提取、特征匹配等算法使用QT进行可视化。

### 环境
软件使用的是QT5.12+vs2019+opencv-3.4.1+win10进行实现，其他版本均可以，由于在CMake编译opencv_contrib的时候出现些问题，导致一些如SURF、BRIEF等算法不能使用。
完整版操作视频可以观看[哔哩哔哩](https://www.bilibili.com/video/BV1uM4y1j7pF/?vd_source=a509462229ac40b30e078ef4e726ffa7)
### 环境配置
#### 1. QT5.12在官网https://download.qt.io/archive/qt/下载
#### 2. opencv3.4.1在[GitHub](https://github.com/opencv/opencv/releases) 中下载
#### 3. 如需使用SURF等算法需在[opencv_contrib](https://github.com/opencv/opencv_contrib/tags)中下载opencv_contrib-3.4.1，版本要对应好，并下载CMake对opencv_contrib进行编译，可以参考[这篇博客](https://blog.csdn.net/Chris_zhangrx/article/details/79090463)。写的很不错，但是不知道我在哪里出了问题，导致总是缺少一些文件，不能正常使用。
#### 4. vs2019配置opencv-3.4.1
##### 1) 在解决方案中右键属性，在VC++目录中的包含目录中加入opencv中的下图中的两个文件
![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/ae6d7ab8-8e45-44d8-94fc-35f1f7d99008)

##### 2) 在VC++目录的库目录中加入加入opencv的lib

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/4f8bb15f-0a0c-4946-8837-f91705aac717)

##### 3) 在链接器中的输入里找到附加依赖项，加入opencv的动态链接库
![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/a8cde3c8-6690-4357-855c-bb6f6f752df0)


## 2. 软件展示

#### 1. 登录界面-username：admin  password-123456 随意修改

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/5569119c-9509-4aac-9e52-9f610f4ceee8)


#### 2. 主界面-主要实现以下几种算法

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/4b4bfd04-816a-4b52-836c-891bf55bc6ce)


#### 3. 图像预处理-实现图像灰度、直方图、翻转、旋转等


![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/0b447e57-7b22-4bdb-ba82-a50aa87ae100)

#### 3. 图像滤波器-实现图像高斯、双边、中值、均值滤波、形态学操作的腐蚀和膨胀


![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/723b8062-59ab-4e33-950b-8a87189c3bd0)


#### 4. 图像噪声-椒盐、高斯

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/d0b2a56e-80a7-4eb7-8587-794690894e00)

#### 5. 特征提取-ORB、Harris、Fast

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/72eb5306-1198-489f-b223-c0bb1046ce55)


#### 6. 特征匹配

![image](https://github.com/helloworld966/Qt-image-processing/assets/59432598/3821d83e-9064-4106-ac53-75c7cbe3fa42)



## 2. 写在最后
记录对QT和opencv的学习，可能有些代码写的比较冗余，效率不高，还请各位看客不要责备，其中一部分函数是直接调用opencv中的函数进行实现。
理论部分可以参考[博客](https://blog.csdn.net/weixin_44945253?spm=1010.2135.3001.5343)。
### 后续可能会继续添加新的算法！

