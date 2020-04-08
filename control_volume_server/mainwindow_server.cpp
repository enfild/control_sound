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
    connect(server, SIGNAL(newConnection()), this, SLOT(newClient()));//слот по новому подключению

        //tray
        /* Инициализируем иконку трея, устанавливаем иконку из набора системных иконок,
         * а также задаем всплывающую подсказку
         * */
        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_MediaVolume));
        trayIcon->setToolTip("Volume server" "\n"
                             "Programm for vork with volume server");
        /* После чего создаем контекстное меню из двух пунктов*/
        menu = new QMenu(this);
        viewWindow = new QAction(tr("Show window"), this);
        quitAction = new QAction(tr("Exit"), this);
    //    slider = new QSlider(Qt::Horizontal, this);
        slider.setOrientation(Qt::Horizontal);
        slider.setMaximum(100);

        /* подключаем сигналы нажатий на пункты меню к соответсвующим слотам.
         * Первый пункт меню разворачивает приложение из трея,
         * а второй пункт меню завершает приложение
         * */
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

        /* Устанавливаем контекстное меню на иконку
         * и показываем иконку приложения в трее
         * */
        trayIcon->setContextMenu(menu);
        trayIcon->show();

        /* Также подключаем сигнал нажатия на иконку к обработчику
         * данного нажатия
         * */
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


        ui->horizontalSlider->setValue(getVolumeLevel());

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

//    quint8 key = dataClient.mid(index1 + 1).toInt(&ok);



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



