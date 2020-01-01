//
//  Advent of Code 2019 Solutions: Day 22
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/22/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day22.h"
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
//#include <thread>
//#include <tuple>
#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay22 {

    static const std::string InputFileName = "Day22.txt";
    std::string solvea() {
        constexpr int64_t standardSize = 10007;
        constexpr int64_t cardOfInterest = 2019;
        auto input = parseFileForLines(InputFileName);
        SpaceDeck sd{standardSize};
        for_each(input.begin(),input.end(),[&sd](const string& s){sd.shuffleMove(s);});
		return to_string(sd.cardPosition(cardOfInterest));
    }
    
    std::string solvea1() {
        int64_t standardSize = 10007;
        
        auto input = parseFileForLines(InputFileName);
        SpaceDeck sd{standardSize};
        int count = 0;
        bool done = false;
        while(!done) {
            for_each(input.begin(),input.end(),[&sd](const string& s){sd.shuffleMove(s);});
            count++;
            auto x = sd.cardAtPos(2020);
            cout << x << "," << count << endl;
            done = count == 100;
        }
        cout << endl;
        
        sd = SpaceDeck(10007);
        count = 0;
        done = false;
        while(!done) {
            for_each(input.begin(),input.end(),[&sd](const string& s){sd.shuffleMove(s);});
            count++;
            auto x = sd.cardAtPos(2020);
            cout << x << "," << count << endl;
            done = count == 100;
        }
        return to_string(count);
    }


    //2480 is too low
    std::string solveb() {
        constexpr int64_t standardSize = 429496729;
//        constexpr int64_t standardSize = 119315717514047;
        constexpr int64_t cardOfInterest = 2020;
        constexpr int64_t shuffleTimes = 101741582076661;
        array<int64_t,standardSize> x;
        for(int64_t i = 0;i < standardSize;i++) {
            x[i] = i;
        }
//        auto input = parseFileForLines(InputFileName);
//        SpaceDeck sd{cardOfInterest};
//        for_each(input.begin(),input.end(),[&sd](const string& s){sd.shuffleMove(s);});
//        return to_string(sd.cardPosition(cardOfInterest));
        return "---";
    }

#if 0
    class SpaceDeck {
    public:
        SpaceDeck() = delete;
        SpaceDeck(const int numCards);
        ~SpaceDeck() = default;
        void reset();
        void dealN(const int n);
        void cut(const int x);
        int cardAtPos(const int pos);
        size_t cardPosition(const int cardId);
        
    private:
        std::vector<int> cards;
        std::vector<int> tempStorage;
    };
#endif
    SpaceDeck::SpaceDeck(const int64_t numCards) {
        cards.resize(numCards, -1);
        tempStorage.resize(numCards, -1);
        reset();
    }
    
    void SpaceDeck::reset() {
        auto numCards = cards.size();
        for(auto i = 0;i < numCards;i++) {
            cards[i] = i;
        }
    }
    
    void SpaceDeck::dealN(const int64_t n) {
        if(n == 0) {
            std::reverse(cards.begin(), cards.end());
        } else {
            auto itr = cards.begin();
            int64_t index = 0;
            while(itr != cards.end()) {
                tempStorage[index] = *itr++;
                index += n;
                index %= tempStorage.size();
            }
            std::swap(cards,tempStorage);
        }
    }
    
    void SpaceDeck::cut(const int64_t x) {
        if(x > 0) {
            std::rotate(cards.begin(), cards.begin()+x, cards.end());
        } else {
            std::rotate(cards.rbegin(), cards.rbegin()-x, cards.rend());
        }
    }
    
    int64_t SpaceDeck::cardAtPos(const int64_t pos) {
        if(pos >= cards.size()) {
            return -1;
        }
        return cards[pos];
    }
    
    size_t SpaceDeck::cardPosition(const int64_t cardId) {
        auto it = std::find(cards.begin(), cards.end(), cardId);
        if(it == cards.end()) {
            return -1;
        }
        return it-cards.begin();
    }
    
    void SpaceDeck::shuffleMove(const std::string &description) {
        auto x = parseLineForWords(description);
        if(x[0] == "deal") {
            auto n = 0;
            if(x[1] == "with") {
                n = stoi(x.back());
            }
            dealN(n);
        } else if(x[0] == "cut") {
            auto n = stoi(x.back());
            cut(n);
        }
    }
    
    bool SpaceDeck::isReset() const {
        for(int64_t i = 0; i < cards.size();i++) {
            if(cards[i] != i) {
                return false;
            }
        }
        return true;
    }
}
