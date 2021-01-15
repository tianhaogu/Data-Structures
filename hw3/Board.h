#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <array>
#include <iomanip>
using namespace std;

class Board {
public:
  //default constructor, constructor, copy constructor, assignment operator, destructor
  Board();
  Board(const string& token_one, const string& token_two, const string& blank);
  Board(const Board& b) { copy(b); }
  Board& operator=(const Board& b);
  ~Board();
  
  //accessors
  int numRows() const;
  int numColumns() const;
  int numTokensInRow(int row) const;
  int numTokensInColumn(int column) const;
  const string& getElement(int col_num, int row_num) const;
  const string& getTokenA() const;
  const string& getTokenB() const;
  
  //modifiers and helper function
  const string& insert(int col_num, bool who);
  int checkWin() const;
  void clear();

private:
  void copy(const Board& b); //private copy function
  string** m_data;
  int num_rows_;
  int num_cols_;
  string token_A_;
  string token_B_;
  string blank_element_;
  int who_win_;
};

//non-member function for print
std::ostream& operator<< (std::ostream& ostr, const Board& b);