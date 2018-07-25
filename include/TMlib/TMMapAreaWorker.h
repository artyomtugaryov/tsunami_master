#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include <iostream>
#include <memory>
#include "TMlib/TMMapArea.h"
#include "TMlib/TMMareograph.h"

namespace TM {
    namespace Map {
        class MapAreaWorker {
        public:
            MapAreaWorker() = default;

            explicit MapAreaWorker(const std::string &);

            size_t getMaxXIndex() const;

            size_t getMaxYIndex() const;

            bool readBathymetryFromFile(); // TODO: Join readBathymetryFromFile with setBathymetryPath

            bool setBathymetryPath(const std::string &path, bool readFromFile = false);

            const std::shared_ptr<TM::Map::MapArea<double>> bathymetry() const noexcept;

            const std::shared_ptr<const TM::Map::MapArea<double>> eta() const noexcept;

            void setEta(std::shared_ptr<TM::Map::MapArea<double>> &newEta) noexcept;

            void setU(std::shared_ptr<TM::Map::MapArea<double>> &newU) noexcept;

            void setV(std::shared_ptr<TM::Map::MapArea<double>> &newV) noexcept;

            const std::shared_ptr<TM::Map::MapArea<double>> uVelocity() const noexcept;

            const std::shared_ptr<TM::Map::MapArea<double>> vVelocity() const noexcept;

            double getLatitudeByIndex(const std::size_t &i) const noexcept;

            double getLongitudeByIndex(const std::size_t &i) const noexcept;

            double getStepX() const noexcept;

            double getStepY() const noexcept;

            double getStepPhi() const noexcept;

            double getStepTetta() const noexcept;

            double getMaxDepth() const noexcept;

            std::shared_ptr<std::vector<Mareograph>> mareoghraphs() const;

            std::string mareographsPath() const;

            void setMareographsPath(const std::string &mareographsPath);

            int mareographStepTime() const;

            void setMareographStepTime(int mareographStepTime);

            void readMareographsFromFile(const std::string &mareographsPath);

            void saveMareographs(std::string path = "");

            void checkMareographs(const std::shared_ptr<const MapArea<double>> &eta);

            bool mareographsUpdating() const noexcept;

            void setMareographsUpdating(bool mareographsUpdating) noexcept;

            void setMareoghraphs(const std::shared_ptr<std::vector<Mareograph>> &mareoghraphs);

        private:
            std::shared_ptr<MapArea<double>> m_eta;
            std::shared_ptr<MapArea<double>> m_uVelocity;
            std::shared_ptr<MapArea<double>> m_vVelocity;
            std::shared_ptr<MapArea<double>> m_max;
            std::shared_ptr<MapArea<double>> m_min;
            std::shared_ptr<MapArea<double>> m_bathymetry;
            std::shared_ptr<std::vector<Mareograph>> m_mareographs;

            //TODO: RENDER TO A SEPARATOR FILE
            std::string m_bathymetryPath;
            std::string m_mareographsPath;
            int m_mareographStepTime;
            bool m_mareographsUpdating;

            void readBathymetryFromFileDat();
        };
    }
}
#endif // MAPAREAWORKER_H
