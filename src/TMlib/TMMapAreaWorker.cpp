#include "TMlib/TMMapAreaWorker.h"
#include <TMlib/TMException.h>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace TM;

Map::MapAreaWorker::MapAreaWorker(const std::string &path) :
    m_mareographsUpdating(false)
{
    clock_t begin = clock();
    this->setBathymetryPath(path, true);
    clock_t end = clock();
    std::cout << "Reading bathymetry from file: "
              << double(end - begin) * 1000. / CLOCKS_PER_SEC
              << " ms."
              << std::endl;
    this->m_uVelocity = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
}

void Map::MapAreaWorker::readBathymetryFromFileDat() {
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

    m_bathymetry = std::make_shared<Map::MapArea<double>>(sizeX, sizeY);

    m_bathymetry->setStepX((maxX - minX) / (sizeX - 1));
    m_bathymetry->setStepY((maxY - minY) / (sizeY - 1));
    m_bathymetry->setEndX(maxX);
    m_bathymetry->setEndY(maxY);
    m_bathymetry->setSizeX(sizeX);
    m_bathymetry->setSizeY(sizeY);
    m_bathymetry->setStartX(minX);
    m_bathymetry->setStartY(minY);

    for (std::size_t k = 0; k < static_cast<std::size_t>(depth.size()); k++) {
        m_bathymetry->setDataByPoint(longitude[k], latitude[k], depth[k]);
    }

    this->m_uVelocity = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<Map::MapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
}

bool Map::MapAreaWorker::readBathymetryFromFile() {
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

bool Map::MapAreaWorker::setBathymetryPath(const std::string &path, bool readFromFile) {
    m_bathymetryPath = path;
    if (readFromFile) {
        return readBathymetryFromFile();
    }
    return false;
}



void TM::Map::MapAreaWorker::setEta(std::shared_ptr<TM::Map::MapArea<double>> &newEta) noexcept {
    m_eta = newEta;
}
void TM::Map::MapAreaWorker::setU(std::shared_ptr<TM::Map::MapArea<double>> &newU) noexcept {
    m_uVelocity = newU;
}
void TM::Map::MapAreaWorker::setV(std::shared_ptr<TM::Map::MapArea<double>> &newV) noexcept {
    m_vVelocity = newV;
}



const std::shared_ptr<const Map::MapArea<double>> Map::MapAreaWorker::eta() const noexcept {
    return m_eta;
}

const std::shared_ptr<const Map::MapArea<double>> Map::MapAreaWorker::bathymetry() const noexcept {
    return m_bathymetry;
}

const std::shared_ptr<Map::MapArea<double>> Map::MapAreaWorker::uVelocity() const noexcept {
    return m_uVelocity;
}

const std::shared_ptr<Map::MapArea<double>> Map::MapAreaWorker::vVelocity() const noexcept {
    return m_vVelocity;
}

size_t Map::MapAreaWorker::getMaxXIndex() const {
    return m_bathymetry->sizeX();
}

size_t Map::MapAreaWorker::getMaxYIndex() const {
    return m_bathymetry->sizeY();
}

double TM::Map::MapAreaWorker::getLongitudeByIndex(const double &i) const noexcept {
    return m_bathymetry->startX() + m_bathymetry->stepX() * i;
}

double TM::Map::MapAreaWorker::getLatitudeByIndex(const double &i) const noexcept {
    return m_bathymetry->endY() - m_bathymetry->stepY() * i;
}

double Map::MapAreaWorker::getStepX() const noexcept {
    return m_bathymetry->stepX();
}

double Map::MapAreaWorker::getStepY() const noexcept {
    return m_bathymetry->stepY();
}

double Map::MapAreaWorker::getStepPhi() const noexcept {
    return getStepY();
}

double Map::MapAreaWorker::getStepTetta() const noexcept {
    return getStepX();
}

double Map::MapAreaWorker::getMaxDepth() const noexcept {
    return m_bathymetry->getMinValue();
}

std::shared_ptr<std::vector<Mareograph> > Map::MapAreaWorker::mareoghraphs() const
{
    return m_mareographs;
}

void Map::MapAreaWorker::setMareoghraphs(const std::shared_ptr<std::vector<Mareograph> > &mareoghraphs)
{
    m_mareographs = mareoghraphs;
}

std::string Map::MapAreaWorker::mareographsPath() const
{
    return m_mareographsPath;
}

void Map::MapAreaWorker::setMareographsPath(const std::string &mareographsPath)
{
    m_mareographsPath = mareographsPath;
}

void Map::MapAreaWorker::readMareographsFromFile(const std::string &mareographsPath)
{
    std::fstream file;
    if(mareographsPath.empty())
    {
        return;
    }
    m_mareographs =  std::make_shared<std::vector <Mareograph>>();
    const char * path = mareographsPath.c_str();
    file.open(path, std::fstream::in);
    int count;
    file >> count;
    for (int i = 0; i < count; i++)
    {
        std::string location;
        double x, y;
        file >> location >> x >> y;
        TM::Mareograph m(y, x, 10, location);

        if(x < bathymetry()->startX() || y < bathymetry()->startY()
                || x > bathymetry()->endX() || y > bathymetry()->endY()){
            continue;
        }
        m.setIndexX(m_bathymetry->getIndexXByPoint(x));
        m.setIndexY(m_bathymetry->getIndexYByPoint(y));
        m_mareographs->push_back(m);
    }
    file.close();
}

void Map::MapAreaWorker::saveMareographs(std::__cxx11::string path)
{
        for (size_t i = 0; i < m_mareographs->size(); i++){
            if (i < 10) (*m_mareographs)[i].writeToFileMareograph(path + "0"  + std::to_string(i));
            else (*m_mareographs)[i].writeToFileMareograph(path + "0" + std::to_string(i));
        }
        Mareograph a;
        a.writeToParametersMareograph(path + "parameters.txt", m_mareographs);
}

void Map::MapAreaWorker::checkMareographs(const std::shared_ptr<const MapArea<double>> &eta) {
    if (!m_mareographs || (m_mareographs->empty() || !m_mareographsUpdating)) {
        std::cout<<"Problems with mareographs"<<std::endl;
        return;
    }
    for (auto i =  m_mareographs->begin(); i != m_mareographs->end(); i++)
    {
        i->pushHeight(eta->getDataByIndex(i->getIndexX(),i->getIndexY()));
    }
}

bool Map::MapAreaWorker::mareographsUpdating() const noexcept
{
    return m_mareographsUpdating;
}

void Map::MapAreaWorker::setMareographsUpdating(bool mareographsUpdating) noexcept
{
    m_mareographsUpdating = mareographsUpdating;
}

int Map::MapAreaWorker::mareographStepTime() const
{
    return m_mareographStepTime;
}

void Map::MapAreaWorker::setMareographStepTime(int mareographStepTime)
{
    m_mareographStepTime = mareographStepTime;
}
