#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QObject>

class DataStationLink : public QObject
{
Q_OBJECT
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

    bool getConnected() { return connected; }

public slots:
    void serialErrorHandler(QSerialPort::SerialPortError err);

signals:
    void connectedChanged(bool isOpen);
};





