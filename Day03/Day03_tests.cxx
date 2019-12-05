//
//  Advent of Code 2019 Tests: Day 3
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/02/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day03.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay03{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay03;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("273", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("15622", solveb());
}

TEST(Example,Test1) {
    string w1{"R8,U5,L5,D3"};
    string w2{"U7,R6,D4,L4"};
    auto x = findIntersections(w1, w2);
	EXPECT_EQ(2,x.size());
    EXPECT_EQ(6,x[0].first);
    EXPECT_EQ(5,x[0].second);
    EXPECT_EQ(3,x[1].first);
    EXPECT_EQ(3,x[1].second);
}


TEST(Example,Test2) {
    string w1{"R75,D30,R83,U83,L12,D49,R71,U7,L72"};
    string w2{"U62,R66,U55,R34,D71,R55,D58,R83"};
    auto x = findBestIntersections(w1, w2);
    EXPECT_EQ(610,x);
}

TEST(Example,Test3) {
    string w1{"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51"};
    string w2{"U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"};
    auto x = findBestIntersections(w1, w2);
    EXPECT_EQ(410,x);
}
