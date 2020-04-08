#include "mainwindow_server.h"
#include "ui_mainwindow_server.h"

MainWindow_Server::MainWindow_Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Server)
{
    ui->setupUi(this);

    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        {
            qDebug() << "Audio device name: " << deviceInfo.deviceName();
        }

    server = new QTcpServer();

    QList<QHostAddress> adress = QNetworkInterface::allAddresses();//все возможные адреса на которых можно вещять
        for(int i = 0; i < adress.size(); i++)
            qDebug() << adress[i];
        for(int i = 0; i < adress.size(); i++)
        {
            if(adress[i].protocol() == QAbstractSocket::IPv4Protocol)
                ui->comboBox_Clients->addItem(adress[i].toString());
        }
        for(int i = 0; i < ui->comboBox_Clients->count(); i++)
        {
            if((ui->comboBox_Clients->itemText(i).indexOf("192.168.") != -1) || (ui->comboBox_Clients->itemText(i).indexOf("172.") != -1))
            {
                ui->comboBox_Clients->setCurrentIndex(i);
                break;
            }

            if(i == (ui->comboBox_Clients->count() - 1))//если не нашел нужный сервер
                ui->comboBox_Clients->setCurrentText("127.0.0.1");
        }
}

MainWindow_Server::~MainWindow_Server()
{
    delete ui;
}

int MainWindow_Server::getVolumeLevel()
{
    CoInitialize(nullptr);
        IMMDeviceEnumerator *deviceEnumerator = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
        IMMDevice *defaultDevice = nullptr;

        hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
        deviceEnumerator->Release();
        deviceEnumerator = nullptr;

        IAudioEndpointVolume *endpointVolume = nullptr;
        hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (LPVOID *)&endpointVolume);
        defaultDevice->Release();
        defaultDevice = nullptr;

        float currentVolume;

        hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

        endpointVolume->Release();

        CoUninitialize();

        Q_UNUSED(hr);
        return currentVolume * 100;
}

void MainWindow_Server::setVolumeLevel(int Volume)
{
    CoInitialize(nullptr);
        IMMDeviceEnumerator *deviceEnumerator = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
        IMMDevice *defaultDevice = nullptr;

        hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
        deviceEnumerator->Release();
        deviceEnumerator = nullptr;

        IAudioEndpointVolume *endpointVolume = nullptr;
        hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (LPVOID *)&endpointVolume);
        defaultDevice->Release();
        defaultDevice = nullptr;

        hr = endpointVolume->SetMasterVolumeLevelScalar((float)Volume / 100, nullptr);

        endpointVolume->Release();

        CoUninitialize();

        Q_UNUSED(hr);
}

void MainWindow_Server::closeWindow(QCloseEvent *event)
{
    /* Если окно видимо и чекбокс отмечен, то завершение приложения
         * игнорируется, а окно просто скрывается, что сопровождается
         * соответствующим всплывающим сообщением
         */
        if(this->isVisible() && ui->checkBox_tray->isChecked()){
            event->ignore();
            this->hide();
            QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

            trayIcon->showMessage("Volume server",
                                  tr("Programm hide window. For show window, "
                                         "click on tray icon"),
                                  icon,
                                  1000);
        }
}

void MainWindow_Server::newClient()
{
    //        int PORT = ui->lineEdit_PORT->text().toInt();

    QTcpSocket *client = server->nextPendingConnection();

    //        connect(client, SIGNAL(newConnection()), this, SLOT(newuser()));

    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayIcon->showMessage("Volume server",
                          tr("New connection : ") + client->peerAddress().toString(),
                          icon,
                          1000);
}

void MainWindow_Server::clientDisconected()
{
    QTcpSocket* client = (QTcpSocket*)sender();
//        disconnect(client ,SIGNAL(readyRead()), this, SLOT(readDataClient()));
//        disconnect(client, SIGNAL(disconnected()), this, SLOT(clientDisconected()));
}

void MainWindow_Server::readDataClient()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    //    QTcpSocket* client = (QTcpSocket*)server->sender();
    QByteArray dataClient = client->readAll();

    //обработка принятых данных

    int val = dataClient.toInt();

    setVolumeLevel(val);


    ui->horizontalSlider->setValue(val);
    if(val != getVolumeLevel())
    {
        client->write("Invalid data!");
        return;
    }


    bool ok;
    int index1 = dataClient.indexOf(';');
    quint8 keyComand = dataClient.mid(_setKey.size(), index1- _setKey.size()).toInt(&ok);
    if(!ok)//если не получилось прочитать число
    {
        client->write("Invalid data!");
        return;
    }
    quint8 key = dataClient.mid(index1 + 1).toInt(&ok);
    if(!ok)//если не получилось прочитать число
    {
        client->write("Invalid data!");
        return;
    }
    emitKeyPresed(keyComand, key);

else if(dataClient.mid(0, _getVolume.size()) == _getVolume)
{
    int val = getVolumeLevel();
    client->write(_isVolume + QByteArray::number(val));//отправляю ключевое слово и значение
    return;
}
else
{
client->write("Invalid data!");
return;
}

client->write("OK");
}

void MainWindow_Server::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
        {
        case QSystemTrayIcon::Trigger:
            if(ui->checkBox_tray->isChecked()){
                if(!this->isVisible()){
                    this->show();
                } else {
                    this->hide();
                }
            }
            break;
        default:
            break;
        }
}



