#include "mainwindow_server.h"
#include "ui_mainwindow_server.h"

MainWindow_Server::MainWindow_Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Server)
{
    ui->setupUi(this);
    server = new QTcpServer();
    QList<QHostAddress> adress = QNetworkInterface::allAddresses();//все возможные адреса на которых можно вещять
    for(int i = 0; i < adress.size(); i++)
        qDebug() << adress[i];
    for(int i = 0; i < adress.size(); i++)
    {
        if(adress[i].protocol() == QAbstractSocket::IPv4Protocol)
            ui->comboBox_Clients->addItem(adress[i].toString());
    }
    for(int i = ui->comboBox_Clients->count(); i > 0; i--)
    {
        if((ui->comboBox_Clients->itemText(i).indexOf("192.168.") != -1) || (ui->comboBox_Clients->itemText(i).indexOf("172.") != -1))
        {
            ui->comboBox_Clients->setCurrentIndex(i);
            break;
        }

        if(i == (ui->comboBox_Clients->count() - 1))
        {
            ui->comboBox_Clients->setCurrentText("127.0.0.1");
        }
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(newClient()));
    qDebug() << "Connect to newClient";
    qDebug() << server;
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_MediaVolume));
    trayIcon->setToolTip("Volume server" "\n"
                         "Programm for vork with volume server");
    menu = new QMenu(this);
    viewWindow = new QAction(tr("Show window"), this);
    quitAction = new QAction(tr("Exit"), this);
    slider.setOrientation(Qt::Horizontal);
    slider.setMaximum(100);
    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    connect(&slider, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    widgetActionSlider = new QWidgetAction(this);
    widgetActionSlider->setDefaultWidget(&slider);
    lableIpServer.setText(ui->label_IP->text());
    lableIpServer.setFont(ui->label_IP->font());
    lableIpServer.setAlignment(ui->label_IP->alignment());
    widgetActionLable = new QWidgetAction(this);
    widgetActionLable->setDefaultWidget(&lableIpServer);
    menu->addAction(widgetActionLable);
    menu->addSeparator();
    menu->addAction(widgetActionSlider);
    menu->addSeparator();
    menu->addAction(viewWindow);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    ui->horizontalSlider->setValue(getVolumeLevel());
}

MainWindow_Server::~MainWindow_Server()
{
    delete server;
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
    ui->horizontalSlider->setValue(Volume);
}

void MainWindow_Server::setMuteVolume()
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
    endpointVolume->SetMute(true, nullptr);
    endpointVolume->Release();
    CoUninitialize();
    Q_UNUSED(hr);
}

void MainWindow_Server::on_comboBox_Clients_currentIndexChanged(const QString &arg1)
{
    qDebug() << arg1 + "ARGUMENT";
    ui->label_IP->setStyleSheet("QLabel{background-color: rgb(255, 0, 0);}");
    lableIpServer.setStyleSheet("QLabel{background-color: rgb(255, 0, 0);}");
    if(server->isListening())
        server->close();
    if(!server->listen(QHostAddress("Any"), DEFAULT_PORT))
    {
        QMessageBox::critical(this, tr("Error connect"), tr("Client -- ") + arg1 );
    }
    else
    {
        ui->label_IP->setText("IP:" + arg1);
        lableIpServer.setText(ui->label_IP->text());
        ui->label_IP->setStyleSheet("QLabel{background-color: rgb(85, 170, 0);}");
        lableIpServer.setStyleSheet("QLabel{background-color: rgb(85, 170, 0);}");
        qDebug() << "Connect";
    }
}

void MainWindow_Server::emitKeyPresed(quint8 keyComand, quint8 key)
{
    qDebug() << "CMD:" << keyComand << "::" << key;

    if(keyComand)
        keybd_event(keyComand, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    if(keyComand)
        keybd_event(keyComand, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void MainWindow_Server::closeEvent(QCloseEvent *event)
{
    qDebug() << "close";
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
    QTcpSocket *client = server->nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(readDataClient()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconected()));
}

void MainWindow_Server::clientDisconected()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    disconnect(client ,SIGNAL(readyRead()), this, SLOT(readDataClient()));
    disconnect(client, SIGNAL(disconnected()), this, SLOT(clientDisconected()));
}

void MainWindow_Server::readDataClient()
{

    QTcpSocket* client = (QTcpSocket*)sender();
    QByteArray dataClient = client->readAll();
    if(dataClient == Key_Words.GET_VOL.toUtf8()){
        QByteArray Send_Volume_bytes;
        Send_Volume_bytes.append(getVolumeLevel());
        client->write(Send_Volume_bytes);
        qDebug() << Send_Volume_bytes;
    }

    else if(dataClient.toInt() == SET_PAUSE)
    {
        emitKeyPresed(0, VK_MEDIA_PLAY_PAUSE);
    }

    else if(dataClient.toInt()>= 0) {
        setVolumeLevel(dataClient.toInt());
    }
    else {
        return;
    }

    qDebug() << dataClient;
    int val = dataClient.toInt();
    qDebug() << val;
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

void MainWindow_Server::on_horizontalSlider_valueChanged(int value)
{
    setVolumeLevel(value);
}
