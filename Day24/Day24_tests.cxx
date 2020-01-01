//
//  Advent of Code 2019 Tests: Day 24
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/24/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day24.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay24{
    extern std::string solvea();
    extern std::string solveb();
}

using namespace std;
using namespace AocDay24;

TEST(Y2019_SolveDay24, FinalSolutionPartA) {
    EXPECT_EQ("1151290", solvea());
}

TEST(Y2019_SolveDay24, FinalSolutionPartB) {
    EXPECT_EQ("1953", solveb());
}

TEST(Y2019_Day24Example,Test1) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    processBugLife(x);
    ASSERT_EQ(5,x.size());
    EXPECT_EQ("#..#.",x[0]);
    EXPECT_EQ("####.",x[1]);
    EXPECT_EQ("###.#",x[2]);
    EXPECT_EQ("##.##",x[3]);
    EXPECT_EQ(".##..",x[4]);
}

TEST(Y2019_Day24Example,Test2) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    processBugLife(x);
    processBugLife(x);
    processBugLife(x);
    processBugLife(x);
    ASSERT_EQ(5,x.size());
    EXPECT_EQ("####.",x[0]);
    EXPECT_EQ("....#",x[1]);
    EXPECT_EQ("##..#",x[2]);
    EXPECT_EQ(".....",x[3]);
    EXPECT_EQ("##...",x[4]);
}

TEST(Y2019_Day24Example,Test3) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    watchForDuplicateLifecycle(x);
    ASSERT_EQ(5,x.size());
    EXPECT_EQ(".....",x[0]);
    EXPECT_EQ(".....",x[1]);
    EXPECT_EQ(".....",x[2]);
    EXPECT_EQ("#....",x[3]);
    EXPECT_EQ(".#...",x[4]);
}

TEST(Y2019_Day24Example,TestBiodiversityCalc) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    watchForDuplicateLifecycle(x);
    auto val = calculateBiodiversity(x);
    ASSERT_EQ(5,x.size());
    EXPECT_EQ(".....",x[0]);
    EXPECT_EQ(".....",x[1]);
    EXPECT_EQ(".....",x[2]);
    EXPECT_EQ("#....",x[3]);
    EXPECT_EQ(".#...",x[4]);
    EXPECT_EQ(2129920,val);
}

TEST(Y2019_Day24Example,TestCountBugs) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    InfiniteGrids ig;
    ig.push_back(x);
    ig.push_back(x);
    auto val = countBugs(ig);
    EXPECT_EQ(16, val);
}

TEST(Y2019_Day24Example,TestRecursiveLifecycle) {
    vector<string> x{
        "....#",
        "#..#.",
        "#..##",
        "..#..",
        "#...."
    };
    auto val = simulateRecursiveLifecycles(x, 10);
    
    EXPECT_EQ(99,val);
}
