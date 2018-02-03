#ifndef TSUNAMIMANAGER_TMFOCUS_H
#define TSUNAMIMANAGER_TMFOCUS_H

#include "TMBlock.h"
#include <vector>
#include <string>

namespace TM {
    class TMFocus {
    public:
        TMFocus() = default;
        TMFocus(const std::string&);
        std::size_t getBlockCount(){ return this->m_blocks.size();}
        const TM::TMBlock getBlock(std::size_t b);
        double getHeigthByIndex(double i, double j, double t);
    private:
        std::vector<TM::TMBlock> m_blocks;
    };
}

#endif //TSUNAMIMANAGER_TMFOCUS_H
