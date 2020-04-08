/********************************************************************************
** Form generated from reading UI file 'mainwindow_server.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_SERVER_H
#define UI_MAINWINDOW_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_Server
{
public:
    QWidget *centralWidget;
    QSlider *horizontalSlider;
    QCheckBox *checkBox_tray;
    QComboBox *comboBox_Clients;
    QLabel *label_IP;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow_Server)
    {
        if (MainWindow_Server->objectName().isEmpty())
            MainWindow_Server->setObjectName(QString::fromUtf8("MainWindow_Server"));
        MainWindow_Server->resize(638, 516);
        centralWidget = new QWidget(MainWindow_Server);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(230, 370, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        checkBox_tray = new QCheckBox(centralWidget);
        checkBox_tray->setObjectName(QString::fromUtf8("checkBox_tray"));
        checkBox_tray->setGeometry(QRect(50, 40, 72, 19));
        comboBox_Clients = new QComboBox(centralWidget);
        comboBox_Clients->setObjectName(QString::fromUtf8("comboBox_Clients"));
        comboBox_Clients->setGeometry(QRect(180, 180, 101, 61));
        label_IP = new QLabel(centralWidget);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));
        label_IP->setGeometry(QRect(450, 70, 47, 13));
        MainWindow_Server->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow_Server);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 638, 20));
        MainWindow_Server->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow_Server);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow_Server->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow_Server);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow_Server->setStatusBar(statusBar);

        retranslateUi(MainWindow_Server);

        QMetaObject::connectSlotsByName(MainWindow_Server);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_Server)
    {
        MainWindow_Server->setWindowTitle(QCoreApplication::translate("MainWindow_Server", "MainWindow_Server", nullptr));
        checkBox_tray->setText(QCoreApplication::translate("MainWindow_Server", "CheckBox", nullptr));
        label_IP->setText(QCoreApplication::translate("MainWindow_Server", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_Server: public Ui_MainWindow_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_SERVER_H
