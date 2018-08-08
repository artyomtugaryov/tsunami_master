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

        enum types_cells {
            LAND = 0,
            WATER = 1,
            BOUNDARY1 = 2,  //near land
            BOUNDARY2 = 3   //end of grid
        };

        template<typename DataType>
        class MapArea {
        public:


            explicit MapArea(const size_t &sizeX = 0,
                             const size_t &sizeY = 0,
                             const DataType &defaultValue = static_cast<DataType>(0));

            MapArea(const MapArea<DataType> &other);

            template<typename T>
            explicit MapArea(const MapArea<T> &other);

            template<typename T>
            MapArea<DataType>& operator=(const MapArea<T> &other);

            MapArea<DataType>& operator=(const MapArea<DataType> &other);

            std::size_t getIndex(const std::size_t &x, const std::size_t &y) const;

            std::size_t getIndexByPoint(double lat, double lon) const;

            std::size_t getIndexXByPoint(double lon) const;

            std::size_t getIndexYByPoint(double lat) const;


            const size_t &sizeX() const noexcept;

            const size_t &sizeY() const noexcept;

            const double &stepX() const noexcept;

            double stepY() const noexcept;

            double startX() const noexcept;

            double startY() const noexcept;

            double endX() const noexcept;

            double endY() const noexcept;

            const DataType getDataByIndex(const std::size_t &x, const std::size_t &y) const;

            DataType getDataByPoint(double longitude, double latitude) const;

            void setSizeX(std::size_t sizeX);

            void setSizeY(std::size_t sizeY);

            void setStepX(double stepX);

            void setStepY(double stepY);

            void setStartX(double startX);

            void setStartY(double startY);

            void setEndX(double endX);

            void setEndY(double endY);

            void setDataByIndex(const std::size_t &x, const std::size_t &y, const DataType &value);

            void setDataByPoint(double longitude, double latitude, DataType value);

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
#endif // MAPAREA_H
