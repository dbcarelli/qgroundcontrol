#ifndef DATASTATION_H
#define DATASTATION_H

#include <QObject>
#include <QString>
#include <QObject>

class DataStation //: public QObject
{
Q_PROPERTY(QString id READ getId)
Q_PROPERTY(double lon READ getLon)
Q_PROPERTY(double lat READ getLat)
Q_PROPERTY(bool active READ getActive)

public:
    DataStation();

    void setId(QString id);
    void setLon(double newLon);
    void setLat(double newLat);
    double getLat() const;
    double getLon() const;
    QString getId() const;
    void setActive(bool newActive);
    bool getActive();
    void toggleActive();

private:
    QString id;
    double lon;
    double lat;
    bool active;

};

#endif // DATASTATION_H




