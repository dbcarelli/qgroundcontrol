#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QTimer>
#include <QTime>

class DataStationLink
{
private:
    bool connected;
    QSerialPort * serialPort;
    QString preamble = "street";
    QString prelimitor = "<";
    QString postlimitor = ">";

    QString _read(size_t size, int time=100);
    int _write(QString buffer);
    QTime clock;

public:
    DataStationLink(QString portname);
    ~DataStationLink(){serialPort->close();}

    int setDataStationId(QString newId);
    QString deployDataStation(QString targetId, bool testStatus);

    void sendCommand(QString targetId, QString command);
    bool turnOnDS(QString targetId);

    void flushIncomingBuffer();

};

