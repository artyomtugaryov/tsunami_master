#include "TMlib/TMMapAreaWorker.h"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <fstream>

TM::Map::MapAreaWorker::MapAreaWorker() {

}

void TM::Map::MapAreaWorker::readBathymetryFromFileDat() {
    std::vector<double> longitude; // y
    std::vector<double> latitude;  // x
    std::vector<double> depth;
    std::fstream infile(m_bathymetryPath.c_str(), std::ios_base::in);

    double minX(0);
    double maxX(0);
    double minY(0);
    double maxY(0);
    double datX(0); // latitude
    double datY(0); // longitude
    double datZ(0); // depth
    char line[25];
    while (infile>>datX>>datY>>datZ) {
//        std::cout << line << std::endl;
//        sscanf(line, " %lf  %lf %lf\r\n", &datX, &datY, &datZ);
        latitude.push_back(datX);
        longitude.push_back(datY);
        depth.push_back(datZ);
    }

    infile.close();

    std::vector<double> lat_uniq(latitude), long_uniq(longitude);
    std::sort(lat_uniq.begin(), lat_uniq.end());
    std::sort(long_uniq.begin(), long_uniq.end());
    std::size_t sizeX = (std::unique(lat_uniq.begin(), lat_uniq.end()) - lat_uniq.begin());
    std::size_t sizeY = (std::unique(long_uniq.begin(), long_uniq.end()) - long_uniq.begin());
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

    m_bathymetry = std::make_shared<TM::Map::MapArea<double>>(sizeX, sizeY);

    m_bathymetry->setEndX(endX);
    m_bathymetry->setEndY(endY);
    m_bathymetry->setSizeX(sizeX);
    m_bathymetry->setSizeY(sizeY);
    m_bathymetry->setStartX(startX);
    m_bathymetry->setStartY(startY);
    m_bathymetry->setStepX(stepX);
    m_bathymetry->setStepY(stepY);

    //bottom = create_array(size_y, size_x);
    //m_bathymetry->setDataByIndex(0, 0, 0);
    for (int k = 0; k < (int) depth.size(); k++) {
        m_bathymetry->setDataByPoint(latitude[k], longitude[k], depth[k]);
    }
    //initMainArrays(size_y, size_x);
    //init_old_arrays();
//    testDraw();
    m_bathymetry->saveMapAreaToTextFile("testFile.mtx", 0);
}

void TM::Map::MapAreaWorker::testDraw() {
//    std::size_t sizeX = m_bathymetry->sizeX();
//    std::size_t sizeY = m_bathymetry->sizeY();
//    QImage bath = QImage(sizeX, sizeY, QImage::Format_RGB32);
//    for(std::size_t y = 0; y < sizeY; y++){
//        for(std::size_t x = 0; x < sizeX; x++){
//            if(m_bathymetry->getDataByIndex(x,y) > 0)
//                bath.setPixelColor(x, y, QColor(0, 255, 0));
//            else bath.setPixelColor(x, y, QColor(0, 0, 255));
//        }
//    }
//    bath.save("testOutput.png");
}

void TM::Map::MapAreaWorker::readBathymetryFromFile() {
    if (m_bathymetryPath.size() < 5) { //WHAT??? Why 5?
        if (m_bathymetryPath.size() == 0) {
            std::cerr << "Empty path.\n";
        } else {
            std::cerr << "Incorrect path.";
        }
        return;
    }
    if (m_bathymetryPath.substr(m_bathymetryPath.size() - 4, 4) == ".dat") {
        readBathymetryFromFileDat();
    } else {
        std::cerr << "No supported format\n";
        return;
    }
}

void TM::Map::MapAreaWorker::setBathymetryPath(std::string path, bool readFromFile) {
    m_bathymetryPath = path;
    if (readFromFile) {
        readBathymetryFromFile();
    }
}

