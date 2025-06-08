#include "BiasManager.h"

void BiasManager::InitializeData(const std::vector<BiasData> biasData)
{
    _biasData = biasData;
}

std::vector<BiasData> BiasManager::_biasData;

bool BiasManager::IsBiasValid(const TerrainTileType tileType)
{
    // For each tile type passed, a random value is generated and run through all the bias categories to see 
    // if the passed tile type belongs to any of the sub-lists and whether the random generated value falls within it's bias value.

    float rand = Utils::Random(0.0f, 1.1f);
    for (int i = 0; i < TerrainBiasCategory::TerrainBiasCategoryCount; i++)
    {
        auto iter = std::find(_biasData[i].ValidTerrainTypes.begin(), _biasData[i].ValidTerrainTypes.end(), tileType);
        if (iter != _biasData[i].ValidTerrainTypes.end())
        {
            if (rand < _biasData[i].Bias)
            {
                return true;
            }
        }
    }

    return false;
}