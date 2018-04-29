
#include <QList>
#include <QStandardPaths>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QSaveFile>
#include <QDebug>
#include <QTime>

#include "QGCApplication.h"
#include "QGCToolbox.h"
#include <QStringList>

#include "DataStationLink.h"
#include "DataStation.h"

class DataStationManager : public QGCTool
{
Q_OBJECT
Q_PROPERTY(QVariantList dataStations READ getDataStations NOTIFY dataStationsChanged)

private:

    DataStationLink * _dsLink;
    QList<DataStation *> dataStations;
    QTime clock;
    const int timeOut=10;

public:

    QVariantList getDataStations (){
        QVariantList varDataStations = QVariantList();
        for (int i = 0; i < dataStations.size(); i++){
            QMap<QString, QVariant> map = QMap<QString, QVariant>();
            map.insert("lat", dataStations.at(i)->getLat());
            map.insert("lon", dataStations.at(i)->getLon());
            map.insert("id", dataStations.at(i)->getId());
            map.insert("active", dataStations.at(i)->getActive());
            map.insert("coordinate", QVariant::fromValue(dataStations.at(i)->getCoordinate()));
            varDataStations.append(map);
        }
        return varDataStations;
    }

    DataStationManager(QGCApplication *app, QGCToolbox *toolbox);
    // close _dsLink
    ~DataStationManager();

    // Initialize _dsLink
    Q_INVOKABLE void connect(QString portname);

    // initialize datastation, give it a new ID, returns ID
    Q_INVOKABLE QString initializeDS(QString newId);

    // get datastation's coordinates, mark as deployed
    Q_INVOKABLE void deployDS(QString targetId, bool testStatus);

    Q_INVOKABLE void turnOnDS(QString targetId);

    Q_INVOKABLE void toggleActive(int index);

    Q_INVOKABLE void loadFromFile(QString path);
    Q_INVOKABLE void saveToFile(QString path);
    // remove datastation from list?
    Q_INVOKABLE void deleteStation(int index);

    DataStation getDataStation(int i);

signals:
    void dataStationsChanged();
    void testPassed();
    void testFailed();
};


