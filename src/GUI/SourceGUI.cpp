#include "SourceGUI.h"


SourceGUI::SourceGUI(QObject *parent) :
    QObject(parent),
    m_tsunamiManager(new TsunamiManagerInfo::TsunamiManager())
{
    m_tsunamiManagerThread = new QThread;
    m_tsunamiManager->moveToThread(m_tsunamiManagerThread);
    //connect(this, SIGNAL(readBathymetryFromFile()),
    //        m_tsunamiManager, SLOT(readBathymetryFromFile()), Qt::DirectConnection);
   // connect(m_tsunamiManagerThread, SIGNAL(started()),
   //         this, SLOT(initTsunamiMaster()));
    connect(m_tsunamiManagerThread, SIGNAL(started()),
            m_tsunamiManager, SLOT(readBathymetryFromFile()));

    m_tsunamiManagerThread->start();
}

SourceGUI::~SourceGUI()
{

}

TsunamiManagerInfo::TsunamiManager *SourceGUI::TsunamiManager() const
{
    return m_tsunamiManager;
}

void SourceGUI::initTsunamiMaster()
{
    m_tsunamiManager = new TsunamiManagerInfo::TsunamiManager();
    m_tsunamiManager->readBathymetryFromFile();
}
