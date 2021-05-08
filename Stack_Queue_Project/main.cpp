// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <getopt.h>
#include <cstdio>
using namespace std; 

struct Point {
  Point(int init_room = -1, int init_row = -1, int init_col = -1, 
        char init_symbol = '.', bool init_discovered = false, 
        char init_direction = ' ', char init_destination = ' ')
      : room_pos(init_room), row_pos(init_row), col_pos(init_col)
        , symbol(init_symbol), discovered(init_discovered)
        , orig_direct(init_direction), destination(init_destination) {}
  ~Point() {}
  int room_pos; 
  int row_pos; 
  int col_pos; 
  char symbol; 
  bool discovered; 
  char orig_direct; 
  char destination; 
}; 

void invalidMapChar(char& character_input) {
  if (!(isdigit(character_input) || character_input == '.' 
     || character_input == '#' || character_input == '!' || 
        character_input == 'S' || character_input == 'C')) {
        cerr << "ERROR! " << character_input << " is an invalid map "
                "character!" << endl; 
    exit(1); 
  }
}

void getOptions(int argc, char* argv[], char& sq_mode, char& ml_out) {
  int option_index = 0, option = 0;
  struct option longOpts[] = {{ "stack", no_argument, nullptr, 's' },
                              { "queue", no_argument, nullptr, 'q'},
                              { "output", required_argument, nullptr, 'o'},
                              { "help", no_argument, nullptr, 'h' },
                              { nullptr, 0, nullptr, '\0' }};
  while ((option = getopt_long(argc, argv, "sqo:h", longOpts, 
          &option_index)) != -1) {
  	switch (option) {
  	  case 's':
        if (sq_mode == 's' || sq_mode == 'q') {
          cerr << "ERROR! More than one stack or queue on command line!" 
               << endl; 
          exit(1); 
        }
  	    sq_mode = 's'; 
  	    break; 
  	  case 'q':
        if (sq_mode == 's' || sq_mode == 'q') {
          cerr << "ERROR! More than one stack or queue on command line!" 
               << endl; 
          exit(1); 
        }
  	    sq_mode = 'q'; 
  	    break; 
  	  case 'o':
        ml_out = *optarg; 
        if (!(ml_out == 'M' || ml_out == 'L')) {
          cerr << "ERROR: Output mode wrong!" << endl; 
          exit(1); 
        }
        break; 
      case 'h':
        std::cout << "This program reads a TXT file that contains input version,\n"
                  << "number of rooms in the castle, size of each room, and all characters\n"
                  <<  "in each room. It uses stack or queue mode to search for valid paths\n"
                  <<  "depending on whether it's stack or queue mode in the command lin arguments\n"
                  <<  "It then prints the path from the beginning position to\n"
                  <<  "the end position in the command line arguments (depends on whether it's\n"
                  <<  "map output mode or list output mode), which defaults to M.\n"
                  <<  "Usage: \'./project1\n\t[--stack | -s]\n"
                  <<                      "\t[--queue | -q]\n"
                  <<                      "\t[--output | -o] <M or L mode>\n"
                  <<                      "\t[--help | -h]\n"
                  <<                      "\t< <TXT Castle File>\'" << std::endl; 
        exit(0); 
  	}
  	if (!ml_out) {
  	  ml_out = 'M'; 
  	}
  	if (!sq_mode) {
  	  cerr << "ERROR! Stack or Queue mode is not specified!" << endl; 
  	  exit(1); 
  	}
  }
}

void readData(vector<vector<vector<Point> > >& castle_structure, 
              int (&start)[3], int (&end)[3], int& room_num, int& room_size) {
  char input_mode; 
  int room_sign; 
  string symbol_castle; 
  string symbol_room; 
  char each_symbol; 
  cin >> input_mode >> ws; 
  cin >> room_num >> ws; 
  cin >> room_size >> ws; 
  Point one_point; 
  castle_structure.resize(room_num, vector<vector<Point> >
                         (room_size, vector<Point>(room_size, one_point))); 
  if (input_mode == 'M') {
    for (int i = 0; i < room_num; ++i) {
      cin >> symbol_castle >> symbol_room >> room_sign >> std::ws; 
      for (int j = 0; j < room_size; ++j) {
        for (int k = 0; k < room_size; ++k) {
          castle_structure[i][j][k].room_pos = i; 
          castle_structure[i][j][k].row_pos = j; 
          castle_structure[i][j][k].col_pos = k; 
          cin >> each_symbol; 
          invalidMapChar(each_symbol); 
          if (each_symbol == 'S') {
            start[0] = i; start[1] = j; start[2] = k; 
          }
          if (each_symbol == 'C') {
            end[0] = i; end[1] = j; end[2] = k; 
          }
          castle_structure[i][j][k].symbol = each_symbol; 
        }
      }
    }
  }
  else if (input_mode == 'L') {
    int lst_room; 
    int lst_row; 
    int lst_col; 
    char spec_symbol; //char lst_pos_symbol;
    while (cin >> spec_symbol) {
      cin >> symbol_castle >> symbol_room >> room_sign >> std::ws;
      while (cin >> spec_symbol) {
        if (spec_symbol == '/') {
          break;
        }
        cin >> lst_room >> spec_symbol >> lst_row >> spec_symbol >> lst_col 
            >> spec_symbol >> each_symbol >> spec_symbol >> std::ws;
        if (lst_room != room_sign) {
          cerr << "ERROR! Room " << lst_room << " doesn't exist!" << endl; 
          exit(1); 
        }
        if (lst_row >= room_size) {
          cerr << "ERROR! Row " << lst_row << " doesn't exist!" << endl; 
          exit(1); 
        }
        if (lst_col >= room_size) {
          cerr << "ERROR! Col " << lst_col << " doesn't exist!" << endl; 
          exit(1); 
        }
        invalidMapChar(each_symbol); 
        castle_structure[lst_room][lst_row][lst_col].room_pos = lst_room; 
        castle_structure[lst_room][lst_row][lst_col].row_pos = lst_row; 
        castle_structure[lst_room][lst_row][lst_col].col_pos = lst_col; 
        castle_structure[lst_room][lst_row][lst_col].symbol = each_symbol; 
        if (each_symbol == 'S') {
          start[0] = lst_room; start[1] = lst_row; start[2] = lst_col; 
        }
        if (each_symbol == 'C') {
          end[0] = lst_room; end[1] = lst_row; end[2] = lst_col; 
        }
      }
    }
    for (int i = 0; i < room_num; ++i) {
      for (int j = 0; j < room_size; ++j) {
        for (int k = 0; k < room_size; ++k) {
          if ((castle_structure[i][j][k]).room_pos == -1) {
            castle_structure[i][j][k].room_pos = i; 
            castle_structure[i][j][k].row_pos = j; 
            castle_structure[i][j][k].col_pos = k; 
          }
        }
      }
    }
  }
  else {
    cerr << "ERROR! Unknown input model!" << endl; 
    exit(0); 
  }
}

void invSearch(vector<vector<vector<Point> > >& castle_structure, int room_num, 
               int room_size, int (&start)[3], bool& whether_success, 
               int& count_discovered, char& sq_mode) {
  deque<Point> container; 
  container.push_back(castle_structure[start[0]][start[1]][start[2]]); 
  //Point* curr_loc;
  //curr_loc = &castle_structure[start[0]][start[1]][start[2]];
  castle_structure[start[0]][start[1]][start[2]].discovered = true; 
  int curr_room = start[0]; 
  int curr_row = start[1]; 
  int curr_col = start[2]; 
  bool on_pipe = false; //bool whether_start = true;
  int enter_room; 
  bool pipe_valid = true; 
  while (!container.empty()) { 
    if (sq_mode == 's') { 
      container.pop_back(); 
    }
    else {
      container.pop_front(); 
    }
    if (isdigit((castle_structure[curr_room][curr_row][curr_col]).symbol) 
                 == true) {
      on_pipe = true;
      enter_room = static_cast<int>
            ((castle_structure[curr_room][curr_row][curr_col]).symbol - '0'); 
      if (enter_room >= room_num || enter_room == curr_room) {
        pipe_valid = false; 
      }
      if (pipe_valid == true) {
        /*if (castle_structure[enter_room][curr_row][curr_col].symbol != '#' && 
            castle_structure[enter_room][curr_row][curr_col].symbol != '!' && 
            castle_structure[enter_room][curr_row][curr_col].discovered == true) {
          on_pipe = false;
        }*/
        if (!(castle_structure[enter_room][curr_row][curr_col].symbol == '#' || 
              castle_structure[enter_room][curr_row][curr_col].symbol == '!' || 
              castle_structure[enter_room][curr_row][curr_col].discovered 
              == true)) {
          container.push_back(castle_structure[enter_room][curr_row][curr_col]); 
          (castle_structure[enter_room][curr_row][curr_col]).discovered = true; 
          (castle_structure[enter_room][curr_row][curr_col]).orig_direct = 
           static_cast<char>('0' + curr_room);
          count_discovered += 1; 
        }
        //else {
        //}
      }
    }
    if (on_pipe == false) {
      if (curr_row != 0 && 
          castle_structure[curr_room][curr_row-1][curr_col].discovered == false 
          && !(castle_structure[curr_room][curr_row-1][curr_col].symbol == '#' || 
          castle_structure[curr_room][curr_row-1][curr_col].symbol == '!')) {
        container.push_back(castle_structure[curr_room][curr_row-1][curr_col]); 
        (castle_structure[curr_room][curr_row-1][curr_col]).discovered = true;
        (castle_structure[curr_room][curr_row-1][curr_col]).orig_direct = 'N'; 
        count_discovered += 1; 
        if (castle_structure[curr_room][curr_row-1][curr_col].symbol == 'C') {
          whether_success = true; 
          break; 
        }
      }
      if (curr_col != room_size-1 && 
          castle_structure[curr_room][curr_row][curr_col+1].discovered == false
          && !(castle_structure[curr_room][curr_row][curr_col+1].symbol == '#' || 
          castle_structure[curr_room][curr_row][curr_col+1].symbol == '!')) {
        container.push_back(castle_structure[curr_room][curr_row][curr_col+1]); 
        (castle_structure[curr_room][curr_row][curr_col+1]).discovered = true; 
        (castle_structure[curr_room][curr_row][curr_col+1]).orig_direct = 'E'; 
        count_discovered += 1; 
        if (castle_structure[curr_room][curr_row][curr_col+1].symbol == 'C') {
          whether_success = true; 
          break; 
        }
      }
      if (curr_row != room_size-1 && 
          castle_structure[curr_room][curr_row+1][curr_col].discovered == false
          && !(castle_structure[curr_room][curr_row+1][curr_col].symbol == '#' ||
          castle_structure[curr_room][curr_row+1][curr_col].symbol == '!')) {
        container.push_back(castle_structure[curr_room][curr_row+1][curr_col]); 
        (castle_structure[curr_room][curr_row+1][curr_col]).discovered = true; 
        (castle_structure[curr_room][curr_row+1][curr_col]).orig_direct = 'S'; 
        count_discovered += 1; 
        if (castle_structure[curr_room][curr_row+1][curr_col].symbol == 'C') {
          whether_success = true; 
          break; 
        }
      }
      if (curr_col != 0 
          && castle_structure[curr_room][curr_row][curr_col-1].discovered == false
          && !(castle_structure[curr_room][curr_row][curr_col-1].symbol == '#' ||
          castle_structure[curr_room][curr_row][curr_col-1].symbol == '!')) {
        container.push_back(castle_structure[curr_room][curr_row][curr_col-1]); 
        (castle_structure[curr_room][curr_row][curr_col-1]).discovered = true; 
        (castle_structure[curr_room][curr_row][curr_col-1]).orig_direct = 'W'; 
        count_discovered += 1; 
        if (castle_structure[curr_room][curr_row][curr_col-1].symbol == 'C') {
          whether_success = true; 
          break; 
        }
      }
    }
    if (container.empty()) {
      break; 
    }
    if (sq_mode == 's') {
      curr_room = (container.back()).room_pos; 
      curr_row = (container.back()).row_pos; 
      curr_col = (container.back()).col_pos; 
      //container.pop_back();
    }
    else { //sq_mode == 'q'
      curr_room = (container.front()).room_pos; 
      curr_row = (container.front()).row_pos; 
      curr_col = (container.front()).col_pos; 
      //container.pop_front();
    }
    //curr_loc = &castle_structure[curr_room][curr_row][curr_col];
    on_pipe = false; 
    pipe_valid = true; 
  }
  //delete curr_loc;
  //curr_loc = NULL;
}

void backTrace(vector<vector<vector<Point> > >& castle_structure, 
               int (&start)[3], int (&end)[3], char& ml_out, 
               deque<Point>& list_path) {
  //Point* backtrace;
  //backtrace = &castle_structure[end[0]][end[1]][end[2]];
  int back_room = end[0]; int back_row = end[1]; int back_col = end[2]; 
  int from_room; //int count = 0;
  while (!(back_room == start[0] && back_row == start[1] && back_col 
           == start[2])) {
    if ((castle_structure[back_room][back_row][back_col]).orig_direct 
         == 'N') {
      (castle_structure[back_room][back_row+1][back_col]).destination = 'n'; 
      back_row += 1; 
      //backtrace = &(castle_structure[back_room][back_row][back_col]);
    }
    else if ((castle_structure[back_room][back_row][back_col]).orig_direct 
              == 'E') {
      (castle_structure[back_room][back_row][back_col-1]).destination = 'e'; 
      back_col -= 1; 
      //backtrace = &(castle_structure[back_room][back_row][back_col]);
    }
    else if ((castle_structure[back_room][back_row][back_col]).orig_direct 
              == 'S') {
      (castle_structure[back_room][back_row-1][back_col]).destination = 's'; 
      back_row -= 1; 
      //backtrace = &(castle_structure[back_room][back_row][back_col]);
    }
    else if ((castle_structure[back_room][back_row][back_col]).orig_direct 
              == 'W') {
      (castle_structure[back_room][back_row][back_col+1]).destination = 'w'; 
      back_col += 1; 
      //backtrace = &(castle_structure[back_room][back_row][back_col]);
    }
    else {
    }
    if (isdigit((castle_structure[back_room][back_row][back_col]).orig_direct)) {
      if (ml_out == 'L') {
        list_path.push_back(castle_structure[back_room][back_row][back_col]); 
      }
      from_room = static_cast<int>
      (castle_structure[back_room][back_row][back_col].orig_direct - '0'); 
      (castle_structure[from_room][back_row][back_col]).destination = 'p'; 
      back_room = from_room; 
      //backtrace = &(castle_structure[from_room][back_row][back_col]);
    }
    if (ml_out == 'L') {
      list_path.push_back(castle_structure[back_room][back_row][back_col]); 
    }
  }
  //delete backtrace; backtrace = NULL;
}

void printPath(const vector<vector<vector<Point> > >& castle_structure, 
               int room_num, int room_size, int (&start)[3], 
               char& ml_out, deque<Point>& list_path) {
  if (ml_out == 'M') {
    cout << "Start in room " << start[0] << ", row " << start[1] 
         << ", column " << start[2] << endl; 
    for (int i = 0; i < room_num; ++i) {
      cout << "//castle room " << i << endl; 
      for (int j = 0; j < room_size; ++j) {
        for (int k = 0; k < room_size; ++k) {
          if (!(castle_structure[i][j][k].destination == ' ')) {
            cout << (castle_structure[i][j][k]).destination; 
          }
          else {
            cout << castle_structure[i][j][k].symbol; 
          }
        }
        cout << endl; 
      }
    }
  }
  else {
    cout << "Path taken:" << endl; 
    while (!list_path.empty()) {
      cout << '(' << (list_path.back()).room_pos << ',' 
           << (list_path.back()).row_pos << ',' << (list_path.back()).col_pos
           << ',' << (list_path.back()).destination << ')' << endl; 
      list_path.pop_back(); 
    }
  }
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false); 
  try {
    char sq_mode; 
    char ml_out; 
    getOptions(argc, argv, sq_mode, ml_out); 
    vector<vector<vector<Point> > > castle_structure; 
    int start[3] = {-1,-1,-1}; 
    int end[3] = {-1,-1,-1}; 
    int room_num; 
    int room_size; 
    readData(castle_structure, start, end, room_num, room_size); 
    bool whether_success = false; int count_discovered = 1; 
    invSearch(castle_structure, room_num, room_size, start, whether_success, 
              count_discovered, sq_mode);
    if (whether_success == true) {
      deque<Point> list_path; 
      backTrace(castle_structure, start, end, ml_out, list_path);
      printPath(castle_structure, room_num, room_size, start, ml_out, 
                list_path); 
    }
    else {
      cout << "No solution, " << count_discovered 
           << " tiles discovered." << endl; 
    }
  }
  catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl; 
    return 1; 
  }
  return 0; 
}