//
//  Advent of Code 2019 Solutions: Day 3
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/02/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay03 {
//Function Definitions

    std::vector<std::pair<int,int>> findIntersections(const std::string& wire1, const std::string& wire2);
    int findBestIntersections(const std::string& wire1, const std::string& wire2);
}
