//
//  Advent of Code 2019 Tests: Day 4
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/03/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day04.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay04{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay04;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("979", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("635", solveb());
}

TEST(Example,TestPart1) {
    EXPECT_TRUE(passwordIsValid("111111"));
    EXPECT_FALSE(passwordIsValid("223450"));
    EXPECT_FALSE(passwordIsValid("123789"));
}

TEST(Example,TestPart2) {
    EXPECT_FALSE(passwordIsValid2("111111"));
    EXPECT_FALSE(passwordIsValid2("223450"));
    EXPECT_FALSE(passwordIsValid2("123789"));
    EXPECT_TRUE(passwordIsValid2("112233"));
    EXPECT_FALSE(passwordIsValid2("123444"));
    EXPECT_TRUE(passwordIsValid2("111122"));
}
