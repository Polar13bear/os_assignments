#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    string line;
    ifstream inputfile("input.txt");
    while (!inputfile)
    {
        cout<<"File not found."<<endl;
        return 1;
    }
    while (getline(inputfile,line))
    {
        cout<<line<<endl;
    }
    inputfile.close();
    return 0;
}
