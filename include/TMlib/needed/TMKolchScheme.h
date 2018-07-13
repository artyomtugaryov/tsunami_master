#ifndef TMKOLCHSCHEMA_H
#define TMKOLCHSCHEMA_H

#include "TMlib/TMScheme.h"

namespace TM {
    namespace Scheme {
        class TMKolchSchema : public Scheme {
        public:
            TMKolchSchema() = default;

            ~TMKolchSchema() override = default;

            void calculation(const std::shared_ptr<TM::Map::MapAreaWorker> &,
                             const double &) override ;

            void configure(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                           const std::shared_ptr<const TM::Focus::Focus> &,
                           const double &) override ;

        private:
            void set_delta(const std::shared_ptr<const TM::Map::RectangleMapArea<double>> &);

            void setBoundary1Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                  const size_t &,
                                  const size_t &,
                                  const double &) override {};

            void setBoundary2Coef(const std::shared_ptr<const TM::Map::MapAreaWorker> &,
                                  const size_t &,
                                  const size_t &,
                                  const double &) override {};

            double delta_x_m;
            std::vector<double> delta_t;
            std::vector<double> delta_y_m;
            std::vector<std::vector<int>> terr_up;
        };
    }
}


#endif //TMKOLCHSCHEMA_H
