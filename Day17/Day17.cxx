//
//  Advent of Code 2019 Solutions: Day 17
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day17.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <functional> //std::function
#include <sstream>
#include <unordered_map>

using namespace std;
namespace AocDay17 {

    static const std::string InputFileName = "Day17.txt";
    unordered_map<int64_t,int64_t> extraMemory;
    int64_t gRelativePC;
    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr);
    union cordinateTranslator{
        int32_t XY[2];
        int64_t both;
    };
    //1214 is too low
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        string outStr{"---"};
        int32_t lastPC = 0;
        auto outI = runProgram(x, args, outStr,&lastPC);
        auto lineLen = outStr.find('\n');
        size_t i = 0;
        vector<string> m;
        m.reserve(outStr.size()/lineLen);
        while(lineLen != string::npos) {
            m.emplace_back(outStr.begin()+i,outStr.begin()+lineLen);
            i = lineLen+1;
            lineLen = outStr.find('\n', i);
        }
        
		return to_string(getAlignmentSum(m));
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        string outStr{"---"};
        int32_t lastPC = 0;
        x[0] = 2;
        //Specific for my input
        vector<string> program {
        /*string mainProgram = */ "A,C,A,B,C,A,B,A,B,C\n",
        /*string functionA =   */ "L,12,L,8,L,8\n",
        /*string functionB =   */ "R,4,L,12,L,12,R,6\n",
        /*string functionC =   */ "L,12,R,4,L,12,R,6\n",
        /*string continuous =  */ "n\n"
        };
        
        for_each(program.begin(),program.end(),[&args](const string& p){appendCommandToArguments(args, p);});
        
        auto outI = runProgram(x, args, outStr,&lastPC);
//		return outStr;
        return to_string(outI.back());
    }
    
    int32_t getAlignmentSum(const std::vector<std::string>& inputMap) {
        int32_t sum = 0;
        for(int y = 1; y < inputMap.size() - 1; y++) {
            for(int x = 1; x < inputMap[y].size()-1;x++) {
                if(inputMap[y][x] == '#') {
                    if(inputMap[y][x-1] == '#' &&
                       inputMap[y][x+1] == '#' &&
                       inputMap[y+1][x] == '#' &&
                       inputMap[y-1][x] == '#') {
                        sum += y*x;
                    }
                }
            }
        }
        return sum;
    }
    
    void appendCommandToArguments(std::vector<int32_t>& args, const std::string& cmds) {
        for(const auto& c : cmds) {
            args.push_back(static_cast<int32_t>(c));
        }
    }
    
        vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr) {
            int64_t relativePC = gRelativePC;
    //        unordered_map<int64_t,int64_t> extraMemory;
            
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
