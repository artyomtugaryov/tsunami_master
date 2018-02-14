#include <TMlib/TMException.h>
#include <TMlib/TMScheme24.h>
#include <TMlib/TMFocus.h>
#include <memory>
#include <gtest/gtest.h>

using namespace testing;

typedef std::shared_ptr<TM::Scheme::TMScheme24> Scheme24_ptr;
typedef std::shared_ptr<TM::Map::MapAreaWorker> MapAreaWorker_ptr;

class TMScheme24Tests : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        char *bPath = getenv("BAT_PATH");
        if (bPath == nullptr)
            throw std::runtime_error("FILE with bathymetry not found");
        m_scheme = std::make_shared<TM::Scheme::TMScheme24>();
        m_area = std::make_shared<TM::Map::MapAreaWorker>(bPath);
    }

    static Scheme24_ptr m_scheme;
    static MapAreaWorker_ptr m_area;
};

Scheme24_ptr TMScheme24Tests::m_scheme;
MapAreaWorker_ptr TMScheme24Tests::m_area;

TEST_F(TMScheme24Tests, configure) {
    try {
        char *fPath = getenv("FOCUS_PATH");
        if (fPath == nullptr)
            throw std::runtime_error("FILE with focus not found");
        std::shared_ptr<TM::TMFocus> focus = std::make_shared<TM::TMFocus>(fPath);
        m_scheme->configure(m_area, focus, -5);
    } catch (TM::details::TMException &ex) {
        std::cout << ex.what() << std::endl;
    }
}

TEST_F(TMScheme24Tests, calculation) {
    try {
        m_scheme->calculation(m_area, 10000000);
    } catch (TM::details::TMException &ex) {
        std::cout << ex.what() << std::endl;
    }
}