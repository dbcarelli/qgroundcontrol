#include "DataStation.h"

DataStation::DataStation()
{
    id = "01";
}

void DataStation::setId(QString newId){
    id = newId;
}

void DataStation::setGPSCoords(double newLon, double newLat){
    lon = newLon;
    lat = newLat;
}

double DataStation::getLat() const{
    return lat;
}

double DataStation::getLon() const{
    return lon;
}

QString DataStation::getId() const{
    return id;
}
