#ifndef LANDINGSEQUENCE_H
#define LANDINGSEQUENCE_H

#include <QObject>
#include <QGeoCoordinate>

class LandingSequence : public QObject
{
Q_OBJECT
public:
    LandingSequence(){}
    LandingSequence(const LandingSequence& other);
    LandingSequence& operator =(const LandingSequence& other);

    QGeoCoordinate getLoiter() const { return loiter; }
    QGeoCoordinate getTouchdown() const { return touchdown; }
    QList<QGeoCoordinate> getWaypoints() const { return waypoints; }
    bool getActive() const { return active; }
    QString getID() const { return id; }
    QString getDescription() const { return description; }

    void setLoiter(QGeoCoordinate newLoiter) { loiter = newLoiter; }
    void setTouchdown(QGeoCoordinate newTouchdown) { touchdown = newTouchdown; }
    void setActive(bool newActive) { active = newActive; }
    void insertWaypoint(QGeoCoordinate newWaypoint) { waypoints.append(newWaypoint); }
    void setDescription(QString newDescription) { description = newDescription ; }


private:
    QGeoCoordinate loiter;
    QGeoCoordinate touchdown;
    QList<QGeoCoordinate> waypoints;
    bool active;
    QString id;
    QString description;
};

#endif // LANDINGSEQUENCE_H
