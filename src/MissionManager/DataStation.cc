#include "DataStation.h"

DataStation::DataStation()
{
    id = "01";
    lon = -1;
    lat = -1;
}

void DataStation::setId(QString newId){
    id = newId;
}

void DataStation::setGPSCoords(double newLon, double newLat){
    lon = newLon;
    lat = newLat;
}
void DataStation::setSelected(){
    selected=!selected;
}
bool DataStation::getSelected(){
    return selected;
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
