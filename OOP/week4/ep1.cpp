/*
 *  QUESTION: Here is the codes：
 *
 *	#include <iostream>
 * 	using namespace std;
 *  int main(){
 *  	cout << "Hello World!\n";
 *  }
 *  
 *  Add some codes and get the results as follows:
 *
 *	Initialize
 * 	Hello, World!
 *  Clear up
 *
 *  NOTES: Don't modify the MAIN function any way! 
 *  
 *  THINKING: 2 method:
 *  1. class's constructor and destructor
 *  2. def __attribute__ ((constructor))
 * 
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-22
*/

//method 1:
#include <iostream>
using namespace std;

class MyClass{
    public:
        MyClass();
        ~MyClass();
};

MyClass::MyClass(){
    cout << "Initialize" << endl;
}

MyClass::~MyClass(){
    cout << "Clear up" << endl;
}

MyClass test;

int main(){
    cout << "Hello World!\n";
}

// method 2:
#include <iostream>
#include <unistd.h>
using namespace std;

void init () __attribute__ ((constructor));
void clean () __attribute__ ((destructor));

void init (){
    write(1,"Initialize\n",12);
}

void clean (){
    write(1,"Clean up\n",10);
}

int main(){
    cout << "Hello World!\n";
}
