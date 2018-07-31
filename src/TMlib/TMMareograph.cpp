#include "TMlib/TMMareograph.h"

using namespace TM;

Mareograph::Mareograph(int _stepTime) : stepTime(_stepTime) {}

Mareograph::Mareograph(double _latitude, double _longitude, int _stepTime, std::string _locationName) :
        latitude(_latitude), longitude(_longitude), stepTime(_stepTime), locationNameASCII(_locationName) {
    std::wstring locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = locationName;
    maxHeight = 0;
    minHeight = 0;
    startTime = 0;
}

Mareograph::Mareograph(double _latitude, double _longitude, int _stepTime, std::wstring _locationName) :
        latitude(_latitude), longitude(_longitude), stepTime(_stepTime), locationNameUTF8(_locationName) {
    std::string locationName(_locationName.begin(), _locationName.end());
    locationNameASCII = locationName;
}

double Mareograph::getLongitude() const noexcept {
    return longitude;
}

double Mareograph::getLatitude() const noexcept {
    return latitude;
}

double Mareograph::getMaxHeight() const noexcept {
    return maxHeight;
}

double Mareograph::getMinHeight() const noexcept {
    return minHeight;
}

std::size_t Mareograph::getIndexX() const noexcept {
    return indexX;
}

std::size_t Mareograph::getIndexY() const noexcept {
    return indexY;
}

int Mareograph::getStepTime() const noexcept {
    return stepTime;
}

int Mareograph::getStartTime() const noexcept {
    return startTime;
}

std::string Mareograph::getLocationNameASCII() const noexcept {
    return locationNameASCII;
}

std::wstring Mareograph::getLocationNameUTF8() const noexcept {
    return locationNameUTF8;
}

double Mareograph::getHeight(int index) const noexcept {
    return heights[index];
}

unsigned int Mareograph::getSizeHeights() const noexcept {
    return static_cast<unsigned int>(heights.size());
}

void Mareograph::setLongitude(double _longitude) {
    longitude = _longitude;
}

void Mareograph::setLatitude(double _latitude) {
    latitude = _latitude;
}

void Mareograph::setStepTime(int _stepTime) {
    stepTime = _stepTime;
}

void Mareograph::setLocationName(std::string _locationName) {
    std::wstring locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = locationName;
    locationNameASCII = _locationName;
}

void Mareograph::setLocationName(std::wstring _locationName) {
    std::string locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = _locationName;
    locationNameASCII = locationName;
}

void Mareograph::setIndexX(double startX, double deltaX) {
    indexX = static_cast<size_t>((longitude - startX) / deltaX);
}

void Mareograph::setIndexX(std::size_t index) {
    indexX = index;
}

void Mareograph::setIndexY(double startY, double deltaY, int sizeY) {
    indexY = sizeY - 1 - static_cast<std::size_t> (((latitude - startY) / deltaY));
}

void Mareograph::setIndexY(std::size_t index) {
    indexY = index;
}

void Mareograph::pushHeight(double height) {
    if (height > maxHeight) {
        if (startTime == 0 && height > 0.0001) startTime = stepTime * heights.size();
        maxHeight = height;
    }
    if (height < minHeight) {
        if (startTime == 0 && height < 0.0001) startTime = stepTime * heights.size();
        minHeight = height;
    }
    heights.push_back(height);
}

void Mareograph::writeToFile(std::string path,
                             const std::vector<Mareograph> &M,
                             bool writeHeights) {
    if (M.empty()) return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << M.size() << "\n";
    file << M[0].getStepTime() << "\n";

    auto size = static_cast<int>(M.size());

    for (int j = 0; j < size; j++) {
        file << M[j].getLocationNameASCII().c_str() << "\t";
    }
    file << "\n";

    for (int j = 0; j < size; j++) {
        file << M[j].getLongitude() << "\t";
    }
    file << "\n";

    for (int j = 0; j < size; j++) {
        file << M[j].getLatitude() << "\t";
    }
    if (writeHeights) {
        if (!M[0].getSizeHeights()) file << "\n";

        for (int i = 0; i < (int) M[0].getSizeHeights(); i++) {

            for (int j = 0; j < size; j++) {
                file << M[j].getHeight(i) << "\t";
            }
            file << "\n";
        }
    }
}

void Mareograph::writeToFileMareograph(std::string path) {
    int size = static_cast<int>( heights.size());
    if (!size) return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << locationNameASCII.c_str() << "\n";
    file << size << "\n";
    for (int i = 0; i < size; i++) {
        file << heights[i] << "\n";
    }
}

std::string Mareograph::getStartTimeString(int t) {
    std::string clock_min, clock_sec, clock_hour, clock_time;
    int time = t - ((t / 60) * 60);
    clock_sec = std::to_string((time));
    time = (t / 60) - ((t / 60 / 60) * 60);
    clock_min = std::to_string((time));
    time = (t / 60 / 60);
    clock_hour = std::to_string((time));
    if (clock_sec.size() == 1) { clock_sec = "0" + clock_sec; }
    if (clock_min.size() == 1) { clock_min = "0" + clock_min; }
    if (clock_hour.size() == 1) { clock_hour = "0" + clock_hour; }
    clock_time = clock_hour + ":" + clock_min + ":" + clock_sec;
    return clock_time;
}

void Mareograph::writeToParametersMareograph(const std::string &path,
                                             const std::vector<Mareograph> &M) {
    int size = (int) M.size();
    if (!size)
        return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << "Location Name\tMax Height\tMinHeight\tStart Time\n";
    for (int i = 0; i < size; i++) {


        file << M[i].getLocationNameASCII() << "\t" << M[i].getMaxHeight()
             << "\t" << M[i].getMinHeight() << "\t" << getStartTimeString(M[i].getStartTime()) << "\n";
    }
}

void Mareograph::writeToFile(std::wstring path,
                             const std::vector<Mareograph> &M,
                             bool writeHeights) {
    std::string _path(path.begin(), path.end());
    writeToFile(_path, M, writeHeights);
}

std::vector<Mareograph> Mareograph::readFromFile(std::string path,
                                                 double startX, double startY,
                                                 double deltaX, double deltaY,
                                                 int sizeY, bool readHeights) {
    std::vector<Mareograph> M;
    std::fstream file;
    file.open(path, std::fstream::in);
    int count, _stepTime;
    file >> count >> _stepTime;
    M.resize(count);
    for (auto i :M) {
        i = Mareograph(_stepTime);
        std::string name;
        file >> name;
        i.setLocationName(std::string(name));
    }
    for (auto i : M) {
        double _longitude;
        file >> _longitude;
        i.setLongitude(_longitude);
        i.setIndexX(startX, deltaX);
    }
    for (auto i : M) {
        double _latitude;
        file >> _latitude;
        i.setLatitude(_latitude);
        i.setIndexY(startY, deltaY, sizeY);
    }
    if (readHeights) {
        while (!file.eof()) {
            for (auto j : M) {
                double height;
                file >> height;
                j.pushHeight(height);
            }
        }
    }
    return M;
}

std::vector<Mareograph> Mareograph::readFromFile(std::__cxx11::wstring path,
                                                 double startX, double startY,
                                                 double deltaX, double deltaY,
                                                 int sizeY, bool readHeights) {
    std::string _path(path.begin(), path.end());
    return readFromFile(_path, startX, startY,
                        deltaX, deltaY, sizeY, readHeights);
}
