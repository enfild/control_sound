#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define SERV
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setRange(0,100);
}

MainWindow::~MainWindow()
{
    timeDisconnect();
    delete ui;
}

//void MainWindow::Create_Server() {
//    int PORT = ui->lineEdit_PORT->text().toInt();

//    //    int socket = ui->spinBox->value(); //set value
//    //    QString sdfig = ui->lineEdit->text();

//    tcpServer = new QTcpServer(this);
//    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
//    if (!tcpServer->listen(QHostAddress::Any, PORT)) {
//        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
//    } else {
//        server_status=1;
//        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
//        qDebug() << QString::fromUtf8("Сервер запущен!");
//    }
//}
// CREATE CLIEN     -----CLIENT
void MainWindow::Create_Client()
{
    QString IPaddres = ui->lineEdit_IP->text();
    int PORT = ui->lineEdit_PORT->text().toInt();
    m_socket = new QTcpSocket;
    m_socket->connectToHost(IPaddres, PORT);
    if(!m_socket->waitForConnected(1000)){
        QMessageBox::critical(this, "Error", "Can't connect to host:" + IPaddres + "::" + QString::number(PORT));
    }
    if(m_socket->waitForConnected())
    {
        emit connectionToServer(true);
        int Valume = GetVolume();
        ui->spinBox->setValue(Valume);
        qDebug() << "volume is:" << Valume;
        if(Valume == -1)
        {
            return;
        }
    }
}

//GetVolume from server   -----CLIENT
int MainWindow::GetVolume(){
    if(!m_socket->isOpen()){
        return 0;
    }
    m_socket->write(Key_Words.GET_VOL.toUtf8());
    if(m_socket->waitForBytesWritten(10))
    {
        while(m_socket->bytesAvailable())
        {
            QByteArray dataRead = m_socket->readAll();
            int val = dataRead.toInt();
            return val;
        }
    }
}

//SendVOLUMEto server   -----CLIENT
bool MainWindow::SendVolume()
{
    return SendData(QByteArray::number(ui->spinBox->value()));
}

bool MainWindow::SendKey(Qt::Key key)
{
    qDebug() << key;
    auto keyCommand = SPACE;
    return SendData(QByteArray::number(keyCommand));
}

//SendDATA to server   -----CLIENT
bool MainWindow::SendData(QByteArray Data)
{
    QString IPaddres = ui->lineEdit_IP->text();
    int PORT = ui->lineEdit_PORT->text().toInt();

    if(!m_socket->isOpen())
    {
        m_socket->connectToHost(IPaddres, PORT);
    }
        m_socket->write(Data);
        return true;
}

void MainWindow::timeDisconnect()
{
    m_socket->disconnectFromHost();
    m_socket->close();
    qDebug() << "time disconnected!";
}





