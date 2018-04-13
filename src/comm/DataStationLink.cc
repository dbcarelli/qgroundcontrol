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
    // write the preamble to the data station
    _write(preamble);

    // send the RESET_ID command, 4
    QString command = "4";
    _write(command);

    // write the prelimitor, idicating the ID is coming
    _write(prelimitor);

    // send the new ID
    _write(newId);

    // send the postlimitor
    _write(postlimitor);

    // wait for receipt confirmation, if recive the pos-amble--> success
    if (_read(3) == "cat")
        return 1;

    // if we receive anything else, this operation failed
    return 0;
}

QString DataStationLink::deployDataStation(QString targetId){
    // write the preamble to the data station
    _write(preamble);

    // address the target data station
    _write(targetId);

    // send the STATUS_REQUEST command, 5
    QString command = "5";
    _write(command);

    // receive all the information in the form a QString that will be parsed
    // later.
    // TODO: determine the actual number of chars expected in this response.
    return _read(20):

}
