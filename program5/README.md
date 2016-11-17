## Program 5
#### Due Thursday, Nov. 17

------------------------------

Problem
------------------------------
Study the effects of different hash table sizes on the search time.
The study will consist of creating a hash class (with a hash table,
an insert function and a search function (feel free to add more main
and class functions that you find necessary and/or helpful). The
size of the hash table must be easily modified (preferably via the
constructor).  All functions that are based on the table size (such
as the hash function) must be aware of any changes to the table size.

Read 100,000 values from the file `/home/win.thackerw/271/p4load.dat`
inserting them into the hash table.  Then read ALL values from
`/home/win.thackerw/271/p4search.dat` and search for those values.
Use this process for table sizes of 200,000, 130,000, 110,000 and 100,500.
This will give us different percentage full in order to see the changes
for different sizes. Time each of these runs. Since the tables are
all different sizes, there will be a different load factor for each
experiment.

Project Input
------------------------------
The input will be character strings of length less than or equal to
30 characters.

Project Output
------------------------------
Your program will print out the average number of probes for all the
searches, the number of searches that were successful and the number
of searches that were unsuccessful. A probe is when you look at a
value in the array.  The number of Unsuccessful probes should be the
same for all the different table sizes since we are always searching
for the same items (similarly, the number of successful searches will
be the same for all table sizes; this is just a check of correctness
for your program.  If you don't have the same numbers throughout each
of these columns then something is wrong). 

Additionally, you will record the times it takes for the programs to
run for each of the table sizes.  You get the time by using the time
function in Unix.  If your program is called `p5`, then instead of
issuing the command `p5` to run your program, you use `time p5`.
This will run your program and report system, cpu, and wallclock times.
The time of interest for us is cpu+system.

You should produce a table of the form:

| Table Size | Load Factor | Time | Probes | Avg. Probes (Probes/(Unsuccessful+Successful)) | Unsuccessful Searches | Successful Searches |
| ---------- | ------------| ---- | ------ | ---------------------------------------------- | --------------------- | ------------------- |
| 200,000    | 0.5         |
| 130,000    | 0.77        |
| 110,000    | 0.91        |
| 100,500    | 0.995       |

Definitions
------------------------------
* **Search** - looking for an item (may take 1 or several probes).
* **Probe** - looking in the table (may have to look more than once for
              a particular search).

Project Options
------------------------------
You may use any hash function you can develop. It needs to be "good".
You are to use linear probe for collision handling. For extra credit,
you may use separate chaining (using appropriate table sizes) and report
the timings and average probes for it.

What to Turn In
------------------------------
Email me your code as attachments (you may use a tar file if you
wish or multiple attachments; also make files will make me happy).
Additionally, you are to hand in a printout of your code.

Late Penalty
------------------------------
There will be a 20% penalty for each day late.
