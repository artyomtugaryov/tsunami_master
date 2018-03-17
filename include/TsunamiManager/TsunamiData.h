#ifndef TSUNAMIDATA_H
#define TSUNAMIDATA_H

#include "TsunamiPlotData.h"

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
    Q_PROPERTY(QString mareographsSavePath READ mareographsSavePath
               WRITE setMareographsSavePath NOTIFY mareographsSavePathChanged)
    Q_PROPERTY(QString mareographsPath READ mareographsPath
               WRITE setMareographsPath NOTIFY mareographsPathChanged)

    Q_PROPERTY(double isobath READ isobath
               WRITE setIsobath NOTIFY isobathChanged)
    Q_PROPERTY(int timeUpdate READ timeUpdate
               WRITE setTimeUpdate NOTIFY timeUpdateChanged)
    Q_PROPERTY(int mareographsTimeUpdate READ mareographsTimeUpdate
               WRITE setMareographsTimeUpdate NOTIFY mareographsTimeUpdateChanged)
    Q_PROPERTY(int calculationTime READ calculationTime
               WRITE setCalculationTime NOTIFY calculationTimeChanged)

    Q_PROPERTY(bool plotReady READ plotReady
               WRITE setPlotReady NOTIFY plotReadyChanged)
    Q_PROPERTY(bool mareographsUpdating READ mareographsUpdating
               WRITE setMareographsUpdating NOTIFY mareographsUpdatingChanged)

    Q_PROPERTY(bool readed READ readed NOTIFY readedChanged)

    Q_PROPERTY(TsunamiPlotData *plotData READ plotData CONSTANT)

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

    bool readed() const;

    void setReaded(bool readed);

    TsunamiPlotData * plotData() const;

    double isobath() const;

    int timeUpdate() const;

    int mareographsTimeUpdate() const;

    int calculationTime() const;

    bool plotReady() const;

    QString mareographsSavePath() const;

    QString mareographsPath() const;

    bool mareographsUpdating() const;

public slots:
    void setImageSavePath(QString imageSavePath);
    void setMaxDistributionSavePath(QString maxDistributionSavePath);

    void setIsobath(double isobath);

    void setTimeUpdate(int timeUpdate);

    void setMareographsTimeUpdate(int mareographsTimeUpdate);

    void setCalculationTime(int calculationTime);

    void setPlotReady(bool plotReady);

    void setMareographsSavePath(QString mareographsSavePath);

    void setMareographsPath(QString mareographsPath);

    void setMareographsUpdating(bool mareographsUpdating);

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

    void readedChanged();

    void isobathChanged(double isobath);

    void timeUpdateChanged(int timeUpdate);

    void mareographsTimeUpdateChanged(int mareographsTimeUpdate);

    void calculationTimeChanged(int calculationTime);
    void plotReadyChanged(bool plotReady);

    void mareographsSavePathChanged(QString mareographsSavePath);

    void mareographsPathChanged(QString mareographsPath);

    void mareographsUpdatingChanged(bool mareographsUpdating);

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

    bool m_readed;
    double m_isobath;
    int m_timeUpdate;
    int m_mareographsTimeUpdate;
    int m_calculationTime;
    bool m_plotReady;
    TsunamiPlotData *m_plotData;
    QString m_mareographsSavePath;
    QString m_mareographsPath;
    bool m_mareographsUpdating;
};
}
#endif // TSUNAMIDATA_H
