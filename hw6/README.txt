HOMEWORK 6: RICOCHET ROBOTS RECURSION


NAME:  < Tianhao Gu >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Mentor: Zixiang Zhang, Tutor: Diyuan Zhu / lecture notes, www.cplusplus.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 18 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

i & j = dimensions of the board
    r = number of robots on the board
    g = number of goals
    w = number of interior walls
    m = maximum total number of moves allowed

Note: I only did the reachability part for 3 maximum moves
Order Notation: O(r*(4*m))
4 means 4 directions, for all the robots(both the targeted robot and other robots), they should move in 4 directions for m(maximum) moves (my calc_reach function)
My main written codes are calc_reach function in main.cpp, moveRobot function in the board class (filling in), and handling basic moves in the main function



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
Unfortunately my code can only calculate the reachability of the robots on the board with maximum 3 moves


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


