/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonConnect;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonPause;
    QLabel *label;
    QPushButton *pushButtonSetVolume;
    QLineEdit *lineEdit_PORT;
    QLineEdit *lineEdit_IP;
    QSlider *horizontalSlider_Volume;
    QLineEdit *lineEdit_valVolume;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(346, 455);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonConnect = new QPushButton(centralWidget);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));
        QFont font;
        font.setPointSize(24);
        pushButtonConnect->setFont(font);

        gridLayout->addWidget(pushButtonConnect, 3, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setPointSize(15);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        pushButtonPause = new QPushButton(centralWidget);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setFont(font);

        gridLayout->addWidget(pushButtonPause, 4, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setPointSize(21);
        label->setFont(font2);

        gridLayout->addWidget(label, 2, 1, 1, 1);

        pushButtonSetVolume = new QPushButton(centralWidget);
        pushButtonSetVolume->setObjectName(QString::fromUtf8("pushButtonSetVolume"));
        pushButtonSetVolume->setFont(font);

        gridLayout->addWidget(pushButtonSetVolume, 5, 0, 1, 1);

        lineEdit_PORT = new QLineEdit(centralWidget);
        lineEdit_PORT->setObjectName(QString::fromUtf8("lineEdit_PORT"));
        lineEdit_PORT->setMinimumSize(QSize(0, 100));
        lineEdit_PORT->setFont(font);

        gridLayout->addWidget(lineEdit_PORT, 1, 1, 1, 1);

        lineEdit_IP = new QLineEdit(centralWidget);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));
        lineEdit_IP->setMinimumSize(QSize(0, 100));
        lineEdit_IP->setFont(font);

        gridLayout->addWidget(lineEdit_IP, 1, 0, 1, 1);

        horizontalSlider_Volume = new QSlider(centralWidget);
        horizontalSlider_Volume->setObjectName(QString::fromUtf8("horizontalSlider_Volume"));
        horizontalSlider_Volume->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_Volume, 4, 1, 1, 1);

        lineEdit_valVolume = new QLineEdit(centralWidget);
        lineEdit_valVolume->setObjectName(QString::fromUtf8("lineEdit_valVolume"));
        lineEdit_valVolume->setFont(font2);

        gridLayout->addWidget(lineEdit_valVolume, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 346, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sound Client", nullptr));
        pushButtonConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PORT", nullptr));
        pushButtonPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Volume", nullptr));
        pushButtonSetVolume->setText(QCoreApplication::translate("MainWindow", "Set Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
