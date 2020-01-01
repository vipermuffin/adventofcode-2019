//
//  Advent of Code 2019 Main Runner: Day 24
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/24/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay24{
    extern std::string solvea();
    extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

    std::cout << "Day24" << "a: " << AocDay24::solvea() << std::endl;
    std::cout << "Day24" << "b: " << AocDay24::solveb() << std::endl;
    return 0;
}
