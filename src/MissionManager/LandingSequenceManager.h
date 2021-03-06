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
Q_PROPERTY(QVariantList landingSequences READ getLandingSequences NOTIFY landingSequencesChanged)

public:

    LandingSequenceManager(QGCApplication *app, QGCToolbox *toolbox);
    ~LandingSequenceManager(){}

    QVariantList getLandingSequences() const;

    Q_INVOKABLE void toggleActive(int index);

    Q_INVOKABLE void setDescription(int index, QString newDescription){ landingSequences[index].setDescription(newDescription); emit landingSequencesChanged(); }

    void loadFromFile();

    Q_INVOKABLE void saveToFile();

    void insertLandingSequence(LandingSequence& landingSequence);

private:
    QList<LandingSequence> landingSequences;

signals:
    void landingSequencesChanged();
};

#endif // LANDINGSEQUENCEMANAGER_H
