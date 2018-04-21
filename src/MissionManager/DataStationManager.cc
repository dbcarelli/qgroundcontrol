#include<DataStationManager.h>

DataStationManager::DataStationManager(QGCApplication *app, QGCToolbox *toolbox)
    :QGCTool(app, toolbox)
{
    qmlRegisterUncreatableType<DataStationManager> ("QGroundControl", 1, 0, "DataStationManager", "Reference only");
//    qRegisterMetaType<DataStationManager*>("DataStationManager*");
}

DataStationManager::~DataStationManager(){
    delete _dsLink;
}

void DataStationManager::connect(QString portname){
    _dsLink = new DataStationLink(portname);
    qInfo() << initializeDS();
}

QString DataStationManager::initializeDS(){
    QString newId;
    int max = 1;
    for (QList<DataStation*>::iterator i = dataStations.begin(); i != dataStations.end(); i++){
        int id = (*i)->getId().toInt();
        if (id > max) max = id;
    }
    newId = QString("%02d").arg(max + 1);
    _dsLink->setDataStationId(newId);

    DataStation *newStation = new DataStation();
    newStation->setId(newId);

    dataStations.append(newStation);

    return newId;
}

void DataStationManager::deployDS(QString targetId){
    QString coords = _dsLink->deployDataStation(targetId);

    int index = -1;
    for (int i = 0; i < dataStations.size(); i++){
        if (targetId == dataStations.at(i)->getId()){
            index = i;
            break;
        }
    }

    if (index == -1){
        DataStation *newStation = new DataStation();
        newStation->setId(targetId);
//        newStation->setGPSCoords(x, y);
        dataStations.append(newStation);
        return;
    }

//    dataStations[index].setGPSCoords(x, y);
}
void DataStationManager::setDataStationSelected(int i){
    dataStations[i]->setSelected();
}
DataStation DataStationManager::getDataStation(int i){
    return *dataStations[i];
}



