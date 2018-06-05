#ifndef RECTANGLEMAPAREA_H
#define RECTANGLEMAPAREA_H

#include "TMLib/TMMapArea.h"

#include <vector>
#include <memory>


namespace TM {
    namespace Map {
        template<typename DataType>
        class RectangleMapArea : public MapArea<DataType> {
        public:

            RectangleMapArea();

            RectangleMapArea(std::size_t sizeX, std::size_t sizeY, DataType defaultValue = static_cast<DataType>(0));

            template<typename T>
            explicit RectangleMapArea(const std::shared_ptr<const RectangleMapArea<T>> &other);

            std::size_t getIndex(const std::size_t &x, const std::size_t &y) const;

            std::size_t getIndexByPoint(double lat, double lon) const;

            std::size_t getIndexXByPoint(double lon) const;

            std::size_t getIndexYByPoint(double lat) const;

            std::size_t sizeLongitude() const noexcept;

            std::size_t sizeLatitude() const noexcept;

            double stepLongitude() const noexcept;

            double stepLatitude() const noexcept;

            double startLongitude() const noexcept;

            double startLatitude() const noexcept;

            double endLongitude() const noexcept;

            double endLatitude() const noexcept;

            DataType getDataByIndex(const std::size_t &x, const std::size_t &y) const;

            DataType getDataByPoint(const double &longitude, const double &latitude) const;

            void setSizeLongitude(std::size_t sizeX);

            void setSizeLatitude(std::size_t sizeY);

            void setStepLongitude(double stepX);

            void setStepLatitude(double stepY);

            void setStartLongitude(double startX);

            void setStartLatitude(double startY);

            void setEndLongitude(double endX);

            void setEndLatitude(double endY);

            void setDataByIndex(const std::size_t &x, const std::size_t &y, const DataType &value);

            void setDataByPoint(const double &longitude, const double &latitude, const DataType &value);

            const DataType getMinValue() const;

            const DataType getMaxValue() const;

            void saveAsTextFile(std::string path, int setprecision) const;

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
#endif // RECTANGLEMAPAREA_H
