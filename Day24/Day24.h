//
//  Advent of Code 2019 Solutions: Day 24
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/24/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay24 {
//Function Definitions
    using InfiniteGrids = std::vector<std::vector<std::string>>;
    void processBugLife(std::vector<std::string>& bugs);
    void processRecursiveBugLifecycle(std::vector<std::string>& bugs,InfiniteGrids& levels,int currentLevel);
    int32_t simulateRecursiveLifecycles(std::vector<std::string>& bugs, int numTimes);
    int32_t watchForDuplicateLifecycle(std::vector<std::string>& bugs);
    int32_t calculateBiodiversity(const std::vector<std::string>& bugs);
    int32_t countBugs(const InfiniteGrids& levels);
}
