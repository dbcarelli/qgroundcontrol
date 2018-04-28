#ifndef LANDINGSEQUENCEMANAGER_H
#define LANDINGSEQUENCEMANAGER_H

#include <QVariant>
#include <QGeoCoordinate>

#include <QList>
#include <QStandardPaths>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QSaveFile>
#include <QDebug>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "QGCToolbox.h"
#include "LandingSequence.h"

#include "QGCApplication.h"


class LandingSequenceManager : public QGCTool
{
Q_OBJECT

public:

    LandingSequenceManager(QGCApplication *app, QGCToolbox *toolbox);
    ~LandingSequenceManager(){};

    QVariantList getLandingSequences() const;

    Q_INVOKABLE void toggleActive(int index);

    void loadFromFile();

    void saveToFile();

private:
    QList<LandingSequence> landingSequences;

signals:
    void landingSequencesChanged();
};

#endif // LANDINGSEQUENCEMANAGER_H
