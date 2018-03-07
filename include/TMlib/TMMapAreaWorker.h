#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include <iostream>
#include <memory>
#include "TMMapArea.h"

namespace TM {
    namespace Map {
        class MapAreaWorker {
        public:
            MapAreaWorker() = default;

            MapAreaWorker(size_t x, size_t y); //TODO: Is it really needs?

            MapAreaWorker(const std::string &);

            size_t getMaxXIndex() const;

            size_t getMaxYIndex() const;

            bool readBathymetryFromFile(); // TODO: Join readBathymetryFromFile with setBathymetryPath

            bool setBathymetryPath(const std::string &path, bool readFromFile = false);

            const std::shared_ptr<const TM::Map::MapArea<double>> bathymetry() const noexcept;

            const std::shared_ptr<TM::Map::MapArea<double>> eta() noexcept;

            const std::shared_ptr<const TM::Map::MapArea<double>> eta() const noexcept;

            void setEta(std::shared_ptr<TM::Map::MapArea<double>> newEta) noexcept ;

            const std::shared_ptr<TM::Map::MapArea<double>> uVelocity() noexcept;

            const std::shared_ptr<TM::Map::MapArea<double>> vVelocity() noexcept;

            double getLatitudeByIndex(const double i) const noexcept;

            double getLongitudeByIndex(const double i) const noexcept;

            double getStepX() const noexcept;

            double getStepY() const noexcept;

            double getStepPhi() const noexcept;

            double getStepTetta() const noexcept;

            double getMaxDepth() const noexcept;

        private:
            std::shared_ptr<MapArea<double>> m_eta;
            std::shared_ptr<MapArea<double>> m_uVelocity;
            std::shared_ptr<MapArea<double>> m_vVelocity;
            std::shared_ptr<MapArea<double>> m_max;
            std::shared_ptr<MapArea<double>> m_min;
            std::shared_ptr<MapArea<double>> m_bathymetry;
            //TODO: RENDER TO A SEPARATOR FILE
            std::string m_bathymetryPath;

            void readBathymetryFromFileDat();
        };
    }
}
#endif // MAPAREAWORKER_H
