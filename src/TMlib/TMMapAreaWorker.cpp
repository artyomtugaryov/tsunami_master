#include "TMlib/TMMapAreaWorker.h"
#include <TMlib/TMException.h>
#include <fstream>
#include <algorithm>

void TM::Map::MapAreaWorker::readBathymetryFromFileDat() {
    std::vector<double> longitude; // y
    std::vector<double> latitude;  // x
    std::vector<double> depth;
    std::fstream infile(m_bathymetryPath.c_str(), std::ios_base::in);
    if (!infile.is_open()) {
        THROW_TM_EXCEPTION << "File with bathymetry did not open\n";
    }

    double minX(0);
    double maxX(0);
    double minY(0);
    double maxY(0);
    double datX(0); // latitude
    double datY(0); // longitude
    double datZ(0); // depth
    while (!infile.eof()) {
        infile >> datX >> datY >> datZ;
        latitude.push_back(datX);
        longitude.push_back(datY);
        depth.push_back(datZ);
    }

    infile.close();

    if (latitude.empty() || longitude.empty() || depth.empty()) {
        THROW_TM_EXCEPTION << "Error of reading bathymetry file\n";
    }

    std::vector<double> lat_uniq(latitude), long_uniq(longitude);
    std::sort(lat_uniq.begin(), lat_uniq.end());
    std::sort(long_uniq.begin(), long_uniq.end());
    std::size_t sizeX = static_cast<std::size_t>(std::unique(lat_uniq.begin(), lat_uniq.end()) - lat_uniq.begin());
    std::size_t sizeY = static_cast<std::size_t>(std::unique(long_uniq.begin(), long_uniq.end()) - long_uniq.begin());

    maxX = *std::max_element(latitude.begin(), latitude.end());
    maxY = *std::max_element(longitude.begin(), longitude.end());
    minX = *std::min_element(latitude.begin(), latitude.end());
    minY = *std::min_element(longitude.begin(), longitude.end());
    double stepX = (maxX - minX) / (sizeX - 1);
    double stepY = (maxY - minY) / (sizeY - 1);
    double startX = minX - stepX / 2.;
    double startY = minY - stepY / 2.;
    double endX = maxX + stepX / 2.;
    double endY = maxY + stepY / 2.;
    std::cout<< stepY << std::endl;
    m_bathymetry = std::make_shared<TM::Map::MapArea<double>>(sizeX, sizeY);

    m_bathymetry->setEndX(endX);
    m_bathymetry->setEndY(endY);
    m_bathymetry->setSizeX(sizeX);
    m_bathymetry->setSizeY(sizeY);
    m_bathymetry->setStartX(startX);
    m_bathymetry->setStartY(startY);
    m_bathymetry->setStepX(stepX);
    m_bathymetry->setStepY(stepY);

    for (int k = 0; k < (int) depth.size(); k++) {
        m_bathymetry->setDataByPoint(latitude[k], longitude[k], depth[k]);
    }
    //initMainArrays(size_y, size_x);
    //init_old_arrays();
    m_bathymetry->saveMapAreaToTextFile("testFile.mtx", 0);
}

bool TM::Map::MapAreaWorker::readBathymetryFromFile() {
    if (m_bathymetryPath.size() < 5) { //WHAT??? Why 5? -
                                       //*.dat, *.mtx, *.grd - all formats can not be less than 5 characters
        if (m_bathymetryPath.empty()) {
            std::cerr << "Empty path.\n";
            return false;
        } else {
            std::cerr << "Incorrect path.";
            return false;
        }
        return false;
    }
    if (m_bathymetryPath.substr(m_bathymetryPath.size() - 4, 4) == ".dat") {
        readBathymetryFromFileDat();
        return true;
    } else {
        std::cerr << "No supported format\n";
        return false;
    }
}

bool TM::Map::MapAreaWorker::setBathymetryPath(const std::string& path, bool readFromFile) {
    m_bathymetryPath = path;
    if (readFromFile) {
        return readBathymetryFromFile();
    }
    return false;
}

std::shared_ptr<TM::Map::MapArea<double> > TM::Map::MapAreaWorker::bathymetry()
{
    return m_bathymetry;
}

