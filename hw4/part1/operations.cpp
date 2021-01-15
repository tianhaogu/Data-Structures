#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint; 


// FUNCTION PROTOTYPES
int arithmetic_operations(int &secret_code);
int array_operations(int &secret_code);
bool close_enough(double d1, double d2);
void corned_beef_hash(int* output, int input);
bool decrypt(int array[4], char* bufPtr, int bufLen, const char* outFile);
std::string file_operations(int argc, char** argv, char*& returned_buffer, int& retlen);
unsigned int hash_browns(unsigned int input);
int list_operations(int &secret_code);
float multidivide(int numerator, int d1, int d2, int d3, int d4);
int pythagoras(int x, int y);
bool vector_compare(const std::vector<int>& v1, const std::vector<int>& v2);
int vector_operations(int &secret_code);
int vector_sum(std::vector<int>& inVec);


 
/* Another hash function for verifying the success of the tests.

  // This function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION
  */
unsigned int hash_browns(unsigned int input) {
  union __sys_rcu_tdb_ {
    unsigned int p;
    float q;
  } v;
  v.p = (input * 27828) + 1456694363;
  v.q /= 1024;
  v.p ^= 1672983815;
  v.p += (input * input ^ (input + v.p));
  unsigned int x = (v.p >> 21) & 2047;
  unsigned int y = (v.p << 11) & 037777774000;
  v.q -= 10;
  v.p ^= (x | y);
  return v.p;
}


int vector_operations(int &secret_code) {

  // create a vector v1 with 7 entries of 25
  std::vector<int> v1(7, 25);
  // create another vector with entries 1-10
  std::vector<int> v2;
  for(uint i=1; i<=10; ++i) {
    v2.push_back(i);
  }
  // and one with entries -5 to 5
  std::vector<int> v3;
  for(int i=-5; i<=5; ++i) {
    v3.push_back(i);
  }
  assert(v3[5] == 0);

  int v1sum = vector_sum(v1);
  int v2sum = vector_sum(v2);
  int v3sum = vector_sum(v3);
  assert(v1sum == 175);
  assert(v1[2] == 75);
  assert(v1[5] == 150);
  assert(v2sum == 55);
  assert(v2[2] == 6);
  assert(v3sum == 0);
  assert(v3[10] == 0);
  for(uint i=0; i<v3.size(); ++i) { assert(v3[i] <= 0); }
  int v1sumsum = vector_sum(v1);
  int v2sumsum = vector_sum(v2);
  assert(v1sumsum == 700);
  assert(v1[2] == 150);
  for(uint i=0; i<v1.size(); ++i) { assert(v1[i] != 225); }
  assert(v1[5] == 525);

  int counter=0;
  for(uint i=0; i<v2.size(); ++i) {
    // count the number of multiples of 10 in v2
    if(v2[i] % 10 == 0) {
      counter++;
    }
  }
  // there should be 4 of them
  assert(counter == 4);


  // more vectors
  std::vector<int> v4;
  v4.push_back(4);
  v4.push_back(23);
  v4.push_back(18);
  v4.push_back(31);
  v4.push_back(167);
  v4.push_back(213);
  v4.push_back(86);
  std::vector<int> v5;
  v5.push_back(-7);
  v5.push_back(10);
  v5.push_back(806);
  v5.push_back(211);
  // create v6 by concatenating v4 and v5
  std::vector<int> v6(v4);
  for(uint i=0; i<v5.size(); ++i) { v6.push_back(v5[i]); }

  assert(v6.size() == 11);
  assert(v6[6] == 86);
  assert(v6[7] == -7);
  assert(v6[10] == 211);

  // compare some vectors
  assert(vector_compare(v1, v4));   
  assert(! vector_compare(v5, v1)); 
  assert(vector_compare(v6, v3));   
  assert(! vector_compare(v3, v6)); 
  assert(! vector_compare(v2, v5)); 
  assert(! vector_compare(v6, v1)); 

  // now concatenate everything into a big vector
  std::vector<int> all(v1);
  all.insert(all.end(), v2.begin(), v2.end());
  all.insert(all.end(), v3.begin(), v3.end());
  // v4 and v5 are already concatenated into v6
  // so just concatenate that
  all.insert(all.end(), v6.begin(), v6.end());
  assert(all.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> threes;
 
  counter = 0;
  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint i = 0; i < all.size(); i++) {
    if(all[i] % 3 == 0) {
      // std::cout << all[i] << " is divisible by 3" << std::endl;
      counter++;
      threes.push_back(all[i]);

    }
  }
  std::cout << "There are " << counter << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int i=counter-1; i >= 0; --i) {
    std::cout << "threes[" << i << "] = " << threes[i] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  counter += v1sumsum + v2sumsum;
  counter += (all.size() == 40);
  for(uint i=13;i<24;++i) { counter += (int) all[i]; }
  counter *= vector_sum(threes)/2;
  secret_code = uint(counter*57296)%__LINE__;
  return counter;
  //********************************************************************************
}


int list_operations(int &secret_code) {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> l1;
  for(char c = 'a'; c <= 'z'; c++) {
    l1.push_back(c);
  }
  for(char c =  'Z'; c >= 'A'; c--) {
    l1.push_front(c);
  }
  assert(l1.back() == 'z');
  assert(l1.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> l500;
  for(int i=1; i<=500; ++i) {
    l500.push_back(i);
  }
  assert(*l500.begin() == 1);

  const int factor = 7;
  const int factor2 = 11;

  // remove every number from the list that is a multiple of at least one of
  // these factors
  for(std::list<int>::iterator itr = l500.begin(); itr != l500.end(); ++itr) {

    if(*itr % factor == 0 || *itr % factor2 == 0) {

      itr = l500.erase(itr);
      itr--;
 
    }
  }

  // make a list
  std::list<std::string> fruits;
  fruits.push_front("banana");
  fruits.push_back("fig");
  fruits.push_back("iodine");
  fruits.push_front("yellow squash");
  fruits.push_front("grape");
  fruits.push_front("durian");
  fruits.push_front("pomegranate");
  fruits.push_back("huckleberry");
  fruits.push_front("zwetschge");
  fruits.push_back("strawberry");
  fruits.push_back("tangerine");
  fruits.push_back("jujube");
  fruits.push_back("lemon");
  fruits.push_back("mango");
  fruits.push_front("orange");
  fruits.push_back("cherry");
  fruits.push_front("nectarine");
  fruits.push_back("uglyfruit");
  fruits.push_front("vapor");
  fruits.push_front("quart");
  fruits.push_back("apple");
  fruits.push_front("elderberry");
  fruits.push_front("raspberry");
  fruits.push_back("watermelon");
  fruits.push_back("kiwi");
  fruits.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> not_fruits;
  not_fruits.push_back("iodine");
  not_fruits.push_back("yellow squash");
  not_fruits.push_back("vapor");
  not_fruits.push_back("quart");
  not_fruits.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator fruit_itr;
  for(std::list<std::string>::iterator ritr = not_fruits.begin();
      ritr != not_fruits.end(); ritr++) {
    
    fruit_itr = std::find(fruits.begin(), fruits.end(), *ritr);
    fruit_itr = fruits.erase(fruit_itr);

  }

  // verify fruits list
  for(std::list<std::string>::iterator itr = fruits.begin(); itr != fruits.end(); ++itr) {

    std::cout << *itr << " ";
  
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from l1.
  for(std::list<std::string>::iterator itr = fruits.begin(); itr != fruits.end(); ++itr) {
   for(uint i=0; i<itr->size(); ++i) {
      l1.remove((*itr)[i]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int count = 0; 

 for(std::list<char>::reverse_iterator itr = l1.rbegin(); itr != l1.rend(); itr++) {
 
    if(*itr < 'a' || *itr > 'z') {
      continue;
    }

    count++;
  }

  std::cout << count << " letters did not ever appear in the fruit names." << std::endl;

  assert(*l1.begin() == 'A');
  assert(*(--l1.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int sum = fruits.size();
  std::list<char>::iterator itr1 = l1.begin();
  std::advance(itr1, 20);
  for(; itr1 != l1.end(); ++itr1) {
    sum += *itr1;
    if (sum % 3) {
      sum *= count;
      sum -= *itr1;
    }
  }
  for(std::list<std::string>::iterator itr2 = fruits.begin(); itr2 != fruits.end(); ++itr2){
    sum -= (*itr2)[2];
  }
  for(std::list<int>::iterator itr3 = l500.begin(); itr3 != l500.end(); ++itr3) {
    sum += *itr3;
  }
  secret_code = uint(sum*70712)%__LINE__;
  return sum;
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

  // This function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION
*/
void corned_beef_hash(int* output, int input) {
  *(output+((input+1962) & 3)) = input ^ 3735928559u; 
  *(output+((input+1492) & 3)) = input ^ 3056505882u; 
  *(output+((input+'G') & 3)) = input ^ 01353340336u; 
  *(output+((input+1) & 3)) = input ^ 3405691582u; 
  int bitCtr = 1;
  char bit = 0;
  char* cPtr = (char*) output;
  for(bitCtr = 32767; bitCtr<32783; bitCtr++) {
    for(bit=7; bit >= 0; --bit) {
      if(((*cPtr)>>bit) & 1) (*cPtr) ^= (input >> (bit/2)*8) & 255; 
      else (*cPtr) = (((*cPtr)<<5) & 224) | (((*cPtr)>>3) & 31);
      if(*cPtr & 4) (*cPtr = ~(*cPtr));
    }
    ++cPtr;
  }
}

/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If outFile is not empty, write to a file as well.

  // This function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION
*/
bool decrypt(int array[4], char* bufPtr, int bufLen, const char* outFile) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int bufCtr = 0;
  int arrayCtr = 0;
  int hashout[4];
  bool all_printable = true;
  char outBuf[1024];
  int outBufCtr = 0;

  for(; bufCtr < bufLen; bufCtr += 16) {
    corned_beef_hash(hashout, array[arrayCtr]);
    arrayCtr++;
    if(arrayCtr > 3) arrayCtr = 0;
    unsigned char* c = (unsigned char*) &bufPtr[bufCtr];
    unsigned char* d = (unsigned char*) hashout;
    for(int i=0; i<16; ++i, ++c, ++d) {
      if(bufCtr+i >= bufLen) break;
      char dc = *c ^ *d;
      if((dc < 32 || dc > 126) && dc != '\n' && dc != '\t') {
	all_printable = false;
      }
      outBuf[outBufCtr] = dc;
      outBufCtr++;
      // putc(dc, stdout);
    }
  }
  outBuf[outBufCtr] = '\0';
  if(outFile[0] != '\0') {
    std::ofstream ofile(outFile, std::ofstream::binary);
    if(!ofile.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    ofile.write(outBuf,bufLen);
  }
  for(int i=0; i<bufLen; ++i) {
    putc(outBuf[i], stdout);
  }
  std::cout << std::endl << std::endl;
  return all_printable;
}


/* Compares two vectors of ints to each other, element by element.
   If every number in v1 is strictly greater than the corresponding number in
   v2, return true; otherwise return false. */
bool vector_compare(const std::vector<int>& v1, const std::vector<int>& v2) {
  
  bool success = true;
  for(uint i=0; i<v1.size(); ++i) {

    if(v1[i] < v2[i]) {
      success = false;
      
    }
  }
  return success;
}


int array_operations(int &secret_code) {
  // what we're doing here is creating and populating a 2D array of ints.
  // We'll use the pythagoras function to store its results for every coordinate
  // pair.
  const int size = 25;
  int** array = new int*[size];
  for(int x=0; x<size; ++x) { 
    array[x] = new int[size];
    for(int y=0; y<size; ++y) {
      array[x][y] = 0;
    }
  }
  // sanity check
  assert(array[1][1] == 0);

  // store pythagorean numbers in the array
  for(int x=1; x<size; ++x) {   
    for(int y=1; y<size; ++y) {
      array[x][y] = pythagoras(x, y);
    }
  }
 
  // do some checks
  assert(array[1][2] == -1); // no triple exists
  assert(array[3][4] == 5);
  assert(array[5][4] == 3);
  assert(array[13][12] == 5);
  assert(array[8][15] == 17);
  assert(array[8][16] != 17);
  assert(array[17][8] == 15);
  assert(array[5][3] == array[3][5]);
  assert(array[7][24] == 25);
  assert(array[12][16] == 20); // 3-4-5 triple times 4
  assert(array[5][15] == -1);
  assert(array[24][7] != -1);

  /* Now iterate over and print the array, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** tmp_ptr = array;
  for(int x = 1; x < size; ++x) {
    int* tmp_ptr2 = tmp_ptr[x];
 
 
    for(int y = 1; y < size; ++y) {
      int tmp = tmp_ptr2[y];
 
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string maybe_space = ((tmp < 10 && tmp >= 0) ? " " : "");
      std::cout << maybe_space << tmp << " ";
 
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int sum = 0;
  for(int x=5; x<18; ++x) {
    for(int y=3; y<10; ++y) {
      sum += array[x][y];
    }
  }
  for(int x=0; x<size; ++x) {
    delete [] array[x];
  }
  delete [] array;

  std::cout << "MY LINE " << __LINE__ << std::endl;
  
  secret_code = uint(sum*18492)%__LINE__;
  return sum;
  //********************************************************************************
}

 
/* Usage:
 * main [operations] [infile] [outfile] 
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 */
int main(int argc, char* argv[]) {
  // argument handling, no bugs in this code
  if(argc != 4) {
    std::cerr << "Incorrect Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

 //int secret_code = 42;
  
  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    int secret_code;
    records[0] = arithmetic_operations(secret_code);
    // test if all bugs were fixed - passing the correct value to hash_browns
    // will return this number
    if(hash_browns(records[0]) == 771403603) {
      std::cout << "Arithmetic bugs are FIXED, secret code A is: `"
                << secret_code << "`" << std::endl << std::endl;
    } else {
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
    }
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(file_operations(argc, argv, file_buffer, file_buffer_length) != "SUCCESS") {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operations DOES NOT CRASH" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    int secret_code;
    records[1] = array_operations(secret_code);
    if(hash_browns(records[1]) == 0x8FDEBF5F) {
      std::cout << "Array bugs are FIXED, secret code B is: `"
                << secret_code << "`" << std::endl << std::endl;
    } else {
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
    }
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    int secret_code;
    records[2] = vector_operations(secret_code);
    if(hash_browns(records[2]) == 1259270366) {
      std::cout << "Vector bugs are FIXED, secret code C is: `"
                << secret_code << "`" << std::endl << std::endl;
    } else {
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
    }
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    int secret_code;
    records[3] = list_operations(secret_code);
    if(hash_browns(records[3]) == 2076188906) {
      std::cout << "List bugs are FIXED, secret code D is: `"
                << secret_code << "`" << std::endl << std::endl;
    } else {
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
    }
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(decrypt(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      delete [] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      delete [] file_buffer;
      return 1;
    }
  }
}
 

/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. inVec will be modified by this function.
   Used in vector operations. */
int vector_sum(std::vector<int>& inVec) {
  for(uint i=1; i<inVec.size(); ++i) {
    inVec[i] = inVec[i] + inVec[i-1];
  }
  return inVec[inVec.size()-1]; 
}


/* Note that this gets passed argc and argv unmodified from main. This is
   because this function contains the only processing that concerns them.

   Other note: "char*&" means "reference to a char*". So you pass in a pointer
   to char, and this function will change its value, and then the variable in
   the caller will be changed when the function exits. */
std::string file_operations(int argc, char** argv, char*& returned_buffer, int& retlen) {

  std::string answer = "SUCCESS";
  
  // Error checking on command line arguments
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return "ERROR: bad arguments";
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream infile(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!infile) {
    std::cerr << "The file '" << argv[2] << "' could not be opened!" << std::endl;
    answer = std::string("ERROR: could not open file") + argv[2];
    return answer;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int length;

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  infile.seekg(0, infile.end);
  length = infile.tellg();
  infile.seekg(0, infile.beg);

  // make an array of bytes to hold this information
  char* buffer = new char[length];
  
  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  infile.read(buffer, length);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << infile.gcount() << " bytes of data."
	    << std::endl;
  assert(infile.gcount() == length);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  retlen = length;
  returned_buffer = buffer;
  return answer;
  //********************************************************************************
}


/* multidivide: A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float multidivide(int numerator, int d1, int d2, int d3, int d4) {
  float f = ((((numerator / d1) / d2) / d3) / d4);
  return f;
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   There are NO BUGS in this function */
bool close_enough(double d1, double d2) {
  return (std::abs(d1-d2) < 0.01);
}


int arithmetic_operations(int &secret_code) {

  // set up some variables
  int a = 10;
  int b = 46;
  int c = 4;
  int d = c - b;              // -42
  int e = b - 3*a + 5*c - 4;      //  32 
  int f = 2*b + 2*c;          //  100
  int g = e - (b/c) + d + 20; // -1 
  int h = (f/c) / a + 1;          //  3 
  int m = (d / (h-1)) / 7 + 1;        // -2 
  int n = g + m;              // -3 
  int p = (f / e) - (h-1) - 2;        // -1 
  int q = f + 2*d;            // 16
  int r = g + m + p + n - 1;      // -8 
  float s = (float)a / f;            //  0.1 

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide #1: " << multidivide(f, g, c, 5, g)
	    << " (expected 5)." << std::endl;

  assert(multidivide(f, g, c, 5, g) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide #2: " << multidivide(840, d, m, p, 1)
	    << " (expected -10)." << std::endl;

  assert(multidivide(840, d, m, p, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide #3: " << multidivide(320, r, p, a, m)
	    << " (expected -2)." << std::endl;

  assert(multidivide(320, r, p, a, m) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide #4: " << multidivide((e*f*-1), p, q, r, (a/2))
	    << " (expected -5)." << std::endl;

  assert(multidivide(e*f*-1, p, q, r, (a/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float zeropointone = multidivide(f*10, a, a, a, a)+0.1;
  std::cout << "Multidivide #5: " << zeropointone
	    << " (expected 0.1)." << std:: endl;

  assert(close_enough(zeropointone, s));

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the arithmetic operations" << std::endl;
  int answer = (m+r) ^ q ^ ((int) zeropointone) ^ (d*e*f*g*h);
  secret_code = uint(answer*16290)%__LINE__;
  return answer;

  //********************************************************************************
}


/* pythagoras: A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   pythagoras(3,4) should be 5
   pythagoras(3,5) should be 4
   pythagoras(3,6) should be -1
*/
int pythagoras(int x, int y) {
  double placeholder; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // x and y are both legs
  float sumsquares = x*x + y*y;
  float fracpart = modf(sqrt(sumsquares), &placeholder);
  if(fracpart == 0)
    return (int) placeholder;

  // x is the hypotenuse, need to subtract instead of add
  float diffsquares = abs(y*y - x*x); 
  fracpart = modf(sqrt(diffsquares), &placeholder);
  if(fracpart == 0)
    return (int) placeholder;
  return -1;
  // no triple exists
  
}

