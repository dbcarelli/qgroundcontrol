//This file will stand control Xbee communication with camera traps like linkManager controls MavLinks with the vehicle. 
//Skeleton of File:

//Parse in
//Parse Out
//Reset DataStation
//Data Station ID Status Request
//Save Data Station to List (spreadsheet)
//Recover Data Station from list by ID
#include "DataStationLink.h"
#include <QDebug>

//Data Station List will be stored in parallel with mission logs, /Home/Documents/QGroundControl/DataStations

//Additionally, the gui will need modificaiton to acess these features.
    serialPort->open(QIODevice::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud57600);

    qInfo("SUUUHHH");
    QString buffer = "sth pretty";
    serialPort->write(buffer.toUtf8());
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
