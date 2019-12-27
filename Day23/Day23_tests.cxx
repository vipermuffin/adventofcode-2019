//
//  Advent of Code 2019 Tests: Day 23
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/26/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day23.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay23{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay23;

TEST(Y2019_SolveDay23, FinalSolutionPartA) {
    EXPECT_EQ("24555", solvea());
}

TEST(Y2019_SolveDay23, FinalSolutionPartB) {
    EXPECT_EQ("19463", solveb());
}

TEST(Y2019_Day23Example,Test1) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day23Example,Test2) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day23Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
