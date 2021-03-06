#include <fstream>
#include <iostream>

#include "TMlib/focus.h"
#include "TMlib/exception.h"

using namespace TM::Focus;

TM::Focus::Focus::Focus(const std::string &path) {
    std::fstream blocksFile(path, std::ios_base::in);
    if (!blocksFile.good())
        THROW_TM_EXCEPTION << "FILE WITH BRICKS DID NOT OPEN\n";
    std::size_t countAngles(0);
    std::size_t terrCnt(0);
    blocksFile >> terrCnt; //Read count of blocks
    blocksFile >> countAngles; //Read count of blocks
    this->m_blocks.resize(terrCnt);
    std::vector<TM::Focus::BrickPoint> points;
    for (std::size_t i = 0; i < terrCnt; i++) {
        int countBrickUp;
        for (std::size_t j = 0; j < countAngles; j++) {
            double x(0), y(0);
            blocksFile >> x;
            blocksFile >> y;
            points.emplace_back(x, y);
        }
        m_blocks[i].buildBlock(points);
        blocksFile >> m_blocks[i].get_beginT();
        blocksFile >> countBrickUp;

        for (int j = 0; j < countBrickUp; j++) {
            double tmpHeightUp;
            int tmpBrickUpT;
            blocksFile >> tmpBrickUpT;
            blocksFile >> tmpHeightUp;
            m_blocks[i].get_numberUp().emplace_back(tmpBrickUpT, tmpHeightUp);
        }
        points.clear();
    }
    blocksFile.close();
}

const TM::Focus::Block TM::Focus::Focus::getBlock(std::size_t b) const noexcept {
    if (b < this->m_blocks.size()) {
        return m_blocks[b];
    } else {
        THROW_TM_EXCEPTION << "FOCUS out of range\n";
    }
}


double Focus::getHeightByPoint(double lat, double lon, double t) const {
    for (auto block : m_blocks) {
        if (block.has(lat, lon)) {
            return block.getUpHeight(t);
        }
    }
    return 0;
}

const std::vector<TM::Focus::Block>& TM::Focus::Focus::blocks(){
    return m_blocks;
}