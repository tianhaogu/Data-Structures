#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <map>
#include "Movie.h"
using namespace std;

Movie::Movie(const string& movie_name) { //constructor according to name
  movie_name_ = movie_name;
}

void Movie::setYear(int release_year) { //accesors start here
  release_year_ = release_year;
}

void Movie::setDuration(int duration) {
  duration_ = duration;
}

void Movie::setNumGenre(int num_genre) {
  num_genre_ = num_genre;
}

void Movie::setNumActor(int num_actor) {
  num_actor_ = num_actor;
}

void Movie::setNumRole(int num_role) {
  num_role_ = num_role;
}

void Movie::addGenre(const string& genre_name) {
  genres_.push_back(genre_name);
}

void Movie::addActor(const string& actor_code) {
  actors_.push_back(actor_code);
}

void Movie::addRole(const string& role_name) {
  roles_.push_back(role_name);
}

const string& Movie::getMovieName() const { //accesors start here
  return movie_name_;
}

int Movie::getMovieYear() const {
  return release_year_;
}

int Movie::getMovieDuration() const {
  return duration_;
}

int Movie::getMovieNumGenre() const {
  return num_genre_;
}

const string& Movie::getMovieGenre(int pos) const {
  return genres_[pos];
}

int Movie::getMovieNumActor() const {
  return num_actor_;
}

const string& Movie::getMovieActorCode(int pos) const {
  return actors_[pos];
}

const string& Movie::getMovieRole(int pos) const {
  return roles_[pos];
}