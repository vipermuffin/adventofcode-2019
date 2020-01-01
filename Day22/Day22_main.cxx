//
//  Advent of Code 2019 Main Runner: Day 22
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/22/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay22{
    extern std::string solvea();
    extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

    std::cout << "Day22" << "a: " << AocDay22::solvea() << std::endl;
    std::cout << "Day22" << "b: " << AocDay22::solveb() << std::endl;
    return 0;
}
