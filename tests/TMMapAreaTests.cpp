#include "TMMapAreaTests.h"
#include <TMException.h>

void TMMapAreaTests::initTestCase()
{
    x = 4;
    y = 5;
    m_mapArea = std::make_shared<TM::Map::MapArea<double>>(x, y);
}

void TMMapAreaTests::getTMException_for_out_of_range(){
        QVERIFY_EXCEPTION_THROWN(m_mapArea->getIndex(6,5), TM::details::TMException);
}

void TMMapAreaTests::get_right_index(){
        std::size_t i = m_mapArea->sizeX()-1;
        std::size_t j = m_mapArea->sizeY()-1;
        QVERIFY(m_mapArea->getIndex(i, j) == (i+j*m_mapArea->sizeX()));
}

QTEST_MAIN(TMMapAreaTests)
