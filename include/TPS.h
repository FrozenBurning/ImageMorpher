#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include "interpolation.h"
#include "include/SelfCV.h"
class TPS
{
private:
    selfcv::Mat input;//distance between control point and p
    selfcv::Mat output;

    std::vector<cv::Point2d> control_points;
    std::vector<cv::Point2d> target_points;
    std::string result_path;
    bool isReady;

    int n;
    selfcv::Mat K;//[n*n]
    selfcv::Mat P;//[n*3]
    selfcv::Mat L;//{[K,P],[P.t,0]}

    selfcv::Mat V;//[2*n]
    selfcv::Mat Y;

    selfcv::Mat params;//[w1,...,wn,a1,ax,ay]

    cv::Mat img;
    cv::Mat tar_img;

    //径向基
    double tps_U_function(cv::Point2d &src,cv::Point2d &des);
    double tps_U_function(double r);

    //read control points
    std::vector<cv::Point2d> read_control_points(std::string filename);

    //crop image to pretty size
    void scissors(cv::Mat &m);
    bool invalid_pixel(cv::Mat &m,int index,bool isrow);
public:
    TPS(std::string src_file_name,std::string des_file_name);
    ~TPS();

    //model solver, called only one time at the beginning for each case
    void model_solver();
    cv::Point2d TPS_transform(cv::Point2d &p);

    //entrance for frontend
    std::string begin_trans(int inter_method_type);

    bool isInitialized();
};
