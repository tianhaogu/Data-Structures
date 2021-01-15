HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  < Tianhao Gu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Mentor: Zixiang Zhang / lecture notes & www.cplusplus.com & stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 18 hours >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame

reading the database/populating your initial data structure:
time: O(logf*logm); space: O(f*m)
Because the first map stores fighter name as key, and class as value, and map with move as key, frame as value stores in the class, 
and inserting a pair<fighter_name, class> and pair<move_name, frame> into the map require O(logn) time.
Space complexity of a map is O(n).

-q (specific move):
time: O(logf*logm); space: O(f*m)
Because the first map has fighter name as key, and class as value, and map with move as key, frame as value stores in the class, 
and searching for/inserting a specific pair in the map requires O(logn) time.

-q (all):
time: O(m*logf); space: O(f*m)
Search for key in the first map same as above O(logn), but for the map in the class, we print all contents, so it's linear: O(n).

-f:
time: O(t*logm); space: O(m*t)
The outer map has move name as key, so searching for a specific name requires O(logm) time, and the inner map(value of the outer map)
has set of fighters as value for each frame, so the highest number of fighters in this move requires O(t) time

-s:
time: O(t*logm); space: O(m*t)
The outer map has move name as key, so searching for a specific name requires O(logm) time, and the inner map(value of the outer map)
has set of fighters as value for each frame, so the highest number of fighters in this move requires O(t) time

-d:
I create a new variable: r-> Number of starting frames of a certain move
time: O(t*logm*logr); space: O(m*t*r)
The outer map has move name as key, so searching for a specific name requires O(logm) time, and the inner map(value of the outer map)
has number of starting frames of the certain move as key, so searching for this certain move requires O(logr) time,
we then iterate over all fighters in the value set, that requires O(t) time.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






