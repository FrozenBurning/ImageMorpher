#include "include/morpher.h"
#include "include/TPS.h"
#include "include/distortion.h"

bool morpher(std::string *original_img_path, int transformation_type, int interpolation_method, double radius, double param, std::string *target_img_path, std::string *result_img_path)
{
    switch (transformation_type)
    {
    case tangent_distortion:
    {
        cv::Mat img = cv::imread(*original_img_path);
        cv::Mat newimg;
        newimg.create(img.size(), img.type());
        if (img.empty())
        {
            std::cout << "image read failed!" << std::endl;
            return false;
        }

        cv::Point2d p;
        cv::Point2d newp;
        // row == height == Point.y
        // col == width  == Point.x

        for (int h = 0; h < img.rows; ++h)
        {
            for (int w = 0; w < img.cols; ++w)
            {
                p = cv::Point2d(w, h);
                newp = distort_trans(p, param, radius, cv::Point2d(img.size().width / 2, img.size().height / 2));
                newimg.at<cv::Vec3b>(h, w) = Interpolation_handler(img, newp, interpolation_method);
            }
        }
        //imshow("NewTHU", newimg);
        if(original_img_path->find("meshgrid") == std::string::npos)
        {
            int tmp = original_img_path->find_last_of('/');
            std::string folder = (original_img_path->substr(0,tmp+1));
            *result_img_path = folder + "tangent_distortion.png";
            cv::imwrite(*result_img_path, newimg);
        }
        else{
            *result_img_path = "./tmp.png";
            cv::imwrite(*result_img_path,newimg);
        }
        return true;
    }
    case radical_distortion:
    {
        cv::Mat img = cv::imread(*original_img_path);
        cv::Mat newimg;
        newimg.create(img.size(), img.type());
        if (img.empty())
        {
            std::cout << "image read failed!" << std::endl;
            return false;
        }

        cv::Point2d p;
        cv::Point2d newp;
        // row == height == Point.y
        // col == width  == Point.x

        for (int h = 0; h < img.rows; ++h)
        {
            for (int w = 0; w < img.cols; ++w)
            {
                p = cv::Point2d(w, h);
                newp = plate2sphere(p, radius, cv::Point2d(img.size().width / 2, img.size().height / 2), param);
                newimg.at<cv::Vec3b>(h, w) = Interpolation_handler(img, newp, interpolation_method);
            }
        }
        if(original_img_path->find("meshgrid") == std::string::npos)
        {
            int tmp = original_img_path->find_last_of('/');
            std::string folder = (original_img_path->substr(0,tmp+1));
            *result_img_path = folder + "radical_distortion.png";
            cv::imwrite(*result_img_path, newimg);
        }
        else{
            *result_img_path = "./tmp.png";
            cv::imwrite(*result_img_path,newimg);
        }
        return true;
    }
    case tps:
    {
        TPS TPSer(*original_img_path, *target_img_path);
        if(!TPSer.isInitialized())
        {
            return false;
        }
        *result_img_path = TPSer.begin_trans(interpolation_method);
        return true;
    }
    default:
        return false;
    }
}
