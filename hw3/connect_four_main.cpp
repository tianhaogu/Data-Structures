#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){

  //normal but more complicated test with totally 19 tokens and finally a winner wins
  std::cout << std::endl;
  std::cout << "Normal but long test begins here: " << std::endl;
  Board s("RPI","MIT",":::");
  std::cout << "Initial Board is this: " << std::endl << s << std::endl;
  std::string result;

  s.insert(1, true);
  s.insert(3, false);
  s.insert(1, true);
  result = s.insert(2, true);
  std::cout << "Board is like this: " << std::endl << s << std::endl;
  if (result == ":::") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  
  s.insert(1, false);
  s.insert(0, true);
  s.insert(4, false);
  result = s.insert(5, false);
  std::cout << "Board is like this: " << std::endl << s << std::endl;
  if (result == ":::") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  
  s.insert(4, true);
  s.insert(0, false);
  s.insert(3, true);
  result = s.insert(1, false);
  std::cout << "Board is like this: " << std::endl << s << std::endl;
  if (result == ":::") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }

  s.insert(1, true);
  s.insert(1, false);
  s.insert(1, false);
  result = s.insert(3, true);
  std::cout << "Board is like this: " << std::endl << s << std::endl;
  if (result == ":::") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }

  s.insert(6, true);
  s.insert(6, true);
  result = s.insert(2, true);
  std::cout << "Board is like this: " << std::endl << s << std::endl;
  if (result == ":::") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  
  //Test the clear function to check row&column numbers and number of tokens after set to original status
  std::cout << std::endl;
  std::cout << "Test the clear function: " << std::endl;
  s.clear();
  std::cout << "Number of Rows after Clear the Board: " << s.numRows() << std::endl;
  std::cout << "Number of Columns after Clear Board: " << s.numColumns() << std::endl;
  std::cout << "Number of tokens in Row0: " << s.numTokensInRow(0) << std::endl;
  std::cout << "Number of tokens in Column3: " << s.numTokensInColumn(3) << std::endl;
  std::cout << std::endl;
  
  
  //Test the assignment operator: d = c after some steps
  std::cout << "Test the assignment operator: " << std::endl;
  Board c("JUV","INT","~~~");
  c.insert(1, true);
  c.insert(3, false);
  c.insert(1, true);
  result = c.insert(2, true);
  std::cout << "Board is like this: " << std::endl << c << std::endl;
  if (result == "~~~") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  Board d("ESP","POR","~~~");
  d = c;
  assert(d.numTokensInColumn(1) == c.numTokensInColumn(1));
  assert(d.numTokensInRow(0) == c.numTokensInRow(0));
  d.insert(1, false);
  d.insert(0, true);
  d.insert(4, false);
  result = d.insert(5, false);
  std::cout << "Board is like this: " << std::endl << d << std::endl;
  if (result == "~~~") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  std::cout << std::endl;

  
  //Test the copy constructor: Board b(a) after some steps
  std::cout << "Test the copy constructor: " << std::endl;
  Board a("RMA","BAR","///");
  a.insert(1, true);
  a.insert(3, false);
  a.insert(1, true);
  result = a.insert(2, true);
  std::cout << "Board is like this: " << std::endl << a << std::endl;
  if (result == "///") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  Board b(a);
  assert(b.numTokensInColumn(1) == a.numTokensInColumn(1));
  assert(b.numTokensInRow(0) == a.numTokensInRow(0));
  b.insert(1, false);
  b.insert(0, true);
  b.insert(4, false);
  result = b.insert(5, false);
  std::cout << "Board is like this: " << std::endl << b << std::endl;
  if (result == "///") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  std::cout << std::endl;

  //More tests: tokens with different lengths & insert column number > (existed column number+1)
  std::cout << "Test tokens with different length and the case of new token "
            << "placed in a column not adjacent to the right of the existed "
            << "largest column: " << std::endl;
  Board m("Liverpool","United",";;;");
  m.insert(1, true);
  m.insert(3, false);
  m.insert(1, true);
  m.insert(2, true);
  m.insert(7, false);
  m.insert(7, true);
  result = m.insert(5, false);
  std::cout << "Board is like this: " << std::endl << m << std::endl;
  if (result == ";;;") {
  	std::cout << "No winner yet." << std::endl;
  }
  else {
  	std::cout << "The winner is: " << result << std::endl;
  }
  std::cout << std::endl;
}

