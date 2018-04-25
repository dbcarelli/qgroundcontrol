
#include <QList>
#include <QStandardPaths>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QSaveFile>
#include <QDebug>

#include "QGCApplication.h"
#include "QGCToolbox.h"

#include "DataStationLink.h"
#include "DataStation.h"

class DataStationManager : public QGCTool
{
Q_OBJECT
Q_PROPERTY(QList<DataStation*> dataStations READ getDataStations NOTIFY dataStationsChanged)

private:

    DataStationLink * _dsLink;
    QList<DataStation *> dataStations;

public:

    DataStationManager(QGCApplication *app, QGCToolbox *toolbox);
    // close _dsLink
    ~DataStationManager();

    // Initialize _dsLink
    Q_INVOKABLE void connect(QString portname);

    // initialize datastation, give it a new ID, returns ID
    Q_INVOKABLE QString initializeDS();

    // get datastation's coordinates, mark as deployed
    void deployDS(QString targetId);

    QList<DataStation *> getDataStations(){ return dataStations; }

    Q_INVOKABLE void toggleActive(int index);

    void loadFromFile(QString path);
    void saveToFile(QString path);
    // remove datastation from list?
    // void removeDS(QString targetId);

    Q_INVOKABLE QGeoCoordinate getCoordinate(int index);
    Q_INVOKABLE double getLat(int index){ return dataStations.at(index)->getLat(); }
    Q_INVOKABLE double getLon(int index){ return dataStations.at(index)->getLon(); }
    Q_INVOKABLE QString getId(int index){ return dataStations.at(index)->getId(); }
    Q_INVOKABLE void deleteStation(int index);
    Q_INVOKABLE bool isActive(int index){ return dataStations.at(index)->getActive(); }
    Q_INVOKABLE void setActive(int index, bool status){ dataStations.at(index)->setActive(status); }
    Q_INVOKABLE int getNumOfDataStations(){ return dataStations.size(); }

signals:
    void dataStationsChanged();
};


