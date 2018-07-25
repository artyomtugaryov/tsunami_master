#include <gtest/gtest.h>
#include <TMlib/TMOperators.hpp>
#include <TMlib/TMMapArea.h>
#include <memory>

using namespace TM::Map;
using namespace TM::Scheme::Operators;

class TMOperatorsTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        TMOperatorsTests::m_maparea = std::make_shared<MapArea<double>>(2, 2);
        m_maparea->setDataByIndex(0, 0, 10);
        m_maparea->setDataByIndex(1, 0, 20);
        m_maparea->setDataByIndex(0, 1, 30);
        m_maparea->setDataByIndex(1, 1, 40);
    }

    static std::shared_ptr<MapArea<double>> m_maparea;
};

std::shared_ptr<MapArea<double>> TMOperatorsTests::m_maparea;

/*
 * TESTS FOR OPERATOR T
 */
TEST_F(TMOperatorsTests, operatorTForwardX) {
    EXPECT_EQ(T(m_maparea, 0, 0, direction::X_FORWARD), 20);
}

TEST_F(TMOperatorsTests, operatorTForwardY) {
    EXPECT_EQ(T(m_maparea, 1, 0, direction::Y_FORWARD), 40);
}

TEST_F(TMOperatorsTests, operatorTBackwarddX) {
    EXPECT_EQ(T(m_maparea, 1, 1, direction::X_BACKWARD), 30);
}

TEST_F(TMOperatorsTests, operatorTBackwardY) {
    EXPECT_EQ(T(m_maparea, 1, 1, direction::Y_BACKWARD), 20);
}

TEST_F(TMOperatorsTests, operatorTException) {
    ASSERT_THROW(T(m_maparea, 1, 1, static_cast<direction>(5)), TM::details::TMException);
}

/*
 * TESTS FOR OPERATOR DELTA
 */
TEST_F(TMOperatorsTests, operatorDeltaForwardX) {
    EXPECT_EQ(delta(m_maparea, 0, 0, direction::X_FORWARD), 10);
}

TEST_F(TMOperatorsTests, operatorDeltaForwardY) {
    EXPECT_EQ(delta(m_maparea, 1, 0, direction::Y_FORWARD), 20);
}

TEST_F(TMOperatorsTests, operatorDeltaBackwarddX) {
    EXPECT_EQ(delta(m_maparea, 1, 1, direction::X_BACKWARD), 10);
}

TEST_F(TMOperatorsTests, operatorDeltaBackwardY) {
    EXPECT_EQ(delta(m_maparea, 1, 1, direction::Y_BACKWARD), 20);
}

TEST_F(TMOperatorsTests, operatorDeltaException) {
    ASSERT_THROW(delta(m_maparea, 1, 1, static_cast<direction>(5)), TM::details::TMException);
}


/*
 * TESTS FOR OPERATOR FEATURE
 */
TEST_F(TMOperatorsTests, operatorFeatureForwardX) {
    EXPECT_EQ(feature(m_maparea, 0, 0, direction::X_FORWARD), 15);
}

TEST_F(TMOperatorsTests, operatorFeatureForwardY) {
    EXPECT_EQ(feature(m_maparea, 1, 0, direction::Y_FORWARD), 30);
}

TEST_F(TMOperatorsTests, operatorFeatureBackwarddX) {
    ASSERT_THROW(feature(m_maparea, 1, 1, direction::X_BACKWARD), TM::details::TMException);
}

TEST_F(TMOperatorsTests, operatorFeatureBackwardY) {
    ASSERT_THROW(feature(m_maparea, 1, 1, direction::Y_BACKWARD), TM::details::TMException);
}

TEST_F(TMOperatorsTests, operatorFeatureException) {
    ASSERT_THROW(feature(m_maparea, 1, 1, static_cast<direction>(5)), TM::details::TMException);
}