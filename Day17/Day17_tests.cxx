//
//  Advent of Code 2019 Tests: Day 17
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day17.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay17{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay17;

TEST(Y2019_SolveDay17, FinalSolutionPartA) {
    EXPECT_EQ("6244", solvea());
}

TEST(Y2019_SolveDay17, FinalSolutionPartB) {
    EXPECT_EQ("1143523", solveb());
}

TEST(Y2019_Day17Example,Test1) {
    vector<string> m {
        "..#..........",
        "..#..........",
        "#######...###",
        "#.#...#...#.#",
        "#############",
        "..#...#...#..",
        "..#####...^.."
    };
    auto x = getAlignmentSum(m);
    EXPECT_EQ(76,x);
}

TEST(Y2019_Day17Example,Test2) {
    string cmds{"A,B,C,B,A,C\n"};
    vector<int32_t> actual;
    vector<int32_t> expected {
        65, 44, 66, 44, 67, 44, 66, 44, 65, 44, 67, 10
    };
    appendCommandToArguments(actual, cmds);
    ASSERT_EQ(expected.size(),actual.size());
    for(int i = 0; i < expected.size();i++) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(Y2019_Day17Example,Test3) {
    int x = 0;
    EXPECT_EQ(0,x);
}
