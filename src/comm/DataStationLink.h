#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>

class DataStationLink
{
private:
    bool connected;
    QSerialPort * serialPort;

    QString _read(size_t size);
    int _write(QString buffer);

public:
    DataStationLink(QString portname);
    ~DataStationLink();

    int setDataStationId(QString newId);
    int deployDataStation(QString targetId);

};

//class DataStationLink
//{
//    bool connected;
//    unsigned int errors;
//    int Xbee;
//    struct termios tty;
//    struct termios tty_old;
//public:
//    DataStationLink(char *portName);
//    ~DataStationLink();

//    int readDataStationLink(char *buffer, size_t buf_size);
//    int writeDataStationLink(char *buffer, size_t buf_size);
//    bool isConnected();
//};

#endif // DATASTATIONLINK_H
