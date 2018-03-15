#include "TMMareograph.h"

using namespace TM;
Mareograph::Mareograph()
{
}


Mareograph::~Mareograph()
{
}

Mareograph::Mareograph(double _latitude, double _longitude, int _stepTime, std::__cxx11::string _locationName):
    latitude(_latitude), longitude(_longitude), stepTime(_stepTime), locationNameASCII(_locationName)
{
    std::wstring locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = locationName;
    maxHeight = 0;
    minHeight = 0;
    startTime = 0;
}

Mareograph::Mareograph(double _latitude, double _longitude, int _stepTime, std::__cxx11::wstring _locationName):
    latitude(_latitude), longitude(_longitude), stepTime(_stepTime), locationNameUTF8(_locationName)
{
    std::string locationName(_locationName.begin(), _locationName.end());
    locationNameASCII = locationName;
}

double Mareograph::getLongitude() const { return longitude; }

double Mareograph::getLatitude() const { return latitude; }

double Mareograph::getMaxHeight() const { return maxHeight; }

double Mareograph::getMinHeight() const { return minHeight; }

int Mareograph::getIndexX() const { return indexX; }

int Mareograph::getIndexY() const { return indexY; }

int Mareograph::getStepTime() const { return stepTime; }

Mareograph::Mareograph(int _stepTime) :stepTime(_stepTime){}

int Mareograph::getStartTime() const { return startTime; }

std::__cxx11::string Mareograph::getLocationNameASCII() const { return locationNameASCII; }

std::__cxx11::wstring Mareograph::getLocationNameUTF8() const { return locationNameUTF8; }

double Mareograph::getHeight(int index) const { return heights[index]; }

unsigned int Mareograph::getSizeHeights() const { return heights.size(); }

void Mareograph::setLongitude(double _longitude)  { longitude = _longitude; }

void Mareograph::setLatitude(double _latitude) { latitude = _latitude; }

void Mareograph::setStepTime(int _stepTime){ stepTime = _stepTime; }

void Mareograph::setLocationName(std::__cxx11::string _locationName) {
    std::wstring locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = locationName;
    locationNameASCII = _locationName;
}

void Mareograph::setLocationName(std::__cxx11::wstring _locationName) {
    std::string locationName(_locationName.begin(), _locationName.end());
    locationNameUTF8 = _locationName;
    locationNameASCII = locationName;
}

void Mareograph::setIndexX(double startX, double deltaX)
{ indexX =(int)((longitude - startX) / deltaX);	}

void Mareograph::setIndexX(int index)
{
    indexX = index;
}

void Mareograph::setIndexY(double startY, double deltaY, int sizeY)
{ indexY = sizeY - 1 - (int)(((latitude - startY) / deltaY));}

void Mareograph::setIndexY(int index)
{
    indexY = index;
}

void Mareograph::pushHeight(double height)
{
    if (height > maxHeight){
        if (startTime == 0 && height > 0.0001) startTime = stepTime * heights.size();
        maxHeight = height;
    }
    if (height < minHeight){
        if (startTime == 0 && height < 0.0001) startTime = stepTime * heights.size();
        minHeight = height;
    }
    heights.push_back(height);
}

void Mareograph::writeToFile(std::__cxx11::string path,
                             const std::shared_ptr<std::vector<Mareograph> > M,
                             bool writeHeights)
{
    if (!M || M->empty()) return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << M->size() << "\n";
    file << (*M)[0].getStepTime() << "\n";

    int size = (int)M->size();

    for (int j = 0; j < size; j++){
        file << (*M)[j].getLocationNameASCII().c_str() << "\t";
    }
    file << "\n";

    for (int j = 0; j < size; j++){
        file << (*M)[j].getLongitude() << "\t";
    }
    file << "\n";

    for (int j = 0; j < size; j++){
        file << (*M)[j].getLatitude() << "\t";
    }
    if (writeHeights){
        if (!(*M)[0].getSizeHeights()) file << "\n";

        for (int i = 0; i < (int)(*M)[0].getSizeHeights(); i++){

            for (int j = 0; j < size; j++){
                file << (*M)[j].getHeight(i) << "\t";
            }
            file << "\n";
        }
    }
}

void Mareograph::writeToFileMareograph(std::__cxx11::string path)
{
    int size = (int)heights.size();
    if (size == 0) return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << locationNameASCII.c_str() << "\n";
    file << size << "\n";
    for (int i = 0; i < size; i++){
        file << heights[i] << "\n";
    }
}

std::__cxx11::string Mareograph::getStartTimeString(int t)
{
    std::string clock_min, clock_sec, clock_hour, clock_time;
    int time = t - (int(t / 60) * 60);
    clock_sec = std::to_string((time));
    time = int(t / 60) - (int(t / 60 / 60) * 60);
    clock_min = std::to_string((time));
    time = int(t / 60 / 60);
    clock_hour = std::to_string((time));
    if (clock_sec.size() == 1) { clock_sec = "0" + clock_sec; }
    if (clock_min.size() == 1) { clock_min = "0" + clock_min; }
    if (clock_hour.size() == 1) { clock_hour = "0" + clock_hour; }
    clock_time = clock_hour + ":" + clock_min + ":" + clock_sec;
    return clock_time;
}

void Mareograph::writeToParametersMareograph(std::__cxx11::string path, const std::shared_ptr<std::vector<Mareograph> > M)
{
    int size = (int)M->size();
    if (size == 0) return;
    std::fstream file;
    file.open(path, std::fstream::out);
    file << "Location Name\tMax Height\tMinHeight\tStart Time\n";
    for (int i = 0; i < size; i++){


        file << (*M)[i].getLocationNameASCII() << "\t" << (*M)[i].getMaxHeight()
             << "\t" << (*M)[i].getMinHeight() << "\t" << getStartTimeString((*M)[i].getStartTime()) << "\n";
    }
    return;
}

void Mareograph::writeToFile(std::__cxx11::wstring path,
                             const std::shared_ptr<std::vector<Mareograph> > M,
                             bool writeHeights)
{
    std::string _path(path.begin(), path.end());
    writeToFile(_path, M, writeHeights);
}

std::shared_ptr<std::vector<Mareograph> > Mareograph::readFromFile(std::__cxx11::string path,
                                                                   double startX, double startY,
                                                                   double deltaX, double deltaY,
                                                                   int sizeY, bool readHeights)
{
    std::shared_ptr<std::vector<Mareograph> > M = std::make_shared <std::vector<Mareograph>>();
    std::fstream file;
    file.open(path, std::fstream::in);
    int count, _stepTime;
    file >> count >> _stepTime;

    for (int i = 0; i < count; i++){
        M->push_back(Mareograph(_stepTime));
        char* name;
        file >> name;
        (*M)[i].setLocationName(std::string(name));
        delete name;
    }
    for (int i = 0; i < count; i++){
        double _longitude;
        file >> _longitude;
        (*M)[i].setLongitude(_longitude);
        (*M)[i].setIndexX(startX, deltaX);
    }
    for (int i = 0; i < count; i++){
        double _latitude;
        file >> _latitude;
        (*M)[i].setLatitude(_latitude);
        (*M)[i].setIndexY(startY, deltaY, sizeY);
    }
    if (readHeights){
        for (int i = 0; !file.eof(); i++){
            for (int j = 0; j < count; count++){
                double height;
                file >> height;
                (*M)[j].pushHeight(height);
            }
        }
    }
    return M;
}

std::shared_ptr<std::vector<Mareograph> > Mareograph::readFromFile(std::__cxx11::wstring path,
                                                                   double startX, double startY,
                                                                   double deltaX, double deltaY,
                                                                   int sizeY, bool readHeights)
{
    std::string _path(path.begin(), path.end());
    std::shared_ptr<std::vector<Mareograph> > M = readFromFile(_path, startX, startY,
                                                               deltaX, deltaY, sizeY, readHeights);
    return M;
}
