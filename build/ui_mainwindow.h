/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *transformer;
    QLabel *label_2;
    QComboBox *interpolater;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *radius;
    QSlider *radius_slider;
    QLabel *param_name;
    QLabel *param;
    QSlider *param_slider;
    QPushButton *original_img;
    QPushButton *target_img;
    QPushButton *start;
    QLabel *result_img;
    QLabel *label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1080, 657);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QWidget#centralWidget\n"
"{\n"
"	background-image: url(:/images/bg.jpg);\n"
"}"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 1081, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        transformer = new QComboBox(verticalLayoutWidget);
        transformer->setObjectName(QStringLiteral("transformer"));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        transformer->setFont(font1);
        transformer->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(transformer);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        interpolater = new QComboBox(verticalLayoutWidget);
        interpolater->setObjectName(QStringLiteral("interpolater"));
        interpolater->setFont(font1);
        interpolater->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(interpolater);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        horizontalLayoutWidget_2 = new QWidget(groupBox);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 20, 1081, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(16);
        label_4->setFont(font2);

        horizontalLayout_3->addWidget(label_4);

        radius = new QLabel(horizontalLayoutWidget_2);
        radius->setObjectName(QStringLiteral("radius"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(radius->sizePolicy().hasHeightForWidth());
        radius->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        radius->setFont(font3);

        horizontalLayout_3->addWidget(radius);

        radius_slider = new QSlider(horizontalLayoutWidget_2);
        radius_slider->setObjectName(QStringLiteral("radius_slider"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(200);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(radius_slider->sizePolicy().hasHeightForWidth());
        radius_slider->setSizePolicy(sizePolicy2);
        radius_slider->setMinimumSize(QSize(300, 0));
        radius_slider->setAcceptDrops(false);
        radius_slider->setMinimum(0);
        radius_slider->setMaximum(1000);
        radius_slider->setValue(250);
        radius_slider->setTracking(true);
        radius_slider->setOrientation(Qt::Horizontal);
        radius_slider->setInvertedAppearance(false);
        radius_slider->setInvertedControls(false);

        horizontalLayout_3->addWidget(radius_slider);

        param_name = new QLabel(horizontalLayoutWidget_2);
        param_name->setObjectName(QStringLiteral("param_name"));
        sizePolicy1.setHeightForWidth(param_name->sizePolicy().hasHeightForWidth());
        param_name->setSizePolicy(sizePolicy1);
        param_name->setFont(font2);

        horizontalLayout_3->addWidget(param_name);

        param = new QLabel(horizontalLayoutWidget_2);
        param->setObjectName(QStringLiteral("param"));
        sizePolicy1.setHeightForWidth(param->sizePolicy().hasHeightForWidth());
        param->setSizePolicy(sizePolicy1);
        param->setFont(font3);

        horizontalLayout_3->addWidget(param);

        param_slider = new QSlider(horizontalLayoutWidget_2);
        param_slider->setObjectName(QStringLiteral("param_slider"));
        sizePolicy1.setHeightForWidth(param_slider->sizePolicy().hasHeightForWidth());
        param_slider->setSizePolicy(sizePolicy1);
        param_slider->setMinimumSize(QSize(300, 0));
        param_slider->setMinimum(-100);
        param_slider->setMaximum(100);
        param_slider->setSingleStep(1);
        param_slider->setPageStep(10);
        param_slider->setValue(0);
        param_slider->setSliderPosition(0);
        param_slider->setOrientation(Qt::Horizontal);
        param_slider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_3->addWidget(param_slider);


        verticalLayout->addWidget(groupBox);

        original_img = new QPushButton(centralWidget);
        original_img->setObjectName(QStringLiteral("original_img"));
        original_img->setGeometry(QRect(20, 210, 300, 400));
        original_img->setIconSize(QSize(300, 400));
        original_img->setFlat(true);
        target_img = new QPushButton(centralWidget);
        target_img->setObjectName(QStringLiteral("target_img"));
        target_img->setEnabled(false);
        target_img->setGeometry(QRect(380, 210, 300, 400));
        target_img->setIconSize(QSize(300, 400));
        target_img->setFlat(true);
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(690, 360, 61, 71));
        start->setStyleSheet(QLatin1String("QPushButton#start\n"
"{\n"
"	border-image: url(:/images/start.png);\n"
"}\n"
"\n"
"QPushButton#start:hover\n"
"{\n"
"    border-radius:35px;\n"
"    background-color:rgb(211, 215, 207);\n"
"}\n"
"QPushButton#start:pressed\n"
"{\n"
"    border-radius:35px;\n"
"    background-color:rgb(136, 138, 133);\n"
"}"));
        result_img = new QLabel(centralWidget);
        result_img->setObjectName(QStringLiteral("result_img"));
        result_img->setGeometry(QRect(770, 210, 300, 400));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(330, 370, 41, 61));
        label_3->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border-image: url(:/images/add.png);\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        original_img->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "\345\217\230\345\275\242\346\226\271\346\263\225\357\274\232", 0));
        transformer->clear();
        transformer->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\270\255\345\277\203\346\211\255\346\233\262\347\225\270\345\217\230", 0)
         << QApplication::translate("MainWindow", "\346\241\266\345\275\242/\346\236\225\345\275\242\347\225\270\345\217\230", 0)
         << QApplication::translate("MainWindow", "TPS\345\217\230\345\275\242", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "\346\217\222\345\200\274\345\207\275\346\225\260\357\274\232", 0));
        interpolater->clear();
        interpolater->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\234\200\350\277\221\351\202\273", 0)
         << QApplication::translate("MainWindow", "\345\217\214\347\272\277\346\200\247", 0)
         << QApplication::translate("MainWindow", "\345\217\214\344\270\211\346\254\241", 0)
        );
        groupBox->setTitle(QApplication::translate("MainWindow", "Panel", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\215\212\345\276\204\357\274\232", 0));
        radius->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        param_name->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\346\211\255\346\233\262\350\247\222\345\272\246\357\274\232", 0));
        param->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        original_img->setText(QString());
        target_img->setText(QString());
        start->setText(QString());
        result_img->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
