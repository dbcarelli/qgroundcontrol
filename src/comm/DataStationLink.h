#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>

class DataStationLink
{
private:
    bool connected;
    QSerialPort * serialPort;
    QString preamble = "street";
    QString prelimitor = "<";
    QString postlimitor = ">";

    QString _read(size_t size);
    int _write(QString buffer);

public:
    DataStationLink(QString portname);
    ~DataStationLink(){serialPort->close();}

    int setDataStationId(QString newId);
    QString deployDataStation(QString targetId);

};

