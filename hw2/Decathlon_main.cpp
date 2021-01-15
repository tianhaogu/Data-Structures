#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "Decathlon.h"
using namespace std;

//function for transfering scores to points, use the event name to call different member functions
//for calculating points according to scores, except 1500m which is calculated seperately
void scores_to_points(const string& an_event_name, double a_score_score, Decathlon& a_decathlon) {
  if (an_event_name == "100_METERS") {
    a_decathlon.calculate_100m(a_score_score);
  }
  if (an_event_name == "LONG_JUMP") {
    a_decathlon.calculate_long_jump(a_score_score);
  }
  if (an_event_name == "SHOT_PUT") {
    a_decathlon.calculate_short_put(a_score_score);
  }
  if (an_event_name == "HIGH_JUMP") {
    a_decathlon.calculate_high_jump(a_score_score);
  }
  if (an_event_name == "400_METERS") {
    a_decathlon.calculate_400m(a_score_score);
  }
  if (an_event_name == "110_METERS_HURDLES") {
    a_decathlon.calculate_110m_hurdles(a_score_score);
  }
  if (an_event_name == "DISCUS_THROW") {
    a_decathlon.calculate_discus_throw(a_score_score);
  }
  if (an_event_name == "POLE_VAULT") {
    a_decathlon.calculate_pole_vault(a_score_score);
  }
  if (an_event_name == "JAVELIN_THROW") {
    a_decathlon.calculate_javelin_throw(a_score_score);
  }
}

//function for printing the output to the file for three output types of the command line
void print_output(string output_type, int max_first_length, int max_last_length, 
                  vector<Decathlon>& a_decathlon, ostream& out_str) {
  if (output_type == "scores") {
    sort(a_decathlon.begin(), a_decathlon.end(), less_country_name); //sort the class vector according to country abbreviation then last name
    out_str << "DECATHLETE SCORES";
  }
  else {
    for (int i = 0; i < a_decathlon.size(); ++i) { //calculate total points for each class if command is points or customs
      a_decathlon[i].calculate_total_points();
    }
    sort(a_decathlon.begin(), a_decathlon.end(), larger_total_points); //sort the class vector according to total points
    out_str << "DECATHLETE POINTS";
  }
  out_str << setw(int(max_first_length+4+max_last_length+4+10-17)) << "100" << setw(7) //print the title line
          << "LJ" << setw(7) << "SP" << setw(7) << "HJ" << setw(7) << "400" << setw(7)
          << "110H" << setw(7) << "DT" << setw(7) << "PV" << setw(7) << "JT";
  if (output_type == "scores") {
    out_str << setw(9) << "1500" << endl;
  }
  else {
    out_str << setw(7) << "1500" << setw(9) << "TOTAL" << endl;
  }
  for (int i = 0; i < a_decathlon.size(); ++i) { //loop over each athelete
    out_str << a_decathlon[i].first_name()
            << string(int(max_first_length+4-a_decathlon[i].get_first_length()), ' ')
            << a_decathlon[i].last_name()
            << string(int(max_last_length+4-a_decathlon[i].get_last_length()), ' ')
            << a_decathlon[i].nationality(); //print basic information for each athelete
    if (output_type == "scores") {
      a_decathlon[i].print_scores(out_str); //call the print score member function 
    }
    else {
      a_decathlon[i].print_points(out_str); //call the print points member function
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 4) { //if number of command line argument wrong
    cerr << "ERROR! Incorrect number of command line arguments!" << endl;
    return 1;
  }
  ifstream in_str(argv[1]);
  if (!in_str) { //if cannot open the input file
    cerr << "ERROR! Could not open " << argv[1] << " to read!" << endl;
    return 1;
  }
  ofstream out_str(argv[2]);
  if (!out_str) { //if cannot write to the output file
    cerr << "ERROR! Could not open " << argv[2] << " to write" << endl;
    return 1;
  }
  string output_type(argv[3]); //record output type ... scores/points/custom
  vector<Decathlon> decathlons; //create a vector to store the classes
  string event_label("event"); //strings for reading event label, event name, first&last name, nationality
  string event_name;
  string first_name, last_name;
  string nationality;
  double score_score; //doubles for reading scores except 1500m
  int minute, second, millisecond; //integer for reading elements of time and characters of 1500m
  char colon, decimal;
  vector<int> first_name_length_vec; //create vector to store length of first&last name for printing later
  vector<int> last_name_length_vec;
  in_str >> event_label; //begin to read the event label
  while (in_str >> event_name) { //read the event name, use it as a beginning of a new loop
    while (in_str >> first_name) { //read the first name, begin of loop of info of an athelete of an event
      if (first_name == "event") { //if all information of the previous event has been read and the program reads the event label
        break; //loop out the inner loop, read the event name and begin a new loop
      }
      in_str >> last_name >> nationality; //read last name and nationality
      int whether_exist = 0;
      for (int i = 0; i < decathlons.size(); ++i) {
        if (decathlons[i].first_name() == first_name && decathlons[i].last_name() == last_name) { //if the athelete has attended the event(s) read before
          whether_exist += 1;
          if (event_name != "1500_METERS") { 
            decathlons[i].add_event(event_name); //add the event name to one member variable(vector) of this athelete
            in_str >> score_score; //read the score
            decathlons[i].add_score_score(score_score); //add the score to one member variable(vector) of this athelete
            scores_to_points(event_name, score_score, decathlons[i]); //call the transfer from score to point function
          }
          else {
            in_str >> minute >> colon >> second >> decimal >> millisecond; //read the 1500m score
            decathlons[i].add_time_score(minute, second, millisecond); //add the 1500m score to one member variable(vector) of this athelete
            decathlons[i].calculate_1500m(minute, second, millisecond); //call the transfer from 1500m score to point function
          }
        }
      }
      if (whether_exist == 0) { //if the name is not in the class vector
        Decathlon one_decathlon; //create a new one
        one_decathlon.set_first_name(first_name); //store his/her basic information in the class
        one_decathlon.set_last_name(last_name);
        one_decathlon.set_nationality(nationality);
        int first_name_length = one_decathlon.get_first_length(); //get the length of name to store in length vector for later use
        int last_name_length = one_decathlon.get_last_length();
        first_name_length_vec.push_back(first_name_length);
        last_name_length_vec.push_back(last_name_length);
        if (event_name != "1500_METERS") {
          one_decathlon.add_event(event_name); //add the event name to the class member variable
          in_str >> score_score; //read the score 
          one_decathlon.add_score_score(score_score); //add the score to one member variable(vector) of this athelete
          scores_to_points(event_name, score_score, one_decathlon); //call the transfer from score to point function
        }
        else {
          in_str >> minute >> colon >> second >> decimal >> millisecond; //read the 1500m score
          one_decathlon.add_time_score(minute, second, millisecond); //add the 1500m score to one member variable(vector) of this athelete
          one_decathlon.calculate_1500m(minute, second, millisecond); //call the transfer from 1500m score to point function
        }
        decathlons.push_back(one_decathlon); //add the new create class to the class vector
      }
    }
  }
  int max_first_length = *max_element(first_name_length_vec.begin(), first_name_length_vec.end()); //get the max length for names for print
  int max_last_length = *max_element(last_name_length_vec.begin(), last_name_length_vec.end());
  if (output_type == "scores") { //if the third argument is scores, call the print function
    print_output(output_type, max_first_length, max_last_length, decathlons, out_str);
  }
  else if (output_type == "points") { //if the third argument is points, ......
    print_output(output_type, max_first_length, max_last_length, decathlons, out_str);
  }
  else if (output_type == "custom") { //if the third argument is customs, ......
    print_output(output_type, max_first_length, max_last_length, decathlons, out_str);
    vector<double> average_points; //create vectors for storing average points and standard deviations
    vector<double> stdv_points;
    for (int i = 0; i < 11; ++i) { //for each event
      int sum_points = 0; double average = 0.0;
      double diff = 0.0; double sum_diff = 0.0; double stdv = 0.0;
      for (int j = 0; j < decathlons.size(); ++j) { //for each athelete
        sum_points += decathlons[j].get_output_points(i); //sum up all points of each event
      }
      average = double(sum_points) / decathlons.size(); //calculate average and store in the vector
      average_points.push_back(average);
      for (int k = 0; k < decathlons.size(); ++k) {
        diff = decathlons[k].get_output_points(i) - average; //same thing for calculating standard deviations
        sum_diff += pow(diff,2);
      }
      stdv = double (sqrt(sum_diff / (decathlons.size()-1)));
      stdv_points.push_back(stdv);
    }
    out_str << "Average:" << setw(int(max_first_length+4+max_last_length+4+10-8)); //print label “Average” and space
    for (int i = 0; i < 11; ++i) { //print average point for each event
      if (i == 9) {
        out_str << fixed << setprecision(1) << average_points[i] << setw(9); //space after 1500m
      }
      else if (i == 10) {
        out_str << fixed << setprecision(1) << average_points[i] << endl; //new line after total
      }
      else {
        out_str << fixed << setprecision(1) << average_points[i] << setw(7); //space after first 9 events
      }
    }
    out_str << "Standard Deviation:" << setw(int(max_first_length+4+max_last_length+4+10-19)); //print label “Standard Deviation” and space
    for (int i = 0; i < 11; ++i) {
      if (i == 9) {
        out_str << fixed << setprecision(1) << stdv_points[i] << setw(9); //space after 1500m
      }
      else if (i == 10) {
        out_str << fixed << setprecision(1) << stdv_points[i] << endl; //new line after total
      }
      else {
        out_str << fixed << setprecision(1) << stdv_points[i] << setw(7); //space after first 9 events
      }
    }
  }
  else { //if the output type name is undefined
    cerr << "ERROR! Undefined output type!" << endl;
    return 1;
  }
  return 0;
}