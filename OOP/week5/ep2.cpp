/*
 *  QUESTION: Create a class, LINT, to save a big integer which is no more than 100 digits.
 *  Define a member function to achieve the sum of two big numbers such as following:
 *	class LINT {
 *	private:
 *	    ...
 *	public:
 *	    LINT Add(const LINT&  L);  // Achieve the sum of two big numbers
 *	    void Print(); // Print a big integer
 *	    ...
 *	};
 *	
 *	NOTES: You can define appropriate member functions and variables.
 *  
 *  THINKING: 
 *   	1. Stroage big number in an array
 *  	2. Reversing string make Add operation easier
 *  	
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-29
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

class LINT{
    private:
        vector<int> s;
    public:
        LINT(){} // no args 
        LINT(const string raw); // get a big integer
        ~LINT(); 
        LINT Add(const LINT& L); // sum of two big numbers
        void Print(); // Print a big integer
};

LINT::LINT(const string raw){
    for(int i=0;i<raw.size();i++)
        s.push_back(raw[i]-'0'); 
    // stroage big number in an integer array
}

LINT::~LINT(){
	s.clear(); 
}

void LINT::Print(){
	if (s[0]) cout << s[0]; 
	// do not print 0 if it's in the front of num
    for(int i=1; i<s.size();i++)
        cout << s[i];
    cout << endl;
}

LINT LINT::Add(const LINT& L){
    LINT res;
    LINT tmp = L;

    // reverse 2 strings
    reverse(tmp.s.begin(),tmp.s.end()); // A
    reverse(s.begin(),s.end()); // B

    if ( s.size()<=tmp.s.size() ){ // len(A) < len(B)
        for (int i=0; i<s.size(); i++)
            res.s.push_back(s[i]+tmp.s[i]); 
        for (int i=s.size(); i<tmp.s.size(); i++)
            res.s.push_back(tmp.s[i]);
    }
    else{ // len(A) >= len(B) 
        for (int i=0; i<tmp.s.size(); i++)
            res.s.push_back(s[i]+tmp.s[i]);
        for (int i=tmp.s.size(); i<s.size(); i++)
            res.s.push_back(s[i]);
    }

    // calc the carry
    res.s.push_back(0); 
    for (int i=0; i<res.s.size(); i++){
        res.s[i+1] += res.s[i] / 10;
        res.s[i] = res.s[i] % 10;
    }

    // reverse result
    reverse(res.s.begin(), res.s.end());
    return res;
}

int main(int argc, char** argv){
    string a, b;
    cin >> a >> b;
    LINT n1 = a, n2 = b;
    
    LINT n3 = n1.Add(n2);
    n3.Print();
}
/* test information
$ ./ep2 
4 
5
9

$ ./ep2 
99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
1
100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

*/