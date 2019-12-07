//
//  Advent of Code 2019 Solutions: Day 7
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/07/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day07.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
//#include <array>
#include <climits>   //INT_MIN, INT_MAX, etc.
//#include <chrono>
//#include <iostream>
//#include <fstream> //ifstream
//#include <functional> //std::function
//#include <iomanip> //setfill setw hex
//#include <map>
//#include <math.h> //sqrt
//#include <numeric> //std::accumulate
//#include <queue>
//#include <regex>
//#include <set>
#include <sstream>
#include <thread>
//#include <tuple>
//#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay07 {

	static const std::string InputFileName = "Day07.txt";
	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto ops = parseCsvLineForNum(input[0]);
        
		return to_string(findMaxSignal(ops, 5));
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto ops = parseCsvLineForNum(input[0]);
        
        return to_string(findMaxSignal(ops, 5, true));
	}

    void runProgram(std::vector<int>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr) {
        stringstream ss{};
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        if(lastPtr != nullptr) {
            itr += *lastPtr;
            *lastPtr = 0;
        }
        bool needsInput{false};
        vector<std::function<int(int*,int*,int*)>> ops = {
            [&itr](int*,int*,int*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](int*p1,int*p2,int*p3){*p3=*p1+*p2;return 4;},
            [](int*p1,int*p2,int*p3){*p3=*p1**p2;return 4;},
            [&](int*p1,int*,int*){if(inItr==stdIn.end()){needsInput = true;if(lastPtr != nullptr) {*lastPtr = static_cast<int>(itr-intops.begin());}}else {*p1= *inItr++;} return 2;},
            [&ss](int*p1,int*,int*){ss << *p1;return 2;},
            [&intops,&itr](int*p1,int*p2,int*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](int*p1,int*p2,int*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](int*p1,int*p2,int*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](int*p1,int*p2,int*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
        };
        
        while(itr <= intops.end() && *itr != 99 && !needsInput) {
            int code = *itr %100;
            int pMode[3];
            pMode[0] = (*itr /100) % 10;
            pMode[1] = (*itr /1000) % 10;
            pMode[2] = (*itr /10000);
            int vals[] = {*(itr+1),*(itr+2)};
            int* params[3];
            params[0] = pMode[0] ? &vals[0] : &intops[*(itr+1)];
            params[1] = pMode[1] ? &vals[1] : &intops[*(itr+2)];
            params[2] = &intops[*(itr+3)];
            if(code < 0 || code >= ops.size()) {
                code = 0;
            }
            itr += ops[code](params[0],params[1],params[2]);
        }
        stdOut = ss.str();
    }
    
    int amplifierCircuit(const std::vector<int>& intops,const std::vector<int>& phases) {
        vector<vector<int>> ops;
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
    
    int amplifierCircuitWithFeedback(const std::vector<int>& intops,const std::vector<int>& phases) {
        vector<vector<int>> ops;
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
    
    int findMaxSignal(const std::vector<int>& intops, const int numCircuits, bool feedback) {
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
}
