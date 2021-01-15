HOMEWORK 8: ROPES


NAME:  < Tianhao Gu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< mentor: Zixiang Zhang / & www.cplusplus.com & some codes directly from lecture notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 hours >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

An extremely balanced tree can be that all children are left ones, so there's only one leaf containing all characters of the string.
(there can be many levels)

Copy Constructor:
Balanced: O(m+2^p), 2^p means the number of nodes in the rope we need to copy, and copy a string requires O(m).
Unbalanced: O(p), like using for loop to loop over each level(node).

Construct from Node*:
Balanced: O(logn), because we have to go from root to leaf to update size of the rope, which depends logarithmically to the weight of the whole string.
          or O(p), because it's linear to the level from root to the deepest leaf.
Unbalanced: O(1), just steal the node, even no need to update size.

Index:
Balanced: O(p), because we have to compare weights at each level, and finally to the leaf, so it depends linearly on the level p.
          or O(logn), because it also depends logarithmically to the weight of the whole string.
Unbalanced: O(1), like like accessing value in vector using operator[].

Report:
Balanced: O(v*logn), first find the node(s), depends logarithmically on the length of the whole string, and then append each char 
          to the output string (like print elements in a vectors), so depends linearly on longest leaf.
Unbalanced: O(1), like like accessing values from a range in vector using operator[].

iterator operator++:
Balanced: O(p), sometimes it's parent or right child, but sometimes we need to traverse from leaf to root, so overall O(p) time.
Unbalanced: O(1), just go to the parent.

Split:
Balanced: O(logn), because we have to find the targeted node, and then find node that has to disconnect with its right child, and then
          connect the disconnected subtrees. All of them depends logarithmically to number of subnodes-> length of string.
Unbalanced: O(1), like accessing value in vector using operator[].

Concat:
Balanced: the real concatenation operation only requires O(1) operation, but when we update weight and size of the root, it depends logarithmically
          on weights, and both *this and rope passed in are related, so overall O(log(n+m)). Since longest path is given, and updating weight
          requires going from root to leaf, so it can also be represented as O(p).
Unbalanced: if right tree only have right child, then O(1) overall, because left subtree only contains left children, no updating weight & size is needed.
            if right tree only have left child, it's also O(1), because the right weight is equal to the weight of the first node, directly get it.


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
-> I first use the provided tree. For the split test, the basic test tests the right leaf, but in my test, I test the left leaf and split index in the 
   the middle of the test. For the concat test, I choose two different subtrees from the basic test (one of them is just a leaf).
   For the report test, I choose normal index pairs like (4,13), and also corner cases like (0,4),(1,5),(13,13).
-> I then create a huge tree in StudentTestRope() function, I test the constructor, index and report as above, like choosing different types of pairs of
   indexes. And for the split test, I also test the right leaf, left leaf, and leaf that has to be seperated in different levels.
   (Note for sove of the above tests, I only put one version in my student test in main.cpp, but I've tested for the remaining for myself for hidden tests).
-> Corners cases include: two same indexes in the report test, concatenate a subtree and a subleaf in concat test, split the left-most or right-most leaves
   or subtrees, and all of them are tested and some are shown in the student test.
-> The basic debugging skill is still to print strings & counts & weights in the middle of the function to see where the program crashes or why assert fails.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

