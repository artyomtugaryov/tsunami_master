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

            const MapArea<double> bathymetry() const noexcept;

            const MapArea<double> eta() const noexcept;

            void setEta(const MapArea<double> &newEta) noexcept;

            void setBathymetry(const MapArea<double> &newBathymetry) noexcept;

            void setU(const MapArea<double> &newU) noexcept;

            void setV(const MapArea<double> &newV) noexcept;

            const MapArea<double> uVelocity() const noexcept;

            const MapArea<double> vVelocity() const noexcept;

            double getLatitudeByIndex(const std::size_t &i) const noexcept;

            double getLongitudeByIndex(const std::size_t &i) const noexcept;

            double getStepX() const noexcept;

            double getStepY() const noexcept;

            double getStepPhi() const noexcept;

            double getStepTetta() const noexcept;

            double getMaxDepth() const noexcept;

            const std::vector<Mareograph> mareoghraphs() const;

            std::string mareographsPath() const;

            void setMareographsPath(const std::string &mareographsPath);

            int mareographStepTime() const;

            void setMareographStepTime(int mareographStepTime);

            void readMareographsFromFile(const std::string &mareographsPath);

            void saveMareographs(std::string path = "");

            void checkMareographs(const MapArea<double> &eta);

            bool mareographsUpdating() const noexcept;

            void setMareographsUpdating(bool mareographsUpdating) noexcept;

            void setMareoghraphs(const std::vector<Mareograph> &mareoghraphs);

        private:
            MapArea<double> m_eta;
            MapArea<double> m_uVelocity;
            MapArea<double> m_vVelocity;
            MapArea<double> m_max;
            MapArea<double> m_min;
            MapArea<double> m_bathymetry;
            std::vector<Mareograph> m_mareographs;

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
