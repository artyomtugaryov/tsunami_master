#include "TMlib/TMSchemeLandSearch.h"
#include <TMlib/TMException.h>

using namespace std;

std::shared_ptr<TM::Map::MapArea <bool>> TM::Scheme::LandSearch::getLandMap(std::shared_ptr<TM::Map::MapAreaWorkerGroundswell> map)
{
    double eps = 0.000001; //надо вынести в константы
    std::shared_ptr<TM::Map::MapArea <bool>> land;
    for (int j = 0; j < map->bathymetry()->sizeY(); j++)
    {
        for (int i = 0; i < map->bathymetry()->sizeX(); i++)
        {
            if (map->eta()->getDataByIndex(i, j) + map->H()->getDataByIndex(i, j)
                    < eps) //суша
            {
                land->setDataByIndex(i, j, true);
            }
            else //вода
            {
                land->setDataByIndex(i, j, false);
            }
        }
    }
    return land;
}

