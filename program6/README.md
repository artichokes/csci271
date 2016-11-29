## Program 6
#### Due Friday, Dec. 9

------------------------------

Problem
------------------------------
Given the courses needed for graduation and their prerequisites,
create a list of courses in an order that will allow the student to
progress successfully.

Project Input
------------------------------
The input will be character strings of length less than or equal to
10 characters. Each string will represent a course. The first course
on each line will be the base course. The rest of the courses on the
same line will be the prerequisite courses that must be completed
before the base course can be taken. There will be a # sign at the
end of each line to make input easier. A course may have no prerequisites.

There will be no more than 500 courses to consider.

Here is a sample input:

```
CSCI311 CSCI211 MATH261 #
CSCI470 CSCI311 MATH201 #
CSCI101 #
CSCI211 CSCI208 CSCI101 #
CSCI208 CSCI207 MATH261 #
MATH261 #
MATH201 #
CSCI207 #
```

Project Output
------------------------------
You will print out a list of courses such that the prerequisites for
every course appear before that course. You must implement this
solution in the most efficient (for the computer) way possible.

What to Turn In
------------------------------
Email me your code as attachments (you may use a tar file if you
wish or multiple attachments; also make files will make me happy).
Additionally, you are to hand in a printout of your code.

Late Penalty
------------------------------
There will be a 20% penalty for each day late.
