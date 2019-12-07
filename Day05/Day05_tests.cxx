//
//  Advent of Code 2019 Tests: Day 5
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/04/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day05.h"
#include "AoCUtils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay05{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay05;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("0000000008332629", solvea());
}

TEST(SolvePartB, FinalSolution) {
    EXPECT_EQ("8805067", solveb());
}

TEST(Example,Test1) {
	vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForNum(inputF[0]);
    vector<int> args{8};
    string outStr{"---"};
    runProgram(input, args, outStr);
	EXPECT_EQ("1000",outStr);
}

TEST(Example,Test2) {
    vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForNum(inputF[0]);
    vector<int> args{7};
    string outStr{"---"};
    runProgram(input, args, outStr);
    EXPECT_EQ("999",outStr);
}

TEST(Example,Test3) {
    vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForNum(inputF[0]);
    vector<int> args{9};
    string outStr{"---"};
    runProgram(input, args, outStr);
    EXPECT_EQ("1001",outStr);
}

