#ifndef DATASTATION_H
#define DATASTATION_H

#include <QString>

class DataStation
{
public:
    DataStation();

    void setId(QString id);
    void setGPSCoords(double newlon, double newlat);
    double getLat() const;
    double getLon() const;
    QString getId() const;

private:
    QString id;
    double lon;
    double lat;
};

#endif // DATASTATION_H
