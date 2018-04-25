//Parse in
//Parse Out
//Reset DataStation
//Data Station ID Status Request
//Save Data Station to List (spreadsheet)
//Recover Data Station from list by ID
#include "DataStationLink.h"
#include <QDebug>
#include <QtTest>

//Data Station List will be stored in parallel with mission logs, /Home/Documents/QGroundControl/DataStations

//Additionally, the gui will need modificaiton to acess these features.
DataStationLink::DataStationLink(QString portname){
    serialPort = new QSerialPort(portname);

    serialPort->open(QIODevice::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud57600);

}

int DataStationLink::_write(QString buffer){
    return serialPort->write(buffer.toUtf8());
}

QString DataStationLink::_read(size_t size){
    QString rcv = "";
    for (int i = 0; i < size; i++){
        serialPort->waitForReadyRead(5000);
        rcv += QString::fromUtf8(serialPort->read(1));
    }
    return rcv;
}

int DataStationLink::setDataStationId(QString newId){
    serialPort->flush();
    // write the preamble to the data station
    _write(preamble);

    // write factory ID
    _write("01");

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
//    QTest::qSleep(10000);
    QString confirmation = _read(3);
    qDebug() << confirmation;
    if (confirmation == "cat")
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
    // later. The first char should be a prelimitor.
    QString retVal = "";
    QString newChar = _read(1);
    if (newChar != prelimitor)
      return retVal;

    while (true){
      newChar = _read(1);
      if (newChar != postlimitor){
        retVal += newChar;
      }
      else{
        return retVal;
      }
    }
}
