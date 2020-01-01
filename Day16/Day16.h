//
//  Advent of Code 2019 Solutions: Day 16
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/16/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay16 {
//Function Definitions

    std::string performFFT(std::string inputSignal, int iterations);
    std::string performFFT2(std::string inputSignal, int iterations, const int mul, const int offset);
}
