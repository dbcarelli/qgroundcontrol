#ifndef DATASTATIONLINK_H
#define DATASTATIONLINK_H

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
class DataStationLink
{
    bool connected;
    unsigned int errors;
    int Xbee;
    struct termios tty;
    struct termios tty_old;
public:
    DataStationLink(char *portName);
    ~DataStationLink();

    int readDataStationLink(char *buffer, unsigned int buf_size);
    bool writeDataStationLink(char *buffer, unsigned int buf_size);
    bool isConnected();
};

#endif // DATASTATIONLINK_H
