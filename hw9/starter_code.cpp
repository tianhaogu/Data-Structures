#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include "Movie.h"
#include "HashSet.h"
using namespace std;

//hash function from queries
class hash_string_obj {
public:
  unsigned int operator() ( const std::string& key ) const {
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
};

void data_query_processing(ifstream& infile1, vector<string>& six_queries,
                           Movie& one_movie, const string& movie_name) {
  six_queries.push_back(movie_name); //set movie name，and add it to query vector(1)
  string release_year; infile1 >> release_year;
  six_queries.push_back(release_year);
  int release_year_int = stoi(release_year);
  one_movie.setYear(release_year_int); //set movie year，and add it to query vector(2)
  string duration; infile1 >> duration;
  six_queries.push_back(duration);
  int duration_int = stoi(duration);
  one_movie.setDuration(duration_int); //set movie duration, and add it to query vector(3)
  int num_genre; infile1 >> num_genre;
  one_movie.setNumGenre(num_genre);
  string merge_genre;
  for (int i = 0; i < num_genre; ++i) {
    string genre_name; infile1 >> genre_name;
    one_movie.addGenre(genre_name); //add genre names to this movie object
    if (i == 0) {
      merge_genre = genre_name;
    }
    else {
      merge_genre += genre_name;
    }
  }
  six_queries.push_back(merge_genre); //merge all genre names to a string and add it to query vector(4)
  int num_actor; infile1 >> num_actor;
  one_movie.setNumActor(num_actor);
  string merge_actor;
  for (int i = 0; i < num_actor; ++i) {
    string actor_code; infile1 >> actor_code;
    one_movie.addActor(actor_code); //add actor codes to this movie object
    if (i == 0) {
      merge_actor = actor_code;
    }
    else {
      merge_actor += actor_code;
    }
  }
  six_queries.push_back(merge_actor); //merge all actor codes to a string and add it to query vector(5)
  int num_role; infile1 >> num_role;
  one_movie.setNumRole(num_role);
  string merge_role;
  for (int i = 0; i < num_role; ++i) {
    string role_name; infile1 >> role_name;
    one_movie.addRole(role_name); ////add role names to this movie object
    if (i == 0) {
      merge_role = role_name;
    }
    else {
      merge_role += role_name;
    }
  }
  six_queries.push_back(merge_role); //merge all role names to a string and add it to query vector(6)
}

void permute_filters(int pos, vector<string>& six_queries, 
                     vector<vector<string> >& all_queries_comb) {
	if (pos == 6) {
    all_queries_comb.push_back(six_queries); //push back each sub-query to vector containing 64 queries
		return;
	}
  vector<string> new_six_queries = six_queries;
  new_six_queries[pos] = "?"; //substitutue the catagory with '?' for sub-query
	permute_filters(pos+1, six_queries, all_queries_comb);
	permute_filters(pos+1, new_six_queries, all_queries_comb);
}

void permute_filters(vector<string>& six_queries, vector<vector<string> >& all_queries_comb) {
  permute_filters(0, six_queries, all_queries_comb);
}

void print_query(const vector<Movie>& movie_object, const list<int>& movie_index_list,
                 const map<string, string>& actor_search) {
  if (movie_index_list.empty() == true) { //if the list is empty, then no corresponding query
    cout << "No results for query." << endl;
    return;
  }
  int result_count = movie_index_list.size();
  cout << "Printing " << result_count << " result(s):" << endl;
  list<int>::const_iterator itr = movie_index_list.begin();
  for ( ; itr != movie_index_list.end(); itr++) {
    int movie_pos = *itr;
    //use the index in the list, find the position of the movie in the vector, and print all info
    cout << movie_object[movie_pos].getMovieName() << endl;
    cout << movie_object[movie_pos].getMovieYear() << endl;
    cout << movie_object[movie_pos].getMovieDuration() << endl;
    int genre_count = movie_object[movie_pos].getMovieNumGenre();
    cout << genre_count;
    for (int m = 0; m < genre_count; ++m) {
      cout << ' ' << movie_object[movie_pos].getMovieGenre(m);
    }
    cout << endl;
    int actor_count = movie_object[movie_pos].getMovieNumActor();
    cout << actor_count;
    for (int m = 0; m < actor_count; ++m) {
      string actor_code = movie_object[movie_pos].getMovieActorCode(m);
      //search for actor code in the actor map and find its name, print it with corresponding role
      map<string, string>::const_iterator itr1 = actor_search.find(actor_code);
      string actor_name = itr1-> second;
      cout << ' ' << actor_name << " (" << movie_object[movie_pos].getMovieRole(m) << ')';
    }
    cout << endl;
  }
}

typedef HashSet<hash_string_obj> MyHashSet;

int main() {
  string command; string filename1; string filename2;
  map<string, string> actor_search;
  MyHashSet my_hash;
  vector<Movie> movie_object;
  while (cin >> command) {
    if (command == "table_size") {
      int size_n;
      cin >> size_n;
      my_hash.setSize(size_n); //set size of hash table if it appears in input file
    }
    else if (command == "occupancy") {
      float occupancy_f;
      cin >> occupancy_f;
      my_hash.setOccupancy(occupancy_f); //set occupancy of hash table if it appears in input file
    }
    else if (command == "movies") {
      cin >> filename1; ifstream infile1(filename1);
      string movie_name; 
      while (infile1 >> movie_name) {
        vector<string> six_queries; //create a new vector for storing normal queries(no wildcards, just what read from input)
        Movie one_movie(movie_name);
        data_query_processing(infile1, six_queries, one_movie, movie_name); //read data and generate all queries
        movie_object.push_back(one_movie);
        int movie_index = movie_object.size()-1; //add this movie object to the vector for movie class, and get the index
        vector<vector<string> > all_queries_comb;
        //create a large vector for storing 64 vectors for all combinations of queries
        permute_filters(six_queries, all_queries_comb);
        int queries_length = all_queries_comb.size();
        for (int i = 0; i < queries_length; ++i) {
          string hash_key;
          for (int j = 0; j < all_queries_comb[i].size(); ++j) {
            if (j == 0) {
              hash_key = all_queries_comb[i][j];
            }
            else {
              hash_key += all_queries_comb[i][j]; //merge all 6 catagories in 1 query to a string
            }
          }
          //insert the pair, with query string as key, and index of the movie object in the movie vector as value
          my_hash.insert(hash_key, movie_index);
        }
      }
    }
    else if (command == "actors") {
      cin >> filename2; ifstream infile2(filename2);
      string actor_code;
      while (infile2 >> actor_code) {
        string actor_name; infile2 >> actor_name;
        actor_search.insert(make_pair(actor_code, actor_name)); //create a map with actor code as key, name as value
      }
    }
    else if (command == "query") {
      //merge movie name, year and duration in this query as a string
      string merge_all;
      string movie_name; cin >> movie_name; merge_all = movie_name;
      string movie_year; cin >> movie_year; merge_all += movie_year;
      string movie_duration; cin >> movie_duration; merge_all += movie_duration;
      int genre_num; cin >> genre_num;
      if (genre_num == 0) {
        merge_all += "?"; //if genre number is 0, add '?' to the merged string
      }
      else {
        string movie_genre;
        for (int i = 0; i < genre_num; ++i) {
          cin >> movie_genre;
          merge_all += movie_genre; //otherwise merge each genre name to the string
        }
      }
      int actor_num; cin >> actor_num;
      if (actor_num == 0) {
        merge_all += "?"; //if genre number is 0, add '?' to the merged string
      }
      else {
        string movie_actor;
        for (int i = 0; i < actor_num; ++i) {
          cin >> movie_actor;
          merge_all += movie_actor; //otherwise merge each actor code to the string
        }
      }
      int role_num; cin >> role_num;
      if (role_num == 0) {
        merge_all += "?"; //if role number is 0, add '?' to the merged string
      }
      else {
        string movie_role;
        for (int i = 0; i < role_num; ++i) {
          cin >> movie_role;
          merge_all += movie_role; //otherwise merge each role name to the string
        }
      }
      //use to query to find list containing index of all matched movies in the movie class vector
      //then print the results
      list<int> movie_index_list;
      my_hash.extractMovie(merge_all, movie_index_list);
      print_query(movie_object, movie_index_list, actor_search);
    }
    else if (command == "quit") {
      break;
    }
    else {
      cout << "ERROR! Unknown Command!" << endl;
    }
  }
  return 0;
}
