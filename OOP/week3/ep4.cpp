/*
 *  QUESTION: Create a class Point, and finish the following functions as below:
 *  1. Define two member variables, X and Y, as coordinate, and the other member variable R is radius;
 *  2. Define a member function, Distace, to calculate the distance between two points.
 *  3. Define a member function, Relationship, to judge the relationship such as seperation, 
 *  intersection, tangent(intenally or externally tangent) between two circles.
 *  Note: You can define appropriate parameters according to your member functions.
 *  
 *  THINKING: compare the difference between two points' radius and the distance, 
 *  then we can get the relationship of two circle.
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-15
*/

#include <iostream>
#include <cmath>
using namespace std;

class Point{
private:
    int X, Y; // coordinate
    double R; // radius
public:
    Point(int x, int y, int r) {X = x; Y = y; R = r;}
    double Distance(Point p);
    void Relationship(Point p);
};

double Point::Distance(Point p) { // calc the distance of two point
    return sqrt((X - p.X)*(X - p.X) + (Y - p.Y)*(Y - p.Y));
}

int cmp(double a, double b){ // compare a and b
    if (a > b) return 1;
    else if (a < b ) return -1;
    else return 0;
}

void Point::Relationship(Point p) {
    double dist = Distance(p);
    switch (cmp(dist,abs(R-p.R))){
        case -1: // the Difference between Radius is greater than Distance
            cout << "seperation" << endl;
            break;
        case 1: // the Difference between Radius is lower than Distance
            cout << "intersection" << endl;
            break;
        case 0: // the Difference between Radius is equal Distance
            cout << "tangent" << endl;
            break;
    }
}

int main(){
    int m_x, m_y;
    double m_r;
    int n_x, n_y;
    double n_r;

    cout << "input coordinate and radius of the first point: ";
    cin >> m_x >> m_y >> m_r;
    cout << "input coordinate and radius of the second point: ";
    cin >> n_x >> n_y >> n_r;

    Point m(m_x,m_y,m_r);
    Point n(n_x,n_y,n_r);

    cout << m.Distance(n) << endl;
    m.Relationship(n);
}

/* output information

$ ./ep4
input coordinate and radius of the first point: 0 0 1.5
input coordinate and radius of the second point: 1 1 1
1.41421
intersection

*/