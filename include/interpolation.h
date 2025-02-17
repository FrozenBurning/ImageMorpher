#pragma once
#include <opencv2/opencv.hpp>
#include "include/SelfCV.h"

//Interpolation methods
cv::Vec3b nearestInterpolation(cv::Mat &img, cv::Point2d &p);
cv::Vec3b bilinearInterpolation(cv::Mat &img,cv::Point2d &p);
cv::Vec3b bicubicInterpolation(cv::Mat &img,cv::Point2d &p);
cv::Vec3b LanczosInterpolation(cv::Mat &img,cv::Point2d &p);

double BiCubic_kernel(double x,double a=-1.0);
double Lanczos_kernel(double x,double a=3.0);

cv::Vec3b Interpolation_handler(cv::Mat &img,cv::Point2d &p,int inter_method_type);
