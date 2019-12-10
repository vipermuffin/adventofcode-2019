//
//  Advent of Code 2019 Tests: Day 9
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/09/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day09.h"
#include "AoCUtils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

namespace AocDay09{
	extern std::string solvea();
	extern std::string solveb();
}

using namespace std;
using namespace AocDay09;

TEST(SolvePartA, FinalSolution) {
	EXPECT_EQ("2752191671", solvea());
}

TEST(SolvePartB, FinalSolution) {
	EXPECT_EQ("87571", solveb());
}

TEST(Example,Test1) {
    vector<long> x{1102,34915192,34915192,7,4,7,99,0};
    vector<int> args{};
    string outStr{"---"};
    runProgram(x, args, outStr);
	EXPECT_EQ(16,outStr.size());
}

TEST(Example,Test2) {
    vector<string> i{"104,1125899906842624,99"};
    auto x = parseCsvLineForLongNum(i[0]);
    vector<int> args{};
    string outStr{"---"};
    runProgram(x, args, outStr);
    EXPECT_EQ("1125899906842624",outStr);
}

TEST(Example,Test3) {
	vector<long> x{109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99};
    vector<int> args{};
    string outStr{"---"};
    runProgram(x, args, outStr);
    EXPECT_EQ("1091204-1100110011001008100161011006101099",outStr);
	EXPECT_EQ(16,x.size());
}


//Regression Tests
int amplifierCircuit(const std::vector<long>& intops,const std::vector<int>& phases) {
    vector<vector<long>> ops;
    ops.reserve(phases.size()*intops.size());
    string outp{"0"};
    vector<int> input{};
    
    for(int i = 0;i < phases.size();i++) {
        ops.push_back(intops);
        input.clear();
        input.push_back(phases[i]);
        input.push_back(stoi(outp));
        runProgram(ops[i], input, outp);
    }

    return stoi(outp);
}

int amplifierCircuitWithFeedback(const std::vector<long>& intops,const std::vector<int>& phases) {
    vector<vector<long>> ops;
    ops.reserve(phases.size()*intops.size());
    string outp{"0"};
    vector<int> input{};
    for(int i = 0;i < phases.size();i++) {
        ops.push_back(intops);
    }
    
    int lastPtr[] = {0,0,0,0,0};
    for(int i = 0;i < phases.size();i++) {
        input.clear();
        input.push_back(phases[i]);
        input.push_back(stoi(outp));
        runProgram(ops[i], input, outp,&lastPtr[i]);
    }
    
    while(lastPtr[0] != 0) {
        for(int i = 0;i < phases.size();i++) {
            input.clear();
            input.push_back(stoi(outp));
            runProgram(ops[i], input, outp,&lastPtr[i]);
        }
    }

    return stoi(outp);
}
int findMaxSignal(const std::vector<long>& intops, const int numCircuits, bool feedback=false);
int findMaxSignal(const std::vector<long>& intops, const int numCircuits, bool feedback) {
    vector<int> phases{};
    int x = 1;
    phases.reserve(numCircuits);
    int offset = feedback ? 5 : 0;
    for(int i = offset; i < numCircuits+offset; i++) {
        phases.push_back(i);
        x *= (i-offset+1);
    }
    
    vector<int> signals{};
    signals.reserve(x);
    
    do {
        signals.push_back(feedback ? amplifierCircuitWithFeedback(intops, phases) : amplifierCircuit(intops, phases));
    }while(std::next_permutation(phases.begin(), phases.end()));
    
    std::sort(signals.rbegin(),signals.rend());
    
    return signals[0];
}
TEST(Example,D7Test1) {
    vector<long> x{3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
    vector<int> p{4,3,2,1,0};
    EXPECT_EQ(43210,amplifierCircuit(x,p));
}

TEST(Example,D7Test1b) {
    vector<long> x{3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
    EXPECT_EQ(43210,findMaxSignal(x, 5));
}

TEST(Example,D7Test2) {
    vector<long> x{3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0};
    vector<int> p{0,1,2,3,4};
    EXPECT_EQ(54321,amplifierCircuit(x,p));
}

TEST(Example,D7Test2b) {
    vector<long> x{3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0};
    EXPECT_EQ(54321,findMaxSignal(x, 5));
}

TEST(Example,D7Test3) {
    vector<long> x{3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0};
    vector<int> p{1,0,4,3,2};
    EXPECT_EQ(65210,amplifierCircuit(x,p));
}

TEST(Example,D7Test3b) {
    vector<long> x{3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0};
    EXPECT_EQ(65210,findMaxSignal(x, 5));
}

TEST(Example,D7Test4) {
    vector<long> x{3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
    vector<int> p{9,8,7,6,5};
    EXPECT_EQ(139629729,amplifierCircuitWithFeedback(x,p));
}

TEST(Example,D7Test4b) {
    vector<long> x{3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
    EXPECT_EQ(139629729,findMaxSignal(x,5,true));
}

TEST(Example,D7Test5) {
    vector<long> x{3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
        -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
        53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10};
    vector<int> p{9,7,8,5,6};
    EXPECT_EQ(18216,amplifierCircuitWithFeedback(x,p));
}

TEST(Example,D7Test5b) {
    vector<long> x{3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
        -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
        53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10};
    EXPECT_EQ(18216,findMaxSignal(x,5,true));
}

TEST(Example,D5Test1) {
    vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForLongNum(inputF[0]);
    vector<int> args{8};
    string outStr{"---"};
    runProgram(input, args, outStr);
    EXPECT_EQ("1000",outStr);
}

TEST(Example,D5Test2) {
    vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForLongNum(inputF[0]);
    vector<int> args{7};
    string outStr{"---"};
    runProgram(input, args, outStr);
    EXPECT_EQ("999",outStr);
}

TEST(Example,D5Test3) {
    vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
    auto input = parseCsvLineForLongNum(inputF[0]);
    vector<int> args{9};
    string outStr{"---"};
    runProgram(input, args, outStr);
    EXPECT_EQ("1001",outStr);
}
