//
//  Advent of Code 2019 Main Runner: Day 7
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/07/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>

namespace AocDay07{
   extern std::string solvea();
   extern std::string solveb();
}
using namespace std;

int main(int argc, char *argv[]) {

	std::cout << "Day07" << "a: " << AocDay07::solvea() << std::endl;
	std::cout << "Day07" << "b: " << AocDay07::solveb() << std::endl;
	return 0;
}
