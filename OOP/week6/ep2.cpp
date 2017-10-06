/*
 *  QUESTION: 
 *  	Define InternetURL class to save a URL string like as 
 *  	"www.bit.edu.cn"，and finish the demands as follows:
 *  	
 *  	2.1 Use MyString you just finished before to save URL string
 *   	2.2 Define member function getDomain() to get domain from URL.
 *   	 	 For example, we can get "www.bit.edu.cn" from "www.bit.edu.cn/jwc/080329.html";
 *   	2.3 Define member function 
 *   	 	 getDomainCountry() to get country name in the domain from URL, such as "us", "uk", etc.
 *    	  	 For example, we can get "cn" from "www.bit.edu.cn/jwc/080329.html"
 *     	2.4 Define member function getDomainType() to get domain type from URL, 
 *     		 such as "gov", "com", "org", and so on.For example, we can get
 *     		 "edu" from "www.bit.edu.cn/jwc/080329.html"；
 *      2.5 The client can use MyString you defined like as in the main:
 *      		void main() {
 *	       		InternetURL URL("www.bit.edu.cn/jwc/080329.html"), s2;
 *  			cout << URL.getDomain();         // The result is:  www.bit.edu.cn
 *  			cout << URL.getDomainCountry();  // The result is:  cn
 *  	    	cout << URL.getDomainType();     // The result is:  edu
 *  	     }
 *
 *  THINKING: just read the code.
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-04-05
*/

#include <iostream>
using namespace std;

/* 
class MyString is in ep1.cpp. If you want to complier 
ep2.cpp, pls copy the code of MyString class in ep1.cpp to ep2.cpp 
*/

class InternetURL{
    private:
        MyString url;
    public:
    	InternetURL(const MyString r){url = r;} // initilize url
    	InternetURL(){url = "";};// initilize url
        MyString getDomain();
        MyString getDomainCountry();
        MyString getDomainType();
};

MyString InternetURL::getDomain(){
	MyString res = url;
	while (res.Find('/')) // find the first '/' of url 
		res = res.Sub(0, res.Find('/')-1); // from begining to the first '/' 
	return res;
}

MyString InternetURL::getDomainCountry(){ // DomainCountry is the substring in the end of domain after '.'
	MyString res = getDomain(); // get the domain
	res = res.Sub(res.Find('.')+1,res.size()-1);// from the last '.' to the end of domain
	return res;
}

MyString InternetURL::getDomainType(){ // DomainCountry is the substring before DomainCountry 
	MyString res = getDomain(); 
	res = res.Sub(0,res.Find('.')-1); // substring without DomainCountry
	res = res.Sub(res.Find('.')+1,res.size()-1); //from the second last '.' to the end of domain
	return res;
}

int main(){
	InternetURL URL("www.bit.edu.cn/jwc/080329.html"), s2;
	cout << URL.getDomain();         // The result is:  www.bit.edu.cn
	cout << URL.getDomainCountry();  // The result is:  cn
    cout << URL.getDomainType();     // The result is:  edu
}
/* output information 

www.bit.edu.cn
cn
edu

*/