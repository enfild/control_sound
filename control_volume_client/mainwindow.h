#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QString>

#define SPACE 0x20

namespace Ui {


class MainWindow;

}

class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    QTcpSocket *m_socket;

    bool server_status;

    Ui::MainWindow *ui;

    struct{
        const QString SET_VOL = "SET_VOL"; // to client
        const QString GET_VOL = "GET_VOL"; // from client
        const QString SET_KEY = "SET_KEY";
    }Key_Words ;

signals:
    void connectionToServer(bool connection);

public slots:
    //server COMP
//    void Create_Server();

    //client TELEFONE
    void Create_Client();
    bool SendData(QByteArray Data);
    int GetVolume();
    bool SendVolume();
    bool SendKey(Qt::Key key);
    void timeDisconnect();
};

#endif // MAINWINDOW_H
