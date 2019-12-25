//
//  Advent of Code 2019 Tests: Day 19
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day19.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay19{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay19;

TEST(Y2019_SolveDay19, FinalSolutionPartA) {
    EXPECT_EQ("215", solvea());
}

TEST(Y2019_SolveDay19, FinalSolutionPartB) {
    EXPECT_EQ("7720975", solveb());
}

TEST(Y2019_Day19Example,Test1) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day19Example,Test2) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day19Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
