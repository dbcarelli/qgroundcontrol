#include "DataStationLink.h"

DataStationLink::DataStationLink(char *portName)
{
    this->connected = false;
    this->Xbee = open( "/dev/ttyXbee0", O_RDWR| O_NOCTTY );//this was taken from a Xbee serial reader, port needs to be changed

//    if ( this->Xbee < 0 )
//    {
//        cout << "Error " << errno << " opening " << "/dev/ttyXbee0" << ": " << strerror (errno) << endl;
//    } //an error reporter that doesn't work

    struct termios tty;
    struct termios tty_old;
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
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush( Xbee, TCIFLUSH );
//    if ( tcsetattr ( Xbee, TCSANOW, &tty ) != 0) {
//       std::cout << "Error " << errno << " from tcsetattr" << std::endl;
//    }//another copied error reoporter that doesn't work


}
DataStationLink::~DataStationLink()
{
    if (this->connected){
        this->connected = false;
    }
}
int DataStationLink::readDataStationLink(char *buffer, unsigned int buf_size)
{
    int n = 0,
        spot = 0;
    char buf = '\0';

    /* Whole response*/
    char response[1024];
    memset(response, '\0', sizeof response);

    do {
        n = read( Xbee, &buf, 1 );
        sprintf( &response[spot], "%c", buf );
        spot += n;
    } while( buf != '\r' && n > 0);

//    if (n < 0) {
//        std::cout << "Error reading: " << strerror(errno) << std::endl;
//    }
//    else if (n == 0) {
//        std::cout << "Read nothing!" << std::endl;
//    }
//    else {
//        std::cout << "Response: " << response << std::endl;
//    } A bunch of uncompliedable error reporting
}

bool DataStationLink::writeDataStationLink(char *buffer, unsigned int buf_size)
{
    unsigned char cmd[] = "INIT \r";
    int n_written = 0,
        spot = 0;

    do {
        n_written = write( Xbee, &cmd[spot], 1 );
        spot += n_written;
    } while (cmd[spot-1] != '\r' && n_written > 0);
}

bool DataStationLink::isConnected()
{
    return this->connected;
}
