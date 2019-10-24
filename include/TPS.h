#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include "interpolation.h"

class TPS
{
private:
    cv::Mat input;//distance between control point and p
    cv::Mat output;

    std::vector<cv::Point2d> control_points;
    std::vector<cv::Point2d> target_points;
    std::string result_path;
    bool isReady;

    int n;
    cv::Mat K;//[n*n]
    cv::Mat P;//[n*3]
    cv::Mat L;//{[K,P],[P.t,0]}

    cv::Mat V;//[2*n]
    cv::Mat Y;
    
    cv::Mat params;//[w1,...,wn,a1,ax,ay]

    cv::Mat img;
    cv::Mat test;
    cv::Mat tar_img;
    double tps_U_function(cv::Point2d &src,cv::Point2d &des);
    double tps_U_function(double r);
    std::vector<cv::Point2d> read_control_points(std::string filename);
    void scissors(cv::Mat &m);
    bool invalid_pixel(cv::Mat &m,int index,bool isrow);
public:
    TPS(std::string src_file_name,std::string des_file_name);
    ~TPS();

    void model_solver();
    cv::Point2d TPS_transform(cv::Point2d &p);

    std::string begin_trans(int inter_method_type);

    bool isInitialized();
};
