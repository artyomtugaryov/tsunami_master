#include <fstream>
#include <algorithm>
#include <ctime>

#include "TMlib/map_area_worker.h"
#include "TMlib/exception.h"

using namespace TM;
using namespace TM::Map;
using namespace TM::details;

MapAreaWorker::MapAreaWorker(const std::string &path) :
        m_uVelocity(this->getMaxXIndex(), this->getMaxYIndex()),
        m_vVelocity(this->getMaxXIndex(), this->getMaxYIndex()),
        m_eta(this->getMaxXIndex(), this->getMaxYIndex()),
        m_mareographsUpdating(false) {
    clock_t begin = clock();
    this->setBathymetryPath(path, true);
    clock_t end = clock();
    std::cout << "Reading bathymetry from file: "
              << double(end - begin) * 1000. / CLOCKS_PER_SEC
              << " ms."
              << std::endl;
}

void MapAreaWorker::conigure(const double &izobata){
    m_types_cells = m_bathymetry;
    setTypesOfCells(izobata);
    m_eta = m_bathymetry;
    m_uVelocity= m_bathymetry;
    m_vVelocity = m_bathymetry;
}


const MapArea<double> &MapAreaWorker::eta() const noexcept {
    return m_eta;
}

const MapArea<double> &MapAreaWorker::bathymetry() const noexcept {
    return m_bathymetry;
}

MapArea<double> &MapAreaWorker::uVelocity() noexcept {
    return m_uVelocity;
}

MapArea<double> &MapAreaWorker::vVelocity() noexcept {
    return m_vVelocity;
}

const types_cells MapAreaWorker::typeOfCell(const size_t &i, const size_t &j) const {
    return m_types_cells.getDataByIndex(i, j);
}

const Focus::Focus &MapAreaWorker::focus() noexcept {
    return m_focus;
}


void MapAreaWorker::readBathymetryFromFileDat() {
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
    std::size_t sizeX = static_cast<std::size_t>(std::unique(long_uniq.begin(), long_uniq.end()) - long_uniq.begin());
    std::size_t sizeY = static_cast<std::size_t>(std::unique(lat_uniq.begin(), lat_uniq.end()) - lat_uniq.begin());

    maxX = *std::max_element(longitude.begin(), longitude.end());
    maxY = *std::max_element(latitude.begin(), latitude.end());
    minX = *std::min_element(longitude.begin(), longitude.end());
    minY = *std::min_element(latitude.begin(), latitude.end());

    m_bathymetry.setSizeX(sizeX);
    m_bathymetry.setSizeY(sizeY);

    m_bathymetry.setStepX((maxX - minX) / (sizeX - 1));
    m_bathymetry.setStepY((maxY - minY) / (sizeY - 1));
    m_bathymetry.setEndX(maxX);
    m_bathymetry.setEndY(maxY);
    m_bathymetry.setSizeX(sizeX);
    m_bathymetry.setSizeY(sizeY);
    m_bathymetry.setStartX(minX);
    m_bathymetry.setStartY(minY);

    for (std::size_t k = 0; k < static_cast<std::size_t>(depth.size()); k++) {
        m_bathymetry.setDataByPoint(longitude[k], latitude[k], depth[k]);
    }

    this->m_uVelocity.setSizeX(this->getMaxXIndex());
    this->m_uVelocity.setSizeY(this->getMaxYIndex());
    this->m_vVelocity.setSizeX(this->getMaxXIndex());
    this->m_vVelocity.setSizeY(this->getMaxYIndex());
    this->m_eta.setSizeX(this->getMaxXIndex());
    this->m_eta.setSizeY(this->getMaxYIndex());
}

bool MapAreaWorker::readBathymetryFromFile() {
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

bool MapAreaWorker::setBathymetryPath(const std::string &path, bool readFromFile) {
    m_bathymetryPath = path;
    if (readFromFile) {
        return readBathymetryFromFile();
    }
    return false;
}


void MapAreaWorker::setEta(const MapArea<double> &newEta) noexcept {
    m_eta = newEta;
}

void MapAreaWorker::setBathymetry(const MapArea<double> &newBathymetry) noexcept {
    m_bathymetry = newBathymetry;
}

void MapAreaWorker::setU(const MapArea<double> &newU) noexcept {
    m_uVelocity = newU;
}

void MapAreaWorker::setV(const MapArea<double> &newV) noexcept {
    m_vVelocity = newV;
}



const size_t &MapAreaWorker::getMaxXIndex() const {
    return m_bathymetry.sizeX();
}

const size_t &MapAreaWorker::getMaxYIndex() const {
    return m_bathymetry.sizeY();
}

double MapAreaWorker::getLongitudeByIndex(const std::size_t &i) const noexcept {
    return m_bathymetry.startX() + m_bathymetry.stepX() * i;
}

double MapAreaWorker::getLatitudeByIndex(const std::size_t &i) const noexcept {
    return m_bathymetry.endY() - m_bathymetry.stepY() * i;
}

double MapAreaWorker::getStepX() const noexcept {
    return m_bathymetry.stepX();
}

double MapAreaWorker::getStepY() const noexcept {
    return m_bathymetry.stepY();
}

double MapAreaWorker::getStepPhi() const noexcept {
    return getStepY();
}

double MapAreaWorker::getStepTetta() const noexcept {
    return getStepX();
}

double MapAreaWorker::getMaxDepth() const noexcept {
    return m_bathymetry.getMinValue();
}

const std::vector<Mareograph> MapAreaWorker::mareoghraphs() const {
    return m_mareographs;
}

void MapAreaWorker::setMareoghraphs(const std::vector<Mareograph> &mareoghraphs) {
    m_mareographs = mareoghraphs;
}

std::string MapAreaWorker::mareographsPath() const {
    return m_mareographsPath;
}

void MapAreaWorker::setMareographsPath(const std::string &mareographsPath) {
    m_mareographsPath = mareographsPath;
}

void MapAreaWorker::readMareographsFromFile(const std::string &mareographsPath) {
    std::fstream file;
    if (mareographsPath.empty()) {
        return;
    }
    const char *path = mareographsPath.c_str();
    file.open(path, std::fstream::in);
    int count;
    file >> count;
    for (int i = 0; i < count; i++) {
        std::string location;
        double x, y;
        file >> location >> x >> y;
        TM::Mareograph m(y, x, 10, location);

        if (x < bathymetry().startX() || y < bathymetry().startY()
            || x > bathymetry().endX() || y > bathymetry().endY()) {
            continue;
        }
        m.setIndexX(m_bathymetry.getIndexXByPoint(x));
        m.setIndexY(m_bathymetry.getIndexYByPoint(y));
        m_mareographs.push_back(m);
    }
    file.close();
}

void MapAreaWorker::saveMareographs(std::string path) {
    for (size_t i = 0; i < m_mareographs.size(); i++) {
        if (i < 10) {
            m_mareographs[i].writeToFileMareograph(path + "0" + std::to_string(i));
        } else {
            m_mareographs[i].writeToFileMareograph(path + "0" + std::to_string(i));
        }
    }
    Mareograph a;
    a.writeToParametersMareograph(path + "parameters.txt", m_mareographs);
}

void MapAreaWorker::checkMareographs(const MapArea<double> &eta) {
    if (m_mareographs.empty() || !m_mareographsUpdating) {
//        std::cout<<"Problems with mareographs"<<std::endl;
        return;
    }
    for (auto i = m_mareographs.begin(); i != m_mareographs.end(); i++) {
        i->pushHeight(eta.getDataByIndex(i->getIndexX(), i->getIndexY()));
    }
}

bool MapAreaWorker::mareographsUpdating() const noexcept {
    return m_mareographsUpdating;
}

void MapAreaWorker::setMareographsUpdating(bool mareographsUpdating) noexcept {
    m_mareographsUpdating = mareographsUpdating;
}

int MapAreaWorker::mareographStepTime() const {
    return m_mareographStepTime;
}

void MapAreaWorker::setMareographStepTime(int mareographStepTime) {
    m_mareographStepTime = mareographStepTime;
}


void MapAreaWorker::setTypesOfCells(const double &izobata) {
    auto maxX = m_types_cells.sizeX();
    auto maxY = m_types_cells.sizeY();
    auto types_of_cells = m_types_cells;
    std::size_t i(0), j(0);
    clock_t begin = clock();
#pragma omp parallel for private(i)
    for (i = 0; i < maxX; i++) {
#pragma omp parallel for private(j)
        for (j = 0; j < maxY; j++) {
            auto v = m_bathymetry.getDataByIndex(i, j);
            if (v >= izobata) {
                m_types_cells.setDataByIndex(i, j, types_cells::LAND);
                continue;
            }
            m_types_cells.setDataByIndex(i, j, types_cells::WATER);
            for (int k: {-1, 1}) {
                for (int t: {-1, 1}) {
                    try {
                        if (m_bathymetry.getDataByIndex(i + k, j + t) >= izobata) {
                            m_types_cells.setDataByIndex(i, j, types_cells::BOUNDARY1);
                        }
                    } catch (std::exception &ex) {
                        m_types_cells.setDataByIndex(i, j, types_cells::BOUNDARY2);
                        break;
                    }
                }
            }
            if (m_types_cells.getDataByIndex(i, j) == types_cells::BOUNDARY1) {
            }
        }
    }
    clock_t end = clock();
    std::cout << "Time of setTypesOfCells is: "
              << static_cast<double>(end - begin) * 1000.0 / double(CLOCKS_PER_SEC)
              << " ms."
              << std::endl;
}
