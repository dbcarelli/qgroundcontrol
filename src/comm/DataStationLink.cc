#include "DataStationLink.h"


DataStationLink::DataStationLink(QString portname){
    serialPort = new QSerialPort(portname);

    serialPort->open(QIODevice::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud57600);
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

