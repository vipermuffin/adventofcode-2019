//
//  Advent of Code 2019 Tests: Day 1
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 11/30/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day01.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay01{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay01;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("3346639", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("5017110", solveb());
}

