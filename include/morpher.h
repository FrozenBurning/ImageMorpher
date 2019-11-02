#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

//mode defined
#define tangent_distortion 0
#define radical_distortion 1
#define tps 2

//entrance for morpher, waiting for call from frontend
bool morpher(std::string* original_img_path,int transformation_type,int interpolation_method, double radius,double param,std::string* target_img_path,std::string* result_img_path);