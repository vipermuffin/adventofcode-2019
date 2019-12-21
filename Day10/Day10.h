//
//  Advent of Code 2019 Solutions: Day 10
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/10/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay10 {
//Function Definitions
    int DetermineVisibleAsteroidsAtPos(const std::vector<std::string>& astMap, int x, int y);
    int DetermineMaxAsteroids(const std::vector<std::string>& astMap);
    std::pair<int,int> DetermineMaxAsteroidsLoc(const std::vector<std::string>& astMap);
    std::pair<int,int> DestroyNumAsteroids(std::vector<std::string>& astMap, int num2Destroy, int x, int y);
}
