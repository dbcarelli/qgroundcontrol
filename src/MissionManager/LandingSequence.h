#ifndef LANDINGSEQUENCE_H
#define LANDINGSEQUENCE_H

#include <QObject>
#include <QGeoCoordinate>

class LandingSequence : public QObject
{
Q_OBJECT
public:
    LandingSequence(){};
    LandingSequence(const LandingSequence& other);
    LandingSequence& operator =(const LandingSequence& other);

    QGeoCoordinate getLoiter() const { return loiter; }
    QGeoCoordinate getTouchdown() const { return touchdown; }
    QList<QGeoCoordinate> getWaypoints() const { return waypoints; }
    bool getActive() const;

    void setLoiter(const QGeoCoordinate newLoiter) { loiter = newLoiter; }
    void setTouchdown(const QGeoCoordinate newTouchdown) { touchdown = newTouchdown; }
    void setActive(const bool newActive) { active = newActive; }
    void insertWaypoint(const QGeoCoordinate newWaypoint) { waypoints.append(newWaypoint); }


private:
    QGeoCoordinate loiter;
    QGeoCoordinate touchdown;
    QList<QGeoCoordinate> waypoints;
    bool active;
};

#endif // LANDINGSEQUENCE_H
