#include <TMlib/TMException.h>
#include <TMlib/TMMapArea.h>
int main()
{
    TM::Map::MapArea<double> a(3,3);
    try{
        a.getIndex(4, 4);
    } catch (TM::details::TMException e){
        std::cerr <<e.what()<<std::endl;
    }
    return 0;
}
