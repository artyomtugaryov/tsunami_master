#ifndef TM_LIB_BRICK_UP_H
#define TM_LIB_BRICK_UP_H

namespace TM {
    namespace Focus {
        class BrickUp {
        public:

            explicit BrickUp(const double &b=0, const double &h=0);

            double get_brickUpT() const;

            double get_heightUp() const;

        private:
            /**
             * Time Up the block
             **/
            double m_brickUpT;
            /**
             * Height Up the  block
             **/
            double m_heightUp;
        };
    }
}

#endif //TM_LIB_BRICK_UP_H
