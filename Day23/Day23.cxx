//
//  Advent of Code 2019 Solutions: Day 23
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/26/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day23.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <array>
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <chrono>
//#include <fstream> //ifstream
#include <functional> //std::function
#include <thread>
#include <tuple>
#include <unordered_map>



using namespace std;
namespace AocDay23 {

    static const std::string InputFileName = "Day23.txt";
    using nicOutput = vector<tuple<int64_t,int64_t,int64_t>>;
    atomic<bool> isComplete{false};
    constexpr int NUM_COMPUTERS = 50;
    array<atomic<bool>,NUM_COMPUTERS> needsInput;

    void runProgram(std::vector<int64_t> intops,const std::vector<int64_t>& stdIn, nicOutput& stdOut);
    std::string solvea() {
        
        auto input = parseFileForLines(InputFileName);
        auto intops = parseCsvLineForLongNum(input[0]);
        array<vector<int64_t>,NUM_COMPUTERS> nicInput;
        array<nicOutput,NUM_COMPUTERS> output;
        array<nicOutput::iterator,NUM_COMPUTERS> outItrs;
        vector<thread> tV{};
        tV.reserve(NUM_COMPUTERS);
        isComplete = false;
        
        for(int i = 0;i < NUM_COMPUTERS;i++) {
            nicInput[i].reserve(1000);
            nicInput[i].push_back(i);
            output[i].reserve(1000);
            needsInput[i] = false;
            tV.emplace_back(runProgram, intops, std::cref(nicInput[i]), std::ref(output[i]));
            outItrs[i] = output[i].begin();
        }
        
        for(;;) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            for(int i = 0;i < NUM_COMPUTERS;i++) {
                if(outItrs[i] < output[i].end()) {
                    auto packet = *outItrs[i]++;
                    auto n = get<0>(packet);
                    auto x = get<1>(packet);
                    auto y = get<2>(packet);
                    if(n == 255) {
                        isComplete = true;
                        for_each(tV.begin(), tV.end(), [](thread& t){t.join();});
                        return to_string(y);
                    } else if (n >= 0 && n < NUM_COMPUTERS) {
//                        cout << "Packet Received from " << i << " --> " << n << " " << x << "," << y << endl;
                        needsInput[n] = false;
                        nicInput[n].push_back(x);
                        nicInput[n].push_back(y);
                    } else {
                        cout << "BOGUS Packet Received from " << i << " --> " << n << " " << x << "," << y << endl;
                    }
                }
            }
        }
		return "---";
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto intops = parseCsvLineForLongNum(input[0]);
        array<vector<int64_t>,NUM_COMPUTERS> nicInput;
        array<nicOutput,NUM_COMPUTERS> output;
        array<nicOutput::iterator,NUM_COMPUTERS> outItrs;
        vector<thread> tV{};
        tV.reserve(NUM_COMPUTERS);
        isComplete = false;
        int64_t lastNatYSent{0};
        int64_t natXVal{-1};
        int64_t natYVal{-1};
        
        for(int i = 0;i < NUM_COMPUTERS;i++) {
            nicInput[i].reserve(1000);
            nicInput[i].push_back(i);
            output[i].reserve(1000);
            needsInput[i] = false;
            tV.emplace_back(runProgram, intops, std::cref(nicInput[i]), std::ref(output[i]));
            outItrs[i] = output[i].begin();
        }
        
        for(;;) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            bool idle = true;
            for(int i = 0;i < NUM_COMPUTERS;i++) {
                if(outItrs[i] < output[i].end()) {
                    auto packet = *outItrs[i]++;
                    auto n = get<0>(packet);
                    auto x = get<1>(packet);
                    auto y = get<2>(packet);
                    if(n == 255) {
                        natXVal = x;
                        natYVal = y;
                    } else if (n >= 0 && n < NUM_COMPUTERS) {
//                        cout << "Packet Received from " << i << " --> " << n << " " << x << "," << y << endl;
                        needsInput[n] = false;
                        nicInput[n].push_back(x);
                        nicInput[n].push_back(y);
                    } else {
                        cout << "BOGUS Packet Received from " << i << " --> " << n << " " << x << "," << y << endl;
                    }
                    idle = false;
                }
                if(!needsInput[i]) {
                    idle = false;
                }
            }
            
            if(idle) {
                for_each(needsInput.begin(), needsInput.end(), [](atomic<bool>& ni){ni=false;});
                isComplete = lastNatYSent == natYVal;
                nicInput[0].push_back(natXVal);
                nicInput[0].push_back(natYVal);
                lastNatYSent = natYVal;
                if(isComplete) {
                    for_each(tV.begin(), tV.end(), [](thread& t){t.join();});
                    return to_string(lastNatYSent);
                }
            }
        }

		return "---";
    }

    void runProgram(std::vector<int64_t> intops,const std::vector<int64_t>& stdIn, nicOutput& stdOut) {
        int64_t relativePC = 0;
        unordered_map<int64_t,int64_t> extraMemory;
        
        vector<int64_t> outInts{};
        outInts.reserve(4);
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        auto id = *inItr;
        
        vector<std::function<int32_t(int64_t*,int64_t*,int64_t*)>> ops = {
            [&itr](int64_t*,int64_t*,int64_t*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1+*p2;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1**p2;return 4;},
            [&](int64_t*p1,int64_t*,int64_t*){if(inItr==stdIn.end()){needsInput[id]=true;*p1=-1;}else {*p1= *inItr++;} return 2;},
            [&outInts](int64_t*p1,int64_t*,int64_t*){outInts.push_back(*p1);return 2;},
            [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
            [&relativePC](int64_t*p1,int64_t*,int64_t*){relativePC += *p1; return 2;}
        };
        
        while(itr <= intops.end() && *itr != 99 && !isComplete) {
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
            
            if(outInts.size()==3) {
                stdOut.emplace_back(outInts[0],outInts[1],outInts[2]);
                outInts.clear();
            }
        }

    }
}
