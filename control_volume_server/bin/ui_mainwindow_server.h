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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QCheckBox *checkBox_tray;
    QLabel *label_IP;
    QComboBox *comboBox_Clients;
    QSlider *horizontalSlider;
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
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_tray = new QCheckBox(centralWidget);
        checkBox_tray->setObjectName(QString::fromUtf8("checkBox_tray"));
        QFont font;
        font.setPointSize(12);
        checkBox_tray->setFont(font);

        gridLayout->addWidget(checkBox_tray, 0, 0, 1, 1);

        label_IP = new QLabel(centralWidget);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));
        QFont font1;
        font1.setPointSize(17);
        label_IP->setFont(font1);

        gridLayout->addWidget(label_IP, 1, 0, 1, 2);

        comboBox_Clients = new QComboBox(centralWidget);
        comboBox_Clients->setObjectName(QString::fromUtf8("comboBox_Clients"));
        QFont font2;
        font2.setPointSize(21);
        comboBox_Clients->setFont(font2);

        gridLayout->addWidget(comboBox_Clients, 2, 0, 1, 2);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 3, 0, 2, 2);

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
        MainWindow_Server->setWindowTitle(QCoreApplication::translate("MainWindow_Server", "Server Sound", nullptr));
        checkBox_tray->setText(QCoreApplication::translate("MainWindow_Server", "Activate Trey", nullptr));
        label_IP->setText(QCoreApplication::translate("MainWindow_Server", "IP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_Server: public Ui_MainWindow_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_SERVER_H
