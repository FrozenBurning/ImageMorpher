#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    meshgrid = new QPixmap(300,400);
    meshgrid->load(":/images/meshgrid.png");
    original_img = new QPixmap(300,400);
    target_img = new QPixmap(300,400);
    result_img = new QPixmap(300,400);

    original_img_path = new std::string;
    target_img_path = new std::string;
    result_img_path = new std::string;

    no_image_available = new QPixmap(300,400);
    no_image_available->load(":/images/no-image-available.png");

    mode_handler();

    ui->radius->setText(QString::number(radius));
    ui->param->setText(QString::number(param));

    connect(ui->radius_slider, SIGNAL(valueChanged(int)), this, SLOT(setRadiusValue(int)));
    connect(ui->param_slider, SIGNAL(valueChanged(int)), this, SLOT(setParamValue(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRadiusValue(int)
{
    mode_handler();
    ui->radius->setText(QString::number(radius));
}

void MainWindow::setParamValue(int)
{
    mode_handler();
    ui->param->setText(QString::number(param));
}

//utility

QString MainWindow::selectimg()
{

    QFileDialog *fileDialog = new QFileDialog(this);

    fileDialog->setWindowTitle(tr("Select Image"));

    fileDialog->setDirectory("../");

    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));

    fileDialog->setFileMode(QFileDialog::ExistingFile);

    fileDialog->setViewMode(QFileDialog::Detail);

    QStringList imgname;
    if(fileDialog->exec())
    {
        imgname = fileDialog->selectedFiles();
    }
    delete fileDialog;
    if(!imgname.empty())
    {
        return imgname.first();
    }
    else
    {
        return NULL;
    }
}

void MainWindow::mode_handler()
{
    int previous_mode = transformation_type;
    interpolation_method = ui->interpolater->currentIndex();
    transformation_type = ui->transformer->currentIndex();
    radius = ui->radius_slider->value();

    //variety of param
    switch (transformation_type) {
    case 0://tangent distortion
    {
        param = (double)ui->param_slider->value()/ui->param_slider->maximum()*3.14;
        if(previous_mode != transformation_type)
        {
            ui->target_img->setIcon(QIcon(*meshgrid));
            ui->original_img->setIcon(QIcon(*no_image_available));
        }
        break;
    }
    case 1://radial distortion
    {
        param = (double)ui->param_slider->value()/ui->param_slider->maximum();
        if(previous_mode != transformation_type)
        {
            ui->target_img->setIcon(QIcon(*meshgrid));
            ui->original_img->setIcon(QIcon(*no_image_available));
        }
        break;
    }
    case 2://tps
    {
        param = 0;
        if(previous_mode != transformation_type)
        {
            ui->target_img->setIcon(QIcon(*no_image_available));
            ui->original_img->setIcon(QIcon(*no_image_available));
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::morpher_handler()
{
    if(morpher(original_img_path, transformation_type,interpolation_method,radius, param, target_img_path,result_img_path))
    {
        result_img->load(QString::fromStdString(*result_img_path));
        ui->result_img->setPixmap((*result_img).scaled(300,400,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else
    {
        ui->result_img->setPixmap((*no_image_available).scaled(300,400,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}

QImage MainWindow::cvMat2QImage(const cv::Mat &mat)
{
    //shallow clone
    QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    return image.rgbSwapped();
    //deep clone
}

cv::Mat MainWindow::QImage2cvMat(const QImage &img)
{
    //shallow clone
    QImage swapped = img.rgbSwapped();
    return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine()).clone();

    //deep clone
}

//slot region

void MainWindow::on_original_img_clicked()
{
    QString img = selectimg();
    if(img != NULL)
    {
        original_img->load(img);
        ui->original_img->setIcon(QIcon(*original_img));
        *original_img_path = img.QString::toStdString();
    }
}


void MainWindow::on_target_img_clicked()
{
    QString img =selectimg();
    if(img != NULL)
    {
        target_img->load(img);
        ui->target_img->setIcon(QIcon(*target_img));
        *target_img_path = img.QString::toStdString();
    }

}

void MainWindow::on_start_clicked()
{
    mode_handler();
    morpher_handler();
}

void MainWindow::on_transformer_currentIndexChanged(int index)
{
    mode_handler();
    if(index == 2)//tps
    {
        ui->groupBox->setEnabled(false);
        ui->target_img->setEnabled(true);
    }
    else if(index == 1)//
    {
        ui->groupBox->setEnabled(true);
        ui->param_name->setText("径向畸变率：");
        ui->param->setText(QString::number(param));
        ui->target_img->setEnabled(false);
    }
    else//central rotating
    {
        ui->groupBox->setEnabled(true);
        ui->param_name->setText("最大扭曲角度：");
        ui->param->setText(QString::number(param));
        ui->target_img->setEnabled(false);
    }

}

void MainWindow::on_param_slider_sliderReleased()
{
    std::string undistorted_grid = "./meshgrid.png";
    std::string distorted_grid = "./tmp.png";

    morpher(&undistorted_grid,transformation_type,0,radius,param,target_img_path,&distorted_grid);
    QPixmap tmp = QPixmap(300,400);
    tmp.load(QString::fromStdString(distorted_grid));
    ui->target_img->setIcon(QIcon(tmp));
}

void MainWindow::on_radius_slider_sliderReleased()
{
    std::string undistorted_grid = "./meshgrid.png";
    std::string distorted_grid = "./tmp.png";

    morpher(&undistorted_grid,transformation_type,0,radius,param,target_img_path,&distorted_grid);
    QPixmap tmp = QPixmap(300,400);
    tmp.load(QString::fromStdString(distorted_grid));
    ui->target_img->setIcon(QIcon(tmp));
}
