#include <iostream>
#include <TMlib/TMRectangleMapArea.h>
#include <c++/map>

using namespace std;
using namespace TM;

int main() {
    std::shared_ptr<Map::RectangleMapArea<double>> map = std::make_shared<Map::RectangleMapArea<double>>();
    for (auto i = map->beginLatitude(); i != nullptr ;++(*i)){

    }
    return 0;
}