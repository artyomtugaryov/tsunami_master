#include "TMlib/TMMapAreaWorker.h"
#include <TMlib/TMException.h>
#include <fstream>
#include <algorithm>
#include <ctime>

TM::Map::MapAreaWorker::MapAreaWorker(const std::string &path) {
    clock_t begin = clock();
    this->setBathymetryPath(path, true);
    clock_t end = clock();
    std::cout << "Reading bathymetry from file: "
              << double(end - begin) * 1000. / CLOCKS_PER_SEC
              << " ms."
              << std::endl;
    this->m_uVelocity = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
}

void TM::Map::MapAreaWorker::readBathymetryFromFileDat() {
    std::vector<double> longitude; // x
    std::vector<double> latitude;  // y
    std::vector<double> depth;
    std::fstream infile(m_bathymetryPath.c_str(), std::ios_base::in);
    if (!infile.is_open()) {
        THROW_TM_EXCEPTION << "File with bathymetry did not open\n";
    }

    double minX(0);
    double maxX(0);
    double minY(0);
    double maxY(0);
    double datX(0); // longitude
    double datY(0); // latitude
    double datZ(0); // depth
    while (!infile.eof()) {
        infile >> datX >> datY >> datZ;
        longitude.push_back(datX);
        latitude.push_back(datY);
        depth.push_back(datZ);
    }

    infile.close();

    if (latitude.empty() || longitude.empty() || depth.empty()) {
        THROW_TM_EXCEPTION << "Error of reading bathymetry file\n";
    }

    std::vector<double> long_uniq(longitude), lat_uniq(latitude);
    std::sort(lat_uniq.begin(), lat_uniq.end());
    std::sort(long_uniq.begin(), long_uniq.end());
    std::size_t sizeX = static_cast<std::size_t>(std::unique(lat_uniq.begin(), lat_uniq.end()) - lat_uniq.begin());
    std::size_t sizeY = static_cast<std::size_t>(std::unique(long_uniq.begin(), long_uniq.end()) - long_uniq.begin());

    maxX = *std::max_element(longitude.begin(), longitude.end());
    maxY = *std::max_element(latitude.begin(), latitude.end());
    minX = *std::min_element(longitude.begin(), longitude.end());
    minY = *std::min_element(latitude.begin(), latitude.end());

    m_bathymetry = std::make_shared<TM::Map::MapArea<double>>(sizeX, sizeY);

    m_bathymetry->setStepX((maxX - minX) / (sizeX - 1));
    m_bathymetry->setStepY((maxY - minY) / (sizeY - 1));
    m_bathymetry->setEndX(maxX);
    m_bathymetry->setEndY(maxY);
    m_bathymetry->setSizeX(sizeX);
    m_bathymetry->setSizeY(sizeY);
    m_bathymetry->setStartX(minX);
    m_bathymetry->setStartY(minY);

    for (std::size_t k = 0; k < static_cast<std::size_t >(depth.size()); k++) {
        m_bathymetry->setDataByPoint(longitude[k], latitude[k], depth[k]);
    }
    this->m_uVelocity = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<TM::Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
}

bool TM::Map::MapAreaWorker::readBathymetryFromFile() {
    if (m_bathymetryPath.size() < 5) { //WHAT??? Why 5? -
        //*.txt, *.doc *.xls ???
        //*.dat, *.mtx, *.grd - all formats can not be less than 5 characters
        if (m_bathymetryPath.empty()) {
            std::cerr << "Empty path.\n";
            return false;
        }
        std::cerr << "Incorrect path.";
        return false;

    }
    if (m_bathymetryPath.substr(m_bathymetryPath.size() - 4, 4) == ".dat") {
        readBathymetryFromFileDat();
        return true;
    }
    std::cerr << "No supported format\n";
    return false;
}

bool TM::Map::MapAreaWorker::setBathymetryPath(const std::string &path, bool readFromFile) {
    m_bathymetryPath = path;
    if (readFromFile) {
        return readBathymetryFromFile();
    }
    return false;
}

const std::shared_ptr<const TM::Map::MapArea<double>> TM::Map::MapAreaWorker::eta() const noexcept {
    return m_eta;
}

const std::shared_ptr<TM::Map::MapArea<double>> TM::Map::MapAreaWorker::eta() noexcept {
    return m_eta;
}

void TM::Map::MapAreaWorker::setEta(std::shared_ptr<TM::Map::MapArea<double>> newEta) noexcept {
    m_eta = newEta;
}


const std::shared_ptr<const TM::Map::MapArea<double>> TM::Map::MapAreaWorker::bathymetry() const noexcept {
    return m_bathymetry;
}


const std::shared_ptr<TM::Map::MapArea<double>> TM::Map::MapAreaWorker::uVelocity() noexcept {
    return m_uVelocity;
}

const std::shared_ptr<TM::Map::MapArea<double>> TM::Map::MapAreaWorker::vVelocity() noexcept {
    return m_vVelocity;
}

size_t TM::Map::MapAreaWorker::getMaxXIndex() const {
    return m_bathymetry->sizeX();
}

size_t TM::Map::MapAreaWorker::getMaxYIndex() const {
    return m_bathymetry->sizeY();
}

double TM::Map::MapAreaWorker::getLongitudeByIndex(const double i) const noexcept {
    return m_bathymetry->startX() + m_bathymetry->stepX() * i;
}

double TM::Map::MapAreaWorker::getLatitudeByIndex(const double i) const noexcept {
    return m_bathymetry->startY() + m_bathymetry->stepY() * i;
}

double TM::Map::MapAreaWorker::getStepX() const noexcept {
    return m_bathymetry->stepX();
}

double TM::Map::MapAreaWorker::getStepY() const noexcept {
    return m_bathymetry->stepY();
}

double TM::Map::MapAreaWorker::getStepPhi() const noexcept {
    return getStepY();
}

double TM::Map::MapAreaWorker::getStepTetta() const noexcept {
    return getStepX();
}

double TM::Map::MapAreaWorker::getMaxDepth() const noexcept {
    return m_bathymetry->getMinValue();
}