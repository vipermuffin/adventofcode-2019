//
//  Advent of Code 2019 Tests: Day 11
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/11/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day11.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay11{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay11;

TEST(Y2019_SolveDay11, FinalSolutionPartA) {
    EXPECT_EQ("1967", solvea());
}

TEST(Y2019_SolveDay11, FinalSolutionPartB) {
    EXPECT_EQ("---", solveb());
}

TEST(Y2019_Day11Example,Test1) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day11Example,Test2) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day11Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
