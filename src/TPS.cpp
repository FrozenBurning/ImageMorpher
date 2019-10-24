#include "include/TPS.h"

TPS::TPS(std::string orig_file_name, std::string target_file_name)
{
    if(orig_file_name.empty() || target_file_name.empty())
    {
        isReady = false;
    }
    else
    {
        isReady = true;
        std::string target_namewithoutExtension = target_file_name.substr(0,target_file_name.find_last_of('.'));
        std::string orig_namewithoutExtension = orig_file_name.substr(0,orig_file_name.find_last_of('.'));

        result_path = orig_file_name.substr(0,orig_file_name.find_last_of('/')+1);
        result_path = result_path + orig_file_name.substr(orig_file_name.find_last_of('/'));
        result_path = result_path.substr(0,result_path.find_last_of('.')) + "to";
        result_path = result_path + target_file_name.substr(target_file_name.find_last_of('/')+1);
        result_path = result_path.substr(0,result_path.find_last_of('.')) + ".png";

        control_points = read_control_points(target_namewithoutExtension + ".txt");//target img
        target_points = read_control_points(orig_namewithoutExtension + ".txt"); //from original img

        img = cv::imread(orig_file_name);
        // cv::imshow("trump",img);
        tar_img = cv::imread(target_file_name);
        // cv::imshow("child",tar_img);
        n = control_points.size();
        input = cv::Mat(1, n + 3, CV_64F);
    }
}

TPS::~TPS()
{
}

bool TPS::isInitialized()
{
    if(isReady) return true;
    else return false;
}

std::string TPS::begin_trans(int inter_method_type)
{
    this->model_solver();
    //target.model_solver();
    cv::Point2d spot, tmp;
    cv::Mat tar =cv::Mat::zeros(tar_img.rows,tar_img.cols,CV_8UC3);
    for (int i = 0; i < tar_img.rows; i++)
    {
        for (int j = 0; j < tar_img.cols; j++)
        {
            tmp = cv::Point2d(j,i);
            spot = TPS_transform(tmp);
            if((spot.x>0)&&(spot.x<img.cols-1)&&(spot.y>0)&&(spot.y<img.rows-1))
            {
                tar.at<cv::Vec3b>(i,j) = Interpolation_handler(img,spot,inter_method_type);
            }

        }
        
    }
    std::string name = result_path;
    scissors(tar);
    cv::imwrite(name,tar);
    return name;
    
    //cv::imshow("TPS",tar);
    
    // //find the region to be transformed which is defined by x_border & y_border
    // std::vector<double> x_border, y_border;

    // int region[4] = {0,0,0,0}; //{x_min,x_max,y_min,y_max}
    // for (int i = 0; i < img.rows; i++)
    // {
    //     tmp = cv::Point2d(0, i);
    //     spot = this->TPS_transform(tmp);
    //     x_border.push_back(spot.x);
    //     y_border.push_back(spot.y);

    //     tmp = cv::Point2d(img.cols - 1, i);
    //     spot = this->TPS_transform(tmp);
    //     x_border.push_back(spot.x);
    //     y_border.push_back(spot.y);
    // }
    // for (int i = 0; i < img.cols; i++)
    // {
    //     tmp = cv::Point2d(i, 0);
    //     spot = this->TPS_transform(tmp);
    //     x_border.push_back(spot.x);
    //     y_border.push_back(spot.y);

    //     tmp = cv::Point2d(i, img.rows - 1);
    //     spot = this->TPS_transform(tmp);
    //     x_border.push_back(spot.x);
    //     y_border.push_back(spot.y);
    // }
    // region[0] = *(std::min_element(x_border.begin(), x_border.end())); //x_min
    // region[1] = *(std::max_element(x_border.begin(), x_border.end())); //x_max
    // region[2] = *(std::min_element(y_border.begin(), y_border.end())); //y_min
    // region[3] = *(std::max_element(y_border.begin(), y_border.end())); //y_max

    // //grid to be interpolated
    // cv::Mat grid = cv::Mat::zeros(region[3] - region[2] + 101, region[1] - region[0] + 101, CV_64FC2); //channel0-x channel1-y
    // for (int i = 0; i < grid.rows; i++)
    // {
    //     for (int j = 0; j < grid.cols; j++)
    //     {
    //         grid.at<cv::Vec2d>(i, j)[0] = j + region[0];
    //         grid.at<cv::Vec2d>(i, j)[1] = i + region[2];
    //     }
    // }

    // cv::Mat des =cv::Mat::zeros(grid.rows,grid.cols,CV_8UC3);
    // for (int i = 0; i < grid.rows; i++)
    // {
    //     for (int j = 0; j < grid.cols; j++)
    //     {
    //         tmp = cv::Point2d(grid.at<cv::Vec2d>(i,j)[0],grid.at<cv::Vec2d>(i,j)[1]);
    //         spot = target.TPS_transform(tmp);
    //         des.at<cv::Vec3b>(i,j)=Interpolation_handler(img,spot,inter_method_type);
    //     }
        
    // }

    // cv::imshow("TPS",des);
    
}

void TPS::scissors(cv::Mat &m)
{
    cv::Point2i top_left = cv::Point2i(0,0);
    cv::Point2i bottom_right = cv::Point2i(m.cols-1,m.rows-1);
    while (invalid_pixel(m,top_left.x,false))
    {
        top_left.x++;
    }
    while (invalid_pixel(m,top_left.y,true))
    {
        top_left.y++;
    }
    while (invalid_pixel(m,bottom_right.x,false))
    {
        bottom_right.x--;
    }
    while (invalid_pixel(m,bottom_right.y,true))
    {
        bottom_right.y--;
    }
    cv::Rect image_after_cut = cv::Rect(top_left.x,top_left.y,bottom_right.x-top_left.x,bottom_right.y-top_left.y);
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
    assert(control_points.size()==target_points.size());
    //mat K
    K = cv::Mat::zeros(n, n, CV_64F);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j)continue;
            K.at<double>(i, j) = tps_U_function(control_points[i], control_points[j]);
        }
    }

    //mat P
    cv::Mat P_xy = cv::Mat(control_points.size(), 2, CV_64F, control_points.data());
    cv::Mat Identity_column = cv::Mat::ones(n, 1, CV_64F);
    cv::hconcat(Identity_column, P_xy, P);

    //mat L
    cv::Mat zero_3x3 = cv::Mat::zeros(3, 3, CV_64F);
    cv::Mat L_row_1;
    cv::hconcat(K, P, L_row_1);
    cv::Mat L_row_2;
    cv::hconcat(P.t(), zero_3x3, L_row_2);
    cv::vconcat(L_row_1, L_row_2, L);

    //mat Y
    V = cv::Mat(target_points.size(), 2, CV_64F, target_points.data());
    cv::Mat zero_3x2 = cv::Mat::zeros(3, 2, CV_64F);
    cv::vconcat(V, zero_3x2, Y);

    //solve all param for L[w1,...,wn,a1,ax,ay]^T=Y
    params = (L.inv() * Y);
}

std::vector<cv::Point2d> TPS::read_control_points(std::string filename)
{
    std::ifstream input_file(filename);
    std::vector<cv::Point2d> buf;
    double x = 0.0, y = 0.0;
    cv::Point2d p;
    while (!input_file.eof()) //end of file?
    {
        input_file >> x >> y;
        p = cv::Point2d(x, y);
        buf.push_back(p);
    }
    return buf;
}
