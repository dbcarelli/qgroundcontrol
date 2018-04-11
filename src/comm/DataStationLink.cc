#include "DataStationLink.h"

DataStationLink::DataStationLink(char *portName)
{
    this->connected = false;
    this->Xbee = open( portName, O_RDWR| O_NOCTTY );

    memset (&tty, 0, sizeof tty);

    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)B9600);
    cfsetispeed (&tty, (speed_t)B9600);

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
}
DataStationLink::~DataStationLink()
{
    if (this->connected){
        this->connected = false;
        //from window version, handle was cleared here.
    }
}
int DataStationLink::readDataStationLink(char *buffer, unsigned int buf_size)
{
    int n = 0,
        spot = 0;
//    char buf = '\0';

    /* Whole response*/
    char response[buf_size];
    memset(response, '\0', sizeof response);

    do {//should read out postlimiter first
        n = read( Xbee, &buffer, 1 );//most likely my use of pointeres is messed up here and the next line//should read the Xbee into the buffer, one character at a time
        sprintf( &response[spot], "%c", *buffer );//if formatting is the issue, go here first
        spot += n;
    } while( spot>0 && (unsigned int) spot<buf_size && n > 0);
    return *response;//returns a pointer to the response, which is where the read in data is written to.
}

bool DataStationLink::writeDataStationLink(char *buffer, unsigned int buf_size)
{
    //unsigned char cmd[] = "INIT \r";//prelimeter here
    int n_written = 0,
        spot = 0;

    do {
        n_written = write( Xbee, &buffer[spot], 1 );
        spot += n_written;
    } while (n_written > 0&& spot>0 && (unsigned int) spot<buf_size);//removed buffer[spot-1] != '\r' &&  in favor of buf_size based limiting
    return spot>0;
}

bool DataStationLink::isConnected()
{
    return this->connected;
}
