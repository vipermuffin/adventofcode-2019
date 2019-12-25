//
//  Advent of Code 2019 Main Runner: Day 19
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay19{
    extern std::string solvea();
    extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

    std::cout << "Day19" << "a: " << AocDay19::solvea() << std::endl;
    std::cout << "Day19" << "b: " << AocDay19::solveb() << std::endl;
    return 0;
}
