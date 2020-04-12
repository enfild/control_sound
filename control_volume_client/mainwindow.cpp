#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define SERV
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



//    ui->spinBox->setRange(0,100);

    ui->lineEdit_PORT->setText("8080");

    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setMinimum(0);

}

MainWindow::~MainWindow()
{
    timeDisconnect();
    delete ui;
}


// CREATE CLIEN     -----CLIENT
void MainWindow::Create_Client()
{
    QString IPaddres = ui->lineEdit_IP->text();
    quint16 PORT = ui->lineEdit_PORT->text().toUInt();

    m_socket = new QTcpSocket;
    m_socket->connectToHost(IPaddres, PORT);
    qDebug() << m_socket->isValid() << "SOCKET";
    if(!m_socket->waitForConnected(10000))
    {
        QMessageBox::critical(this, "Error", "Can't connect to host:" + IPaddres + "::" + QString::number(PORT));
    }
    if(m_socket->waitForConnected())
    {
        emit connectionToServer(true);
        int Valume = GetVolume();

//        ui->spinBox->setValue(Valume);

        ui->horizontalSlider_Volume->setValue(Valume);

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
        qDebug() << "is not open";
        return 0;
    }
    m_socket->write(Key_Words.GET_VOL.toUtf8());
    if(m_socket->waitForBytesWritten())
    {
        if(m_socket->waitForReadyRead())
        {
            QByteArray dataRead = m_socket->readAll();
            qDebug() << dataRead;
            int val = dataRead.at(0);

//            ui->spinBox->setValue(val);
            ui->horizontalSlider_Volume->setValue(val);


            return val;
        }
    }
}

//SendVOLUMEto server   -----CLIENT
bool MainWindow::SendVolume()
{
    return SendData(QByteArray::number(ui->horizontalSlider_Volume->value()));
}

bool MainWindow::SendKey()
{
//    auto keyCommand = SPACE;
//    qDebug() << keyCommand;
    return SendData(QByteArray::number(SPACE));
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




void MainWindow::on_pushButtonConnect_clicked()
{
    Create_Client();
}

void MainWindow::on_pushButtonPause_clicked()
{
    SendKey();
}

void MainWindow::on_pushButtonSetVolume_clicked()
{
    SendVolume();
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{

}
