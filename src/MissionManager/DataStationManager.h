
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

Q_DECLARE_METATYPE(DataStation)

class DataStationManager : public QGCTool
{
Q_OBJECT
Q_PROPERTY(QVariantList dataStations READ getDataStations NOTIFY dataStationsChanged)

private:

    DataStationLink * _dsLink;
    QList<DataStation *> dataStations;

public:

    QVariantList getDataStations (){
        QVariantList varDataStations = QVariantList();
        for (int i = 0; i < dataStations.size(); i++){
            QMap<QString, QVariant> map = QMap<QString, QVariant>();
            map.insert("lat", dataStations.at(i)->getLat());
            map.insert("lon", dataStations.at(i)->getLon());
            map.insert("id", dataStations.at(i)->getId());
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
    QString initializeDS();

    // get datastation's coordinates, mark as deployed
    void deployDS(QString targetId);


    Q_INVOKABLE void toggleActive(int index);

    void loadFromFile();
    void saveToFile();
    // remove datastation from list?
    // void removeDS(QString targetId);
    Q_INVOKABLE void toggleActive(int i);

    DataStation getDataStation(int i);

signals:
    void dataStationsChanged();
};


