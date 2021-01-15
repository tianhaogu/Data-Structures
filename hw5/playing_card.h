// =================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =================================================================


#ifndef _playing_card_h
#define _playing_card_h

#include <iostream>
#include <clocale>
#include <sstream>
#include <string>
#include <cassert>

// ============================================================================================
// GLOBAL VARIABLE FOR PRINTING SUIT SYMBOLS
// GLOBAL_suit_print == 0 => print UTF symbols black clubs & spades, black outline white center hearts & diamonds
// GLOBAL_suit_print == 1 => print UTF symbols black clubs, spades, hearts, & diamonds (no_outline_symbols)
// GLOBAL_suit_print == 2 => print 'C', 'S', 'H', & 'D' (no symbols)
extern int GLOBAL_suit_print_symbols;
// ============================================================================================


// a global constant variable storing the suit names
const std::string suit_names[4] = { "clubs", "diamonds", "hearts", "spades" };


// ==================================================================================
// THE PLAYING CARD CLASS
// ==================================================================================

class PlayingCard {
 public:
  // CONSTRUCTOR
  PlayingCard(const std::string &s, int c) : suit(s), card(c) {
    assert (suit == "diamonds" || suit == "hearts" || suit == "spades" || suit == "clubs");
    assert (c >= 1 && c <= 13);
  }

  // ACCESSORS
  int getCard() const { return card; }
  const std::string& getSuit() const { return suit; }

  // returns a short 2 character wide string representation of the
  // character (using special suit characters if possible)
  std::string getString() const; 

 private:
  // REPRESENTATION
  std::string suit;
  int card;
};

// ==================================================================================

// various comparison operators for PlayingCards (used for sorting!)
bool operator< (const PlayingCard &a, const PlayingCard &b);
bool operator> (const PlayingCard &a, const PlayingCard &b);
bool operator== (const PlayingCard &a, const PlayingCard &b);
bool operator!= (const PlayingCard &a, const PlayingCard &b);


#endif
