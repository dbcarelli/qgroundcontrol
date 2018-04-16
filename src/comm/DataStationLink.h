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



