//
//  Advent of Code 2019 Tests: Day 8
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/08/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day08.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay08{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay08;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("---", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("---", solveb());
}

TEST(Example,Test1) {
	int x = 0;
	EXPECT_EQ(0,x);
}

TEST(Example,Test2) {
	int x = 0;
	EXPECT_EQ(0,x);
}

TEST(Example,Test3) {
	int x = 0;
	EXPECT_EQ(0,x);
}
