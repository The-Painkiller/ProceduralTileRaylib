#pragma once
#include "Utils.h"
#include "GlobalHeader.h"

/// <summary>
/// Bias manager is a simple manager that will initialize with the bias data from the JSON through the data parser, and then for every tile type, runs a bias to return whether that type should be applied to a tile or not.
/// It maintains a list of a biases based on Water, Sand, Grass and Rock type tiles and a sub-list of valid terrain types for each.
/// Bias goes from 0-1. So anything falling under the more biased terrain type, will be more visible.
/// </summary>
class BiasManager
{
public:
    BiasManager() = default;
    void InitializeData(const std::vector<BiasData> biasData);
    static bool IsBiasValid(const TerrainTileType tileType);

private:
    static std::vector<BiasData> _biasData;
};

