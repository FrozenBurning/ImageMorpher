#include "include/interpolation.h"

cv::Vec3b nearestInterpolation(cv::Mat &img, cv::Point2d &p)
{
    int newy = floor(p.y + 0.5);
    int newx = floor(p.x + 0.5);

    if (newy < 0 || newx < 0 || newy > img.rows || newx > img.cols)
    {
        return cv::Vec3b(0,0,0);
    }
    

    return img.at<cv::Vec3b>(newy, newx);
}

cv::Vec3b bilinearInterpolation(cv::Mat &img, cv::Point2d &p)
{
    int bottom_x = floor(p.x);
    int bottom_y = floor(p.y);
    int next_x = bottom_x + 1;
    int next_y = bottom_y + 1;

    if(bottom_x <0 ||bottom_y<0 || bottom_x > img.cols || bottom_y > img.rows)
    {
        return cv::Vec3b(0,0,0);
    }
    return img.at<cv::Vec3b>(bottom_y, bottom_x) * (next_x - p.x) * (next_y - p.y) + img.at<cv::Vec3b>(bottom_y, next_x) * (p.x - bottom_x) * (next_y - p.y) + img.at<cv::Vec3b>(next_y, bottom_x) * (next_x - p.x) * (p.y - bottom_y) + img.at<cv::Vec3b>(next_y, next_x) * (p.x - bottom_x) * (p.y - bottom_y);
}

cv::Vec3b bicubicInterpolation(cv::Mat &img, cv::Point2d &p)
{
    cv::Vec3b target_pix;
    int bottom_x = floor(p.x);
    int bottom_y = floor(p.y);
    double u = p.x - bottom_x;
    double v = p.y - bottom_y;

    if(bottom_x <0 ||bottom_y<0 || bottom_x > img.cols || bottom_y > img.rows)
    {
        return cv::Vec3b(0,0,0);
    }

    double target;

    std::vector<double> C = {BiCubic_kernel(1 + u), BiCubic_kernel(u), BiCubic_kernel(1 - u), BiCubic_kernel(2 - u)};
    std::vector<double> A = {BiCubic_kernel(1 + v), BiCubic_kernel(v), BiCubic_kernel(1 - v), BiCubic_kernel(2 - v)};

    cv::Mat mat_A = cv::Mat(A, CV_64F);
    cv::Mat mat_C = cv::Mat(C, CV_64F);

    cv::Mat mat_B[3] = {cv::Mat::zeros(4, 4, CV_64F), cv::Mat::zeros(4, 4, CV_64F), cv::Mat::zeros(4, 4, CV_64F)};
    // std::cerr << mat_B[0].size()<<mat_B[0]<<std::endl;
    for (int channel = 0; channel < 3; channel++)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (bottom_x - 1 + col < 0)
                    continue;
                if (bottom_y - 1 + row < 0)
                    continue;
                mat_B[channel].at<double>(row, col) = img.at<cv::Vec3b>(bottom_y - 1 + row, bottom_x - 1 + col)[channel];
            }
        }
        cv::Mat f = (mat_A.t()) * mat_B[channel] * mat_C;
        target = f.at<double>(0, 0);
        //std::cerr << target << std::endl;
        target = (target > 255) ? 255 : target;
        target = (target < 0) ? 0 : target;
        target_pix[channel] = target;
    }

    return target_pix;
}

cv::Vec3b Interpolation_handler(cv::Mat &img, cv::Point2d &p, int inter_method_type)
{
    switch (inter_method_type)
    {
    case 0:
        return nearestInterpolation(img, p);
    case 1:
        return bilinearInterpolation(img, p);
    case 2:
        return bicubicInterpolation(img, p);
    default:
        return cv::Vec3b();
        break;
    }
}

double BiCubic_kernel(double x, double a)
{
    double x_abs = fabs(x);
    if (x_abs >= 2) //|x|>=2
        return 0.0;

    double x2_abs = x_abs * x_abs;
    double x3_abs = x2_abs * x_abs;

    if (x_abs <= 1) //|x|<=1
    {
        return (a + 2) * x3_abs - (a + 3) * x2_abs + 1;
    }
    else //1<|x|<2
    {
        return a * x3_abs - 5 * a * x2_abs + 8 * a * x_abs - 4 * a;
    }
}
