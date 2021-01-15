// =================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =================================================================

#include "playing_card.h"

// =================================================================
// GLOBAL VARIABLE FOR PRINTING SUIT SYMBOLS
// GLOBAL_suit_print == 0 => print UTF symbols black clubs & spades,
//        black outline white center hearts & diamonds
// GLOBAL_suit_print == 1 => print UTF symbols black clubs, spades,
//        hearts, & diamonds (no_outline_symbols)
// GLOBAL_suit_print == 2 => print 'C', 'S', 'H', & 'D' (no symbols)

int GLOBAL_suit_print_symbols = 0;
// =================================================================

std::string PlayingCard::getString() const { 
  
  // First, determine a single character to use for the suit
  std::string shortsuit;
  if (GLOBAL_suit_print_symbols == 0) {
    // print UTF symbols black clubs & spades, black outline white center hearts & diamonds
    if (suit == "hearts") shortsuit = "\xe2\x99\xa1";
    else if (suit == "diamonds") shortsuit ="\xe2\x99\xa2";
    else if (suit == "clubs") shortsuit = "\xe2\x99\xa3";
    else { assert(suit == "spades"); shortsuit = "\xe2\x99\xa0"; }
  } else if (GLOBAL_suit_print_symbols == 1) {
    // print UTF symbols black clubs, spades, hearts, & diamonds (no_outline_symbols)
    if (suit == "hearts") shortsuit = "\xe2\x99\xa5";
    else if (suit == "diamonds") shortsuit ="\xe2\x99\xa6";
    else if (suit == "clubs") shortsuit = "\xe2\x99\xa3";
    else { assert(suit == "spades"); shortsuit = "\xe2\x99\xa0"; }
  } else {
    // print 'C', 'S', 'H', & 'D' (no symbols)
    assert (GLOBAL_suit_print_symbols == 2);
    if (suit == "hearts") shortsuit = "H";
    else if (suit == "diamonds") shortsuit = "D";
    else if (suit == "clubs") shortsuit = "C";
    else { assert(suit == "spades"); shortsuit = "S"; }
  }

  // then, determine a single character to use for the card value
  if (card == 1) {
    return "A" + shortsuit;
  } else if (card == 10) {
    return "T" + shortsuit;
  } else if (card == 11) {
    return "J" + shortsuit;
  } else if (card == 12) {
    return "Q" + shortsuit;
  } else if (card == 13) {
    return "K" + shortsuit;
  } else {
    assert (card >= 2 && card <= 10);
    std::stringstream ss;
    ss << card << shortsuit;
    return ss.str();
  } 
}


// common ordering for playing cards alternates red (hearts/diamonds)
// & black (clubs/spades).  We choose: spades < diamonds < clubs < hearts
bool suit_less_than(const std::string suit_a, const std::string suit_b) {
  if (suit_a == "spades" && 
      (suit_b == "diamonds" || suit_b == "clubs" || suit_b == "hearts")) return true;
  if (suit_a == "diamonds" && 
      (suit_b == "clubs" || suit_b == "hearts")) return true;
  if (suit_a == "clubs" && 
      suit_b == "hearts") return true;
  return false;
}


// standard ordering for playing cards goes from Ace (high) -> King -> 2 (low)
bool card_less_than(int card_a, int card_b) {
  if (card_a == card_b) return false;
  if (card_a == 1) return true;
  if (card_b == 1) return false;
  return (card_a > card_b);
}


// combined comparison functions for sorting
bool operator< (const PlayingCard &a, const PlayingCard &b)  { 
  if (suit_less_than(a.getSuit(),b.getSuit())) return true;
  if (a.getSuit() == b.getSuit() &&
      card_less_than(a.getCard(),b.getCard())) return true;
  return false;
}

bool operator> (const PlayingCard &a, const PlayingCard &b)  { 
  if (a == b) return false;
  return (!( a < b));
}


// other comparison operators
bool operator==(const PlayingCard &a, const PlayingCard &b) { 
  return (a.getSuit() == b.getSuit() && a.getCard()  == b.getCard()); 
}

bool operator!=(const PlayingCard &a, const PlayingCard &b) { 
  return !operator==(a,b); 
}
