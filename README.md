# ImageMorpher
## Numercial Analysis Project 1

ImageMorpher is an application that can do tangent or radical distortion in images with customized params, as well as face morphing between 2 images within the help of given 68 control points from figures' faces. The GUI is developed on framework of Qt5.

**Features:**

- 使用给定参数对原图进行中心切向畸变或径向畸变
- 支持插值函数：最近邻、双线性、双三次
- 使用给定脸部特征点的两张人脸图片，可实现基于TPS的人脸融合变形。


**Author:** 陈昭熹 2017011552

## 1.Prerequisites

### 1.1 OS

Ubuntu 18.04 LTS

### 1.2 OpenCV

Given in directory [3rdparty](3rdparty/)
在3rdparty中含有编译好的动态库v3.2.0 以及opencv源码v3.4.1供不同环境情况使用。

### 1.3 Compiler

- qmake version 3.1, using Qt version 5.9.5
###### Install qmake if you don't have one
```bash
sudo apt-get install qt5-qmake
sudo apt-get install libqt5-dev
```
Then do ```qmake -v``` checking for installation

- g++ 7.4.0 (actually lower or higher version can also works)

## 2. Build ImageMorpher

### 2.1 方式一：Use Dynamic Library in 3rdparty/lib
Enter the ImageMorpher folder, then do the following:
```bash
cd path-to-ImageMorpher
mkdir build
cd build
qmake -o Makefile ../ImageMorpher.pro -spec linux-g++
make 
(or 'make -j8' for speed)
```
### 2.2 方式二： 如果方式一编译失败，为了避免不必要的环境问题则请使用提供的Opencv库，该步骤只需要编译opencv不需要安装，不会破坏本地环境，请放心。
```bash
cd path-to-ImageMorpher
cd 3rdparty/opencv-3.4.1
mkdir build
cd build
cmake -D WITH_CUDA=OFF -D CMAKE_BUILD_TYPE=Release ..
make -j8
(... waiting compiling opencv-3.4.1...)

cd ../../..
mkdir build_isolated
cd build_isolated
qmake -o Makefile ../ImageMorpher_isolated.pro -spec linux-g++
make 
(or 'make -j8' for speed)
```

## 3. Run ImageMorpher

**请在运行前，将提供的资源图片`meshgrid.png`放置在应用所在目录中，以获得通过网格来实时直观显示变形效果的功能。**
### Option1
Enter build folder and double-click the execuable ImageMorpher.

### Option2
```bash
cd path-to-ImageMorpher
cd build
./ImageMorpher
```

## Report
See [report.pdf](report/report.pdf)
Latex source code at [report.tex](report/report.tex)
