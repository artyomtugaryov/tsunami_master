#include "HDlib/MapAreaWorker.h"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <QImage>

Map::MapAreaWorker::MapAreaWorker()
{

}

void Map::MapAreaWorker::readBathymetryFromFileDat()
{
    std::vector <double> longitude; // y
    std::vector <double> latitude;  // x
    std::vector <double> depth;
    FILE* infile;

    infile = fopen(m_bathymetryPath.c_str(), "rt");

    double minX;
    double maxX;
    double minY;
    double maxY;
    double datX; // latitude
    double datY; // longitude
    double datZ; // depth

    while (fscanf(infile, "%lf%lf%lf", &datX, &datY, &datZ) == 3)
    {
        latitude.push_back(datX);
        longitude.push_back(datY);
        depth.push_back(datZ);
    }

    fclose(infile);

    std::vector <double> lat_uniq(latitude), long_uniq(longitude);
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

    m_bathymetry = std::make_shared<Map::MapArea <double>>(sizeX, sizeY);

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
    for (int k = 0; k < (int)depth.size(); k++)
    {
        m_bathymetry->setDataByPoint(latitude[k], longitude[k], depth[k]);
    }
    //initMainArrays(size_y, size_x);
    //init_old_arrays();
    testDraw();
    m_bathymetry->saveMapAreaToTextFile("testFile.mtx", 0);
}

void Map::MapAreaWorker::testDraw()
{
    std::size_t sizeX = m_bathymetry->sizeX();
    std::size_t sizeY = m_bathymetry->sizeY();
    QImage bath = QImage(sizeX, sizeY, QImage::Format_RGB32);
    for(std::size_t y = 0; y < sizeY; y++){
        for(std::size_t x = 0; x < sizeX; x++){
            if(m_bathymetry->getDataByIndex(x,y) > 0)
                bath.setPixelColor(x, y, QColor(0, 255, 0));
            else bath.setPixelColor(x, y, QColor(0, 0, 255));
        }
    }
    bath.save("testOutput.png");
}

void Map::MapAreaWorker::readBathymetryFromFile()
{
    if (m_bathymetryPath.size() < 5) {
        if(m_bathymetryPath.size() == 0) {
            std::cerr <<"Empty path.\n";
        }
        else {
            std::cerr << "Incorrect path.";
        }
        return;
    }
    if (m_bathymetryPath.substr(m_bathymetryPath.size() - 4, 4) == ".dat") {
        readBathymetryFromFileDat();
    }
    else {
        std::cerr << "No supported format\n";
        return;
    }
}

void Map::MapAreaWorker::setBathymetryPath(std::__cxx11::string path, bool readFromFile)
{
    m_bathymetryPath = path;
    if (readFromFile) {
        readBathymetryFromFile();
    }
}
