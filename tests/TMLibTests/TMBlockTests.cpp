#include <gtest/gtest.h>
#include <TMlib/TMBlock.h>
#include <memory>

class TMBlockTests : public ::testing::Test {
protected:

    static std::shared_ptr<TM::Focus::Block> m_block;

};

std::shared_ptr<TM::Focus::Block> TMBlockTests ::m_block;

TEST_F(TMBlockTests, Constructor) {
//    m_block = std::make_shared<TM::Focus::BrickPoint>();
//    EXPECT_EQ(m_brickpoint_first->x(), 0);
//    EXPECT_EQ(m_brickpoint_first->y(), 0);
}
