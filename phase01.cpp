#include<iostream>
#include<string>
#include<fstream>
#include <iomanip>
// #include<bits/stdc++.h>
using namespace std;
void init();
void Load();
void ExecuteUserProgram();
void MOS();
void printMemory();
void endWhile();
char IR[4];
char R[4];
int IC, SI;
bool toggle;
char memory[100][4];
fstream input;
fstream output;
int main(){
    input.open("input.txt", ios::in);
    output.open("output.txt", ios::out);
    Load();
    input.close();
    output.close();
    return 0;
}
void init(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            memory[i][j] = ' ';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = ' ';
        R[i] = ' ';
    }
}
void printMemory(){
    cout << "\nMemory Map:\n";
    for (int i = 0; i < 100; i++) {
        bool hasCharacter = false;
        
        for (int j = 0; j < 4; j++) {
            if (memory[i][j] != ' ') {
                hasCharacter = true;
                break;
            }
        }
        cout << setw(2) << setfill('0') << i << ": ";
        for (int j = 0; j < 4; j++) {
            if (memory[i][j] == ' ' && hasCharacter)
                cout << "  ";
            else if (memory[i][j] == ' ')
                cout << "* ";
            else
                cout << memory[i][j] << " ";
        }
        cout << endl;
    }
}
void endWhile(){
    cout << "Job ended." << endl;
}
void MOS(){
    if (SI == 1)
    {
        string buffer;
        getline(input, buffer);
        int k = 0;
        int add = (IR[2] - '0') * 10 + (IR[3] - '0');
        for (int i = 0; i < buffer.length() && i < 40; i++)
        {
            memory[add][k++] = buffer[i];
            if (k == 4)
            {
                k = 0;
                add++;
            }
        }
    }
    else if (SI == 2)
    {
        int add = (IR[2] - '0') * 10 + (IR[3] - '0');
        string out;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                out += memory[add][j];
            }
            add++;
        }
        output << out << '\n';
    }
    else if (SI == 3)
    {
        output << '\n';
    }
}
void ExecuteUserProgram(){
    int I = 0;
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = memory[I][i];
        }
        I++;
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (int i = 0; i < 4; i++)
            {
                R[i] = memory[add][i];
            }
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (int i = 0; i < 4; i++)
            {
                memory[add][i] = R[i];
            }
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int flag = 0;
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (int i = 0; i < 4; i++)
            {
                if (R[i] != memory[add][i])
                    flag = 1;
            }
            toggle = (flag == 0);
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int add = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (toggle)
            {
                I = add;
            }
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}
void Load(){
    string buffer;
    string line;
    int block = 0;
    bool isEOF = false;
    while (getline(input, buffer, '\n') && !isEOF)
    {
        line = buffer.substr(0, 4);
        if (line == "$AMJ")
        {
            cout << "\nProcessing new job\n";
            block = 0;
            buffer.clear();
            line.clear();
            init();
        }
        else if (line == "$DTA")
        {
            buffer.clear();
            line.clear();
            ExecuteUserProgram();
        }
        else if (line == "$END")
        {
            buffer.clear();
            line.clear();
            endWhile();
            printMemory();
            
        }
        else
        {
            if (block > 100)
            {
                cout << "Out of memory.";
            }
            else
            {
                int k = 0;
                for (int i = block; i < block + 10 && k < buffer.length(); i++)
                {
                    for (int j = 0; j < 4 && k < buffer.length(); j++)
                    {
                        if (buffer[k] == 'H')
                        {
                            memory[i][j] = buffer[k++];
                            break;
                        }
                        else
                        {
                            memory[i][j] = buffer[k++];
                        }
                    }
                }
                block += 10;
                line.clear();
            }
        }
        isEOF = input.eof();
    }
    cout << "\nAll jobs processed\n";
}