#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {

   int externalMemory[100][4] = {0};

   string buffer = "Hello Student SY B This is OS Lab ";

   int index = 0;

   for (int i = 0; i < buffer.size(); i++) {

       externalMemory[index][i % 4] = buffer[i];

       if (i % 4 == 3) {

           index++;

       }

   }

   cout << "External memory locations and their content:\n"; 

    for (int i = 0; i < 100; i++) {

       cout << "Location " << setfill('0') << setw(2) << i << ": ";

       bool empty = true;

       for (int j = 0; j < 4; j++) {

           if (externalMemory[i][j] != 0) {

               cout << (char)externalMemory[i][j] << " ";

               empty = false;

           }

       }

       if (empty) {

           cout << "*";

       }

       cout << endl;

   }

   return 0;

}