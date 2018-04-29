#include "LandingSequenceManager.h"

LandingSequenceManager::LandingSequenceManager(QGCApplication *app, QGCToolbox *toolbox)
    : QGCTool(app, toolbox)
{
    qmlRegisterUncreatableType<LandingSequenceManager> ("QGroundControl", 1, 0, "LandingSequenceManager", "Reference only");
    loadFromFile();
}

void LandingSequenceManager::toggleActive(int index){
    landingSequences[index].setActive(!(landingSequences.at(index).getActive()));
    for(int i= 0; i< landingSequences.size(); i++){
        landingSequences[i].setActive(false);
    }
    emit landingSequencesChanged();
}

QVariantList LandingSequenceManager::getLandingSequences() const
{
    QVariantList varLandingSeqs = QVariantList();

    for (int i = 0; i < landingSequences.size(); i++){
        QMap<QString, QVariant> map = QMap<QString, QVariant>();
        map.insert("loiter", QVariant::fromValue(landingSequences.at(i).getLoiter()));
        map.insert("touchdown", QVariant::fromValue(landingSequences.at(i).getTouchdown()));
        map.insert("active", QVariant::fromValue(landingSequences.at(i).getActive()));
        map.insert("id", QVariant::fromValue(landingSequences.at(i).getID()));
        map.insert("description", QVariant::fromValue(landingSequences.at(i).getDescription()));
        QVariantList varWaypoints = QVariantList();
        for (int j = 0; j < landingSequences.at(i).getWaypoints().size(); j++){
            qInfo() << "get a waypoint";
            varWaypoints.append(QVariant::fromValue(landingSequences.at(i).getWaypoints().at(j)));
        }
        map.insert("waypoints", varWaypoints);
        varLandingSeqs.append(map);
    }
    return varLandingSeqs;
}

void LandingSequenceManager::insertLandingSequence(LandingSequence& landingSequence){
    landingSequences.append(landingSequence);
}

void LandingSequenceManager::loadFromFile()
{
    // For whovever is going to look throught this... json fucking sucks and is the most ridiculous
    // thing I have ever seen. Sorry. -DC

    QString loc = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    loc += "/QGroundControl/landingsequences.json";

    QFile *saveFile = new QFile(loc);
    if (!saveFile->exists()){
        qDebug() << "LandingSequence::loadFromFile - file does not exist at " << loc << "\n";
        return;
    }

    saveFile->open(QIODevice::ReadOnly);
    QJsonArray jsonArr = QJsonDocument::fromJson(saveFile->readAll()).array();
    saveFile->close();
    delete saveFile;

    landingSequences.clear();
    // each of these is a landing sequence
    for (QJsonArray::iterator i = jsonArr.begin(); i != jsonArr.end(); i++){
        // create new LandingSequence pointer
        LandingSequence *newLandingSequence = new LandingSequence();

        // get a Landing Sequence json object
        QJsonObject jsonLandingSequence = (*i).toObject();

        // get the loiter coordinate and add to this LandingSequence
        qInfo() << "Found a loiter point!";
        QJsonObject jsonLoiterCoordinate = jsonLandingSequence.value("loiter").toObject();
        double loiterLat = jsonLoiterCoordinate.value("lat").toDouble();
        double loiterLon = jsonLoiterCoordinate.value("lon").toDouble();
        double loiterAlt = jsonLoiterCoordinate.value("alt").toDouble();
        QGeoCoordinate loiterPoint = QGeoCoordinate(loiterLat, loiterLon, loiterAlt);
        qInfo() << "Loiter Point";
        qInfo() << "    Lat: "; qInfo() << loiterLat;
        qInfo() << "    Lon: "; qInfo() << loiterLon;
        qInfo() << "    Alt: "; qInfo() << loiterAlt;
        newLandingSequence->setLoiter(loiterPoint);

        // get the touchdown coordinate and add to this LandingSequence
        qInfo() << "Found a touchdown point";
        QJsonObject jsonTouchdownCoordinate = jsonLandingSequence.value("touchdown").toObject();
        double touchdownLat = jsonTouchdownCoordinate.value("lat").toDouble();
        double touchdownLon = jsonTouchdownCoordinate.value("lon").toDouble();
        double touchdownAlt = jsonTouchdownCoordinate.value("alt").toDouble();
        QGeoCoordinate touchdownPoint = QGeoCoordinate(touchdownLat, touchdownLon, touchdownAlt);
        qInfo() << "Touchdown Point";
        qInfo() << "    Lat: "; qInfo() << touchdownLat;
        qInfo() << "    Lon: "; qInfo() << touchdownLon;
        qInfo() << "    Alt: "; qInfo() << touchdownAlt;
        newLandingSequence->setTouchdown(touchdownPoint);

        // get waypoints that define the landing corridor
        QJsonArray corridor = jsonLandingSequence.value("corridor").toArray();
        for (QJsonArray::iterator i = corridor.begin(); i != corridor.end(); i++){
            qInfo() << "Found a corridor point";
            QJsonObject jsonWaypoint = (*i).toObject();
            double waypointLat = jsonWaypoint.value("lat").toDouble();
            double waypointLon = jsonWaypoint.value("lon").toDouble();
            double waypointAlt = jsonWaypoint.value("alt").toDouble();
            QGeoCoordinate newWaypoint = QGeoCoordinate(waypointLat, waypointLon, waypointAlt);
            qInfo() << "Corridor Point";
            qInfo() << "    Lat: "; qInfo() << waypointLat;
            qInfo() << "    Lon: "; qInfo() << waypointLon;
            qInfo() << "    Alt: "; qInfo() << waypointAlt;
            newLandingSequence->insertWaypoint(newWaypoint);
        }
        landingSequences.append(*newLandingSequence);
        delete newLandingSequence;
    }

    // activate one landing sequence at least
    if (landingSequences.size() > 0){
        qInfo() << "Activated a landing sequence!";
        landingSequences[0].setActive(true);
    }

    emit landingSequencesChanged();
}

void LandingSequenceManager::saveToFile()
{
    QString loc = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    loc += "/QGroundControl/landingsequences.json";

    QFile *saveFile = new QFile(loc);

    QJsonArray jsonLandingSequenceArray;

    // each of these is a landing sequence
    for (QList<LandingSequence>::iterator i = landingSequences.begin();
         i != landingSequences.end(); i++){
        // create new landing sequence json object
        QJsonObject jsonLandingSequenceObject;
        qInfo() << "Creating loiter jsonObject";
        // create a loiter json object and add it to the landing sequence
        QJsonObject jsonLoiterObject;
        jsonLoiterObject.insert("lat", i->getLoiter().latitude());
        jsonLoiterObject.insert("lon", i->getLoiter().longitude());
        jsonLoiterObject.insert("alt", i->getLoiter().altitude());
        jsonLandingSequenceObject.insert("loiter", jsonLoiterObject);

        // create a touchdown json object and add it to the landing sequence
        QJsonObject jsonTouchdownObject;
        jsonTouchdownObject.insert("lat", i->getTouchdown().latitude());
        jsonTouchdownObject.insert("lon", i->getTouchdown().longitude());
        jsonTouchdownObject.insert("alt", i->getTouchdown().altitude());
        jsonLandingSequenceObject.insert("touchdown", jsonTouchdownObject);

        // creat json waypoints that define the landing corridor and add them to the landing sequence
        QJsonArray jsonCorridorArray;
        for (QList<QGeoCoordinate>::iterator j = i->getWaypoints().begin();
             j != i->getWaypoints().end(); j++){
            // make a new json waypoint object
            QJsonObject jsonWaypointObject;
            jsonWaypointObject.insert("lat", j->latitude());
            jsonWaypointObject.insert("lon", j->longitude());
            jsonWaypointObject.insert("alt", j->altitude());
            jsonCorridorArray.append(jsonWaypointObject);
        }
        jsonLandingSequenceObject.insert("corridor", jsonCorridorArray);

        // append the json landing sequence object to the landing sequences
        jsonLandingSequenceArray.append(jsonLandingSequenceObject);
    }

    QJsonDocument doc = QJsonDocument(jsonLandingSequenceArray);

    saveFile->open(QIODevice::WriteOnly);
    saveFile->write(doc.toJson(QJsonDocument::Indented));
    saveFile->close();
}


