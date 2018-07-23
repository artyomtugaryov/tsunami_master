#include <gtest/gtest.h>
#include <TMlib/TMOperators.h>
#include <TMlib/TMMapArea.h>
#include <memory>

using namespace TM::Map;
using namespace TM::Scheme::Operators;

class TMOperatorsTests : public ::testing::Test {
protected:
    static std::shared_ptr<MapArea<double>> m_maparea;

};

std::shared_ptr<MapArea<double>> TMOperatorsTests::m_maparea;

TEST_F(TMOperatorsTests, operatorT) {
    m_maparea = std::make_shared<MapArea<double>>(3, 3);
    m_maparea->setDataByPoint(0, 0, 10);
    m_maparea->setDataByPoint(1, 0, 10);
    EXPECT_EQ(T(m_maparea, 0, 0, direction::X_FORWARD), 0);
}
