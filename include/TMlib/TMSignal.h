#ifndef TMSIGNAL_H
#define TMSIGNAL_H

#include <QObject>
#include <memory>
#include "TMlib/TMMapArea.h"

namespace TM {
class TMSignal : public QObject {
    Q_OBJECT
public:
    explicit TMSignal(QObject *parent = 0):QObject(parent){}

    void emitSignal(std::shared_ptr<TM::Map::MapArea<double>> map);

signals:
    void signalUpdate(std::shared_ptr<TM::Map::MapArea<double>>);
};
}
#endif // TMSIGNAL_H
