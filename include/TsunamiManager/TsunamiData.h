#ifndef TSUNAMIDATA_H
#define TSUNAMIDATA_H

#include <QObject>

namespace TsunamiManagerInfo {
class TsunamiData : public QObject
{

    Q_OBJECT

    Q_PROPERTY(uint sizeX READ sizeX NOTIFY sizeXChanged)
    Q_PROPERTY(uint sizeY READ sizeY NOTIFY sizeYChanged)

    Q_PROPERTY(double startX READ startX NOTIFY startXChanged)
    Q_PROPERTY(double startY READ startY NOTIFY startYChanged)

    Q_PROPERTY(double endX READ endX NOTIFY endXChanged)
    Q_PROPERTY(double endY READ endY NOTIFY endYChanged)

    Q_PROPERTY(double stepX READ stepX NOTIFY stepXChanged)
    Q_PROPERTY(double stepY READ stepY NOTIFY stepYChanged)

    Q_PROPERTY(QString bathymetryPath READ bathymetryPath NOTIFY bathymetryPathChanged)
    Q_PROPERTY(QString brickPath READ brickPath NOTIFY brickPathChanged)
    Q_PROPERTY(QString imageSavePath READ imageSavePath
               WRITE setImageSavePath NOTIFY imageSavePathChanged)
    Q_PROPERTY(QString maxDistributionSavePath READ maxDistributionSavePath
               WRITE setMaxDistributionSavePath NOTIFY maxDistributionSavePathChanged)

public:
    TsunamiData(QObject *parent = 0);
    virtual ~TsunamiData();

    uint sizeX() const;
    uint sizeY() const;

    double startX() const;
    double startY() const;

    double endX() const;
    double endY() const;

    double stepX() const;
    double stepY() const;

    QString bathymetryPath() const;
    QString brickPath() const;
    QString imageSavePath() const;
    QString maxDistributionSavePath() const;

    void setSizeX(uint size);
    void setSizeY(uint size);

    void setStartX(double start);
    void setStartY(double start);

    void setEndX(double end);
    void setEndY(double end);

    void setStepX(double step);
    void setStepY(double step);

    void setBathymetryPath(const QString &bathymetryPath);
    void setBrickPath(const QString &brickPath);

public slots:
    void setImageSavePath(QString imageSavePath);
    void setMaxDistributionSavePath(QString maxDistributionSavePath);

signals:
    void sizeXChanged(uint sizeX);
    void sizeYChanged(uint sizeY);

    void startXChanged(double startX);
    void startYChanged(double startY);

    void endXChanged(double endX);
    void endYChanged(double endY);

    void stepXChanged(double stepX);
    void stepYChanged(double stepY);

    void bathymetryPathChanged();
    void brickPathChanged();
    void imageSavePathChanged();
    void maxDistributionSavePathChanged();

private:

    uint m_sizeX;
    uint m_sizeY;

    double m_startX;
    double m_startY;

    double m_endX;
    double m_endY;

    double m_stepX;
    double m_stepY;
    QString m_bathymetryPath;
    QString m_brickPath;
    QString m_imageSavePath;
    QString m_maxDistributionSavePath;
};
}
#endif // TSUNAMIDATA_H
