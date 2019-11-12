#include "include/TPS.h"

TPS::TPS(std::string orig_file_name, std::string target_file_name)
{
    if (orig_file_name.empty() || target_file_name.empty())
    {
        isReady = false;
    }
    else
    {
        isReady = true;
        std::string target_namewithoutExtension = target_file_name.substr(0, target_file_name.find_last_of('.'));
        std::string orig_namewithoutExtension = orig_file_name.substr(0, orig_file_name.find_last_of('.'));

        result_path = orig_file_name.substr(0, orig_file_name.find_last_of('/') + 1);
        result_path = result_path + orig_file_name.substr(orig_file_name.find_last_of('/'));
        result_path = result_path.substr(0, result_path.find_last_of('.')) + "to";
        result_path = result_path + target_file_name.substr(target_file_name.find_last_of('/') + 1);
        result_path = result_path.substr(0, result_path.find_last_of('.')) + ".png";

        control_points = read_control_points(target_namewithoutExtension + ".txt"); //target img
        target_points = read_control_points(orig_namewithoutExtension + ".txt");    //from original img

        if (control_points.empty() || target_points.empty())
        {
            isReady = false;
        }
        

        img = cv::imread(orig_file_name);
        // cv::imshow("trump",img);
        tar_img = cv::imread(target_file_name);
        // cv::imshow("child",tar_img);
        n = control_points.size();
        input = selfcv::Mat(1, n + 3);
    }
}

TPS::~TPS()
{
}

bool TPS::isInitialized()
{
    if (isReady)
        return true;
    else
        return false;
}

std::string TPS::begin_trans(int inter_method_type)
{
    this->model_solver();
    //target.model_solver();
    cv::Point2d spot, tmp;
    cv::Mat tar = cv::Mat::zeros(tar_img.rows, tar_img.cols, CV_8UC3);
    for (int i = 0; i < tar_img.rows; i++)
    {
        for (int j = 0; j < tar_img.cols; j++)
        {
            tmp = cv::Point2d(j, i);
            spot = TPS_transform(tmp);
            if ((spot.x > 0) && (spot.x < img.cols - 1) && (spot.y > 0) && (spot.y < img.rows - 1))
            {
                tar.at<cv::Vec3b>(i, j) = Interpolation_handler(img, spot, inter_method_type);
            }
        }
    }
    std::string name = result_path;
    scissors(tar);
    cv::imwrite(name, tar);
    return name;
}

void TPS::scissors(cv::Mat &m)
{
    cv::Point2i top_left = cv::Point2i(0, 0);
    cv::Point2i bottom_right = cv::Point2i(m.cols - 1, m.rows - 1);
    while (invalid_pixel(m, top_left.x, false))
    {
        top_left.x++;
    }
    while (invalid_pixel(m, top_left.y, true))
    {
        top_left.y++;
    }
    while (invalid_pixel(m, bottom_right.x, false))
    {
        bottom_right.x--;
    }
    while (invalid_pixel(m, bottom_right.y, true))
    {
        bottom_right.y--;
    }
    cv::Rect image_after_cut = cv::Rect(top_left.x, top_left.y, bottom_right.x - top_left.x, bottom_right.y - top_left.y);
    m = m(image_after_cut);
}

bool TPS::invalid_pixel(cv::Mat &m, int index, bool isrow)
{
    cv::Vec3b black = cv::Vec3b(0, 0, 0);
    if (isrow)
    {
        for (int i = 0; i < m.cols; i++)
        {
            if (m.at<cv::Vec3b>(index, i) != black)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        for (int i = 0; i < m.rows; i++)
        {
            if (m.at<cv::Vec3b>(i, index) != black)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

cv::Point2d TPS::TPS_transform(cv::Point2d &p)
{
    for (int i = 0; i < n; i++)
    {
        input.at<double>(0, i) = tps_U_function(p, control_points[i]);
    }

    input.at<double>(0, n) = 1;
    input.at<double>(0, n + 1) = p.x;
    input.at<double>(0, n + 2) = p.y;
    output = input * params;

    return cv::Point2d(output.at<double>(0, 0), output.at<double>(0, 1));
}

double TPS::tps_U_function(double r)
{
    if (r == 0.0)
        return 0.0;
    else
        return r * log10(r);
}

double TPS::tps_U_function(cv::Point2d &src, cv::Point2d &des)
{
    cv::Point2d gap = des - src;
    double distance2 = gap.x * gap.x + gap.y * gap.y;
    return tps_U_function(distance2);
}

void TPS::model_solver()
{
    assert(control_points.size() == target_points.size());
    //mat K
    K = selfcv::Mat::zeros(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            K.at<double>(i, j) = tps_U_function(control_points[i], control_points[j]);
        }
    }

    //mat P
    selfcv::Mat P_xy(control_points);
    selfcv::Mat Identity_column = selfcv::Mat::ones(n, 1);
    P = selfcv::Mat::hconcat(Identity_column, P_xy);

    //mat L
    selfcv::Mat zero_3x3 = selfcv::Mat::zeros(3, 3);
    selfcv::Mat L_row_1;
    L_row_1 = selfcv::Mat::hconcat(K, P);
    selfcv::Mat L_row_2;
    selfcv::Mat PT = P.t();
    L_row_2 = selfcv::Mat::hconcat(PT, zero_3x3);
    L = selfcv::Mat::vconcat(L_row_1, L_row_2);

    //mat Y
    V = selfcv::Mat(target_points);
    selfcv::Mat zero_3x2 = selfcv::Mat::zeros(3, 2);
    Y = selfcv::Mat::vconcat(V, zero_3x2);

    //solve all param for L[w1,...,wn,a1,ax,ay]^T=Y
    params = (L.inv() * Y);
}

std::vector<cv::Point2d> TPS::read_control_points(std::string filename)
{
    std::ifstream input_file(filename);
    std::vector<cv::Point2d> buf;
    double x = 0.0, y = 0.0;
    cv::Point2d p;

    if (!input_file)
    {
        std::cout << "no control points file!" << std::endl;   
        return buf;
    }
    while (!input_file.eof()) //end of file?
    {
        input_file >> x >> y;
        p = cv::Point2d(x, y);
        buf.push_back(p);
    }
    return buf;
}
