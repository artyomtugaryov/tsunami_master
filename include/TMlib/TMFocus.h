#ifndef TMFOCUS_H
#define TMFOCUS_H

#include "TMBlock.h"

#include <vector>
#include <string>

namespace TM {
    namespace Focus {
        class Focus {
        public:
            Focus() = default;

            explicit Focus(const std::string &);

            std::size_t getBlockCount() const noexcept { return this->m_blocks.size(); }

            const TM::Focus::Block getBlock(std::size_t b) const noexcept;

            double getHeightByPoint(double i, double j, double t);

            const std::vector<TM::Focus::Block> &blocks();

        private:
            std::vector<TM::Focus::Block> m_blocks;
        };
    }
}

#endif //TMFOCUS_H
