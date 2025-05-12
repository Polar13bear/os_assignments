#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


char R[4];
char IR[4];
int IC;
int C;
char M[100][4] = {}; 

void INIT() {
    IC = '*';
    C = '*';
    for (int i = 0; i < 4; i++) {
        R[i] = '*';
        IR[i] = '*';
    }

    cout << "content of R: ";
    for (int i = 0; i < 4; i++) {
        cout << R[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 100; i++) {
        cout << "Location " << setfill('0') << setw(2) << i << ": ";
        for (int j = 0; j < 4; j++) {
            cout << "*" << " ";
        }
        cout << endl;
    }
}

void endWhile() {

}
void EUP(){

}
void startExecutionModule() {
    IC=0;
    EUP();

    for(int i=0;i<4;i++){
        
    }
}
void read(){

}
void write(){

}

int main() {
    ifstream inputfile("input.txt");
    string line;
    int roww = 20, coll = 0;
    while (getline(inputfile, line)) {  
        cout << line << endl;
        
        if (line.substr(0, 4) == "$AMJ") {
            INIT();  
        }
        else if (line.substr(0, 2) == "GD") {
            
            string temp = line;
            char buffer[40] = {};
            int idx = 0;
            int l = 0;
            
            
            while (l < temp.size()) {
                while (l < temp.size() && temp[l] != ' ') {
                    buffer[idx++] = temp[l++];
                }
                if (idx >= 40) break; 
                
                l++;
            }
            

            int row = 0, col = 0;
            for (int i = 0; i < 40; i++) {
                M[row][col] = buffer[i];
                col++;
                if (col == 4) {
                    row++;
                    col = 0;
                }
            }
           
            for (int i = 0; i < 100; i++) {
                cout << "Location " << setfill('0') << setw(2) << i << ": ";
                bool check = true;
                for (int j = 0; j < 4; j++) {
                    if (M[i][j] != 0) {
                        cout << M[i][j] << " ";
                        check = false;
                    }
                }
                if (check) {
                    cout << "* * * *";
                }
                cout << endl;
            }
        }
        else if (line.substr(0, 4) == "$END") {
            endWhile();  
        }
        else if (line.substr(0, 4) == "$DTA") {
            startExecutionModule();  
        }
        else {
            
            if (line.substr(0, 2) != "GD" && line.substr(0, 2) != "PD") {
                string temp = line;
                char buffer[40] = {};
                int len =temp.length(); 

                for (int i = 0; i < len; i++) {
                    buffer[i] = temp[i];
                }

                char M1[100][4] = {};
                for (int i = 0; i < 40; i++) {
                    M[roww][coll] = buffer[i];
                    coll++;
                    if (coll == 4) {
                        roww++;
                        coll = 0;
                    }
                }
                //roww+=9;
                for (int i = 0; i < 100; i++) {
                    cout << "Location " << setfill('0') << setw(2) << i << ": ";
                    bool check = true;
                    for (int j = 0; j < 4; j++) {
                        if (M[i][j] != 0) {
                            cout << M[i][j] << " ";
                            check = false;
                        }
                    }
                    if (check) {
                        cout << "* * * *";
                    }
                    cout << endl;
                }
            }
            write();
        }
    }

    //    char ch;
    //    int idx=0;
    //    while(inputfile.get(ch)){
    //        if(idx<100){
    //            buffer[idx]=ch;
    //            idx++;
    //        }
    //    }

    //    for(int i=0;i<100;i++){
    //        cout<<buffer[i]<<" ";
    //    }


    return 0;
}