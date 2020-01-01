//
//  Advent of Code 2019 Tests: Day 15
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/31/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day15.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay15{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay15;

TEST(Y2019_SolveDay15, FinalSolutionPartA) {
    EXPECT_EQ("232", solvea());
}

TEST(Y2019_SolveDay15, FinalSolutionPartB) {
    EXPECT_EQ("320", solveb());
}

