//
//  Advent of Code 2019 Solutions: Day 17
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay17 {
//Function Definitions
    int32_t getAlignmentSum(const std::vector<std::string>& inputMap);
    void appendCommandToArguments(std::vector<int32_t>& args, const std::string& cmds);
}
