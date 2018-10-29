//Functioning program using input/output files
//========================================= file = candycount.cpp =============
//=  A program to count the number of unique arrangements of candy.           =
//=============================================================================
//   Input: Reads from an input file input.txt                                =
//   Output: Writes to an output file output.txt                              =
//=---------------------------------------------------------------------------=
//=  Build: g++ -o candycount *.cpp                                           =
//=---------------------------------------------------------------------------=
//=  Execute: ./candycount                                                    =
//=---------------------------------------------------------------------------=
//=  Authors:                                                                 =
//=          Lily Tang                                                        =
//=          My Nguyen                                                        =
//=          Gericho Ball                                                     =
//=---------------------------------------------------------------------------=
//=  Notes:                                                                   =
//=          Input file must be named input.txt                               =
//=============================================================================
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <algorithm>
using namespace std;
 
//===== Sampler Function ===============================================================
// Returns the final number of possible combinations using iterative dynamic programming
// Unsigned long long was used to prevent overflow and to store 64-bits data
unsigned long long sampler(long long n, long long s, long long l){
  unsigned long long count[n + 1];
  int i;

  // Base cases
  count[0] = 1;
  count[1] = s;
  count[2] = s*s + l; 

  // For loop used for iterative dynamic programming
  for (i = 3; i <= n; i++){
    count[i] = s*count[i - 1] + l*count[i - 2]; 
  }
  
  return count[n]; 
}

//===== Main program  =================================================================
int main()
{
    vector<string> box;
    vector<unsigned long long> boxC;
    string line;

    // Number of cases in input file
    int cases = 0;

    // Reading from file 
    ifstream inputFile("input.txt");
    if(!inputFile){
        cout << "Error opening file" << endl;
        return -1;
    } 
    else {
        // Reach each character from file until end 
        // Store the value in a string vector
        while(getline(inputFile, line, '\n'))
        {
            box.push_back(line);
        }
        inputFile.close();
    }
    cases = atoi(box[0].c_str());
   
    // Writing to file by creating an output file
    ofstream outputFile("output.txt");
    if(!outputFile)  
    {
        cout << "Error opening file" << endl;
        return -1;
    }  
    
    //Loop goes through each string storing the values in an empty int vector, then calculates
    //the number of combinations, writes to output file then clears the vector to be used for the next string
    string token, iden;
    int i;
    for(i = 1; i < cases + 1; i++)
    {
        istringstream ss(box[i]);
        while(getline(ss,token, ' ')){
            long long val = atof(token.c_str());
            boxC.push_back(val);
        }

        outputFile << sampler(boxC[0], boxC[1], boxC[2]) << '\n';
        boxC.pop_back();
        boxC.pop_back();
        boxC.pop_back();
    }
    return 0;
}


