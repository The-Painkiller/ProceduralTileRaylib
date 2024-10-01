#include <iostream>
#include <raylib.h>
#include "DataParser.h"
int main()
{
    DataParser* dataParser = new DataParser();
    dataParser->Initialize();
    std::cout << dataParser->GetTerrainTileData();
}