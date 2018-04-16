#include "DataStationLink.h"


DataStationLink::DataStationLink(QString portname){
    serialPort = new QSerialPort(portname);

<<<<<<< HEAD
    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)B57600);
    cfsetispeed (&tty, (speed_t)B57600);

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block- read will return on a single character if no more appear
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout- read returns if 0.5 seconds pass without an incoming character
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush( Xbee, TCIFLUSH );
    //should check connection, then set connected to true;
    this->connected = true;
=======
    serialPort->open(QIODevice::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud57600);
>>>>>>> 3eee0397a2667c848b8ce6d40f26af4ad6c6f74f
}

int DataStationLink::_write(QString buffer){
    return serialPort->write(buffer.toUtf8());
}

QString DataStationLink::_read(size_t size){
    return QString::fromUtf8(serialPort->read(size));

}

int DataStationLink::setDataStationId(QString newId){
    QString message = "changin data station id...";
    _write(message);
    return 0;
}

int DataStationLink::deployDataStation(QString targetId){
    QString message = "data station deployed";
    _write(message);
    return 0;
}

DataStationLink::~DataStationLink(){}
