//
//  Advent of Code 2019 Solutions: Day 5
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/04/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day05.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <sstream>



using namespace std;
namespace AocDay05 {

	static const std::string InputFileName = "Day05.txt";
	std::string solvea() {
        auto inputF = parseFileForLines(InputFileName);
        auto input = parseCsvLineForNum(inputF[0]);
        vector<int> args{1};
        string outStr{"---"};
        runProgram(input,args,outStr);

		return outStr;
	}

	std::string solveb() {
        auto inputF = parseFileForLines(InputFileName);
        auto input = parseCsvLineForNum(inputF[0]);
        vector<int> args{5};
        string outStr{"---"};
        runProgram(input,args,outStr);
        
		return outStr;
	}
    
    void runProgram(std::vector<int>& intops,const std::vector<int>& stdIn, std::string& stdOut) {
        stringstream ss{};
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        vector<std::function<int(int*,int*,int*)>> ops = {
            [&itr](int*,int*,int*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](int*p1,int*p2,int*p3){*p3=*p1+*p2;return 4;},
            [](int*p1,int*p2,int*p3){*p3=*p1**p2;return 4;},
            [&inItr,&stdIn](int*p1,int*,int*){*p1=inItr != stdIn.end() ? *inItr++ : 0;return 2;},
            [&ss](int*p1,int*,int*){ss << *p1;return 2;},
            [&intops,&itr](int*p1,int*p2,int*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](int*p1,int*p2,int*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](int*p1,int*p2,int*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](int*p1,int*p2,int*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
        };
        
        while(itr <= intops.end() && *itr != 99) {
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
}
