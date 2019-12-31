//
//  Advent of Code 2019 Solutions: Day 21
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/26/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day21.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <functional> //std::function
#include <sstream>
#include <unordered_map>



using namespace std;
namespace AocDay21 {

    static const std::string InputFileName = "Day21.txt";
    void appendCommandToArguments(std::vector<int32_t>& args, const std::string& cmds);
    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr);

    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        string outStr{"---"};
        int32_t lastPC = 0;
        //Specific for my input
        vector<string> program {
            "NOT C T\n",
            "OR D J\n",
            "AND T J\n",
            "NOT A T\n",
            "OR T J\n",
            "WALK\n",
        };

        
        for_each(program.begin(),program.end(),[&args](const string& p){appendCommandToArguments(args, p);});
        
        auto outI = runProgram(x, args, outStr,&lastPC);
//                return outStr;
        return to_string(outI.back());

		return "---";
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        string outStr{"---"};
        int32_t lastPC = 0;
        //Specific for my input
        vector<string> program {
            "NOT B T\n",
            "AND C T\n",
            "AND D T\n",
            "OR T J\n",
            "NOT C T\n",
            "AND D T\n",
            "AND H T\n",
            "AND A T\n",
            "OR T J\n",
            "NOT A T\n"
            "OR T J\n",
            "RUN\n",
        };
        
        for_each(program.begin(),program.end(),[&args](const string& p){appendCommandToArguments(args, p);});
        
        auto outI = runProgram(x, args, outStr,&lastPC);
//        return outStr;
        return to_string(outI.back());
		return "---";
    }
    
    void appendCommandToArguments(std::vector<int32_t>& args, const std::string& cmds) {
        for(const auto& c : cmds) {
            args.push_back(static_cast<int32_t>(c));
        }
    }
    
    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr) {
        int64_t relativePC = 0;
        unordered_map<int64_t,int64_t> extraMemory;
        
        stringstream ss{};
        vector<int64_t> outInts{};
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        if(lastPtr != nullptr) {
            if(*lastPtr > 0) {
                itr += *lastPtr;
            }
            *lastPtr = 0;
        }
        bool needsInput{false};
        vector<std::function<int32_t(int64_t*,int64_t*,int64_t*)>> ops = {
            [&itr](int64_t*,int64_t*,int64_t*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1+*p2;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1**p2;return 4;},
            [&](int64_t*p1,int64_t*,int64_t*){if(inItr==stdIn.end()){needsInput = true;if(lastPtr != nullptr) {*lastPtr = static_cast<int32_t>(itr-intops.begin());if(*lastPtr == 0) {*lastPtr = -1;}}}else {*p1= *inItr++;} return 2;},
            [&ss,&outInts](int64_t*p1,int64_t*,int64_t*){if(*p1 < 128) {ss << static_cast<char>(*p1);} else {ss << *p1;}outInts.push_back(*p1);return 2;},
            [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
            [&relativePC](int64_t*p1,int64_t*,int64_t*){relativePC += *p1; return 2;}
        };
        
        while(itr <= intops.end() && *itr != 99 && !needsInput) {
            int32_t code = *itr %100;
            int32_t pMode[3];
            pMode[0] = (*itr /100) % 10;
            pMode[1] = (*itr /1000) % 10;
            pMode[2] = (*itr /10000);
            int64_t vals[] = {*(itr+1),*(itr+2),*(itr+3)};
            int64_t* params[3];
            for(int32_t i = 0; i < 3; i++) {
                int64_t index = pMode[i] == 2 ? vals[i]+relativePC : vals[i];
                params[i] = pMode[i] == 1 ? &vals[i] : index >= intops.size() ? &extraMemory[index] : &intops[index];
            }
            
            if(code < 0 || code >= ops.size()) {
                code = 0;
            }
            itr += ops[code](params[0],params[1],params[2]);
        }
        stdOut = ss.str();
        return outInts;
    }
}
