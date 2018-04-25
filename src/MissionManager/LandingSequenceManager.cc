#include "LandingSequenceManager.h"

LandingSequenceManager::LandingSequenceManager(QGCApplication *app, QGCToolbox *toolbox)
    : QGCTool(app, toolbox)
{
    qmlRegisterUncreatableType<LandingSequenceManager> ("QGroundControl", 1, 0, "LandingSequenceManager", "Reference only");
}

QVariantList LandingSequenceManager::getLandingSequences() const{
    QVariantList varLandingSeqs = QVariantList();

    for (int i = 0; i < landingSequences.size(); i++){
        QMap<QString, QVariant> map = QMap<QString, QVariant>();
        map.insert("loiter", QVariant::fromValue(landingSequences.at(i).getLoiter()));
        map.insert("touchdown", QVariant::fromValue(landingSequences.at(i).getTouchdown()));

        QVariantList varWaypoints = QVariantList();
        for (QList<QGeoCoordinate>::iterator i = landingSequences.at(i).getWaypoints().begin();
             i != landingSequences.at(i).getWaypoints().end(); i++){
            varWaypoints.append(QVariant::fromValue(*i));
        }

        map.insert("waypoints", varWaypoints);
    }

    return varLandingSeqs;
}


