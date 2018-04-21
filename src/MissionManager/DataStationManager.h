
#include <QList>

#include "QGCApplication.h"
#include "QGCToolbox.h"

#include "DataStationLink.h"
#include "DataStation.h"

class DataStationManager : public QGCTool
{
Q_OBJECT
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
    QString initializeDS();

    // get datastation's coordinates, mark as deployed
    void deployDS(QString targetId);

    QList<DataStation *> getDataStations(){ return dataStations; }

    Q_INVOKABLE void toggleActive(int index);

    void loadFromFile();
    void saveToFile();
    // remove datastation from list?
    // void removeDS(QString targetId);
};



