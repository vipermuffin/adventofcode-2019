//
//  Advent of Code 2019 Tests: Day 6
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/05/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day06.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay06{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay06;

TEST(SolvePartA, FinalSolution) {
    EXPECT_EQ("253104", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("499", solveb());
}

TEST(Example,Test1) {
    unordered_map<string, vector<string>> x;
    vector<string> inp{
        "COM)B",
        "B)C",
        "C)D",
        "D)E",
        "E)F",
        "B)G",
        "G)H",
        "D)I",
        "E)J",
        "J)K",
        "K)L"};
    buildTree(x, inp);
	EXPECT_EQ(8,x.size());
}

TEST(Example,Test2) {
    unordered_map<string, vector<string>> x;
    vector<string>outp;
    vector<string> inp{
        "COM)B",
        "B)C",
        "C)D",
        "D)E",
        "E)F",
        "B)G",
        "G)H",
        "D)I",
        "E)J",
        "J)K",
        "K)L"};
    buildTree(x, inp);
    parseTree("COM", x, outp);
	EXPECT_EQ(11,outp.size());
}

TEST(Example,Test3) {
    unordered_map<string, vector<string>> x;
    vector<string>outp;
    vector<string> inp{
        "COM)B",
        "B)C",
        "C)D",
        "D)E",
        "E)F",
        "B)G",
        "G)H",
        "D)I",
        "E)J",
        "J)K",
        "K)L"};
    buildTree(x, inp);
    parseTree("E", x, outp);
    EXPECT_EQ(4,outp.size());
}

TEST(Example,Test4) {
    unordered_map<string, vector<string>> x;
    vector<string>outp;
    vector<string> inp{
        "COM)B",
        "B)C",
        "C)D",
        "D)E",
        "E)F",
        "B)G",
        "G)H",
        "D)I",
        "E)J",
        "J)K",
        "K)L"};
    buildTree(x, inp);
    for(const auto& kvp : x) {
        parseTree(kvp.first, x, outp);
    }
    
    EXPECT_EQ(42,outp.size());
}

TEST(Example,Test5) {
    unordered_map<string, vector<string>> x;
    vector<string>outp;
    vector<string> inp{
        "COM)B",
        "B)C",
        "C)D",
        "D)E",
        "E)F",
        "B)G",
        "G)H",
        "D)I",
        "E)J",
        "J)K",
        "K)L",
        "K)YOU",
        "I)SAN"};
    buildTree(x, inp);
    
    EXPECT_EQ(4,findPath("YOU", "SAN", x));
}
