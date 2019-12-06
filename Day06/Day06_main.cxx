//
//  Advent of Code 2019 Main Runner: Day 6
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/05/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay06{
   extern std::string solvea();
   extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

	std::cout << "Day06" << "a: " << AocDay06::solvea() << std::endl;
	std::cout << "Day06" << "b: " << AocDay06::solveb() << std::endl;
	return 0;
}
