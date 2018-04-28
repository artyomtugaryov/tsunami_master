#include <TMlib/TMException.h>
#include <TMlib/TMKolchScheme.h>
#include <TMlib/TMFocus.h>
#include <TMlib/TMSignal.h>
#include <memory>
#include <gtest/gtest.h>

using namespace testing;

class TMKolchSchemeTests : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        char *bPath = getenv("BAT_PATH");
        if (bPath == nullptr)
            throw std::runtime_error("FILE with bathymetry not found");
        m_scheme = std::make_shared<TM::Scheme::TMKolchSchema>();
        m_area = std::make_shared<TM::Map::MapAreaWorker>(bPath);
        m_sender = std::make_shared<TM::TMTimeManager>();
        m_signal = std::make_shared<TM::TMSignal>();
    }

    static std::shared_ptr<TM::Scheme::TMKolchSchema>  m_scheme;
    static std::shared_ptr<TM::Map::MapAreaWorker> m_area;
    static std::shared_ptr<TM::TMTimeManager> m_sender;
    static std::shared_ptr<TM::TMSignal> m_signal;
};

std::shared_ptr<TM::Scheme::TMKolchSchema> TMKolchSchemeTests::m_scheme;
std::shared_ptr<TM::Map::MapAreaWorker> TMKolchSchemeTests::m_area;
std::shared_ptr<TM::TMTimeManager> TMKolchSchemeTests::m_sender;
std::shared_ptr<TM::TMSignal> TMKolchSchemeTests::m_signal;

TEST_F(TMKolchSchemeTests, configure) {
    try {
        char *fPath = getenv("FOCUS_PATH");
        if (fPath == nullptr)
            throw std::runtime_error("FILE with focus not found");
        std::shared_ptr<TM::Focus::Focus> focus = std::make_shared<TM::Focus::Focus>(fPath);
        m_scheme->configure(m_area, focus, -5, m_sender, m_signal);
    } catch (TM::details::TMException &ex) {
        std::cout << ex.what() << std::endl;
    }
}

TEST_F(TMKolchSchemeTests, calculation) {
    try {
        m_sender->updateSendingTimeStep(5.);
        m_scheme->calculation(m_area, 10000);
    } catch (TM::details::TMException &ex) {
        std::cout << ex.what() << std::endl;
    }
}