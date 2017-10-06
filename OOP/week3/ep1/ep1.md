## Source code from book
### Stack
```cpp
struct Stack {
  struct Link {
    void* data;
    Link* next;
    void initialize(void* dat, Link* nxt);
  }* head;
  void initialize();
  void push(void* dat);
  void* peek();
  void* pop();
  void cleanup();
};
```
### Stash
```cpp
struct Stash {
  int size;      // Size of each space
  int quantity;  // Number of storage spaces
  int next;      // Next empty space
   // Dynamically allocated array of bytes:
  unsigned char* storage;
  // Functions!
  void initialize(int size);
  void cleanup();
  int add(const void* element);
  void* fetch(int index);
  int count();
  void inflate(int increase);
}; 
```
## Questions
### Main data structure of Stack
> The main data structure is *link stack*. There are a `struct Link` in `struct Stack` which defined data's content, next element and declared initialize function.
> In addition, there are also some other functions in `struct Stack` to do some operatation of the stack or elements in satck.

### Differences in the data storage of Stash and Stack
> In *Stack*, data storaged by an array of `struct Link`;
> In *Stash*, data storaged by isolated variable.

> In *Stack*, data added by function `push`. OS will allocate a part of unused memory to storage the new data;
> In *Stash*, data added by function `add`. Data storaged in memory which was already allocated when Satsh was initalized. If there is no enough room to storage new data, `inflate` function will be called.
