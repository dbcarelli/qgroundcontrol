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
    clock = QTime();

}

int DataStationLink::_write(QString buffer){
    return serialPort->write(buffer.toUtf8());
}

QString DataStationLink::_read(size_t size, int time){
    QString rcv = "";
    for (int i = 0; i < size; i++){
        serialPort->waitForReadyRead(time);
        rcv += QString::fromUtf8(serialPort->read(1));
    }
    qInfo() << "read: "+rcv;
    return rcv;
}

int DataStationLink::setDataStationId(QString newId){
    flushIncomingBuffer();
    QString command = "4";
    QString targetId = "01";
    sendCommand(targetId, command);
    _write(prelimitor);
    _write(newId);
    _write(postlimitor);

    QString incomingBuffer = "      ";

    // wait for some bytes mothafucka -DC
    while (!(serialPort->waitForReadyRead(3000))){}

    int count = 0;
    while ((serialPort->bytesAvailable()) && (count < 100)){

        qInfo() << "Checking for response to command 6";
        // shift the buffer
        incomingBuffer[0] = incomingBuffer[1];
        incomingBuffer[1] = incomingBuffer[2];
        incomingBuffer[2] = incomingBuffer[3];
        incomingBuffer[3] = incomingBuffer[4];
        incomingBuffer[4] = incomingBuffer[5];
        incomingBuffer[5] = _read(1, 1000)[0];

        // compare the buffer
        if ((incomingBuffer[0] == 'c') &&
            (incomingBuffer[1] == 'a') &&
            (incomingBuffer[2] == 't') &&
            (incomingBuffer[3] == targetId.at(0)) &&
            (incomingBuffer[4] == targetId.at(1)) &&
            (incomingBuffer[5] == command[0])){
            qInfo() << "ackowledged";
            return 1;
        }
        else {
            count++;
        }
        if (count%6 == 5){
            sendCommand(targetId, command);
            _write("<");
            _write(newId);
            _write(">");
        }

    }

    return 0;
}

QString DataStationLink::deployDataStation(QString targetId, bool testStatus){
    flushIncomingBuffer();

    // send the STATUS_REQUEST command, 5
    QString command = "5";
    if(testStatus){
        command = "6";
        qInfo() << "Running DEPLOYMENT_SYS_TEST";
    }


    sendCommand(targetId, command);

    QString incomingBuffer = "      ";

    // wait for some bytes mothafucka -DC
    while (!(serialPort->waitForReadyRead(3000))){}

    int count = 0;
    while ((serialPort->bytesAvailable()) && (count < 100)){

        qInfo() << "Checking for response to command 6";
        // shift the buffer
        incomingBuffer[0] = incomingBuffer[1];
        incomingBuffer[1] = incomingBuffer[2];
        incomingBuffer[2] = incomingBuffer[3];
        incomingBuffer[3] = incomingBuffer[4];
        incomingBuffer[4] = incomingBuffer[5];
        incomingBuffer[5] = _read(1, 1000)[0];

        // compare the buffer
        if ((incomingBuffer[0] == 'c') &&
            (incomingBuffer[1] == 'a') &&
            (incomingBuffer[2] == 't') &&
            (incomingBuffer[3] == targetId.at(0)) &&
            (incomingBuffer[4] == targetId.at(1)) &&
            (incomingBuffer[5] == command[0])){
            qInfo() << "ackowledged";
            break;
        }
        else {
            count++;
        }
        if (count%6 == 5){
            sendCommand(targetId, command);
        }

    }

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

void DataStationLink::sendCommand(QString targetId, QString command){

    // write the preamble to the data station
    _write(preamble);

    // address the target data station
    _write(targetId);

    // send the command
    _write(command);

    serialPort->flush();
}

bool DataStationLink::turnOnDS(QString targetId){
    flushIncomingBuffer();
    sendCommand(targetId, "1");
    int count = 0;

    QString incomingBuffer = "     ";

    while (serialPort->bytesAvailable() && count < 20){
        // shift the buffer
        incomingBuffer[0] = incomingBuffer[1];
        incomingBuffer[1] = incomingBuffer[2];
        incomingBuffer[2] = incomingBuffer[3];
        incomingBuffer[3] = incomingBuffer[4];
        incomingBuffer[4] = _read(1, 1000)[0];

        // compare the buffer
        if ((incomingBuffer[0] == 'c') &&
            (incomingBuffer[1] == 'a') &&
            (incomingBuffer[2] == 't') &&
            (incomingBuffer[3] == targetId.at(0)) &&
            (incomingBuffer[4] == targetId.at(1))){
            return true;
        }
        else {
            count++;
        }
        if (count%3 == 2){
            sendCommand(targetId, "1");
        }
    }

    return false;
}

void DataStationLink::flushIncomingBuffer(){
    while(serialPort->bytesAvailable()){
        _read(1,1);
    }
}
