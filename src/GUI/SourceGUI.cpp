#include "SourceGUI.h"


SourceGUI::SourceGUI(QObject *parent) :
    QObject(parent),
    m_tsunamiManager(new TsunamiManagerInfo::TsunamiManager())
{}

SourceGUI::~SourceGUI()
{

}

TsunamiManagerInfo::TsunamiManager *SourceGUI::tsunamiManager() const
{
    return m_tsunamiManager;
}
