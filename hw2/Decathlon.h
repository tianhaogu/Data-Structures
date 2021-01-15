#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <algorithm>
using namespace std;

class Decathlon {
public:
  Decathlon(); //default constructor
  const string& first_name() const; //get basic personal information
  const string& last_name() const;
  const string& nationality() const;
  int get_total_points() const; //get points and length
  int get_first_length() const;
  int get_last_length() const;
  int get_output_points(int index) const;

  void set_first_name(const string& first_name); //set basic personal information
  void set_last_name(const string& last_name);
  void set_nationality(const string& nationality);
  void add_event(const string& event_name); //store event names, scores for both 1500m and non-1500m
  void add_score_score(double score_score);
  void add_time_score(int minute, int second, int millisecond);

  void calculate_100m(double score_score); //calculate points according to scores
  void calculate_long_jump(double score_score);
  void calculate_short_put(double score_score);
  void calculate_high_jump(double score_score);
  void calculate_400m(double score_score);
  void calculate_110m_hurdles(double score_score);
  void calculate_discus_throw(double score_score);
  void calculate_pole_vault(double score_score);
  void calculate_javelin_throw(double score_score);
  void calculate_1500m(int minute, int second, int millisecond);
  void calculate_total_points(); //calculate total point
  
  ostream& print_scores(ostream& out_str) const; //print scores and points
  ostream& print_points(ostream& out_str);

private:
  string first_name_; //basic information variables
  string last_name_;
  string nationality_;
  vector<string> event_names_; //event name variable except 1500m
  vector<double> score_scores_; //score vector for non-1500m events
  vector<int> time_scores_; //vector for storing minute, second and millisecond of 1500m
  vector<int> points_; //point vector except 1500m
  int time_longrun_point_; //1500m point
  int total_points_; 
  vector<int> output_points_; //point vector for both 1500m and non-1500m events
};

bool less_country_name(const Decathlon& left, const Decathlon& right); //for sort function 
bool larger_total_points(const Decathlon& left, const Decathlon& right);