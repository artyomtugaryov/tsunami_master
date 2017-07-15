#ifndef UNITTEST_H
#define UNITTEST_H

#include "TestCommon.h"
#include <TMMapArea.h>

#include <QtTest/QtTest>
#include <memory>

class TMMapAreaTests
        : public QObject
{
    Q_OBJECT
    std::size_t x;
    std::size_t y;
    std::shared_ptr<TM::Map::MapArea<double>> m_mapArea;
public:
    virtual ~TMMapAreaTests(){}
private slots:
    void initTestCase();
    void getTMException_for_out_of_range();
    void get_right_index();

};

#endif // UNITTEST_H
