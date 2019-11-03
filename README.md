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

Given in directory [3rdparty](3rdparty/opencv2)

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
Enter the ImageMorpher folder, then do the following:
```bash
cd path-to-ImageMorpher
mkdir build
cd build
qmake -o Makefile ../ImageMorpher.pro -spec linux-g++
make
```

## 3. Run ImageMorpher

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
