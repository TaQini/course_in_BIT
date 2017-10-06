/*
 *  QUESTION:  Define MyString class with demands as follows:
 *  1.1  MyString can save any string;
 *  1.2  Overload operator+ to append string to another one;
 *  1.3  Define Find function to locate the position of searching a character;
 *  1.4  Define Mid function to get substring from one string;
 *  1.5  The client can use MyString you define like as in the main:
 *  
 *  void main(){
 *      MyString s1("China"), s2;
 *      s2 = "Love";
 *      cout << "I" + s2 + s1;
 *
 *		int pos = s1.Find('a');  // pos is 4, or zero if  'a'  is not found.
 *      int a = 1, b = 3;
 *      MyString my = s2.Mid(a, b);  // a represents starting position, 
 *      // b represents length. So Mid can get substring.
 *  }
 *  
 *  NOTE: The type, string and template in C++, and string 
 *  	  library in C are both FORBIDDEN in your program.
 *
 *  THINKING: 
 *  	   String in MyString must be allocated dynamically, so there is a pointer point to the string in class. 
 *  	   When the object are copyed to a new object by defalut copy function, the pointer will be copyed too.
 *  	   At that time, 2 pointer are point to the same place in memory. It will cause double free when destructor
 *  	   function called. So we need to overload operator "=" to allocate other place for new object.
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-04-05
*/

#include <iostream>
using namespace std;

class MyString{
    private:
        char *str; // string
        int len;   // length of string
    public:
        MyString(){len = 0;}
        MyString(const char s[]); 
        MyString(const int l);
        ~MyString();
        MyString &operator=(const MyString &s); // overload "="
        friend MyString operator+(const MyString &raw, const MyString &add);
        int Find(const char c); // get the position of target char
        MyString Mid(const int a, const int b); // get the substring start at a and length is b
        MyString Sub(const int a, const int b); // get the substring between a and b
        friend ostream& operator<<(ostream &os, const MyString &s); // overload "<<" to print string
        int size(){return len;} // an interface (not used in ep1.cpp)
};

MyString::MyString(const char s[]){
	for(len = 0; s[len]; len++); // length of string 
    str = new char[len]; // allocate a new space to stroage string
    for(int i = 0; i < len; i++)
        str[i] = s[i]; // copy content byte by byte
}

MyString::MyString(const int l){
	len = l;
	str = new char[len];
}

MyString & MyString::operator=(const MyString &s){
	len = s.len; // copy the length 
	str = new char[len]; // allocate a new space for new object 
	for(int i = 0; s.str[i]; i++)
		str[i] = s.str[i]; // copy content byte by byte
	return *this; // using for a = b = c = ...;
}

MyString::~MyString(){
	if (*str)  // if there are content in str, release it
		delete[] str; // free it
}

MyString operator+(const MyString &raw, const MyString &add) {
	MyString res(raw.len+add.len); // create a new MyString object whose len is sum of 2 string
	int i,j;
	for(i = 0; raw.str[i]; i++)
		res.str[i] = raw.str[i]; // copy string 'raw'
	for(j = 0; add.str[j]; j++)
		res.str[i+j] = add.str[j]; // copy string 'add' in the end of 'raw'
	return res;
}

int MyString::Find(const char c){
	int pos = len-1;
	while(str[pos] != c && pos) 
		pos--;
	return pos;
}

MyString MyString::Mid(const int a, const int b){
	MyString res(b); // create new object whose len is b
	for(int i = 0; i < res.len; i++)
		res.str[i] = str[a+i]; // copy substring byte by byte
	return res;
}

MyString MyString::Sub(const int a, const int b){
	MyString res(b-a+1); // create new object whose len is b-a+1
	for(int i = 0; i < res.len; i++)
		res.str[i] = str[a+i]; // copy substring byte by byte
	return res;
}

ostream& operator<<(ostream &os, const MyString &s){
	for(int i = 0; i < s.len; i++) os << s.str[i]; // print string 
	return os << endl; 
}

int main(){
   MyString s1("China"), s2;
   s2 = "Love";
   cout << "I" + s2 + s1;
      
   int pos = s1.Find('a');  // pos is 4, or zero if  'a'  is not found.
   cout << pos << endl;

   int a = 1, b = 3;
   MyString my = s2.Mid(a, b);  // a represents starting position, b represents length. So Mid can get substring.
   cout << my;

   MyString k;
   k = s1 + s2;
   cout << k << endl;
}
/* output information

ILoveChina
4
ove
ChinaLove
 */