#include <gtest/gtest.h>
#include <TMlib/TMBrickPoint.h>
#include <memory>

class TMBrickPointTests : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        TMBrickPointTests::x = 1.0;
        TMBrickPointTests::x = 2.0;
    }

    static double x;
    static double y;
    static std::shared_ptr<TM::Focus::BrickPoint> m_brickpoint_first;
    static std::shared_ptr<TM::Focus::BrickPoint> m_brickpoint_second;
    static std::shared_ptr<TM::Focus::BrickPoint> m_brickpoint_third;

};

std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_first;
std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_second;
std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_third;
double TMBrickPointTests::x;
double TMBrickPointTests::y;

TEST_F(TMBrickPointTests, EmptyConstructor) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>();
    EXPECT_EQ(m_brickpoint_first->x(), 0);
    EXPECT_EQ(m_brickpoint_first->y(), 0);
}

TEST_F(TMBrickPointTests, ConstructorWithParameters) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(x, y);
    EXPECT_EQ(m_brickpoint_first->x(), x);
    EXPECT_EQ(m_brickpoint_first->y(), y);
}

TEST_F(TMBrickPointTests, OperatorLESSRetunrFalseWithDifferentX) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(x+1, y);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(x, y-1);
    EXPECT_FALSE(m_brickpoint_first->operator<(*m_brickpoint_second.get()));
}

TEST_F(TMBrickPointTests, OperatorLESSRetunrFalseWithEqualstX) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(x, y);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(x, y-1);
    EXPECT_FALSE(m_brickpoint_first->operator<(*m_brickpoint_second.get()));
}

TEST_F(TMBrickPointTests, OperatorLESSRetunrTrue) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(x-1, y);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(x, y-1);
    EXPECT_TRUE(m_brickpoint_first->operator<(*m_brickpoint_second.get()));
}

TEST_F(TMBrickPointTests, rotate) {
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(x-1, y);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(x, y-1);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(x-1, y-1);
    std::cout<<TM::Focus::BrickPoint::rotate(*m_brickpoint_first, *m_brickpoint_second, *m_brickpoint_second)<<std::endl;
}

