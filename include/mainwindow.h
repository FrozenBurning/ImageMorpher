#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMovie>
#include <opencv2/opencv.hpp>
#include "morpher.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString selectimg();
    void mode_handler();
    void morpher_handler();

    //only for 8U3C
    QImage cvMat2QImage(const cv::Mat &mat);
    cv::Mat QImage2cvMat(const QImage &img);

    int interpolation_method;
    int transformation_type;
    double radius;
    double param;
    QPixmap *meshgrid;
    QPixmap *no_image_available;
    QPixmap *original_img;
    QPixmap *target_img;
    QPixmap *result_img;

    std::string* original_img_path;
    std::string* target_img_path;
    std::string* result_img_path;

public slots:
    void setRadiusValue(int);
    void setParamValue(int);
private slots:
    void on_original_img_clicked();
    void on_target_img_clicked();
    void on_start_clicked();
    void on_transformer_currentIndexChanged(int index);
    void on_param_slider_sliderReleased();
    void on_radius_slider_sliderReleased();
};

#endif // MAINWINDOW_H
