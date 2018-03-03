#include <fstream>
#include <iostream>

#include "TMlib/TMFocus.h"
#include "TMlib/TMException.h"

TM::TMFocus::TMFocus(const std::string &path) {
    std::fstream blocksFile(path, std::ios_base::in);
    if (!blocksFile.good())
        THROW_TM_EXCEPTION << "FILE WITH BRICKS DID NOT OPEN\n";
    std::size_t countAngles(0);
    std::size_t terrCnt(0);
    blocksFile >> terrCnt; //Read count of blocks
    blocksFile >> countAngles; //Read count of blocks
    this->m_blocks.resize(terrCnt);

    for (std::size_t i = 0; i < terrCnt; i++) {
        int countBrickUp;
        for (int j = 0; j < countAngles; j++) {
            double x(0), y(0);
            blocksFile >> x;
            blocksFile >> y;
            this->m_blocks[i].m_points.emplace_back(x, y);
        }
        std::sort(m_blocks[i].m_points.begin(), m_blocks[i].m_points.end());
        blocksFile >> m_blocks[i].m_beginT ;
        blocksFile >> countBrickUp;

        for (int j = 0; j < countBrickUp; j++) {
            double tmpHeightUp;
            int tmpBrickUpT;
            blocksFile >> tmpBrickUpT;
            blocksFile >> tmpHeightUp;
            m_blocks[i].m_numberUp.emplace_back(tmpBrickUpT, tmpHeightUp);
        }
    }
    blocksFile.close();
}

const TM::TMBlock TM::TMFocus::getBlock(std::size_t b) {
    if (b < this->m_blocks.size()) {
        return m_blocks[b];
    } else {
        THROW_TM_EXCEPTION << "FOCUS out of range\n";
    }
}


double TM::TMFocus::getHeigthByIndex(double lat, double lon, double t) {
    for (auto block = m_blocks.begin(); block != this->m_blocks.end(); block++) {
        if (block->has(lat, lon)) {
            return block->getUpHeihgt(t);
        }
    }
    return 0;
}
