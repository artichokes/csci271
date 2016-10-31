## Program 3
#### Due Thursday, Oct. 20

------------------------------

Problem
------------------------------
There are really 2 problems:
1. Binary sort tree templated class. Create a binary sort tree templated
class that will perform appropriate binary sort tree operations.
2. Write a main to facilitate testing your class.

Project Input
------------------------------
There will be 3 types of input. The main input will be interactive commands
from the screen. You will present a menu that will have the various choices
numbered:
1. Insert from a file
2. Insert from the keyboard
3. Find
4. Delete
5. Print inorder
6. Print preorder
7. Print postorder
8. Exit

You should not do I/O in your class.

Processes
------------------------------
For your test main, the data stored in each node will be a character string
of at most 20 characters. You should make your tree class templated so
your class will handle any data type for future different mains. The
insert from a file should prompt for a file name to open. Then the data is
read in and inserted into the tree. Do not assume the tree is always
empty when this process is chosen.  We may read from more than one file
during the execution of this program.

The insert from keyboard will prompt for one data value and then insert
it into the tree. Do not assume the tree is not empty (the tree can be
empty or not empty when this process is called).

The find and delete will prompt for a value and then search the tree for
that value.  For a find, you will just report found or not found and
print the value (in real life, the data in the node will be an entire
record and we will just input a key, so when it is found we would be
printing out more than just the key).  Of course, the delete will remove
the node and leave the tree as a binary sort tree.

The three print functions are self explanatory as well as exit.

Project Output
------------------------------
All the output will be to the screen in response to the commands.

Suggested Implementation
------------------------------
I would suggest you get the insert from a file and the print functions
working first. Get them thoroughly debugged. This will help with
implementing the rest.

What to Turn In
------------------------------
Email me your code as attachments (you may use a tar file if you
wish or multiple attachments; also make files will make me happy).
Additionally, you are to hand in a printout of your code.

Late Penalty
------------------------------
There will be a 20% penalty for each day late.
