#ifndef DATASTATIONLINK_H
#define DATASTATIONLINK_H

#define ARDUINO_WAIT_TIME 2000//rename this once scope is clear
#define MAX_DATA_LENGTH 255

//#include <windows.h>//from SerialPort.h
#include <stdio.h>
#include <stdlib.h>
//most code simply copied from SerialPort.h
class DataStationLink
{
    HANDLE handler;
    bool connected;
    COMSTAT status;
    unsigned int errors;
public:
    DataStationLink(char *portName);
    ~SerialPort();

    int readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(char *buffer, unsigned int buf_size);
    bool isConnected();
};

#endif // DATASTATIONLINK_H
