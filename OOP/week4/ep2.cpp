/*
 *  QUESTION: Define an integer set class which is named Set 
 *  	with some memeber functions as follows:
 *  	a. IsExist(): To judge if an integer is a member of a Set or not;
 *  	b. RemoveItem(): To delete an integer from the Set;
 *  	c. IsEqual(): To judge if two Sets are equal or not;
 *  	d. Intersection(): To intersection with another Set;
 *  	e. Union: To union with another Set.
 *  
 *  NOTES: In order to complement Set class, you can define constructor, 
 *  	member functions with available arguments as well as destrctor if you need.
 *  
 *  THINKING: It's easy for struct 'vector' to add/delete elements. What's more, vector can 
 * 		allocate memory dynamaticly. So I choose vector<int> to stroage the item in set.
 * 		When adding items to the set, more than one item may be added at once time. so I use
 * 		the 'va_list' to add more items at once time. Intersection and union function are esay
 * 		to achieve by using IsExist,AddItem,RemoveItem function.
 * 
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-22
*/

#include <iostream>
#include <vector>
#include <cstdarg>
using namespace std;

class Set{
    private:
        vector<int> members; // items in set
    public:
        ~Set(); // release rescoures
        void AddItem(const int n, ...); // add n item as members
        void PrintItem(); // show item in members
        int IsExist(const int item); //return the pos of item
        int RemoveItem(int item); //delete an item
        bool IsEqual(Set &s); // is set A equal to set B ?
        Set Intersection(Set &s); // set A - B
        Set Union(Set &s); // set A + B
};

Set::~Set(){
    members.clear(); //free vector
}

void Set::AddItem(int n, ...){
    va_list ap;	// to get unknow account of args
    va_start(ap, n); 
    for(int i=0; i<n; i++){
        members.push_back(va_arg(ap, int)); 
        // add item at the end of set
    }
    va_end(ap);
}

void Set::PrintItem(){
    for(int i=0; i < members.size(); i++){
        cout << members[i] << " ";
    }
    cout << endl;
}

int Set::IsExist(int item){
    for(int i=0; i < members.size(); i++) // visit all item
        if(members[i] == item) 
            return i; // item in set -> ret it's pos
    return -1; // item not in set -> ret -1
}

int Set::RemoveItem(int item){
    int tmp = IsExist(item);
    if (tmp == -1) 
        return -1; // item does not exist -> ret -1
    else 
        members.erase(members.begin()+tmp); // delete item
    return 0; // delete successfully -> ret 0
}

bool Set::IsEqual(Set &s){
    if (members.size() != s.members.size()) return false; // size not equal
    else
        for(int i=0; i<members.size(); i++)
            if(s.IsExist(members[i]) == -1) return false; // item not equal
    return true;
}

Set Set::Union(Set &s){
    Set res; // set a new set to stroage result
    res.members = members; // new set = A
    for(int i=0; i<s.members.size(); i++){
        if(res.IsExist(s.members[i]) == -1) res.AddItem(1, s.members[i]);
    } // add item in B which not in A
    return res;
}

Set Set::Intersection(Set &s){
    Set res;
    res.members = members; // new set = A
    for(int i=0; i<s.members.size(); i++){
        if(res.IsExist(s.members[i]) != -1) res.RemoveItem(s.members[i]);
    } // delete item in B which also in A
    return res;
}

int main(int argc, char **argv){
    Set a, b, c;
    a.AddItem(7, 1, 4, 6, 7,  3,  9 , 13); //a: 1 4 6 7 3 9 13 
    b.AddItem(8, 1, 3, 6, 2, 15, 23 , 45, 12); //b: 1 3 6 2 15 23 45 12 
    c.AddItem(7, 1, 4, 6, 7,  3,  9 , 13); //c: 1 4 6 7 3 9 13 

    cout << "a: "; a.PrintItem();
    cout << "b: "; b.PrintItem();
    cout << "c: "; c.PrintItem();

    cout << a.IsExist(3) << endl;

    a.RemoveItem(3);
    cout << "a: "; a.PrintItem();

    a.AddItem(1, 3);
    cout << "a: "; a.PrintItem();
    
    cout << "is a euqal b? ";
    if(a.IsEqual(b))  cout << "yes" << endl;
    else cout << "no" << endl;

    cout << "is a euqal c? ";
    if(a.IsEqual(c))  cout << "yes" << endl;
    else cout << "no" << endl;

    cout << "a union b: ";
    a.Union(b).PrintItem();
    
    cout << "a intersection b: ";
    a.Intersection(b).PrintItem();
}

/* output information

$ ./ep2
a: 1 4 6 7 3 9 13 
b: 1 3 6 2 15 23 45 12 
c: 1 4 6 7 3 9 13 
4
a: 1 4 6 7 9 13 
a: 1 4 6 7 9 13 3 
is a euqal b? no
is a euqal c? yes
a union b: 1 4 6 7 9 13 3 2 15 23 45 12 
a intersection b: 4 7 9 13

*/