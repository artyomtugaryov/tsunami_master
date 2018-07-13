#include <iostream>
#include <TMlib/TMRectangleMapArea.h>

using namespace std;
using namespace TM;

int main() {
    std::shared_ptr<Map::RectangleMapArea<double>> map = std::make_shared<Map::RectangleMapArea<double>>();
    return 0;
}