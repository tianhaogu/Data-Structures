#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Fighters.h"
using namespace std;

/* I define two kinds of maps and one kind of set ihere. The first map is created by reading data,
of which key is name of the fighter and value is the Fighters class where private variable is also
a map storing move name and frame. The second map is created after data structure is transfered for
q & f & s command, of which key is the name of the move, and value is another map where key is frame
and value is a set of fighters that has move of this frame. The described above is the third typedef
below. Note that this set typedef is also used for only storing the 7 moves after reading the first
line of the dbfile (same as the array given), but it's automatically sorted so I can directly use it
after the q command is called.
*/
typedef map<string, Fighters> FIGHTER_WHOLE_INFO;
typedef map<string, map<int, set<string> > > MOVE_WHOLE_INFO;
typedef set<string> NAME_MOVE_CHAR;
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

// prototypes for the five functions
void Query(const string& in_char_name, const string& in_move_type, FIGHTER_WHOLE_INFO &fighter_allinfo_map, 
           NAME_MOVE_CHAR &move_name_set, ostream &outfile);
void Transfer_Structure(FIGHTER_WHOLE_INFO &fighter_allinfo_map, MOVE_WHOLE_INFO &move_allinfo_map, 
                        NAME_MOVE_CHAR &move_name_set);
void D_move(const string& in_move_type, int in_move_limit, MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile);
void Fast_move(const string& in_move_type, int in_move_limit, MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile);
void Slow_move(const string& in_move_type, int in_move_limit, MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile);

int main(int argc, char** argv) {
  //deal with arguments errors
  if (argc != 4) {
	  std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
	  return -1;
  }
  std::ifstream dbfile(argv[1]);
  if (!dbfile) {
	  std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
  }
  std::ifstream infile(argv[2]);
  if (!infile) {
	  std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
  }
  std::ofstream outfile(argv[3]);
  if (!outfile) {
	  std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
  }
  //create all maps and sets and strings & ints for reading the files
  string character_title; string character_name;
  string move_title; int move_frame;
  NAME_MOVE_CHAR move_name_set;
  FIGHTER_WHOLE_INFO fighter_allinfo_map;
  MOVE_WHOLE_INFO move_allinfo_map;
  dbfile >> character_title;
  for (int i = 0; i < 7; ++i) { //read 7 names of moves and store them in the set
  	dbfile >> move_title; 
  	move_name_set.insert(move_title);
  }
  while (dbfile >> character_name) {
    Fighters one_fighter(character_name); //create the fighter class after reading names
    for (int i = 0; i < move_name_set.size(); ++i) { //store move names and frames in the class using map as private
      dbfile >> move_frame;
      one_fighter.storeInfo(move_names[i], move_frame);
    } //insert fighter name and class as a pair into the first map
    fighter_allinfo_map.insert(make_pair(character_name, one_fighter)); 
  }
  //create strings and ints for commands and corresponding information
  string command;
  string in_char_name;
  string in_move_type; int in_move_limit;
  int count_transfer = 0;
  while (infile >> command) {
    if (command == "-q") { //call Query function after reading information of q command
      infile >> in_char_name;
      infile >> in_move_type;
      Query(in_char_name, in_move_type, fighter_allinfo_map, move_name_set, outfile);
    }
    else {
      if (count_transfer == 0) {
        Transfer_Structure(fighter_allinfo_map, move_allinfo_map, move_name_set);
      }
      infile >> in_move_type;
      infile >> in_move_limit;
      if (command == "-d") {
        count_transfer += 1;
        D_move(in_move_type, in_move_limit, move_allinfo_map, outfile);
      }
      else if (command == "-f") {
        count_transfer += 1;
        Fast_move(in_move_type, in_move_limit, move_allinfo_map, outfile);
      }
      else if (command == "-s") {
        count_transfer += 1;
        Slow_move(in_move_type, in_move_limit, move_allinfo_map, outfile);
      }
      else {
        outfile << "Unknown Command!!!" << endl;
      }
    }
  }
  return 0;
}

void Query(const string& in_char_name, const string& in_move_type, 
           FIGHTER_WHOLE_INFO &fighter_allinfo_map, NAME_MOVE_CHAR &move_name_set, ostream &outfile) {
  FIGHTER_WHOLE_INFO::iterator itr = fighter_allinfo_map.find(in_char_name);
  if (itr == fighter_allinfo_map.end()) { //if no such fighter exists
    outfile << "Invalid character name: " << in_char_name << endl;
  }
  else {
    string char_name = itr-> first;
    if (in_move_type != "all") {
      int fighter_moveframe = (itr-> second).getFrameInMove(in_move_type); //get frame number in the map 
      if (fighter_moveframe == -1) {                                       //of the fighter class
        outfile << "Invalid move name: " << in_move_type << endl;
      }
      else { //print the name of character, name of the certain move and frame of move
        outfile << char_name << ' ' << in_move_type << ": " << fighter_moveframe << endl;
      }
    }
    else { //same as above, this print print all moves and frames of moves of this character
      for (NAME_MOVE_CHAR::iterator itr1 = move_name_set.begin(); itr1 != move_name_set.end(); itr1++) {
        int fighter_moveframe_each = (itr-> second).getFrameInMove((*itr1));
        outfile << char_name << ' ' << (*itr1) << ": " << fighter_moveframe_each << endl;
      }
    }
  }
  outfile << endl;
}

void Transfer_Structure(FIGHTER_WHOLE_INFO &fighter_allinfo_map, 
                        MOVE_WHOLE_INFO &move_allinfo_map, NAME_MOVE_CHAR &move_name_set) {
  FIGHTER_WHOLE_INFO::iterator itr2 = fighter_allinfo_map.begin();
  for ( ; itr2 != fighter_allinfo_map.end(); itr2++) { //for each character (key) in the first map
    if (itr2 == fighter_allinfo_map.begin()) { //if it's the first character (key)
      for (int i = 0; i < move_name_set.size(); ++i) { //for each move name in the set
        string movename_of_fighter = (itr2-> second).getFrameName(i); //get name & frame of move in the map of fighter class
        int moveframe_of_fighter = (itr2-> second).getFrameInMove(movename_of_fighter);
        NAME_MOVE_CHAR temp_set; //create a temporary set to store the name of the first fighter
        temp_set.insert(itr2-> first);
        map<int, NAME_MOVE_CHAR > temp_map; //create a temporary map to store the first frame and fighter pair
        temp_map.insert(make_pair(moveframe_of_fighter, temp_set));
        move_allinfo_map.insert(make_pair(movename_of_fighter, temp_map)); //form move name and temporary map as a pair 
      }                                                                    //and insert into the second map
    }
    else { //if previous pair(s) has(have) already inserted into the second map
      MOVE_WHOLE_INFO::iterator itr3 = move_allinfo_map.begin();
      for (int i = 0; i < move_name_set.size(); ++i) { //for each move name in the set
        string movename_of_fighter1 = (itr2-> second).getFrameName(i);
        int moveframe_of_fighter1 = (itr2-> second).getFrameInMove(movename_of_fighter1);
        map<int, NAME_MOVE_CHAR >::iterator itr_search = (itr3-> second).find(moveframe_of_fighter1);
        if (itr_search == (itr3-> second).end()) { //if the frame of such move has not yet existed in the value map
          NAME_MOVE_CHAR temp_set1; //create a temporary set to store and fighter name and insert the pair in the value map
          temp_set1.insert(itr2-> first);
          (itr3-> second).insert(make_pair(moveframe_of_fighter1, temp_set1));
        }
        else { //if the frame of such move exists in the value map
          (itr_search-> second).insert(itr2-> first); //insert the fighter name into the set
        }
        itr3++;
      }
    }
  }
}

void D_move(const string& in_move_type, int in_move_limit, 
            MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile) {
  MOVE_WHOLE_INFO::iterator itr4 = move_allinfo_map.find(in_move_type);
  if (itr4 == move_allinfo_map.end()) {
    outfile << "Invalid move name: " << in_move_type << endl;
  }
  else {
    //find the targeted frame of this move
    map<int, NAME_MOVE_CHAR >::iterator itr_search1 = (itr4-> second).find(in_move_limit);
    if (itr_search1 == (itr4-> second).end()) { //no such frame exists
      outfile << "Invalid move limit: " << in_move_limit << " of " << in_move_type << endl;
    }
    else {
      outfile << "-d " << in_move_type << ' ' << in_move_limit << endl;
      for (NAME_MOVE_CHAR::iterator itr_set = (itr_search1-> second).begin(); 
           itr_set != (itr_search1-> second).end(); itr_set++) {
        outfile << (*itr_set) << endl; //print all the fighter names in the set
      }
    }
  }
  outfile << endl;
}

void Fast_move(const string& in_move_type, int in_move_limit, 
               MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile) {
  int move_accum = 0;
  MOVE_WHOLE_INFO::iterator itr5 = move_allinfo_map.find(in_move_type);
  if (itr5 == move_allinfo_map.end()) {
    outfile << "Invalid move name: " << in_move_type << endl;
  }
  else { //if the name of the move exists in the second map
    outfile << "-f " << in_move_type << ' ' << in_move_limit << endl;
    bool check_limit = false;
    for (map<int, NAME_MOVE_CHAR >::iterator itr_search2 = (itr5-> second).begin(); 
         itr_search2 != (itr5-> second).end(); itr_search2++) { //for each frame of targed move
      for (NAME_MOVE_CHAR::iterator itr_set1 = (itr_search2-> second).begin(); 
           itr_set1 != (itr_search2-> second).end(); itr_set1++) { //for each fighter in the set
        if (move_accum < in_move_limit) { //if it's the 20 fastest fighter of this move
          outfile << (*itr_set1) << ' '  << (itr_search2-> first) << endl;
          move_accum += 1;
        }
        else { //break the two for loops if limit reaches
          check_limit = true;
          break;
        }
      }
      if (check_limit == true) {
        break;
      }
    }
  }
  outfile << endl;
}

void Slow_move(const string& in_move_type, int in_move_limit, 
               MOVE_WHOLE_INFO &move_allinfo_map, ostream &outfile) {
  int move_accum1 = 0;
  MOVE_WHOLE_INFO::iterator itr6 = move_allinfo_map.find(in_move_type);
  if (itr6 == move_allinfo_map.end()) {
    outfile << "Invalid move name: " << in_move_type << endl;
  }
  else { //if the name of the move exists in the second map
    outfile << "-s " << in_move_type << ' ' << in_move_limit << endl;
    bool check_limit1 = false;
    for (map<int, NAME_MOVE_CHAR >::reverse_iterator itr_search3 = (itr6-> second).rbegin(); 
         itr_search3 != (itr6-> second).rend(); itr_search3++) { //for each frame of targed move
      for (NAME_MOVE_CHAR::iterator itr_set2 = (itr_search3-> second).begin(); 
           itr_set2 != (itr_search3-> second).end(); itr_set2++) { //for each fighter in the set
        if (move_accum1 < in_move_limit) { //if it's the 20 slowest fighter of this move
          outfile << (*itr_set2) << ' ' << (itr_search3-> first) << endl;
          move_accum1 += 1;
        }
        else { //break the two for loops if limit reaches
          check_limit1 = true;
          break;
        }
      }
      if (check_limit1 == true) {
        break;
      }
    }
  }
  outfile << endl;
}