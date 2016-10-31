## Program 1
#### Due Thursday, Sept. 1

------------------------------

Purpose
------------------------------
To work with the STL `list` type

Problem Statement
------------------------------
We would like to easily find "cluster" or "peer" groups for people.
For this assignment, we will talk about people that have a "similar" grade
average to the person that we are finding the group for.

Since we sometimes have a loose definition of a peer group and sometimes it
is stronger, we will allow the size of a peer group  to vary.  Most people
do not have the same grade average exactly.  We will allow the user to decide
how big of a group is desired.

Details
------------------------------
You will read the master list from the file `/home/win.thackerw/271/peer/master.dat`.
In this file will be a person's last name (at most 20 characters) and their grade average
(a decimal number) separated by white space.  You will insert these values into a
doubly linked list in grade average order.

Next you will read from `/home/win.thackerw/271/peer/groups.dat`
(repeatedly until end of file) a name and a group size (an integer).
You will then find this person on your master list and print out the
"group size" number of people that have the closest grades to his/her grade.
The group may not be symmetrical.  For a group of size 10, there may be 3
students with higher grades than the one we are considering and 7 with lower
grades and having these be the 10 closest grades. Use the STL List class,
which is a doubly linked list.

What to Turn In
------------------------------
You are to email me your program with the code as an attachment.
You may tar it if you wish. Also, turn in a printout of your program.
2 points (out of 20) penalty for each day late. It is due at the beginning 
of class on the due date.
