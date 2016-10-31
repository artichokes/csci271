## Program 2
#### Due Tuesday, Sept. 27

------------------------------

Purpose
------------------------------
Reverse engineer the `list` STL class

Problem Statement
------------------------------
Now that you are experienced with the `list` STL, you will create your own
`list` template class to use in place of the `list` STL class. I will provide
a main later for you to test with.

The main that you can use for testing is: `/home/win.thackerw/271/p2main.cpp`

Because of implementation difficulties, your STL-like `list` class will be a
little different. One significant difference is that the iterator class will
be a templated class of its own, not a class within the `list` class. So to
get a list of cars, you would say: `list<cars> mylist;`. However, there is a
builtin class called `iterator` (different from the `list<..>::iterator` class).
So, we cannot use `iterator` as the name of our iterator class. We will use `iter`.
To get an iterator to a node within a list of cars, you would use: `iter<cars> myiterator;`.

Details
------------------------------
You are to call your class `list` and have the following member functions.
You may use additional ones if you wish/need, but they must look and act
like `list` STL methods. Of course, you will need to create 3 classes, one
for the linked list, one for the node and one for the iterator.

| Member                      | Spec
| --------------------------- |-------------
| constructor                 | Create the list.  You will probably want head and tail nodes and pointers.
| copy constructor            | Allows you to do `list A(B)` so that you create `A` as a copy of `B`. This is a little involved as it is NOT just copying the values of the head pointers.
| destructor                  | Removes and deletes all the nodes (including head an tail nodes)
| `operator=`                 | Copies one linked list into another (requires creating a new set of nodes)
| `bool empty()`              | `true` if there are no values in the list
| `int size()`                | Returns the number of elements in the list
| `iter begin()`              | Returns an iterator to the first item in the list
| `iter end()`                | Returns an iterator to after the last item in the list
| `Type front()`              | Returns a reference to the first item in the list
| `Type back()`               | Returns a reference to the last item in the list
| `void clear()`              | Removes all items from the list
| `void erase(iter)`          | Removes the item `iterator` indicates from the list
| `void push_back(value)`     | Insert `value` at the end
| `void push_front(value)`    | Insert `value` at the beginning
| `void pop_front()`          | Removes the first value in the list
| `void pop_back()`           | Removes the last value in the list
| `++iter`                    | Move iterator to the next and return the modified value of the iterator
| `iter++`                    | Move iterator to the next and returns the original value of the iterator
| `--iter`                    | Move iterator to the previous and return the modified value of the iterator
| `iter--`                    | Move iterator to the previous and returns the original value of the iterator
| `*iter`                     | Return the value in the node pointed to by the iterator

Again, feel free to add any methods that you wish.

I suggest you implement just the constructors, the `push_back`,
the `begin` and the `++` methods so you can write a main that simply
creates a list and prints it out. Get this working before continuing
with the design of the other methods.

What to Turn In
------------------------------
Email me your code as attachments (you may use a tar file if you
wish or multiple attachments; also make files will make me happy).
Additionally, you are to hand in a printout of your code.

Late Penalty
------------------------------
There will be a 20% penalty for each day late.
