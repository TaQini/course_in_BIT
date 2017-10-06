/*
 *  QUESTION: Create a class, IntChar, to archieve an integer
 *			to save a string which length is no more than 4.
 * 			Suppose that a character length is 1 byte.
 *
 * 	For example: "Love", it's binary form associated with 
 *		an integer is: 0100 1100 0110 1111 0111 0110 0110 0101
 *      If the string length is less than 4 characters, the 
 *		remaining part is made up by zero.
 *
 *  NOTES:
 * 		(1) You can define appropriate member functions and variables;
 * 		(2) The string type in C++ is FORBIDDEN in the IntChar;
 * 		(3) In main, programmer can call member function in the following way.
 *
 * 	void main(){
 *      IntChar IC("Love");
 *
 *	    IC.ASC_Print(); // Print the content with string format:  Love
 *	    IC.Binary_Print(); // Print the content with binary format:  
 *      					// 0100 1100 0110 1111 0111 0110 0110 0101
 *	    IC.Int_Print(); // Print the content with integer format: 1282373221
 * 	}
 *
 *  THINKING: stroage ASCII text byte by byte to an integer array. Then it's 
 *  		  easy to convert integer to binary string (by shift optration).
 *  		  At last, convert the whole binary string to one integer.
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-22
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <cmath>
using namespace std;

class IntChar{
    private:
        vector<int> msg;
    public:
        IntChar(char *raw);
        ~IntChar();
        void ASC_Print();
        void Binary_Print();
        void Int_Print();
};

IntChar::IntChar(char *raw){
    char *p = raw; 
    //stroage string byte by byte in Integer
    for(int i=0; i<strlen(p); i++){
        msg.push_back((int)*(p+i)); 
        // char to integer
    }
}

IntChar::~IntChar(){
    msg.clear(); // release resoures
}

//print the ASCII of msg
void IntChar::ASC_Print(){ 
    for(int i=0; i<msg.size(); i++)
        cout << (char)msg[i];
    cout << endl;     
}

//print the binary string of msg
void IntChar::Binary_Print(){
    for(int i=0; i<msg.size(); i++)
        for(int j=7; j>=0; j--)
            cout << (msg[i]>>j&1);
    // print integer in binary
    cout << endl;
}

//print the integer namber of msg (encoded by int)
void IntChar::Int_Print(){
    long long res = 0;
    int w = msg.size()*8-1;
    // used to mark the weight of each bit of binary value
    for(int i=0; i<msg.size(); i++)
        for(int j=7; j>=0; j--){
            res = res + ((msg[i]>>j&1)*pow(2,w)); // bin to dec
            w--; // mark the next bit of binary string
        }
    cout << res << endl;
}

int main(){
	char* msg = "Apple";
    IntChar IC(msg);

    IC.ASC_Print(); 
    IC.Binary_Print();
    IC.Int_Print();
}
/* output information
$ ./ep3 
Love
01001100011011110111011001100101
1282373221

$ ./ep3 
Apple
0100000101110000011100000110110001100101
281059290213
*/