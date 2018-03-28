#ifndef MAPAREA_H
#define MAPAREA_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

//TODO: For test. Remove after all work with calculation part.
#include <QString>
//TODO END

namespace TM {
    namespace Map {
        template<typename DataType>
        class MapArea {
        public:

            MapArea() = default;

            MapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue = static_cast<DataType>(0));

            template<typename T>
            MapArea(const std::shared_ptr<const MapArea<T>> &other);

            std::size_t getIndex(const std::size_t &x, const std::size_t &y) const;

            std::size_t getIndexByPoint(double lat, double lon) const;

            std::size_t getIndexXByPoint(double lon) const;

            std::size_t getIndexYByPoint(double lat) const;

            std::size_t sizeX() const noexcept;

            std::size_t sizeY() const noexcept;

            double stepX() const noexcept;

            double stepY() const noexcept;

            double startX() const noexcept;

            double startY() const noexcept;

            double endX() const noexcept;

            double endY() const noexcept;

            DataType getDataByIndex(const std::size_t &x, const std::size_t &y) const;

            DataType getDataByPoint(double longitude, double latitude) const;

            void setSizeX(std::size_t sizeX);

            void setSizeY(std::size_t sizeY);

            void setStepX(double stepX);

            void setStepY(double stepY);

            void setStartX(double startX);

            void setStartY(double startY);

            void setEndX(double endX);

            void setEndY(double endY);

            void setDataByIndex(std::size_t &x, std::size_t &y, DataType value);

            void setDataByPoint(double longitude, double latitude, DataType value);

            const DataType getMinValue() const;

            const DataType getMaxValue() const;

            void saveAsTextFile(std::string path, int setprecision) const;

/*
 * Indexing operator
 * */
            class Operator {
            public:
                Operator(MapArea<DataType> *p, const std::size_t  &x) : m_x(x) { m_p = p; };

                DataType operator[](const std::size_t  &y) {
                    return m_p->getDataByIndex(m_x, y);
                }

            private:
                std::size_t m_x;
                MapArea<DataType> *m_p;
            };

            Operator operator[](const std::size_t  &x){
                return Operator(this, x);
            }

        private:
            std::size_t m_sizeX;
            std::size_t m_sizeY;
            double m_startX;
            double m_startY;
            double m_stepX;
            double m_stepY;
            double m_endX;
            double m_endY;
            std::vector<DataType> m_data;
        };
    }
}
#endif // MAPAREA_H
