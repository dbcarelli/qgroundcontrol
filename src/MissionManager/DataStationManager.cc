
#include "DataStationManager.h"

DataStationManager::DataStationManager(QGCApplication *app, QGCToolbox *toolbox)
    :QGCTool(app, toolbox)
{
    qmlRegisterUncreatableType<DataStationManager> ("QGroundControl", 1, 0, "DataStationManager", "Reference only");
    qmlRegisterType<DataStation>("QGroundControl", 1, 0, "DataStation");

    loadFromFile("/QGroundControl/datastations.json");
    saveToFile("/QGroundControl/datastations.json");
    _dsLink = nullptr;
    clock = QTime();

}

DataStationManager::~DataStationManager(){
    delete _dsLink;
}

void DataStationManager::connect(QString portname){
    if (_dsLink != nullptr) delete _dsLink;
    _dsLink = new DataStationLink(portname);
//    qDebug() << "DataStationManager::connect - initializeDS output: " << initializeDS("02");
}

QString DataStationManager::initializeDS(QString newId){
    if (!_dsLink){
        qDebug() << "not connected!";
        return "Failed";
    }

    if (_dsLink->setDataStationId(newId)){
        DataStation *newStation = new DataStation();
        newStation->setId(newId);
        dataStations.append(newStation);
        emit dataStationsChanged();
        return newId;
    }

    return "-1";
}
void DataStationManager::turnOnDS(QString targetId){
    if (!_dsLink){
        qDebug() << "not connected!";
        return;
    }

    if(_dsLink->turnOnDS(targetId))
        qInfo() << "Data Station "+targetId+" turned on.";
    return;

}

void DataStationManager::deployDS(QString targetId, bool testStatus){
    if (!_dsLink){
        qDebug() << "not connected!";
        return;
    }

    QString coords;

    coords =_dsLink->deployDataStation(targetId, testStatus);

    if(testStatus){
        if(coords=="245233230,544344570"){
            emit testPassed();
            return;
        }
        emit testFailed();
        return;
    }
    qInfo() << "coords: "+coords;

    QStringList list= coords.split(",");
    double lat=list.at(0).toDouble()/10000000;
    double lon=list.at(1).toDouble()/10000000;

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
        newStation->setLat(lat);
        newStation->setLon(lon);
        dataStations.append(newStation);
        emit dataStationsChanged();
        return;
    }



    dataStations[index]->setLat(lat);
    dataStations[index]->setLon(lon);

    emit dataStationsChanged();
}

void DataStationManager::loadFromFile(QString path){
    QString loc = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //loc += "/QGroundControl/datastations.json";
    loc+= path;

    QFile *saveFile = new QFile(loc);
    if (!saveFile->exists()){
        qDebug() << "DataStationManager::loadFromFile - file does not exist at " << loc << "\n";
        return;
    }

    saveFile->open(QIODevice::ReadOnly);
    QJsonArray jsonArr = QJsonDocument::fromJson(saveFile->readAll()).array();
    saveFile->close();
    delete saveFile;

    dataStations.clear();
    for (QJsonArray::iterator i = jsonArr.begin(); i != jsonArr.end(); i++){
        QJsonObject jsonObj = (*i).toObject();

        DataStation *newStation = new DataStation();
        newStation->setId(jsonObj.value("id").toString());
        newStation->setLat(jsonObj.value("lat").toDouble());
        newStation->setLon(jsonObj.value("lon").toDouble());
        newStation->setActive(jsonObj.value("active").toBool());

        dataStations.append(newStation);
    }
    emit dataStationsChanged();

}

void DataStationManager::saveToFile(QString path){
    QString loc = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //loc += "/QGroundControl/datastations.json";
    loc+= path;

    QFile *saveFile = new QFile(loc);

    QJsonArray jsonArr;
    QJsonObject jsonObj;
    for (QList<DataStation *>::iterator i = dataStations.begin();
         i != dataStations.end(); i++){
        jsonObj.insert("id", (*i)->getId());
        jsonObj.insert("lat", (*i)->getLat());
        jsonObj.insert("lon", (*i)->getLon());
        jsonObj.insert("active", (*i)->getActive());

        jsonArr.append(jsonObj);
    }

    QJsonDocument doc = QJsonDocument(jsonArr);

    saveFile->open(QIODevice::WriteOnly);
    saveFile->write(doc.toJson(QJsonDocument::Indented));
    saveFile->close();
}

void DataStationManager::toggleActive(int index){
    dataStations.at(index)->toggleActive();
    emit dataStationsChanged();
}

//QGeoCoordinate DataStationManager::getCoordinate(int index){
//    QGeoCoordinate retVal = QGeoCoordinate();
//    retVal.setLatitude(dataStations.at(index)->getLat());
//    retVal.setLongitude(dataStations.at(index)->getLon());
//    // TODO: data station object should have altitude parameter
//    //retVal.setAltitude(dataStation.at(index).getAlt());

//    return retVal;
//}

void DataStationManager::deleteStation(int index){
    DataStation * dataStationDead = dataStations.at(index);
    delete dataStationDead;
    dataStations.removeAt(index);
    emit dataStationsChanged();
}





