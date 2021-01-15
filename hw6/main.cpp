#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <cassert>
#include "board.h"
using namespace std;

// ==================================================================================
// ==================================================================================

// This function is called if there was an error with the command line arguments
bool usage(const std::string &executable_name) {
  std::cerr << "Usage: " << executable_name << " <puzzle_file>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -visualize <which_robot>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -visualize <which_robot>" << std::endl;
  exit(0);
}

// ==================================================================================
// ==================================================================================

// load a Ricochet Robots puzzle from the input file
Board load(const std::string &executable, const std::string &filename) {

  // open the file for reading
  std::ifstream istr (filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
    usage(executable);
  }

  // read in the board dimensions and create an empty board
  // (all outer edges are automatically set to be walls
  int rows,cols;
  istr >> rows >> cols;
  assert (rows > 0 && cols > 0);
  Board answer(rows,cols);

  // read in the other characteristics of the puzzle board
  std::string token;
  while (istr >> token) {
    if (token == "robot") {
      char a;
      int r,c;
      istr >> a >> r >> c;
      answer.placeRobot(Position(r,c),a);
    } else if (token == "vertical_wall") {
      int i;
      double j;
      istr >> i >> j;
      answer.addVerticalWall(i,j);
    } else if (token == "horizontal_wall") {
      double i;
      int j;
      istr >> i >> j;
      answer.addHorizontalWall(i,j);
    } else if (token == "goal") {
      std::string which_robot;
      int r,c;
      istr >> which_robot >> r >> c;
      answer.addGoal(which_robot,Position(r,c));
    } else {
      std::cerr << "ERROR: unknown token in the input file " << token << std::endl;
      exit(0);
    }
  }

  // return the initialized board
  return answer;
}

//function for calculating reachability of the robot on the board
void calc_reach(int robot_index, Board& board, vector<vector<int> > &reachable_vec, const vector<string> &direction_vec, 
                int original_row, int original_col, bool touch_robot0) {
  for (int i = 0; i < board.numRobots(); ++i) {
    if (i == robot_index) { //skip the targeted robot itself
      continue;
    }
    int another_row = board.getRobotPosition(i).row; //record the position of another robot
    int another_col = board.getRobotPosition(i).col;
    for (int j = 0; j < direction_vec.size(); ++j) { //loop over the 4 directions
      int counter0 = 0;
      while (board.moveRobot(i, direction_vec[j], touch_robot0) == true) { //if it can move
        counter0 += 1;
      }
      if (counter0 != 0) { //if it really moved
        for (int k = 0; k < direction_vec.size(); ++k) { //loop over the 4 directions for the targeted robot
          bool touch_robot = false;
          int counter1 = 0;
          while (board.moveRobot(robot_index, direction_vec[k], touch_robot) == true) { //ifthe targeted robot can move
            counter1 += 1;
          }
          if (touch_robot == true && counter1 != 0) { //if the targeted robot touches another robot after both move
            reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2; //add reachability
          }
          if (touch_robot == false && counter1 != 0) { //if the targeted robot moves but doesn't touch another robot
            int next_row = board.getRobotPosition(robot_index).row; //record the position of the targeted robot after move(s)
            int next_col = board.getRobotPosition(robot_index).col;
            for (int m = 0; m < direction_vec.size(); ++m) {
              bool touch_robot1 = false;
              int counter2 = 0;
              while (board.moveRobot(robot_index, direction_vec[m], touch_robot1) == true) { //if again it can move
                counter2 += 1;
              }
              if (counter2 != 0) {
                //if the position has no reachability and is not the original position of the robot, add reachability
                if (reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] == 0 && 
                    board.getRobotPosition(robot_index).row != original_row && board.getRobotPosition(robot_index).col != original_col) {
                  reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 3;
                }
              }
              else { //if not move return back the targeted robot to the last position
                board.laterplaceRobot(Position(next_row, next_col), robot_index,
                                    Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
              }
            }
          }
          //return back the targeted robot to the original position
          board.laterplaceRobot(Position(original_row, original_col), robot_index,
                                Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
        }
        //return back the another robot to the last position
        board.laterplaceRobot(Position(another_row, another_col), i,
                              Position(board.getRobotPosition(i).row, board.getRobotPosition(i).col), board.getRobot(i));
      }
    }
  }
}

// ==================================================================================
// ==================================================================================

int main(int argc, char* argv[]) {

  // There must be at least one command line argument, the input puzzle file
  if (argc < 2) {
    usage(argv[0]);
  }

  // By default, the maximum number of moves is unlimited
  int max_moves = -1;

  // By default, output one solution using the minimum number of moves
  bool all_solutions = false;

  // By default, do not visualize the reachability
  char visualize = ' ';   // the space character is not a valid robot!

  // Read in the other command line arguments
  for (int arg = 2; arg < argc; arg++) {
    if (argv[arg] == std::string("-all_solutions")) {
      // find all solutions to the puzzle that use the fewest number of moves
      all_solutions = true;
    } else if (argv[arg] == std::string("-max_moves")) {
      // the next command line arg is an integer, a cap on the  # of moves
      arg++;
      assert (arg < argc);
      max_moves = atoi(argv[arg]);
      assert (max_moves > 0);
    } else if (argv[arg] == std::string("-visualize")) {
      // As a first step towards solving the whole problem, with this
      // option, let's visualize where the specified robot can move
      // and how many steps it takes to get there
      arg++;
      assert (arg < argc);
      std::string tmp = argv[arg];
      assert (tmp.size() == 1);
      visualize = tmp[0];
      assert (isalpha(visualize) && isupper(visualize));
      visualize = toupper(visualize);
    } else {
      std::cout << "unknown command line argument" << argv[arg] << std::endl;
      usage(argv[0]);
    }
  }

  // Load the puzzle board from the input file
  Board board = load(argv[0],argv[1]);

  // YOUR CODE STARTS HERE
  vector<vector<int> > reachable_vec; //create the 2D reachability vector
  for (int i = 0; i < board.getRows(); ++i) {
    vector<int> sub_reachable_vec;
    for (int j = 0; j < board.getCols(); ++j) {
      sub_reachable_vec.push_back(0);
    }
    reachable_vec.push_back(sub_reachable_vec);
  }
  int robot_index = 0;
  for (int i = 0; i < board.numRobots(); ++i) {
    if (board.getRobot(i) == visualize) {
      robot_index = i; //get the index of teh targeted robot
      break;
    }
  }
  int original_row = board.getRobotPosition(robot_index).row; //record the original position of targeted robot
  int original_col = board.getRobotPosition(robot_index).col;
  bool touch_robot0 = false;
  for (int i = 0; i < 4; ++i) { //loop over the four directions
    if (i == 0) {
      int count0 = 0;
      while (board.moveRobot(robot_index, "north", touch_robot0) == true) { //if it can move to the north
        count0 += 1;
      }
      //if it has moved, add the step of the stoped position of the robot by one
      if (board.getRobotPosition(robot_index).row != original_row || board.getRobotPosition(robot_index).col != original_col) {
        reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 1;
      }
      int new0_row = board.getRobotPosition(robot_index).row; //record the new position
      int new0_col = board.getRobotPosition(robot_index).col;
      if (count0 != 0) {
        for (int j = 0; j < 2; ++j) { //loop over the two horizontal directions
          if (j == 0) {
            bool touch_robot0 = false;
            while (board.moveRobot(robot_index, "west", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new0_row || board.getRobotPosition(robot_index).col != new0_col) {
              reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
          else {
            while (board.moveRobot(robot_index, "east", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new0_row || board.getRobotPosition(robot_index).col != new0_col) {
              reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
        }
      }
      //return back the targeted robot to the original position
      board.laterplaceRobot(Position(original_row, original_col), robot_index,
                            Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
    }
    else if (i == 1) {
      int count1 = 0;
      while (board.moveRobot(robot_index, "south", touch_robot0) == true) { //if it can move to the south
        count1 += 1;
      }
      //if it has moved, add the step of the stoped position of the robot by one
      if (board.getRobotPosition(robot_index).row != original_row || board.getRobotPosition(robot_index).col != original_col) {
        reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 1;
      }
      int new1_row = board.getRobotPosition(robot_index).row; //record the new position
      int new1_col = board.getRobotPosition(robot_index).col;
      if (count1 != 0) {
        for (int j = 0; j < 2; ++j) { //loop over the two horizontal directions
          if (j == 0) {
            while (board.moveRobot(robot_index, "west", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new1_row || board.getRobotPosition(robot_index).col != new1_col) {
                reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
          else {
            while (board.moveRobot(robot_index, "east", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new1_row || board.getRobotPosition(robot_index).col != new1_col) {
                reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
        }
      }
      //return back the targeted robot to the original position
      board.laterplaceRobot(Position(original_row, original_col), robot_index,
                            Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
    }
    else if (i == 2) {
      int count2 = 0;
      while (board.moveRobot(robot_index, "west", touch_robot0) == true) { //if it can move to the west
        count2 += 1;
      }
      //if it has moved, add the step of the stoped position of the robot by one
      if (board.getRobotPosition(robot_index).row != original_row || board.getRobotPosition(robot_index).col != original_col) {
        reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 1;
      }
      int new2_row = board.getRobotPosition(robot_index).row; //record the new position
      int new2_col = board.getRobotPosition(robot_index).col;
      if (count2 != 0) {
        for (int j = 0; j < 2; ++j) { //loop over the two vertical directions
          if (j == 0) {
            while (board.moveRobot(robot_index, "north", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new2_row || board.getRobotPosition(robot_index).col != new2_col) {
                reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
          else {
            while (board.moveRobot(robot_index, "south", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new2_row || board.getRobotPosition(robot_index).col != new2_col) {
                reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
        }
      }
      //return back the targeted robot to the original position
      board.laterplaceRobot(Position(original_row, original_col), robot_index,
                            Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
    }
    else if (i == 3) {
      int count3 = 0;
      while (board.moveRobot(robot_index, "east", touch_robot0) == true) { //if it can move to the east
        count3 += 1;
      }
      //if it has moved, add the step of the stoped position of the robot by one
      if (board.getRobotPosition(robot_index).row != original_row || board.getRobotPosition(robot_index).col != original_col) {
        reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 1;
      }
      int new3_row = board.getRobotPosition(robot_index).row; //record the new position
      int new3_col = board.getRobotPosition(robot_index).col;
      if (count3 != 0) {
        for (int j = 0; j < 2; ++j) { //loop over the two vertical directions
          if (j == 0) {
            while (board.moveRobot(robot_index, "north", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new3_row || board.getRobotPosition(robot_index).col != new3_col) {
                reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
          else {
            while (board.moveRobot(robot_index, "south", touch_robot0) == true) {
              continue;
            }
            //if again it has moved, add the step of the stoped position of the robot by one
            if (board.getRobotPosition(robot_index).row != new3_row || board.getRobotPosition(robot_index).col != new3_col) {
              reachable_vec[board.getRobotPosition(robot_index).row-1][board.getRobotPosition(robot_index).col-1] += 2;
            }
          }
        }
      }
      //return back the targeted robot to the original position
      board.laterplaceRobot(Position(original_row, original_col), robot_index,
                            Position(board.getRobotPosition(robot_index).row, board.getRobotPosition(robot_index).col), board.getRobot(robot_index));
    }
  }
  board.morereach(robot_index, reachable_vec, max_moves);
  vector<string> direction_vec; //create the directino vector for move
  direction_vec.push_back("north"); direction_vec.push_back("west"); direction_vec.push_back("south"); direction_vec.push_back("east");
  calc_reach(robot_index, board, reachable_vec, direction_vec, original_row, original_col, touch_robot0); //call the function of calculating reachability
  
  cout << "Reachable by robot " << board.getRobot(robot_index) << ":" << endl; //print the reachability
  for (int i = 0; i < board.getRows(); ++i) {
    for (int j = 0; j < board.getCols(); ++j) {
      if ((reachable_vec[i][j] == 0) && (i != original_row-1 || j != original_col-1)) { //if no reachability or it's the original position of the robot
        cout << "  .";
      }
      else {
        cout << "  " << reachable_vec[i][j]; //print the nonzero reachability
      }
    }
    cout << endl;
  }

  // for now...  an example of how to use the board print function
  //board.print();

}

// ================================================================
// ================================================================
