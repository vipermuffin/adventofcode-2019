//
//  Advent of Code 2019 Tests: Day 2
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/01/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day02.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay02{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay02;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("4330636", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("6086", solveb());
}

TEST(Example,Test1) {
    vector<int> x{1,9,10,3,2,3,11,0,99,30,40,50};
    runProgram(x);
	EXPECT_EQ(3500,x[0]);
}

TEST(Example,Test2) {
    vector<int> x{1,0,0,0,99};
    runProgram(x);
    EXPECT_EQ(2,x[0]);
}

TEST(Example,Test3) {
    vector<int> x{2,3,0,3,99};
    runProgram(x);
    EXPECT_EQ(6,x[3]);
}

TEST(Example,Test4) {
    vector<int> x{2,4,4,5,99,0};
    runProgram(x);
    EXPECT_EQ(9801,x[5]);
}

TEST(Example,Test5) {
    vector<int> x{1,1,1,4,99,5,6,0,99};
    runProgram(x);
    EXPECT_EQ(30,x[0]);
}
