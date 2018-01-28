#include "ApplicationGUI.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QQuickImageProvider>
#include <TsunamiManager/TsunamiPlotProvider.h>

ApplicationGUI::ApplicationGUI(int &argc, char **argv) :
    QGuiApplication(argc, argv),
    m_sourceGUI(new SourceGUI(this))
{
    m_view = new QQuickView;
    m_view->engine()->addImageProvider(QLatin1String("plot"), m_sourceGUI->tsunamiManager()->plotProvider());
    m_view->rootContext()->setContextProperty("_sourceGUI", m_sourceGUI);
    m_view->setSource(QUrl(QLatin1String("qrc:/Resources/Main.qml")));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);

    connect(m_sourceGUI->tsunamiManager(), SIGNAL(imageUpdate()),(QObject *)m_view->rootObject(),SLOT(onImageUpdate()));
    //TODO: remake
    // ************************* //
    QRect rect = m_view->screen()->availableGeometry();
    QSize screenSize(rect.width(), rect.height()-35);

    m_view->resize(screenSize);
    // ************************* //
    m_view->setMaximumSize(screenSize);
    m_view->setMinimumSize(screenSize);
    setPositionByCenter();
    m_view->show();


}

ApplicationGUI::~ApplicationGUI()
{
    delete m_view;
}

void ApplicationGUI::setPositionByCenter()
{
    QRect rect = m_view->screen()->geometry();
    QPoint center(rect.width() / 2, (rect.height()- 15) / 2);
    QSize sizeView = m_view->size();
    QPoint position(center.x() - sizeView.width() / 2,
                    center.y() - sizeView.height() /2);
    m_view->setPosition(position);
}
