//
//  Advent of Code 2019 Solutions: Day 16
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/16/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day16.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <array>
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
//#include <sstream>
#include <thread>
//#include <tuple>
//#include <unordered_map>
//#include <unordered_set>
//#define THREADED

using namespace std;
namespace AocDay16 {

    static const std::string InputFileName = "Day16.txt";
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto s = performFFT(input[0], 100);
        auto os = string(s.begin(),s.begin()+8);
		return os;
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto osp = string(input[0].begin(),input[0].begin()+7);
        auto z = stoi(osp);
        auto s = performFFT2(input[0], 100, 10000,z);
        auto os = string(s.begin(),s.begin()+8);
		return os;
    }

#if 1
        void computePhase(const std::string& input, int z, const int sz, const int mul, const int offset, char* output) {
            const char base = '0';
            const array<int, 4> bp{0,1,0,-1};
            int32_t sum = 0;
            
            int j = z;
            for(j = z; j < sz*mul;j++) {
                int x = ((j+1)/(z+1))&3;
                if(x&1) {
                    auto idx = (j-offset);
                    sum += static_cast<int>(input[idx]-base)*bp[x];
                }
            }
            sum %= 10;
            *output = base + static_cast<char>(sum < 0 ? -sum : sum);
        }
        
        std::string performFFT2(std::string inputSignal, int iterations, const int mul, const int offset) {
            array<int, 4> bp{0,1,0,-1};
            const char base = '0';
            const auto sz = inputSignal.size();
            string outputSignal;
            if(mul > 1) {
                outputSignal = string(sz*mul-offset,'0');
                auto outpItr = outputSignal.begin();
                auto inItr = inputSignal.begin()+offset%sz;
                while(outpItr != outputSignal.end()) {
                    if(inItr == inputSignal.end()) {
                        inItr = inputSignal.begin();
                    }
                    *outpItr++ = *inItr++;
                }
                inputSignal = outputSignal;
            }else{
                outputSignal = inputSignal;
            }

            vector<thread> tV;
            tV.reserve(12);
            for(int i = 1;i <= iterations;i++) {
                std::swap(inputSignal,outputSignal);
                
                for(int z = offset; z < sz*mul;z++) {
                    tV.emplace_back(computePhase,std::ref(inputSignal),z,sz,mul,offset,&outputSignal[z-offset]);
                    if(tV.size() == 12) {
                        for_each(tV.begin(),tV.end(),[](std::thread& t){if(t.joinable()){ t.join();}});
                        tV.clear();
                    }
                    
//                    int32_t sum = 0;
//                    int j = z;
//                    for(j = z; j < sz*mul;j++) {
//                        int x = ((j+1)/(z+1))&3;
//                        if(x&1) {
//                            auto idx = (j-offset);
//                            sum += static_cast<int>(inputSignal[idx]-base)*bp[x];
//                        }
//                    }
//                    sum %= 10;
//                    outputSignal[z-offset] = base + static_cast<char>(sum < 0 ? -sum : sum);
                }
                if(tV.size() > 0) {
                    for_each(tV.begin(),tV.end(),[](std::thread& t){if(t.joinable()){ t.join();}});
                }
            }
            return outputSignal;
        }
#endif

#if 1
        std::string performFFT(std::string inputSignal, int iterations) {
            array<int, 4> bp{0,1,0,-1};
            const char base = '0';
            string outputSignal{inputSignal};
            
            for(int i = 1;i <= iterations;i++) {
                std::swap(inputSignal,outputSignal);
                for(int z = 0; z < inputSignal.size();z++) {
                    int sum = 0;
                    for(int j = z; j < inputSignal.size();j++) {
                        int x = ((j+1)/(z+1))&3;
                        if(x&1) {
                            auto idx = j%inputSignal.size();
                            sum += static_cast<int>(inputSignal[idx]-base)*bp[x];
                        }
                    }
                    sum %= 10;
                    outputSignal[z%inputSignal.size()] = base + static_cast<char>(sum < 0 ? -sum : sum);
                }
            }
            return outputSignal;
        }
#endif

}
