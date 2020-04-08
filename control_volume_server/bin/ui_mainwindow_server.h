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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QLineEdit *lineEdit;
    QPushButton *pushButton_Connect;
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
        horizontalSlider->setGeometry(QRect(130, 300, 401, 91));
        horizontalSlider->setOrientation(Qt::Horizontal);
        checkBox_tray = new QCheckBox(centralWidget);
        checkBox_tray->setObjectName(QString::fromUtf8("checkBox_tray"));
        checkBox_tray->setGeometry(QRect(100, 0, 72, 19));
        comboBox_Clients = new QComboBox(centralWidget);
        comboBox_Clients->setObjectName(QString::fromUtf8("comboBox_Clients"));
        comboBox_Clients->setGeometry(QRect(80, 170, 521, 61));
        QFont font;
        font.setPointSize(21);
        comboBox_Clients->setFont(font);
        label_IP = new QLabel(centralWidget);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));
        label_IP->setGeometry(QRect(40, 50, 91, 21));
        QFont font1;
        font1.setPointSize(17);
        label_IP->setFont(font1);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(380, 30, 221, 41));
        pushButton_Connect = new QPushButton(centralWidget);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        pushButton_Connect->setGeometry(QRect(190, 370, 251, 61));
        QFont font2;
        font2.setPointSize(18);
        pushButton_Connect->setFont(font2);
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
        checkBox_tray->setText(QCoreApplication::translate("MainWindow_Server", "CheckBox", nullptr));
        label_IP->setText(QCoreApplication::translate("MainWindow_Server", "IP", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("MainWindow_Server", "Create Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_Server: public Ui_MainWindow_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_SERVER_H
