#include "54_poker_hands.hpp"
#include <fstream>


int main()
{
    ifstream file;
    file.open("p054_poker.txt", ios::in);
    if (file.good()) {
        string line, code1, code2;
        int h1_wins = 0;
        while (getline(file, line)) {
            code1 = line.substr(0, 14);
            code2 = line.substr(15, 14);
            Hand h1(code1), h2(code2);
            if (h1 > h2)
                h1_wins++;
        }
        cout << "Player 1 wins: " << h1_wins << endl;
        file.close();
    }
    return 0;
}