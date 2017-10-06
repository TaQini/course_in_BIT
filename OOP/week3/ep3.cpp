/*
 *  QUESTION: Define an array of int. Take the starting address of that array 
 *  and use static_cast to convert it into and void*. Write a function that 
 *  takes a void*, a number(indicating a number of bytes), and a value 
 *  (indicating the value to which each byte should be set) as arguments. 
 *  The function should set each byte in the specified range to the spcified 
 *  value. Try out the function on your array of int.
 *
 *  THINKING: I don't really understand the meaning of question. I just write 
 *  the func copy the val byte by byte... and it can pass 3 arguments. *_*
 *
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-15
*/

#include <iostream>
using namespace std;

void func(void *ptr, int num, const void *val) {
    unsigned char *src = (unsigned char *)val; // source of data
    unsigned char *dest = (unsigned char *)ptr; // destation of data
    for (int i = 0; i < num* sizeof(int); ++i) {
        dest[i] = src[i % sizeof(int)];
    }
}

int main(){
    int a_array[100] = {0}; // the array of int
    int num, val;
    void *ptr = static_cast <void *> (a_array);

    cout << "array start at " << ptr << endl; //debug information

    cout << "please input the number to write: ";
    cin >> num;  // input number
    cout << "please input the value: ";
    cin >> val;  // input value

    for (int i = 0; i < num; ++i)
        cout << "[before] array[" << i << "] = " << a_array[i] << endl;

    func(ptr, num, (void *)&val);
    // args: void*, a num, a value

    for (int i = 0; i < num; ++i)
        cout << "[after] array[" << i << "] = " << a_array[i] << endl;
}

/* test information
$ g++ ep3.cpp -o ep3
$ ./ep3
array start at 0x7ffc33e9****
please input the number to write: 2
please input the value: 33
[before] array[0] = 0
[before] array[1] = 0
[after] array[0] = 33
[after] array[1] = 33
 */