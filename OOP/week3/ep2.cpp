/*
 *  QUESTION: Create a program that opens a text file in English and 
 *  counts the words number in that file.
 *  NOTE: Words are seperated by spaces.
 *
 *  THINKING: Two method:
 *  1.using linux command wc (word count) to count the word of text
 *  2.using ifstream
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-15
*/

// method 1
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(){
    string cmd; // command to call
    cout << "please input file name: ";
    cin >> cmd;
    cmd = "wc -w " + cmd; // use wc (word count) command to count words
//    cout << cmd.c_str() << endl; // debug information
    system(cmd.c_str());
}

// method 2
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    string filename; 
    string tmp;
    int cnt = 0; // the counter
    cout << "please input file name: ";
    cin >> filename; //get filename
    ifstream fin(filename.c_str()); // open file
    while (fin >> tmp) if (tmp.c_str()[0] > '9' || tmp.c_str()[0] < '0') cnt ++; // count
    cout << cnt << endl;
}

/* output information

$ ./ep2 
please input file name: tmp.txt
218

*/
