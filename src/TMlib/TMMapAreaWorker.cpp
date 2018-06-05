#include "TMlib/TMMapAreaWorker.h"
#include "TMlib/TMException.h"

#include <fstream>
#include <algorithm>
#include <ctime>

TM::Map::MapAreaWorker::MapAreaWorker(const std::string &path) :
    m_mareographsUpdating(false)
{
#ifdef DEBUG
    clock_t begin = clock();
#endif
    this->setBathymetryPath(path, true);
#ifdef DEBUG
    clock_t end = clock();
    std::cout << "Reading bathymetry from file: "
              << double(end - begin) * 1000. / CLOCKS_PER_SEC
              << " ms."
              << std::endl;
#endif
    this->m_uVelocity = std::make_shared<Map::RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<Map::RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<Map::RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
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
    std::size_t sizeX = static_cast<std::size_t>(std::unique(long_uniq.begin(), long_uniq.end()) - long_uniq.begin());
    std::size_t sizeY = static_cast<std::size_t>(std::unique(lat_uniq.begin(), lat_uniq.end()) - lat_uniq.begin());

    maxX = *std::max_element(longitude.begin(), longitude.end());
    maxY = *std::max_element(latitude.begin(), latitude.end());
    minX = *std::min_element(longitude.begin(), longitude.end());
    minY = *std::min_element(latitude.begin(), latitude.end());

    m_bathymetry = std::make_shared<RectangleMapArea<double>>(sizeX, sizeY);

    m_bathymetry->setStepLongitude((maxX - minX) / (sizeX - 1));
    m_bathymetry->setStepLatitude((maxY - minY) / (sizeY - 1));
    m_bathymetry->setEndLongitude(maxX);
    m_bathymetry->setEndLatitude(maxY);
    m_bathymetry->setSizeLongitude(sizeX);
    m_bathymetry->setSizeLatitude(sizeY);
    m_bathymetry->setStartLongitude(minX);
    m_bathymetry->setStartLatitude(minY);

    for (std::size_t k = 0; k < static_cast<std::size_t>(depth.size()); k++) {
        m_bathymetry->setDataByPoint(longitude[k], latitude[k], depth[k]);
    }

    this->m_uVelocity = std::make_shared<RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_vVelocity = std::make_shared<RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
    this->m_eta = std::make_shared<RectangleMapArea<double>>(this->getMaxXIndex(), this->getMaxYIndex());
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


void TM::Map::MapAreaWorker::setEta(std::shared_ptr<TM::Map::RectangleMapArea<double>> &newEta) noexcept {
    m_eta = newEta;
}
void TM::Map::MapAreaWorker::setU(std::shared_ptr<TM::Map::RectangleMapArea<double>> &newU) noexcept {
    m_uVelocity = newU;
}
void TM::Map::MapAreaWorker::setV(std::shared_ptr<TM::Map::RectangleMapArea<double>> &newV) noexcept {
    m_vVelocity = newV;
}


const std::shared_ptr<const TM::Map::RectangleMapArea<double>> TM::Map::MapAreaWorker::eta() const noexcept {
    return m_eta;
}

const std::shared_ptr<const TM::Map::RectangleMapArea<double>> TM::Map::MapAreaWorker::bathymetry() const noexcept {
    return m_bathymetry;
}

const std::shared_ptr<TM::Map::RectangleMapArea<double>> TM::Map::MapAreaWorker::uVelocity() const noexcept {
    return m_uVelocity;
}

const std::shared_ptr<TM::Map::RectangleMapArea<double>> TM::Map::MapAreaWorker::vVelocity() const noexcept {
    return m_vVelocity;
}

size_t TM::Map::MapAreaWorker::getMaxXIndex() const {
    return m_bathymetry->sizeLongitude();
}

size_t TM::Map::MapAreaWorker::getMaxYIndex() const {
    return m_bathymetry->sizeLatitude();
}

double TM::Map::MapAreaWorker::getLongitudeByIndex(const std::size_t &i) const noexcept {
    return m_bathymetry->startLongitude() + m_bathymetry->stepLongitude() * i;
}

double TM::Map::MapAreaWorker::getLatitudeByIndex(const std::size_t &i) const noexcept {
    return m_bathymetry->endLatitude() - m_bathymetry->stepLatitude() * i;
}

double TM::Map::MapAreaWorker::getStepX() const noexcept {
    return m_bathymetry->stepLongitude();
}

double TM::Map::MapAreaWorker::getStepY() const noexcept {
    return m_bathymetry->stepLatitude();
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

//std::shared_ptr<std::vector<Mareograph>> TM::Map::MapAreaWorker::mareoghraphs() const
//{
//    return m_mareographs;
//}

//void TM::Map::MapAreaWorker::setMareoghraphs(const std::shared_ptr<std::vector<Mareograph> > &mareoghraphs)
//{
//    m_mareographs = mareoghraphs;
//}

std::string TM::Map::MapAreaWorker::mareographsPath() const
{
    return m_mareographsPath;
}

void TM::Map::MapAreaWorker::setMareographsPath(const std::string &mareographsPath)
{
    m_mareographsPath = mareographsPath;
}

void TM::Map::MapAreaWorker::readMareographsFromFile(const std::string &mareographsPath)
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

        if(x < bathymetry()->startLongitude() || y < bathymetry()->startLatitude()
                || x > bathymetry()->endLongitude() || y > bathymetry()->endLatitude()){
            continue;
        }
        m.setIndexX(m_bathymetry->getIndexXByPoint(x));
        m.setIndexY(m_bathymetry->getIndexYByPoint(y));
        m_mareographs->push_back(m);
    }
    file.close();
}

void TM::Map::MapAreaWorker::saveMareographs(std::__cxx11::string path)
{
        for (size_t i = 0; i < m_mareographs->size(); i++){
            if (i < 10) (*m_mareographs)[i].writeToFileMareograph(path + "0"  + std::to_string(i));
            else (*m_mareographs)[i].writeToFileMareograph(path + "0" + std::to_string(i));
        }
        Mareograph a;
        a.writeToParametersMareograph(path + "parameters.txt", m_mareographs);
}

//void TM::Map::MapAreaWorker::checkMareographs(const std::shared_ptr<const RectangleMapArea<double>> &eta) {
//    if (!m_mareographs || (m_mareographs->empty() || !m_mareographsUpdating)) {
////        std::cout<<"Problems with mareographs"<<std::endl;
//        return;
//    }
//    for (auto i =  m_mareographs->begin(); i != m_mareographs->end(); i++)
//    {
//        i->pushHeight(eta->getDataByIndex(i->getIndexX(),i->getIndexY()));
//    }
//}

bool TM::Map::MapAreaWorker::mareographsUpdating() const noexcept
{
    return m_mareographsUpdating;
}

void TM::Map::MapAreaWorker::setMareographsUpdating(bool mareographsUpdating) noexcept
{
    m_mareographsUpdating = mareographsUpdating;
}

int TM::Map::MapAreaWorker::mareographStepTime() const
{
    return m_mareographStepTime;
}

void TM::Map::MapAreaWorker::setMareographStepTime(int mareographStepTime)
{
    m_mareographStepTime = mareographStepTime;
}
