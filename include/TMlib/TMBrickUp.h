#ifndef TMBRICKUP_H
#define TMBRICKUP_H

namespace TM {
    namespace Focus {
        class BrickUp {
        public:

            BrickUp() : m_brickUpT(0.0), m_heightUp(0.0) {}

            BrickUp(const double &b, const double &h) : m_brickUpT(b), m_heightUp(h) {}

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

#endif //TMBRICKUP_H
