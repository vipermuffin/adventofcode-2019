//
//  Advent of Code 2019 Solutions: Day 9
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/09/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day09.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <sstream>
#include <unordered_map>


using namespace std;
namespace AocDay09 {

	static const std::string InputFileName = "Day09.txt";
	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{1};
        string outStr{"---"};
        runProgram(x, args, outStr);
		return outStr;
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{2};
        string outStr{"---"};
        runProgram(x, args, outStr);
        return outStr;
	}

    void runProgram(std::vector<long>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr) {
        long relativePC = 0;
        unordered_map<long,long> extraMemory;
        
        stringstream ss{};
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        if(lastPtr != nullptr) {
            itr += *lastPtr;
            *lastPtr = 0;
        }
        bool needsInput{false};
        vector<std::function<int(long*,long*,long*)>> ops = {
            [&itr](long*,long*,long*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](long*p1,long*p2,long*p3){*p3=*p1+*p2;return 4;},
            [](long*p1,long*p2,long*p3){*p3=*p1**p2;return 4;},
            [&](long*p1,long*,long*){if(inItr==stdIn.end()){needsInput = true;if(lastPtr != nullptr) {*lastPtr = static_cast<int>(itr-intops.begin());}}else {*p1= *inItr++;} return 2;},
            [&ss](long*p1,long*,long*){ss << *p1;return 2;},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](long*p1,long*p2,long*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](long*p1,long*p2,long*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
            [&relativePC](long*p1,long*,long*){relativePC += *p1; return 2;}
        };
        
        while(itr <= intops.end() && *itr != 99 && !needsInput) {
            int code = *itr %100;
            int pMode[3];
            pMode[0] = (*itr /100) % 10;
            pMode[1] = (*itr /1000) % 10;
            pMode[2] = (*itr /10000);
            long vals[] = {*(itr+1),*(itr+2),*(itr+3)};
            long* params[3];
            for(int i = 0; i < 3; i++) {
                long index = pMode[i] == 2 ? vals[i]+relativePC : vals[i];
                params[i] = pMode[i] == 1 ? &vals[i] : index >= intops.size() ? &extraMemory[index] : &intops[index];
            }
            
            if(code < 0 || code >= ops.size()) {
                code = 0;
            }
            itr += ops[code](params[0],params[1],params[2]);
        }
        stdOut = ss.str();
    }
}
