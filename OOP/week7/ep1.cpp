/*
 *  QUESTION: The Vehicle is composed of Frame, CarDoor and Tyre.
 *    1) The statement, cin >> Frame, means that we can input ID and weight of Frame.
 *    2) The statement, cin >> Cardoor, means that we can input number and color of CarDoor.
 *    3) The statement, cin >> Tyre, means that we can input number of Tyre
 *    4) The statement, cout << Vehicle, means that we can output ID, number of door and tyre.
 *	   Write the codes and finish these demands as above.
 *
 *	NOTE: DON'T define global variables.
 *   
 *  THINKING: 
 *  	Vehicle = Frame + CarDoor + Tyre
 *  	car combination with frame door and tyre
 *  	
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-04-12
*/

#include <iostream>
using namespace std;

class Frame{
    private:
        int ID;
        double f_weight;
    public:
        int const get_ID(){return ID;}       
        double const get_f_weight(){return f_weight;}
        friend istream& operator>> (istream &is, Frame &f); //overload >>
};

class CarDoor{
    private:
        int d_number;
        string d_color;
    public:
    	int get_d_number(){return d_number;}
    	string get_d_color(){return d_color;}
        friend istream& operator>> (istream &is, CarDoor &d); //overload >>
};

class Tyre{
    private:
        int t_number;
    public:
    	int get_t_number(){return t_number;}
        friend istream& operator>> (istream &is, Tyre &t); //overload >>
};

class Vehicle : Frame, CarDoor, Tyre{
    public:
    	Vehicle(Frame &f, CarDoor &d, Tyre &t):Frame(f),CarDoor(d),Tyre(t){}; //Vehicle = Frame + CarDoor + Tyre
		friend ostream& operator<<(ostream &os, Vehicle &v); // overload <<

};

istream& operator>> (istream &is, Frame &f){
	cout << "ID & weight of Frame: ";
	is >> f.ID >> f.f_weight;
    return is;
}

istream& operator>> (istream &is, CarDoor &d){
	cout << "color & number of CarDoor: ";
	is >> d.d_color >> d.d_number;
    return is;
}

istream& operator>> (istream &is, Tyre &t){
	cout << "number of Tyre: ";
	is >> t.t_number;
    return is;
}

ostream& operator<<(ostream &os, Vehicle &v){
    os << "ID: " << v.get_ID() << endl;
	os << "Weight: " << v.get_f_weight() << endl;
	os << "Color: " << v.get_d_color() << endl;
	os << "Number of Door: " << v.get_d_number() << endl;
	os << "Number of Tyre: " << v.get_t_number() << endl;
    return os;
}

int main(){
	Frame FrameA;
    cin >> FrameA;
	CarDoor DoorA;
    cin >> DoorA;
	Tyre TyreA;
    cin >> TyreA;
    Vehicle CarA(FrameA, DoorA, TyreA); // car combination with frame door and tyre
    cout << endl << CarA << endl;
}
