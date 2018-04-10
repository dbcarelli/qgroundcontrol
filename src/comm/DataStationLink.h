#ifndef DATASTATIONLINK_H
#define DATASTATIONLINK_H

#define ARDUINO_WAIT_TIME 2000//rename this once scope is clear
#define MAX_DATA_LENGTH 255

//#include <windows.h>//from SerialPort.h
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
//most code simply copied from SerialPort.h
class DataStationLink
{
    bool connected;
    unsigned int errors;
    int Xbee;
public:
    DataStationLink(char *portName);
    ~DataStationLink();

    int readDataStationLink(char *buffer, unsigned int buf_size);
    bool writeDataStationLink(char *buffer, unsigned int buf_size);
    bool isConnected();
};

#endif // DATASTATIONLINK_H
