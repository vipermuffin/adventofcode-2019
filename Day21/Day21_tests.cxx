//
//  Advent of Code 2019 Tests: Day 21
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/26/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day21.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay21{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay21;

TEST(Y2019_SolveDay21, FinalSolutionPartA) {
    EXPECT_EQ("19362822", solvea());
}

TEST(Y2019_SolveDay21, FinalSolutionPartB) {
    EXPECT_EQ("1143625214", solveb());
}

TEST(Y2019_Day21Example,Test1) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day21Example,Test2) {
    int x = 0;
    EXPECT_EQ(0,x);
}

TEST(Y2019_Day21Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
