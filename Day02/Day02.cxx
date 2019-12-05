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
#include <climits>   //INT_MIN, INT_MAX, etc.



using namespace std;
namespace AocDay02 {

	static const std::string InputFileName = "Day02.txt";
	std::string solvea() {
        auto inputF = parseFileForLines(InputFileName);
        auto input = parseCsvLineForNum(inputF[0]);
        input[1] = 12;
        input[2] = 2;
        
        runProgram(input);
        
		return to_string(input[0]);
	}

	std::string solveb() {
        auto inputF = parseFileForLines(InputFileName);
        constexpr int MAGIC_OUTPUT = 19690720;
        constexpr int RANGE = 100;
        auto initOps = parseCsvLineForNum(inputF[0]);
        
        //Instead of iterating through all search a little smarter
        // - Start with course adjustments, then fine adjustments
        //Determine which gives bigger jumps
        auto i1{initOps};
        i1[1] = 1;
        i1[2] = 0;
        runProgram(i1);
        auto i2{initOps};
        i2[1] = 0;
        i2[2] = 1;
        
        bool nounBigger = i1[0] > i2[0];
        
        //Find combo that generates magical output
        int noun{0},verb{0};
        int x{0},y{0},z{0};
        bool found{false};
        while(z!= MAGIC_OUTPUT && x < RANGE && y < RANGE) {
            if(!found && z > MAGIC_OUTPUT) {
                //value that goes past magic output found, go back below and search slower
                found = true;
                x--;
            }
            found ? y++ : x++;
            auto input{initOps};
            input[1] = nounBigger ? x : y;
            input[2] = nounBigger ? y : x;
            runProgram(input);
            z = input[0];
        }
        noun = nounBigger ? x : y;
        verb = nounBigger ? y : x;

        return to_string(noun*100+verb);
	}

    void runProgram(std::vector<int>& intops) {
        auto itr = intops.begin();
        while(itr <= intops.end() && *itr != 99) {
            switch(*itr) {
                case 1:
                    intops[*(itr+3)] = intops[*(itr+1)]+intops[*(itr+2)];
                    break;
                    
                case 2:
                    intops[*(itr+3)] = intops[*(itr+1)]*intops[*(itr+2)];
                    break;
                    
                default:
                    cerr << "ERROR: Op code Undefinded: " << *itr << endl;
                    break;
            }
            itr +=4;
        }
    }
}
