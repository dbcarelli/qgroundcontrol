#ifndef DATASTATION_H
#define DATASTATION_H

#include <QObject>
#include <QString>

#include <QGeoCoordinate>

class DataStation : public QObject
{
Q_OBJECT
Q_PROPERTY(QString id READ getId)
Q_PROPERTY(double lon READ getLon)
Q_PROPERTY(double lat READ getLat)
Q_PROPERTY(bool active READ getActive)
Q_PROPERTY(QGeoCoordinate coordinate READ getCoordinate)

public:
    DataStation();
    DataStation(const DataStation& other);

    ~DataStation() {}

    void setId(QString id);
    void setLon(double newLon);
    void setLat(double newLat);
    double getLat() const;
    double getLon() const;
    QString getId() const;
    void setActive(bool newActive);
    bool getActive() const;
    void toggleActive();
    QGeoCoordinate getCoordinate() const;

private:
    QString id;
    double lon;
    double lat;
    bool active;
    QGeoCoordinate coordinate;

};

#endif // DATASTATION_H




