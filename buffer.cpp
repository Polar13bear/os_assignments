#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
using namespace std;
int main(int argc, char const *argv[])
{
    string line;
    char buffer[256];
    ifstream inputfile("input.txt");
    while (!inputfile)
    {
        cout<<"File not found."<<endl;
        return 1;
    }
    while (getline(inputfile,line))
    {
        strcpy(buffer, line.c_str());
        cout << "Buffer contains: " << buffer << endl;
    }
    inputfile.close();
    return 0;
}
