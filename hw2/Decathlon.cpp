#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "Decathlon.h"
using namespace std;

Decathlon::Decathlon() {
  time_longrun_point_ = 0; //set default point for 1500m
}

const string& Decathlon::first_name() const { //get basic information
  return first_name_;
}

const string& Decathlon::last_name() const {
  return last_name_;
}

const string& Decathlon::nationality() const {
  return nationality_;
}

int Decathlon::get_total_points() const { //get total points for the athelete
  return total_points_;
}

int Decathlon::get_first_length() const {
  return first_name_.length();
}

int Decathlon::get_last_length() const {
  return last_name_.length();
}

int Decathlon::get_output_points(int index) const { //get specific point for certain event
  return output_points_[index];
}

void Decathlon::set_first_name(const string& first_name) { //set basic information
  first_name_ = first_name;
}

void Decathlon::set_last_name(const string& last_name) {
  last_name_ = last_name;
}

void Decathlon::set_nationality(const string& nationality) {
  nationality_ = nationality;
}

void Decathlon::add_event(const string& event_name) { //add event to event vector
  event_names_.push_back(event_name);
}

void Decathlon::add_score_score(double score_score) { //add score except 1500m to score vector 
  score_scores_.push_back(score_score);
}

void Decathlon::add_time_score(int minute, int second, int millisecond) { //add minute, second, millisecond value for 1500m to the 1500m score vector
  time_scores_.push_back(minute);
  time_scores_.push_back(second);
  time_scores_.push_back(millisecond);
}

void Decathlon::calculate_100m(double score_score) { //calculate point according to score for each event and store it in the point vector
  int point = int(25.4347 * pow(18-score_score, 1.81));
  points_.push_back(point);
}

void Decathlon::calculate_long_jump(double score_score) { //same as above
  int point = int(0.14354 * pow(score_score*100-220, 1.4));
  points_.push_back(point);
}

void Decathlon::calculate_short_put(double score_score) { //same as above
  int point = int(51.39 * pow(score_score-1.5, 1.05));
  points_.push_back(point);
}

void Decathlon::calculate_high_jump(double score_score) { //same as above
  int point = int(0.8465 * pow(score_score*100-75, 1.42));
  points_.push_back(point);
}

void Decathlon::calculate_400m(double score_score) { //same as above
  int point = int(1.53775 * pow(82-score_score, 1.81));
  points_.push_back(point);
}

void Decathlon::calculate_110m_hurdles(double score_score) { //same as above
  int point = int(5.74352 * pow(28.5-score_score, 1.92));
  points_.push_back(point);
}

void Decathlon::calculate_discus_throw(double score_score) { //same as above
  int point = int(12.91 * pow(score_score-4, 1.1));
  points_.push_back(point);
}

void Decathlon::calculate_pole_vault(double score_score) { //same as above
  int point = int(0.2797 * pow(score_score*100-100, 1.35));
  points_.push_back(point);
}

void Decathlon::calculate_javelin_throw(double score_score) { //same as above
  int point = int(10.14 * pow(score_score-7, 1.08));
  points_.push_back(point);
}

void Decathlon::calculate_1500m(int minute, int second, int millisecond) { //same as above, except store the point for 1500m seperately as an int
  double score_score = double(60*minute + second + 0.01*millisecond);
  int point = int(0.03768 * pow(480-score_score, 1.85));
  time_longrun_point_ = point;
}

void Decathlon::calculate_total_points() { 
  int sum_up = 0;
  for (int i = 0; i < points_.size(); ++i) {
    sum_up += points_[i]; //sum up points for non-1500m events
  }
  total_points_ = sum_up + time_longrun_point_; //add non-1500m points and 1500m point together
}

ostream& Decathlon::print_scores(ostream& out_str) const {
  int judge1 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //loop over to match the event with that in the event name vector to get the index
    if (event_names_[i] == "100_METERS") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //print the corresponding score
      judge1 += 1;
    }
    if ((i == event_names_.size()-1) && judge1 == 0) { //if no such event in the event name vector
      out_str << setw(7) << string(5, ' '); //print white space
    }
  }
  int judge2 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "LONG_JUMP") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge2 += 1;
    }
    if ((i == event_names_.size()-1) && judge2 == 0) { //same as above
      out_str << setw(7) << string(4, ' '); //same as above
    }
  }
  int judge3 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "SHOT_PUT") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge3 += 1;
    }
    if ((i == event_names_.size()-1) && judge3 == 0) { //same as above
      out_str << setw(7) << string(5, ' '); //same as above
    }
  }
  int judge4 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "HIGH_JUMP") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge4 += 1;
    }
    if ((i == event_names_.size()-1) && judge4 == 0) { //same as above
      out_str << setw(7) << string(4, ' '); //same as above
    }
  }
  int judge5 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "400_METERS") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge5 += 1;
    }
    if ((i == event_names_.size()-1) && judge5 == 0) { //same as above
      out_str << setw(7) << string(5, ' '); //same as above
    }
  }
  int judge6 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "110_METERS_HURDLES") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge6 += 1;
    }
    if ((i == event_names_.size()-1) && judge6 == 0) { //same as above
      out_str << setw(7) << string(5, ' '); //same as above
    }
  }
  int judge7 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "DISCUS_THROW") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge7 += 1;
    }
    if ((i == event_names_.size()-1) && judge7 == 0) { //same as above
      out_str << setw(7) << string(5, ' '); //same as above
    }
  }
  int judge8 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "POLE_VAULT") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge8 += 1;
    }
    if ((i == event_names_.size()-1) && judge8 == 0) { //same as above
      out_str << setw(7) << string(4, ' '); //same as above
    }
  }
  int judge9 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "JAVELIN_THROW") {
      out_str << setw(7) << fixed << setprecision(2) << score_scores_[i]; //same as above
      judge9 += 1;
    }
    if ((i == event_names_.size()-1) && judge9 == 0) { //same as above
      out_str << setw(7) << string(5, ' '); //same as above
    }
  }
  if (time_scores_.size() != 0) { //if the athelete takes the 1500m event
    if (time_scores_[1] >= 10 && time_scores_[2] >= 10) { //print the score, and find digit of each integer to decide whether to add '0' before
      out_str << string(2, ' ') << time_scores_[0] << ':' << time_scores_[1] << '.' << time_scores_[2] << endl;
    }
    else if (time_scores_[1] >= 10 && time_scores_[2] <= 10) {
      out_str << string(2, ' ') << time_scores_[0] << ':' << time_scores_[1] << ".0" << time_scores_[2] << endl;
    }
    else if (time_scores_[1] <= 10 && time_scores_[2] >= 10) {
      out_str << string(2, ' ') << time_scores_[0] << ":0" << time_scores_[1] << '.' << time_scores_[2] << endl;
    }
    else {
      out_str << string(2, ' ') << time_scores_[0] << ":0" << time_scores_[1] << ".0" << time_scores_[2] << endl;
    }
  }
  else { //if he/she doen't take 1500m, print space
    out_str << string(2, ' ') << string(7, ' ') << endl;
  }
  return out_str;
}

ostream& Decathlon::print_points(ostream& out_str) { //function for print the points
  int judge1 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //loop over to match the event with that in the event name vector to get the index
    if (event_names_[i] == "100_METERS") {
      out_str << setw(7) << points_[i]; //print the corresponding point
      output_points_.push_back(points_[i]); //add the point to the output_point vector for custom command
      judge1 += 1;
    }
    if ((i == event_names_.size()-1) && judge1 == 0) { //if no such event, print space
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge2 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "LONG_JUMP") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge2 += 1;
    }
    if ((i == event_names_.size()-1) && judge2 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge3 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "SHOT_PUT") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge3 += 1;
    }
    if ((i == event_names_.size()-1) && judge3 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge4 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "HIGH_JUMP") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge4 += 1;
    }
    if ((i == event_names_.size()-1) && judge4 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge5 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "400_METERS") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge5 += 1;
    }
    if ((i == event_names_.size()-1) && judge5 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge6 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "110_METERS_HURDLES") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge6 += 1;
    }
    if ((i == event_names_.size()-1) && judge6 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge7 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "DISCUS_THROW") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge7 += 1;
    }
    if ((i == event_names_.size()-1) && judge7 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge8 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "POLE_VAULT") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge8 += 1;
    }
    if ((i == event_names_.size()-1) && judge8 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  int judge9 = 0;
  for (int i = 0; i < event_names_.size(); ++i) { //same as above
    if (event_names_[i] == "JAVELIN_THROW") {
      out_str << setw(7) << points_[i]; //same as above
      output_points_.push_back(points_[i]); //same as above
      judge9 += 1;
    }
    if ((i == event_names_.size()-1) && judge9 == 0) { //same as above
      out_str << setw(7) << 0;
      output_points_.push_back(0);
    }
  }
  if (time_scores_.size() != 0) { //if have 1500m event
    out_str << setw(7) << time_longrun_point_; //print 1500m point
    output_points_.push_back(time_longrun_point_); //also add to the output point vector for custom command
  }
  else {
    out_str << setw(7) << 0; //print space if no 1500m event
    output_points_.push_back(0);
  }
  out_str << setw(9) << total_points_ << endl; //print the already calculated total points
  output_points_.push_back(total_points_); //add total point to output point vector for custom command
  return out_str;
}

bool less_country_name(const Decathlon& left, const Decathlon& right) { //sort for scores command according to country abbreviation
  return (left.nationality() < right.nationality()) || //smaller country name
         (left.nationality() == right.nationality() && left.last_name() < right.last_name()) || //smaller last name
         (left.nationality() == right.nationality() && left.last_name() == right.last_name() && left.first_name() < right.first_name()); //smaller first name
}

bool larger_total_points(const Decathlon& left, const Decathlon& right) { //sort for points&custom command according to total points
  return (left.get_total_points() > right.get_total_points()) || //larger total points
         (left.get_total_points() == right.get_total_points() && left.nationality() < right.nationality()) || //smaller country name abbreviation
         (left.get_total_points() == right.get_total_points() && left.nationality() == right.nationality() && left.last_name() < right.last_name()); //smaller name
}