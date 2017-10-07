#include "SourceGUI.h"


SourceGUI::SourceGUI(QObject *parent) :
    QObject(parent),
    m_tsunamiManager(new TsunamiManagerInfo::TsunamiManager())
{
    m_tsunamiManagerThread = new QThread;
    m_tsunamiManager->moveToThread(m_tsunamiManagerThread);
    connect(m_tsunamiManagerThread, SIGNAL(started()),
            m_tsunamiManager, SLOT(readBathymetryFromFile()));
}

SourceGUI::~SourceGUI()
{

}

TsunamiManagerInfo::TsunamiManager *SourceGUI::TsunamiManager() const
{
    return m_tsunamiManager;
}

void SourceGUI::startReadFromFile(const QString &path)
{
    m_tsunamiManager->setPath(path);
    m_tsunamiManagerThread->start();
}
