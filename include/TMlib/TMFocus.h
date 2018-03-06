#ifndef TSUNAMIMANAGER_TMFOCUS_H
#define TSUNAMIMANAGER_TMFOCUS_H

#include "TMBlock.h"
#include <vector>
#include <string>

namespace TM {
    namespace Focus {
        class Focus {
        public:
            Focus() = default;

            Focus(const std::string &);

            std::size_t getBlockCount() { return this->m_blocks.size(); }

            const TM::Focus::Block getBlock(std::size_t b);

            double getHeightByIndex(double i, double j, double t);

        private:
            std::vector<TM::Focus::Block> m_blocks;
        };
    }
}

#endif //TSUNAMIMANAGER_TMFOCUS_H
