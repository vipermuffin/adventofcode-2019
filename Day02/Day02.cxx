//
//  Advent of Code 2019 Solutions: Day 2
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/01/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day02.h"
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
//#include <thread>
//#include <tuple>
//#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay02 {

    std::vector<int> parseCsvLineForNum(const std::string& line)
    {
        vector<int> words{};
        stringstream ss{line};
        string word;
        while(getline(ss,word,',')) {
            words.push_back(stoi(word));
        }
        return words;
    }
    
	static const std::string InputFileName = "Day02.txt";
	std::string solvea() {
        auto inputF = parseFileForLines(InputFileName);
        auto input = parseCsvLineForNum(inputF[0]);
        input[1] = 60;
        input[2] = 0;
        auto itr = input.begin();
        while(itr <= input.end() && *itr != 99) {
            switch(*itr) {
                case 1:
                    input[*(itr+3)] = input[*(itr+1)]+input[*(itr+2)];
                    break;
                    
                case 2:
                    input[*(itr+3)] = input[*(itr+1)]*input[*(itr+2)];
                    break;
                    
                default:
                    cout << "ERROR: Op code Undefinded: " << *itr << endl;
                    break;
            }
            itr +=4;
        }
		return to_string(input[0]);
	}

	std::string solveb() {
        auto inputF = parseFileForLines(InputFileName);
        bool nounFound = false;
        bool done = false;
        int noun{0},verb{0};
        
        while(!done) {
            auto input = parseCsvLineForNum(inputF[0]);
            input[1] = noun;
            input[2] = verb;
            auto itr = input.begin();
            while(itr <= input.end() && *itr != 99) {
                switch(*itr) {
                    case 1:
                        input[*(itr+3)] = input[*(itr+1)]+input[*(itr+2)];
                        break;
                        
                    case 2:
                        input[*(itr+3)] = input[*(itr+1)]*input[*(itr+2)];
                        break;
                        
                    default:
                        cout << "ERROR: Op code Undefinded: " << *itr << endl;
                        break;
                }
                itr +=4;
            }
            
            done = input[0] == 19690720;
            if(!done) {
                //noun has bigger jumps, search first
                if(nounFound) {
                    verb++;
                } else {
                    if(input[0] > 19690720) {
                        noun--;
                        nounFound = true;
                        verb++;
                    } else {
                        noun++;
                    }
                }
            }
        }

        return to_string(noun*100+verb);
	}

}
