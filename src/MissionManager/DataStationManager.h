
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
    Q_PROPERTY(QList<DataStation *> dataStations READ getDataStations NOTIFY dataStationsChanged)//add a write when we know what writing will look like
   // QList<DataStation *> getDataStations                  () { return dataStations; }
    QList<DataStation *> getDataStations (){return dataStations;}
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
    Q_INVOKABLE void setDataStationSelected(int i);

    DataStation getDataStation(int i);
signals:
    void dataStationsChanged();
};



