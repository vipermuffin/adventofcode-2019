//
//  Advent of Code 2019 Solutions: Day 7
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/07/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>

namespace AocDay07 {
//Function Definitions
    void runProgram(std::vector<int>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr = nullptr);
    int amplifierCircuit(const std::vector<int>& intops,const std::vector<int>& phases);
    int amplifierCircuitWithFeedback(const std::vector<int>& intops,const std::vector<int>& phases);
    int findMaxSignal(const std::vector<int>& intops, const int numCircuits, bool feedback = false);
}
