#include "include/SelfCV.h"

selfcv::Mat::Mat() : _rows(0), _cols(0), _data(nullptr)
{
    _size = _rows * _cols;
}

selfcv::Mat::~Mat()
{
    if (_data)
    {
        delete[] _data;
    }
}

selfcv::Mat::Mat(int rows, int cols) : _rows(rows), _cols(cols)
{
    _size = _rows * _cols;
    _data = new double[_rows * _cols];
}

selfcv::Mat::Mat(const selfcv::Mat &img)
{
    _rows = img._rows;
    _cols = img._cols;
    _size = img._size;

    _data = new double[_size];
    memcpy(_data, img._data, sizeof(double) * _size);
}

selfcv::Mat::Mat(std::vector<double> &v) : Mat(v.size(), 1)
{
    for (int i = 0; i < v.size(); i++)
    {
        _data[i] = v[i];
    }
}

selfcv::Mat::Mat(std::vector<cv::Point2d> &v) : Mat(v.size(), 2)
{
    for (int i = 0; i < v.size(); i++)
    {
        this->at<double>(i, 0) = v[i].x;
        this->at<double>(i, 1) = v[i].y;
    }
}

selfcv::Mat selfcv::Mat::t()
{
    selfcv::Mat trans(_cols, _rows);
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            trans.at<double>(j, i) = this->at<double>(i, j);
        }
    }
    return trans;
}

selfcv::Mat selfcv::Mat::inv()
{
    // assert(_rows == _cols);
    int n = _rows;

    selfcv::Mat inversed(n, n);
    double tmp[n][2 * n];
    double bridge;
    for (int i = 0; i < n; i++)
    {
        memcpy(tmp[i], &this->_data[i * n], sizeof(double) * n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < 2 * n; j++)
        {
            if (i == j - n)
                tmp[i][j] = 1;
            else
            {
                tmp[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        bridge = tmp[i][i];
        if (bridge != 0)
        {
            for (int j = i; j < 2 * n; j++)
            {
                tmp[i][j] = tmp[i][j] / bridge;
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                bridge = tmp[j][i];
                for (int k = 0; k < 2 * n; k++)
                {
                    tmp[j][k] = tmp[j][k] - bridge * tmp[i][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        memcpy(&inversed._data[i * n], &tmp[i][n], sizeof(double) * n);
    }

    return inversed;
}


selfcv::Mat &selfcv::Mat::operator=(selfcv::Mat &img)
{
    if (_data)
        delete[] _data;
    _rows = img._rows;
    _cols = img._cols;
    _size = img._size;

    _data = new double[_size];
    memcpy(_data, img._data, sizeof(double) * _size);

    return *this;
}

selfcv::Mat selfcv::Mat::operator=(selfcv::Mat img)
{
    if (_data)
        delete[] _data;
    _rows = img._rows;
    _cols = img._cols;
    _size = img._size;

    _data = new double[_size];
    memcpy(_data, img._data, sizeof(double) * _size);

    return *this;
}

selfcv::Mat selfcv::Mat::operator+(selfcv::Mat &img)
{
    selfcv::Mat sum(img);
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            sum.at<double>(i, j) = sum.at<double>(i, j) + img.at<double>(i, j);
        }
    }
    return sum;
}

selfcv::Mat selfcv::Mat::operator*(selfcv::Mat &img)
{
    selfcv::Mat multiple(_rows, img._cols);
    double sum = 0.0;
    for (int i = 0; i < multiple._rows; i++)
    {
        for (int j = 0; j < multiple._cols; j++)
        {
            sum = 0;
            for (int k = 0; k < _cols; k++)
            {
                sum += this->at<double>(i, k) * img.at<double>(k, j);
            }
            multiple.at<double>(i, j) = sum;
        }
    }

    return multiple;
}

selfcv::Mat selfcv::Mat::hconcat(selfcv::Mat &img1, selfcv::Mat &img2)
{
    selfcv::Mat des(img1._rows, img1._cols + img2._cols);
    for (int i = 0; i < des._rows; i++)
    {
        for (int j = 0; j < des._cols; j++)
        {
            if (j < img1._cols)
            {
                des.at<double>(i, j) = img1.at<double>(i, j);
            }
            //connect
            else
            {
                des.at<double>(i, j) = img2.at<double>(i, j - img1._cols);
            }
        }
    }
    return des;
}

selfcv::Mat selfcv::Mat::vconcat(selfcv::Mat &img1, selfcv::Mat &img2)
{
    selfcv::Mat des(img1._rows + img2._rows, img1._cols);
    for (int i = 0; i < des._rows; i++)
    {
        for (int j = 0; j < des._cols; j++)
        {
            if (i < img1._rows)
            {
                des.at<double>(i, j) = img1.at<double>(i, j);
            }
            //connect
            else
            {
                des.at<double>(i, j) = img2.at<double>(i - img1._rows, j);
            }
        }
    }
    return des;
}

selfcv::Mat selfcv::Mat::zeros(int rows, int cols)
{
    selfcv::Mat z(rows, cols);
    for (int i = 0; i < z._size; i++)
    {
        (z._data)[i] = 0;
    }
    return z;
}

selfcv::Mat selfcv::Mat::ones(int rows, int cols)
{
    selfcv::Mat o(rows, cols);
    for (int i = 0; i < o._size; i++)
    {
        (o._data)[i] = 1;
    }
    return o;
}

bool selfcv::Mat::Solve(selfcv::Mat A, selfcv::Mat b, selfcv::Mat x, int n)
{
    selfcv::Mat M(n, n + 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M.at<double>(i, j) = A.at<double>(i, j);
        }
        M.at<double>(i, n) = b.at<double>(i, 0);
    }
    for (int k = 0; k < n; k++)
    {
        double colMax = fabs(M.at<double>(k, k));
        int maxLineIndex = k;
        for (int i = k + 1; i < n; i++)
        {
            if (fabs(M.at<double>(i, k)) > colMax)
            {
                colMax = fabs(M.at<double>(i, k));
                maxLineIndex = i;
            }
        }
        if (colMax < 0.001)
        {
            return false;
        }
        double tmp;
        for (int m = 0; m < n + 1; m++)
        {
            tmp = M.at<double>(k, m);
            M.at<double>(k, m) = M.at<double>(maxLineIndex, m);
            M.at<double>(maxLineIndex, m) = tmp;
        }

        for (int i = k + 1; i < n; i++)
        {
            for (int j = k + 1; j < n + 1; j++)
            {
                M.at<double>(i, j) = M.at<double>(k, k) * M.at<double>(i, j) / M.at<double>(i, k) - M.at<double>(k, j);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        x.at<double>(i, 0) = M.at<double>(i, n);
        for (int j = i + 1; j < n; j++)
        {
            x.at<double>(i, 0) -= M.at<double>(i, j) * x.at<double>(j, 0);
        }
        x.at<double>(i, 0) /= M.at<double>(i, i);
    }
    return true;
}
