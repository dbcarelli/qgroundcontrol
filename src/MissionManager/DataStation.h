#ifndef DATASTATION_H
#define DATASTATION_H

#include <QString>
#include <QObject>

class DataStation //: public QObject
{
    //Q_OBJECT
public:
    DataStation();

    void setId(QString id);
    void setGPSCoords(double newlon, double newlat);
    void setSelected();
    bool getSelected();
    double getLat() const;
    double getLon() const;
    QString getId() const;
    //Q_PROPERTY(Qbool selected READ getSelected WRITE setSelected NOTIFY selectionChanged)


private:
    QString id;
    double lon;
    double lat;
    bool selected;
signals:
    void selectionChanged();

};

#endif // DATASTATION_H
