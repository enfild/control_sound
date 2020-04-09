#ifndef MAINWINDOW_SERVER_H
#define MAINWINDOW_SERVER_H

#include <QMainWindow>
#include <QAudioDeviceInfo>
#include <QTcpServer>
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpSocket>

#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <QNetworkInterface>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QSlider>
#include <QWidgetAction>
#include <QLabel>

#include <windows.h>

#define DEFAULT_PORT    8080


#define SPACE 0x20

namespace Ui {
class MainWindow_Server;
}
class QTcpServer;

class MainWindow_Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_Server(QWidget *parent = nullptr);
    ~MainWindow_Server();



private:
    Ui::MainWindow_Server *ui;

    int getVolumeLevel();
    void setVolumeLevel(int Volume);
    bool getMuteStatus();
    void setMuteVolume();

    QTcpServer *server;
    /* Объявляем объект будущей иконки приложения для трея */
    QSystemTrayIcon* trayIcon;
    QMenu* menu;
    QAction* viewWindow;
    QAction* quitAction;
    QSlider slider;
    QWidgetAction* widgetActionSlider;
    QWidgetAction* widgetActionLable;
    QLabel lableIpServer;

    struct{
        const QString SET_VOL = "SET_VOL"; // to client
        const QString GET_VOL = "GET_VOL"; // from client
        const QString SET_KEY = "SET_KEY";
    }Key_Words;
protected:
void closeEvent(QCloseEvent * event);
private slots:
    void newClient();
    void clientDisconected();
    void readDataClient();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_comboBox_Clients_currentIndexChanged(const QString &arg1);

    void emitKeyPresed(quint8 keyComand, quint8 key);

    void on_horizontalSlider_valueChanged(int value);
};

#endif // MAINWINDOW_SERVER_H
