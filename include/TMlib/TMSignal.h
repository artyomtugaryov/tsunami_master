#ifndef TMSIGNAL_H
#define TMSIGNAL_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM{
class TMSignal : public QObject {
    Q_OBJECT
public:
    TMSignal(QObject *parent = 0);
    void emitSignal(std::shared_ptr<TM::Map::MapArea<double>> map){
        emit signalUpdate(map);
    }
signals:
    void signalUpdate(std::shared_ptr<TM::Map::MapArea<double>>);
};
}

#endif // TMSIGNAL_H
