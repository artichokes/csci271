## Program 4
#### Due Tuesday, Nov. 1

------------------------------

Problem
------------------------------
Compare an O(n<sup>2</sup>) sort with an O(n log n) sort. To do this, you
will program the bubble sort and the heap sort. You will not need to use
classes in this project, but you can if you wish.

Project Input
------------------------------
The input will be character strings of length less than or equal to 30
characters. They will come from the file `/home/win.thackerw/271/sort.dat`.

You will run these programs with several different input and array sizes.
You can pass arguments from the command line to your program.  For example
you should be able to type into the command line `p4 20000` and the
executable `p4` is executed passing the argument `20000` to the program.
To see how to access the argument(s) check out:
<http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html>

Project Output
------------------------------
The program should print out the sorted array to a file `sorted.dat`.

You will need to measure the time it takes the computer to perform each
sort. You get the time by using the `time` command in linux. If your
program is called `p4` then instead of issuing the command `p4` to run
your program, you use `time p4`.  This will run your program and report
system (sys), user, and real times. The time of interest for us is user
time and sys time added together. You (not your program) should produce
a table of the form:

| Table Size | Time for Bubble Sort | Time for Heap Sort
| ---------- | -------------------- | ------------------
| 2,000
| 4,000
| 10,000
| 20,000
| 50,000
| 100,000
| 1,000,000  | **DO NOT TIME**
| 10,000,000 | **DO NOT TIME**

 Some of these arrays may be too big for static declaration. Instead you
 can use the NEW command to create an array of appropriate size. This
 gets the data from the heap and not from static area (which is more
 limited).
 
 Produce a prediction for the time it will take to do an bubble sort
 for 1,000,000 and 10,000,000 items. Justify your estimate.

Project Options
------------------------------
For extra credit, you may do one additional O(n<sup>2</sup>) sort
(ex. insertion, selection) **AND** one additional O(n log n) sort
(ex., quick sort, merge sort).

What to Turn In
------------------------------
Email me your code as attachments (you may use a tar file if you
wish or multiple attachments; also make files will make me happy).
Additionally, you are to hand in a printout of your code.

Late Penalty
------------------------------
There will be a 20% penalty for each day late.
