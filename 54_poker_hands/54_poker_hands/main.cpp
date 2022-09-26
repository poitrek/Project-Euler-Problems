// Problem no. 54: Poker hands
// ###### SOLVED ######

#include <fstream>
#include <iostream>

#include "Hand.h"
#include "tools.h"


int main()
{
    std::ifstream file;
    file.open("p054_poker.txt", std::ios::in);
    if (file.good()) {
        std::string line, code1, code2;
        int h1_wins = 0;
        while (std::getline(file, line)) {
            code1 = line.substr(0, 14);
            code2 = line.substr(15, 14);
            poker_hands::Hand h1(code1), h2(code2);
            if (h1 > h2)
                h1_wins++;
        }
        std::cout << "Player 1 wins: " << h1_wins << std::endl;
        file.close();
    }
    return 0;
}