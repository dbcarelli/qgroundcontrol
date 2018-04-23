#include "DataStation.h"

DataStation::DataStation()
{
    id = "01";
    lon = -1;
    lat = -1;
    active=false;
}

DataStation::DataStation(const DataStation &other)
{
    id = other.getId();
    coordinate = other.getCoordinate();
    active = other.getActive();
}

void DataStation::setId(QString newId){
    id = newId;
}

void DataStation::setLat(double newLat){
    coordinate.setLatitude(newLat);
}
void DataStation::setLon(double newLon){
    coordinate.setLongitude(newLon);
}

double DataStation::getLat() const{
    return coordinate.latitude();
}

double DataStation::getLon() const{
    return coordinate.longitude();
}

QString DataStation::getId() const{
    return id;
}

void DataStation::setActive(bool newActive){
    active = newActive;
}

bool DataStation::getActive() const{
    return active;
}

void DataStation::toggleActive(){
    active = !active;
}

QGeoCoordinate DataStation::getCoordinate() const{
    return coordinate;
}

