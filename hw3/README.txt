HOMEWORK 3: CONNECT FOUR


NAME:  < Tianhao Gu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Mentor: Zixiang Zhang / Lecture Note 4,6,7,8; www.cplusplus.com; stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 13 hours >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four): O(m*n+n*m) = O(m*n)
(Note that all my columns are in the same height, which is a little different from what the homework shows)

insert (including checking for connected four): O(m*n+n*m+m*n) = O(m*n)

numTokensInColum: O(n)

numTokensInRow: O(m)

numColumns: O(1)

numRows: O(1)

print: O(m*n)

clear: O(n)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I use Dr. Memory. I haven't met even one memory leak since I follow the instructions on lecture notes very carefully,
and delete each 1D&2D pointer in the for loop after I created new ones and values get copied.
The debugging process of this homework was also very smooth as I checked my logic of each function carefully after I finished.
I used cout to debug, to see in which step my code might have some errors that generated different results with sample output.
In student test, I used a complicated example which took 19 steps (as I was actually played the game) so that some corner problems
can be excluded. One example is that the insert column is not adjacent to the right of the already existed right-most column.
I also tested the clear function, copy constructor and assignment operator to make the test case complete.
To prevent ugly output like if lengths of tokens are different, I use setw to align to the left to make the output beautiful.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

