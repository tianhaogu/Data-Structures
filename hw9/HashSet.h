#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;

template <class HashFunction>
class HashSet {
public:
  HashSet(int init_size = 100, float init_occupancy = 0.5) //default constructor
    : hash_table_(init_size), table_occupancy_(init_occupancy), table_size_(init_size), key_size_(0) {}

  HashSet(const HashSet<HashFunction>& old) //copy constructor
    : hash_table_(old.hash_table_), table_occupancy_(old.table_occupancy_), table_size_(old.table_size_), key_size_(old.key_size_) {}

  ~HashSet() {} //destructor

  HashSet& operator=(const HashSet<HashFunction>& old) { //assignment operator
    if (&old != this) {
      this-> hash_table_ = old.hash_table_;
      this-> table_occupancy_ = old.table_occupancy_;
      this-> table_size_ = old.table_size_;
      this-> key_size_ = old.key_size_;
      this-> hash_func_ = old.hash_func_;
    }
    return *this;
  }

  void setSize(int size) { //if the size command appears in input file, set the size
  	hash_table_.resize(size);
  	this-> table_size_ = size;
  }

  void setOccupancy(float occupancy) { //if the occupancy command appears in input file, set the occupancy
  	this-> table_occupancy_ = occupancy;
  }

  void insert(const string& hash_key, int movie_index) {
    int multiplier = 2;
    //if number of keys divide by size of table larger than occupancy level, resize table
    if (key_size_ > int(table_occupancy_ * table_size_)) {
      this-> resize_table(multiplier*table_size_);
    }
    unsigned int hash_value = hash_func_(hash_key);
    unsigned int index = hash_value % table_size_; //hash string and get primary index
    //if this index is not occupied, directly insert the key-value pair (first create list)
    if ((hash_table_[index].first).empty() == true) {
      list<int> movie_index_list0; movie_index_list0.push_back(movie_index);
      hash_table_[index] = make_pair(hash_key, movie_index_list0);
      key_size_ += 1;
    }
    else { //if pre-occipied
      //if the existed query is the same as passed-in query, push back the movie index to the value list
      if (hash_table_[index].first == hash_key) {
        (hash_table_[index].second).push_back(movie_index);
      }
      //if not the query we want, use linear probing to find the next empty index and insert the pair
      else {
        unsigned int probe = (index+1) % table_size_;
        while ((hash_table_[probe].first).empty() == false) {
          probe = (probe+1) % table_size_;
        }
        list<int> movie_index_list1; movie_index_list1.push_back(movie_index);
        hash_table_[probe] = make_pair(hash_key, movie_index_list1);
        key_size_ += 1;
      }
    }
  }

  void extractMovie(const string& merge_all, list<int>& movie_index_list) {
    unsigned int hash_value1 = hash_func_(merge_all);
    unsigned int index1 = hash_value1 % table_size_; //hash the query and find index
    //if the query at the index matches exactly with what we want, copy(get) the list
    if (hash_table_[index1].first == merge_all) {
      movie_index_list = hash_table_[index1].second;
    }
    else { //if the query at the index is not what we want
      unsigned int probe1 = (index1+1) % table_size_;
      while (hash_table_[probe1].first != merge_all) { //use linear probing to find
        //if still not found after one around search of the table, means no such query exists
        if (probe1 == index1) {
          return;
        }
        else { //if find then copy(get) the list
          probe1 = (probe1+1) % table_size_;
        }
      }
      movie_index_list = hash_table_[probe1].second;
    }
  }

private:
  int table_size_;
  int key_size_;
  float table_occupancy_;
  //note that although list is not directly of the Movie type, it stores index information
  //of all the movies to avoid copying of list of movie objects, see readme for detail
  vector<pair<string, list<int> > > hash_table_;
  HashFunction hash_func_;

  void resize_table(int new_size) {
    vector<pair<string, list<int> > > old_table = hash_table_;
    hash_table_.clear();
    hash_table_.resize(new_size);
    table_size_ = new_size; //make a copy of the old table, delete it, and resize
    for (int m = 0; m < old_table.size(); ++m) {
      if ((old_table[m].first).empty() == false) { //if a certain index in old table is occupied
        unsigned int hash_value0 = hash_func_(old_table[m].first);
        unsigned int index0 = hash_value0 % new_size; //hash the query string, and get new index according to new size
        //if the position in the new table is empty, copy the corresponding pair from the old table
        if ((hash_table_[index0].first).empty() == true) {
          hash_table_[index0] = make_pair((old_table[m].first), (old_table[m].second));
        }
        //if the position in the new table is occupied, use linear probing to find empty position and copy pair from old
        else {
          unsigned int probe0 = (index0+1) % new_size;
          while ((hash_table_[probe0].first).empty() == false) {
            probe0 = (probe0+1) % new_size;
          }
          hash_table_[probe0] = make_pair((old_table[m].first), (old_table[m].second));
        }
      }
    }
    old_table.clear();
  }

};