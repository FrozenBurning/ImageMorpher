#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

//my cv mat
namespace selfcv
{
    
    class Mat
    {
    public:
        int _rows;
        int _cols;
        int _size;
        double *_data;

        Mat();
        Mat(int rows,int cols);
        // Mat(cv::Mat &img);
        Mat(const Mat &img);
        Mat(std::vector<double> &v);
        Mat(std::vector<cv::Point2d> &v);
        ~Mat();

        Mat t();
        Mat inv();

        //same as inv,solve linear equations
        bool Solve(Mat A,Mat b,Mat x,int n);

        Mat& operator=(Mat &img);
        Mat operator=(Mat img);
        Mat operator+(Mat &img);
        Mat operator*(Mat &img);

        static Mat hconcat(Mat &img1,Mat &img2);
        static Mat vconcat(Mat &img1,Mat &img2);

        static Mat zeros(int rows,int cols);
        static Mat ones(int rows,int cols);

        //operator
        template<typename T>T& at(int row,int col){return ((T *)_data)[row * _cols + col];}
    };

    
} // namespace selfcv


