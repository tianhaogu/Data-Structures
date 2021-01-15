#ifndef Board_h_
#define Board_h_
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <array>
#include <iomanip>
#include "Board.h"
using namespace std;

Board::Board() { //default constructor
  num_rows_ = 5;
  num_cols_ = 4;
  who_win_ = 0;
  token_A_ = ",";
  token_B_ = ",";
  blank_element_ = ".";
  m_data = new string*[num_cols_]; //create the 2D pointer
  for (int i = 0; i < num_cols_; ++i) {
    m_data[i] = NULL; //set each column 1D pointer to NULL pointer
  }
}

Board::Board(const string& token_one, const string& token_two, const string& blank) { //constructor
  num_rows_ = 5;
  num_cols_ = 4;
  who_win_ = 0;
  token_A_ = token_one;
  token_B_ = token_two;
  blank_element_ = blank;
  m_data = new string*[num_cols_];  //create the 2D pointer
  for (int i = 0; i < num_cols_; ++i) {
    m_data[i] = new string[num_rows_]; //create column arrays
    for (int j = 0; j < num_rows_; ++j) {
      m_data[i][j] = blank; //set default elements as blank
    }
  }
}

void Board::copy(const Board& b) { //copy constructor
  this-> num_rows_ = b.num_rows_;
  this-> num_cols_ = b.num_cols_;
  this-> who_win_ = b.who_win_;
  this-> token_A_ = b.token_A_;
  this-> token_B_ = b.token_B_;
  this-> blank_element_ = b.blank_element_;
  this-> m_data = new string*[this-> num_cols_]; //create the 2D pointer
  for (int i = 0; i < this-> num_cols_; ++i) {
  	this-> m_data[i] = new string[this-> num_rows_]; //create column arrays
  	for (int j = 0; j < this-> num_rows_; ++j) {
  	  this-> m_data[i][j] = b.m_data[i][j]; //copy each element
  	}
  }
}

Board& Board::operator=(const Board& b) { //assignment operator
  if (this != &b) {
    for (int i = 0; i < num_cols_; ++i) {
      if (m_data[i] != NULL) {
      	delete [] m_data[i]; //delete each column and set it to NULL pointer
      	m_data[i] = NULL;
      }
    }
    delete [] m_data;
    this-> copy(b); //call the copy constructor
  }
  return *this;
}

Board::~Board() { //destructor
  this-> clear();
  delete [] m_data;
}

int Board::numRows() const {
  return num_rows_;
}

int Board::numColumns() const {
  return num_cols_;
}

const string& Board::getTokenA() const {
  return token_A_;
}

const string& Board::getTokenB() const {
  return token_B_;
}

int Board::numTokensInRow(int row) const {
  if (row >= num_rows_) { //if the row we take doesn't exist
  	return -1;
  }
  else {
    int token_row = 0;
    for (int i = 0; i < num_cols_; ++i) { // loop over each column
      if (m_data[i] != NULL) { //if the column array exists with value
        if (m_data[i][row] != blank_element_) { //if the element is not blank element
          token_row += 1; //token number plus one
        }
      }
      else { //if the column doesn't exist
        return -1;
      }
    }
    return token_row;
  }
}

int Board::numTokensInColumn(int column) const {
  if (column >= num_cols_) { //if the column we take doesn't exist
  	return -1;
  }
  else {
    int token_column = 0;
    for (int i = 0; i < num_rows_; ++i) { //loop over each row
      if (m_data[column] != NULL) { //if the column array exists with value
        if (m_data[column][i] != blank_element_) { // if element not blank
      	  token_column += 1; //token number plus one
        }
        else { //if element is blank
      	  break; //this means no token can token can be existed above due to gravity
        }
      }
      else { //if the column doesn't exist
        return -1;
      }
    }
    return token_column;
  }
}

const string& Board::insert(int col_num, bool who) {
  int num_token_in_column = this-> numTokensInColumn(col_num);
  if (col_num < num_cols_) { //if the column we want to insert exists
  	if (num_token_in_column < num_rows_) { //if this column has not been fully "occupied"
      if (who == true) { //insert the token according to the player number
  	    m_data[col_num][num_token_in_column] = token_A_;
  	  }
  	  else {
  	  	m_data[col_num][num_token_in_column] = token_B_;
  	  }
  	}
  	else { //if this column has been fully "occupied" we need to create a new one with size+1
      string* new_column = new string[num_token_in_column+1]; //create a new column array
      for (int i = 0; i < num_token_in_column; ++i) {
      	new_column[i] = m_data[col_num][i]; //copy elements into new array
      }
      if (who == true) { //insert token to the last (top) position in the new array
        new_column[num_token_in_column] = token_A_;
      }
      else {
      	new_column[num_token_in_column] = token_B_;
      }
      delete [] m_data[col_num]; //delete the old column array after elements get copied
      m_data[col_num] = new_column; //the pointer of each column points to the new array
      num_rows_ += 1; //increase number of rows by one
      for (int i = 0; i < num_cols_; ++i) { //for all other columns also delete old column arrays and create new ones
      	if (i != col_num) {
      	  string* each_new_column = new string[num_rows_];
      	  for (int j = 0; j < num_rows_-1; ++j) {
      	  	each_new_column[j] = m_data[i][j];
      	  }
      	  each_new_column[num_rows_-1] = blank_element_; //fill the top (newly created) position with blank element
      	  delete [] m_data[i];
      	  m_data[i] = each_new_column;
      	}
      }
  	}
  }
  else { //if the column we want to insert doesn't exist
  	string** new_data = new string*[col_num+1]; //create new 2D pointer, length according to column we want to insert
  	for (int i = 0; i < col_num+1; ++i) {
  	  string* new_data_column = new string[num_rows_];
  	  if (i < num_cols_) { //for already existed columns, just copy and paste elements
  	    for (int j = 0; j < num_rows_; ++j) {
  	  	  new_data_column[j] = m_data[i][j];
  	    }
  	    delete [] m_data[i];
  	    new_data[i] = new_data_column;
  	  }
  	  else { //for non-existed columns
        if (i != col_num) { 
          for (int j = 0; j < num_rows_; ++j) {
            new_data_column[j] = blank_element_; //fill in the newly created arrays (not the column we want to insert) with blank elements
          }
        }
        else {
  	      for (int j = 0; j < num_rows_; ++j) {
  	        if (j == 0) {
  	      	  if (who == true) {
  	      	    new_data_column[j] = token_A_; //fill in the first(bottom) position with target token if it's the column to insert
  	      	  }
  	      	  else {
  	      	    new_data_column[j] = token_B_;
  	      	  }
  	        }
  	        else {
  	      	  new_data_column[j] = blank_element_; //fill in non-bottom positions of the target column with blank elements
  	        }
          }
  	    }
  	    new_data[i] = new_data_column;
  	  }
  	}
  	delete [] m_data;
  	m_data = new_data;
  	num_cols_ += col_num-(num_cols_-1); //change number of columns according to difference of targetd column and originally existed columns
  }
  who_win_ = this-> checkWin(); //check who wins
  if (who_win_ == 1) {
    return token_A_; //return who wins or no one wins
  }
  else if (who_win_ == 2) {
    return token_B_;
  }
  else {
    return blank_element_;
  }
}

int Board::checkWin() const {
  for (int i = 0; i < num_rows_; ++i) { //check each row
    if (this-> numTokensInRow(i) < 4) { //directly jump out if number of tokens in the row is less than 4
      continue;
    }
    int horizontal_count = 0;
    for (int j = 1; j < num_cols_; ++j) {
      if (m_data[j][i] != blank_element_ && m_data[j][i] == m_data[j-1][i]) { //if the same non-blank element as the previous one
        horizontal_count += 1;
      }
      if (m_data[j][i] != m_data[j-1][i] || m_data[j][i] == blank_element_) { //otherwise clear the count 
        horizontal_count = 0;
      }
      if (horizontal_count == 3) { //if 4 consecutive same tokens
        if (m_data[j][i] == token_A_) {
          return 1;
        }
        if (m_data[j][i] == token_B_) {
          return 2;
        }
      }
    }  
  }
  for (int i = 0; i < num_cols_; ++i) { //check each column
    if (this-> numTokensInColumn(i) < 4) { //directly jump out if number of tokens in the column is less than 4
      continue;
    }
    int vertical_count = 0;
    for (int j = 1; j < num_rows_; ++j) { 
      if (m_data[i][j] == blank_element_) { //if it's token element directly jump out due to gravity
        vertical_count = 0;
        break;
      }
      else {
        if (m_data[i][j] == m_data[i][j-1]) { //if same token as below
          vertical_count += 1;
        }
        else { //otherwise clear count
          vertical_count = 0;
        }
      }
      if (vertical_count == 3) { //if 4 consecutive same tokens
        if (m_data[i][j] == token_A_) {
          return 1;
        }
        if (m_data[i][j] == token_B_) {
          return 2;
        }
      }
    }
  }
  return 0;
}

const string& Board::getElement(int col_num, int row_num) const {
  return m_data[col_num][row_num];
}

void Board::clear() {
  for (int i = 0; i < num_cols_; ++i) {
    delete [] m_data[i]; //delete each column and set to NULL pointer
    m_data[i] = NULL;
  }
  num_rows_ = 5; //return to original status
  num_cols_ = 4;
  who_win_ = 0;
}

std::ostream& operator<< (std::ostream& ostr, const Board& b) {
  int larger_length = 0;
  if (b.getTokenA().length() >= b.getTokenB().length()) { //check which token has larger length
    larger_length = b.getTokenA().length();
  }
  else {
    larger_length = b.getTokenB().length();
  }
  for (int i = b.numRows()-1; i >= 0; --i) {
    for (int j = 0; j < b.numColumns(); ++j) {
      ostr << setw(larger_length) << b.getElement(j,i); //print each element
      if (j != b.numColumns()-1) {
        ostr << ' ';
      }
      else {
        if (i != 0) {
          ostr << std::endl; //if last element in each non-bottom row
        }
      }
    }
  }
  ostr << std::endl;
  return ostr;
}
#endif