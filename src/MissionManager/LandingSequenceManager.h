#ifndef LANDINGSEQUENCEMANAGER_H
#define LANDINGSEQUENCEMANAGER_H

#include <QVariant>
#include <QGeoCoordinate>

#include "QGCToolbox.h"
#include "LandingSequence.h"

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
