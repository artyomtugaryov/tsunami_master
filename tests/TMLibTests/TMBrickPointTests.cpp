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
    static std::shared_ptr<TM::Focus::BrickPoint> m_brickpoint_fourth;

};

std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_first;
std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_second;
std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_third;
std::shared_ptr<TM::Focus::BrickPoint> TMBrickPointTests::m_brickpoint_fourth;
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

TEST_F(TMBrickPointTests, LeftRotate) {
    /*
     *  ^
     *  |
     *  | C*
     *  |
     *  |
     *  | A*----->*B
     *  |---------------->
     *
     */

    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(0, 0);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(1, 0);
    m_brickpoint_third = std::make_shared<TM::Focus::BrickPoint>(1, 1);
    EXPECT_EQ(TM::Focus::BrickPoint::rotate(*m_brickpoint_first, *m_brickpoint_second, *m_brickpoint_third), 1);
}

TEST_F(TMBrickPointTests, RightRotate) {
    /*
     *  ^
     *  |
     *  | A*----->*B
     *  |
     *  |
     *  |  *C
     *  |---------------->
     *
     */
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(0, 0);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(1, 0);
    m_brickpoint_third = std::make_shared<TM::Focus::BrickPoint>(1, -1);
    EXPECT_EQ(TM::Focus::BrickPoint::rotate(*m_brickpoint_first, *m_brickpoint_second, *m_brickpoint_third), -1);
}

TEST_F(TMBrickPointTests, NoRotate) {
    /*
     *  ^
     *  |
     *  | A*----->*B   *C
     *  |---------------->
     *
     */
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(0, 0);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(1, 0);
    m_brickpoint_third = std::make_shared<TM::Focus::BrickPoint>(21, 0);
    EXPECT_EQ(TM::Focus::BrickPoint::rotate(*m_brickpoint_first, *m_brickpoint_second, *m_brickpoint_third), 0);
}

TEST_F(TMBrickPointTests, IncreeseReturnTrue) {
    /*
     *  ^
     *  |    *C
     *  |    |
     *  | A*----->*B
     *  |    |
     *  |    *D
     *  |---------------->
     *
     */
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(0, 0);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(3, 3);
    m_brickpoint_third = std::make_shared<TM::Focus::BrickPoint>(0, 1);
    m_brickpoint_fourth = std::make_shared<TM::Focus::BrickPoint>(3, 0);
    EXPECT_TRUE(TM::Focus::BrickPoint::intersect(*m_brickpoint_first,
                                                 *m_brickpoint_second,
                                                 *m_brickpoint_third,
                                                 *m_brickpoint_fourth));
}

TEST_F(TMBrickPointTests, IncreeseReturnFalse) {
    /*
     *  ^
     *  |    *C
     *  |    |
     *  |    |
     *  |    *D
     *  | A*----->*B
     *  |---------------->
     *
     */
    m_brickpoint_first = std::make_shared<TM::Focus::BrickPoint>(0, 0);
    m_brickpoint_second = std::make_shared<TM::Focus::BrickPoint>(3, 0);
    m_brickpoint_third = std::make_shared<TM::Focus::BrickPoint>(2, 6);
    m_brickpoint_fourth = std::make_shared<TM::Focus::BrickPoint>(2, 1);
    EXPECT_FALSE(TM::Focus::BrickPoint::intersect(*m_brickpoint_first,
                                                 *m_brickpoint_second,
                                                 *m_brickpoint_third,
                                                 *m_brickpoint_fourth));
}