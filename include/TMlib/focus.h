#ifndef TM_LIB_FOCUS_H
#define TM_LIB_FOCUS_H

#include "TMlib/block.h"
#include <vector>
#include <string>

using namespace std;

namespace TM {
    namespace Focus {
        class Focus {
        public:
            Focus() = default;

            Focus(const string &);

            size_t getBlockCount() const noexcept { return this->m_blocks.size(); }

            const Block getBlock(size_t b)const noexcept ;

            double getHeightByPoint(double i, double j, double t) const;

            const vector<Block>& blocks();

        private:
            vector<Block> m_blocks;
        };
    }
}

#endif //TM_LIB_FOCUS_H
