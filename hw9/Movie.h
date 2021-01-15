#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Movie {
public:
  Movie(const string& movie_name); //constructor according to name
  //modifiers start here
  void setYear(int release_year);
  void setDuration(int duration);
  void setNumGenre(int num_genre);
  void setNumActor(int num_actor);
  void setNumRole(int num_role);
  void addGenre(const string& genre_name);
  void addActor(const string& actor_code);
  void addRole(const string& role_name);

  //accesors start here
  const string& getMovieName() const;
  int getMovieYear() const;
  int getMovieDuration() const;
  int getMovieNumGenre() const;
  const string& getMovieGenre(int pos) const;
  int getMovieNumActor() const;
  const string& getMovieActorCode(int pos) const;
  const string& getMovieRole(int pos) const;

private:
  string movie_name_;
  int release_year_;
  int duration_;
  int num_genre_;
  vector<string> genres_;
  int num_actor_;
  vector<string> actors_;
  int num_role_;
  vector<string> roles_;
};