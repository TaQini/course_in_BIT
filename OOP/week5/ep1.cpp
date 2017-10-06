/*
 *  QUESTION: Give the outputs and explain how to get the results.
 *
 *  THINKING: My complier is g++ 4.8.4
 *  
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-29
*/

#include <iostream>
using namespace std;

class TPoint{
public:
     TPoint(int x,int y) {X=x;Y=y;}
     TPoint(TPoint& p);		//copy constructor
     ~TPoint() {cout<<"Destructor called."<<endl;}
     int Xcoord() {return X;}
     int Ycoord() {return Y;}
private:
     int X,Y;
};

TPoint::TPoint(TPoint& p){
     X=p.X;
     Y=p.Y;
     cout<<"Copy_initialization Constructor called.\n";
}

TPoint Value(TPoint Q){   // Pass by data value
     cout<<"OK! "<<endl;
     int x, y;
     x=Q.Xcoord()+10;
     y=Q.Ycoord()+20;
     TPoint R(x,y);
     return R;        // Return R's data value
}

int main(){     
	TPoint M(20,35),P(0,0);

    TPoint N(M);    //M is a created object, N is a creating object
    P = Value(N);

    cout<<"P="<<P.Xcoord()<<", "<<P.Ycoord()<<endl;
}

/* output. compiler: g++ (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4

Copy_initialization Constructor called.  
# TPoint N(M), TPoint M copy to N

Copy_initialization Constructor called.  
# call Value(N), TPoint N copy to Q

OK! 
# in function Value(), print "OK"

Destructor called. 
# destructor TPoint R

Destructor called. 
# destructor TPoint Q

P=30, 55 
# output in main()

Destructor called. 
# after main(), destructor TPoint M

Destructor called. 
# destructor TPoint P

Destructor called. 
# destructor TPoint N

*/