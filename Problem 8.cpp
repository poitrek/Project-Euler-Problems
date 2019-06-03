#include<iostream>
#include<fstream>
using namespace std;

string download()
{
    ifstream plik;
    plik.open("dane.txt");
    string s;
    plik >> s;
    plik.close();
    return s;
}

int main()
{
    string s = download();
    return 0;
}
