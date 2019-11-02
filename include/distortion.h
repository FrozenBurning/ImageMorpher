#pragma once
#include <opencv2/opencv.hpp>

// for radical distortion trans
cv::Point2d plate2sphere(cv::Point2d point_on_sphere,double radius,cv::Point2d centre,double distort_k);

//for tangent distortion trans
cv::Point2d distort_trans(cv::Point2d &p,double max_rotation,double radius,cv::Point2d centre);
