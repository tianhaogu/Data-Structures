#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <array>
using namespace std;

void square(const string &char_str, int &num_height, ofstream &out_str) {
  const string star_line(num_height, '*');
  out_str << star_line << endl; // print the first line of stars first
  vector<vector<char> > middle_part; // create a 2D vector
  if (num_height >= 2) { // check whether the height is greater or equal to 2, if not, exit the program
    for (int i = 0; i < (num_height-2); ++i) { // loop over the figure row by row (excluding stars)
      out_str << '*';
      vector<char> sub_part; // create a vector storing rows of the figure
      for (int j = 0; j < (num_height-2); ++j) { // loop over each line column by column
        int position = (i*(num_height-2)+j) % char_str.size(); // get the index of the targeted character in the input character string 
        sub_part.push_back(char_str[position]); // append the targeted character to each block of the vector
      }
      middle_part.push_back(sub_part); // append the vector to the 2D vector
      for (int k = 0; k < (num_height-2); ++k) { // use loop to print each character in the vector
        out_str << sub_part[k];
      }
      sub_part.clear(); // clear the vector
      out_str << '*' << endl;
    }
    out_str << star_line << endl; // print the last line of stars finally
  }
}

void right_triangle(const string &char_str, int &num_height, ofstream &out_str) {
  const string star_line1(num_height, '*');
  out_str << '*' << endl;
  if (num_height >= 2) {
    out_str << "**" << endl;
  }
  if (num_height >= 3) { // check whether height is larger than or equal to 3, if not, just print the star lins(s) above
    vector<vector<char> > middle_part1;
    for (int i = 0; i < (num_height-3); ++i) { // loop over the figure row by row (excluding stars)
      out_str << '*';
      vector<char> sub_part1; // create a vector storing rows of the figure
      for (int j = 0; j < i+1; ++j) { // loop over each line column by column
        int position1 = (i*(i+1)/2+j) % char_str.size(); // get the index of the targeted character in the input character string 
        sub_part1.push_back(char_str[position1]); // append the targeted character to each block of the vector
      }
      middle_part1.push_back(sub_part1); // append the vector to the 2D vector
      for (int k = 0; k < i+1; ++k) { // use loop to print each character in the vector
        out_str << sub_part1[k];
      }
      sub_part1.clear(); // clear the vector
      out_str << '*' << endl;
    }
    out_str << star_line1 << endl; // print the last line of stars finally
  }
}

void isosceles_triangle(const string &char_str, int &num_height, ofstream &out_str) {
  int num_star = 2*num_height - 1; // calculate the number of stars in the last line according to height
  const string star_line2(num_star, '*');
  int num_space_half;
  vector<vector<char> > middle_part2;
  for (int i = 0; i < (num_height-1); ++i) { // loop over the figure row by row (including stars)
    num_space_half = (num_height-i) - 1; // calculate half length of space in each row
    string space(num_space_half, ' ');
    if (i == 0) {
      out_str << space + '*' << endl; // only print one star and two half spaces in the first line
    }
    else {
      out_str << space + '*'; // print the space and one star in the left half
      vector<char> sub_part2; // create a vector storing rows of the figure
      for (int j = (num_height-i); j < (num_height+i-1); ++j) { // loop over each line column by column
        int previous_level_num = pow((i-1), 2); // calculate number of printed characters in the previous lines
        int same_level_num = j - (num_space_half+1); // calculate number of printed characters left to the targeted character in the same line
        int position2 = (previous_level_num+same_level_num) % char_str.size(); // get the index of the targeted character in the input character string 
        sub_part2.push_back(char_str[position2]); // append the targeted character to each block of the vector
      }
      middle_part2.push_back(sub_part2); // append the vector to the 2D vector
      for (int k = 0; k < (2*i-1); ++k) { // use loop to print each character in the vector
        out_str << sub_part2[k];
      }
      sub_part2.clear(); // clear the vector
      out_str << '*' << endl; // print one star and the space in the right half
    }
  }
  out_str << star_line2 << endl; // print the last line of stars finally
}

int main(int argc, char* argv[]) {
  string char_str(argv[1]); // ascii character string
  string num_height0(argv[2]); // get height
  for (int i = 0; i < num_height0.length(); ++i) { // check whether the height is an integer
    if (!isdigit(num_height0[i])) { // loop over each character to check
      cerr << "ERROR! Number of height not an integer!" << endl;
      exit(0);
    }
  } 
  int num_height(atoi(argv[2])); // transfer it to integer
  string shape_name(argv[3]); // shape of the expected output
  ofstream out_str(argv[4]); // output: write to file
  if (num_height == 0) { // if number of height is zero, then print nothing and exit the program
    out_str << ' ';
    exit(0);
  }
  if (argc != 5) { // check whether the command line argument number is 5
  	cerr << "ERROR! Wrong argument number!" << endl;
  	exit(0);
  }
  if (!out_str.good()) { // check whether the file can be opened correctly
    cerr << "ERROR! File cannot be open!" << endl;
    exit(0);
  }
  else {
    if (shape_name == "square") { // 1. output shape is square
      square(char_str, num_height, out_str); // call square function
    }
    else if (shape_name == "right_triangle") { // 2. output shape is right triangle
      right_triangle(char_str, num_height, out_str); // call right triangle function
    }
    else if (shape_name == "isosceles_triangle") { // 3. output shape is isosceles triangle
      isosceles_triangle(char_str, num_height, out_str); // call isosceles triangle function
    }
    else { // check whether the input shape is defined or not
      cerr << "ERROR! Shape undefined!" << endl;
      exit(0);
    }
  }
  return 0;
}