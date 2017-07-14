#ifndef MAPDATA_H
#define MAPDATA_H

#include <QObject>

class MapData : public QObject
{

    Q_OBJECT

    Q_PROPERTY(uint sizeX READ sizeX NOTIFY sizeXChanged)
    Q_PROPERTY(uint sizeY READ sizeY NOTIFY sizeYChanged)

    Q_PROPERTY(double startX READ startX NOTIFY startXChanged)
    Q_PROPERTY(double startY READ startY NOTIFY startYChanged)

    Q_PROPERTY(double endX READ endX NOTIFY endXChanged)
    Q_PROPERTY(double endY READ endY NOTIFY endYChanged)

    Q_PROPERTY(double deltaX READ deltaX NOTIFY deltaXChanged)
    Q_PROPERTY(double deltaY READ deltaY NOTIFY deltaYChanged)
public:
    MapData(QObject *parent = 0);
    ~MapData();

    uint sizeX() const;
    uint sizeY() const;

    double startX() const;
    double startY() const;

    double endX() const;
    double endY() const;

    double deltaX() const;
    double deltaY() const;

    void setSizeX(uint size);
    void setSizeY(uint size);

    void setStartX(double start);
    void setStartY(double start);

    void setEndX(double end);
    void setEndY(double end);

    void setDeltaX(double delta);
    void setDeltaY(double delta);

signals:
    void sizeXChanged(uint sizeX);
    void sizeYChanged(uint sizeY);

    void startXChanged(double startX);
    void startYChanged(double startY);

    void endXChanged(double endX);
    void endYChanged(double endY);

    void deltaXChanged(double deltaX);
    void deltaYChanged(double deltaY);
private:

    uint m_sizeX;
    uint m_sizeY;

    double m_startX;
    double m_startY;

    double m_endX;
    double m_endY;

    double m_deltaX;
    double m_deltaY;
};

#endif // MAPDATA_H
