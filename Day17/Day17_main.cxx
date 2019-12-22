//
//  Advent of Code 2019 Main Runner: Day 17
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay17{
    extern std::string solvea();
    extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

    std::cout << "Day17" << "a: " << AocDay17::solvea() << std::endl;
    std::cout << "Day17" << "b: " << AocDay17::solveb() << std::endl;
    return 0;
}
