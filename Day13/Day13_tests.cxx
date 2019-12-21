//
//  Advent of Code 2019 Tests: Day 13
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/13/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day13.h"
#include "gtest/gtest.h"
#include <functional>
#include <iostream>
#include <string>

namespace AocDay13{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay13;

TEST(Y2019_SolveDay13, FinalSolutionPartA) {
    EXPECT_EQ("301", solvea());
}

TEST(Y2019_SolveDay13, FinalSolutionPartB) {
    EXPECT_EQ("14096", solveb());
}

TEST(Y2019_Day13Example,Test1) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day13Example,Test2) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day13Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
