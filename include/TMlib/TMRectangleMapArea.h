#ifndef TMRECTANGLEMAPAREA_H
#define TMRECTANGLEMAPAREA_H

#include "TMLib/TMMapArea.h"
#include "TMLib/TMRectangleCoordinateIterator.h"

#include <vector>
#include <memory>

using namespace TM::Map;

namespace TM {
    namespace Map {
        template<typename DataType>
        class RectangleMapArea : public MapArea<DataType> {
        public:
            explicit RectangleMapArea(std::size_t sizeX = 0, std::size_t sizeY = 0,
                                      DataType defaultValue = static_cast<DataType>(0));

            template<typename OtherDataType>
            explicit RectangleMapArea(const std::shared_ptr<const RectangleMapArea<OtherDataType>> &other);


            double minLongitude() const noexcept;

            double minLatitude() const noexcept;

            double maxLongitude() const noexcept;

            double maxLatitude() const noexcept;

            double stepLongitude() const noexcept;

            double stepLatitude() const noexcept;

            std::size_t sizeLongitude() const noexcept;

            std::size_t sizeLatitude() const noexcept;


            DataType getDataByIndex(const std::size_t &x, const std::size_t &y) const;

            DataType getDataByPoint(const double &longitude, const double &latitude) const;


            void setDataByIndex(const std::size_t &x, const std::size_t &y, const DataType &value);

            void setDataByPoint(const double &longitude, const double &latitude, const DataType &value);


            void setSizeLongitude(const std::size_t &sizeX);

            void setSizeLatitude(const std::size_t &sizeY);

            void setMinLongitude(double startX);

            void setMintLatitude(double startY);

            void setMaxLongitude(double endX);

            void setMaxLatitude(double endY);

            const DataType getMinValue() const override;

            const DataType getMaxValue() const override;

            void saveAsTextFile(std::string path, int precision = 3) const;

            using RectangleCoordinateIterator<DataType> iterator;

            using ptr_iterator=std::unique_ptr<RectangleCoordinateIterator<DataType>>;

            MapArea<DataType>::ptr_iterator beginLongitude(); // X

        protected:

            std::size_t getIndex(const std::size_t &x, const std::size_t &y) const;

            std::size_t getIndexByPoint(double lat, double lon) const;

            std::size_t getIndexXByPoint(double lon) const;

            std::size_t getIndexYByPoint(double lat) const;

            double calcStepByCoordinate(const double &minCoordinate, const double &maxCoordinate,
                                        const std::size_t &size) const;

        private:
            std::size_t m_sizeX;
            std::size_t m_sizeY;

            double m_startX;
            double m_startY;
            double m_endX;
            double m_endY;
            double m_stepX;
            double m_stepY;

            std::vector<DataType> m_data;
        };
    }
}
#endif // TMRECTANGLEMAPAREA_H
