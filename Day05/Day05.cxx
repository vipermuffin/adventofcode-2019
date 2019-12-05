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
//#include <sstream>
//#include <thread>
//#include <tuple>
//#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay05 {

	static const std::string InputFileName = "Day05.txt";
	std::string solvea() {
        auto inputF = parseFileForLines(InputFileName);
        auto input = parseCsvLineForNum(inputF[0]);
        
        runProgram(input);

		return "---";
	}

	std::string solveb() {
        auto inputF = parseFileForLines(InputFileName);
//        vector<string> inputF = {"3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,        1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,        999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"};
        auto input = parseCsvLineForNum(inputF[0]);
        
        runProgram(input);
		return "---";
	}
    
    void runProgram(std::vector<int>& intops) {
        auto itr = intops.begin();
        while(itr <= intops.end() && *itr != 99) {
            int code = *itr %100;
            int pMode[3];
            pMode[0] = (*itr /100) % 10;
            pMode[1] = (*itr /1000) % 10;
            pMode[2] = (*itr /10000);
            int vals[] = {*(itr+1),*(itr+2)};
            int* params[2];
            params[0] = pMode[0] ? &vals[0] : &intops[*(itr+1)];
            params[1] = pMode[1] ? &vals[1] : &intops[*(itr+2)];
            
            switch(code) {
                case 1:
                    intops[*(itr+3)] = *params[0]+*params[1];
                    itr +=4;
                    break;
                    
                case 2:
                    intops[*(itr+3)] = *params[0]**params[1];
                    itr +=4;
                    break;
                    
                case 3:
                    int inVal;
                    cin >> inVal;
                    intops[*(itr+1)] = inVal;
                    itr += 2;
                    break;
                    
                case 4:
                    cout << *params[0];
                    itr += 2;
                    break;
                    
                case 5:
                    if(*params[0] != 0) {
                        itr = intops.begin()+*params[1];
                    } else {
                        itr += 3;
                    }
                    break;
                    
                case 6:
                    if(*params[0] == 0) {
                        itr = intops.begin()+*params[1];
                    } else {
                        itr += 3;
                    }
                    break;
                    
                case 7:
                    if(*params[0] < *params[1]) {
                        intops[*(itr+3)] = 1;
                    } else {
                        intops[*(itr+3)] = 0;
                    }
                    itr +=4;
                    break;
                    
                case 8:
                    if(*params[0] == *params[1]) {
                        intops[*(itr+3)] = 1;
                    } else {
                        intops[*(itr+3)] = 0;
                    }
                    itr +=4;
                    break;
                    
                default:
                    cerr << "ERROR: Op code Undefinded: " << *itr << endl;
                    itr +=4;
                    break;
            }
        }
    }

}
