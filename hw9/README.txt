HOMEWORK 9: IMDB SEARCH


NAME:  < Tianhao Gu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Mentor: Zixiang Zhang / lecture notes, lab, www.cplusplus.com, stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 hours >


HASH FUNCTION DESCRIPTION
I directly use the hash function from lab 11. The hash function loops through each char in the query string, use certain operations,
finally convert to a large unsigned int. For the query string, there are 64 combinations of a movie. For example for the normal one (without wildcard),
I merge all 6 catagories to a string (with no ' ' or _ in the middle), and I use '?' to represent a wildcard (like "??????" for all-wildcard query string).
The way I generate 64 combinations of 6 catagories is through permute_filter function, with a large containing all 64 sub-vectors.
After the hash value is generated, mod by table size to get the index in the hash table.
If the index is not occupied, just create a new list for value and insert the pair to this position.
If the index is occupied, check whether key of this position matches with the newly passed-in query string to see whether it's collision or real match.
If math, push back the movie info to the existing list. If not, use linear probing to find a new empty position to insert.

Important Note: I follow the vector<pair<Query, list<> > > structure for the hash table. In pdf, the list is of Movie_Data type of which all movie info
of one movie is here. However, I use int as list type, but each int represents the index of this movie in the vector for all movie objects, of which I think
is also a way to represent data information of a movie. The reason is to avoid copying movie objects when resizing the hash table.
(I create a vector for movie class object at the beginning, and add movie object after each movie is read from input, then I get index of this movie object
in the movie vector, this index is the int I store in the hash table list)
Although I do not explicitly store movie info in the list, I believe I do it implicitly which I think is not a violation of the structure mentioned in pdf.
<Reference: This method is introduced by one of the mentors!>






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


