#ifndef MAPAREAWORKER_H
#define MAPAREAWORKER_H

#include "TMlib/TMMapArea.h"
#include "TMlib/TMMareograph.h"
#include "TMlib/TMFocus.h"

#include <iostream>
#include <memory>


namespace TM {
    namespace Map {

        class MapAreaWorker {

        public:

            MapAreaWorker() = default;

            explicit MapAreaWorker(const std::string &);


            const MapArea<double> &bathymetry() const noexcept;

            const MapArea<double> &eta() const noexcept;

            MapArea<double> &uVelocity() noexcept;

            MapArea<double> &vVelocity() noexcept;

            const types_cells typeOfCell(const size_t &i, const size_t &j) const;

            const Focus::Focus &focus() noexcept;


            const size_t &getMaxXIndex() const;

            const size_t &getMaxYIndex() const;

            bool readBathymetryFromFile();

            bool setBathymetryPath(const std::string &path, bool readFromFile = false);

            void conigure(const double & izobata);

            void setEta(const MapArea<double> &newEta) noexcept;

            void setBathymetry(const MapArea<double> &newBathymetry) noexcept;

            void setU(const MapArea<double> &newU) noexcept;

            void setV(const MapArea<double> &newV) noexcept;


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

            void setTypesOfCells(const double &izobata = -5);

        private:
            void readBathymetryFromFileDat();

        private:

            MapArea<double> m_bathymetry;
            MapArea<double> m_eta;
            MapArea<double> m_uVelocity;
            MapArea<double> m_vVelocity;

            MapArea <types_cells> m_types_cells;

            Focus::Focus m_focus;

            std::vector<Mareograph> m_mareographs;
            //TODO: RENDER TO A SEPARATOR FILE
            std::string m_bathymetryPath;
            std::string m_mareographsPath;
            int m_mareographStepTime;
            bool m_mareographsUpdating;
        };
    }
}
#endif // MAPAREAWORKER_H
