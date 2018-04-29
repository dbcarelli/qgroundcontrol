
#include "DataStationManager.h"

DataStationManager::DataStationManager(QGCApplication *app, QGCToolbox *toolbox)
    :QGCTool(app, toolbox)
{
    qmlRegisterUncreatableType<DataStationManager> ("QGroundControl", 1, 0, "DataStationManager", "Reference only");
    qmlRegisterType<DataStation>("QGroundControl", 1, 0, "DataStation");

    loadFromFile("/QGroundControl/datastations.json");
    saveToFile("/QGroundControl/datastations.json");
    _dsLink = nullptr;
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
    _dsLink->setDataStationId(newId);
    DataStation *newStation = new DataStation();
    newStation->setId(newId);
    dataStations.append(newStation);
    emit dataStationsChanged();
    return newId;
//    QString newId;
//    int max = 1;
//    for (QList<DataStation*>::iterator i = dataStations.begin(); i != dataStations.end(); i++){
//        int id = (*i)->getId().toInt();
//        if (id > max) max = id;
//    }
//    newId = QString("%1").arg(max + 1, 2, 10, QChar('0'));
//    _dsLink->setDataStationId(newId);

//    DataStation *newStation = new DataStation();
//    newStation->setId(newId);

//    dataStations.append(newStation);

//    emit dataStationsChanged();

//    return newId;
}

void DataStationManager::deployDS(QString targetId, bool testStatus){
    if (!_dsLink){
        qDebug() << "not connected!";
        return;
    }

    QString coords = _dsLink->deployDataStation(targetId, testStatus);

    if(testStatus){
        if(coords=="245233230,544344570"){
            emit testPassed();
            qInfo() << "coords: "+coords;
            return;
        }
        emit testFailed();
        qInfo() << "coords: "+coords;
        return;
    }

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
        emit dataStationsChanged();
        return;
    }

    emit dataStationsChanged();

//    dataStations[index].setGPSCoords(x, y);
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
        newStation->setLon(jsonObj.value("lon").toDouble());
        newStation->setLat(jsonObj.value("lat").toDouble());

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
}




