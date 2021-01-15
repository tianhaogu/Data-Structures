// =================================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =================================================================

#include <iostream>
#include <cstdlib>
#include <cmath>

// provided helper classes
#include "playing_card.h"
#include "node.h"


// =================================================================
// where you will specify the prototypes for the functions you write
// (you will implement those functions in deck.cpp)
#include "deck.h"
using namespace std;


// =================================================================
// PROVIDED HELPER FUNCTIONS
// =================================================================


// Helper function to check the validity of the primary doubly
// linked-list structure.  This function returns true if the structure
// is valid, false otherwise.
bool SanityCheckPrimary(Node* primary_order_top) {
  if (primary_order_top == NULL) return true;
  if (primary_order_top->before != NULL) return false;
  Node *tmp = primary_order_top;
  // walk through the list, checking forward & backward pointers
  while (tmp != NULL) {
    if (tmp->before != NULL) { if (tmp->before->after != tmp) return false; }
    if (tmp->after != NULL)  { if (tmp->after->before != tmp) return false; }
    tmp = tmp->after;
  }
  return true;
}


// Helper function to check the validity of the secondary,
// sorted-order, doubly linked-list structure.  This function returns
// true if the structure is valid, false otherwise.
bool SanityCheckSorted(Node* sorted_order_first) {
  if (sorted_order_first == NULL) return true;
  if (sorted_order_first->sorted_prev != NULL) return false;
  Node *tmp = sorted_order_first;
  while (tmp != NULL) {
    // walk through the list, checking forward & backward pointers
    if (tmp->sorted_prev != NULL) { if (tmp->sorted_prev->sorted_next != tmp) return false; }
    if (tmp->sorted_next != NULL)  { if (tmp->sorted_next->sorted_prev != tmp) return false; }
    // verity that the elements are sorted
    if (tmp->sorted_next != NULL) {
      if (!(tmp->getCard() < tmp->sorted_next->getCard())) return false;
    }
    tmp = tmp->sorted_next;
  }
  return true;
}


// Helper function to really scrutinize both traversal orders
bool SanityCheckBoth(Node* primary_order_top) {
  if (primary_order_top == NULL) return true;
  if (!SanityCheckPrimary(primary_order_top)) return false;
  
  // find the start of the sorted list 
  // (the node that has sorted_prev == NULL)
  Node *sorted_order_first = primary_order_top;
  while (sorted_order_first != NULL) {
    if (sorted_order_first->sorted_prev == NULL) break;
    // step through the nodes in primary order
    sorted_order_first = sorted_order_first->after;
  }
  if (sorted_order_first == NULL) return false;
  if (!SanityCheckSorted(sorted_order_first)) return false;

  // verify that the nodes in the two sequences are the same 
  // (that we didn't somehow copy some or all of the nodes)

  // step through the nodes in sorted order, 
  // verify that node is in the primary order too
  int count_nodes = 0;
  for (Node *tmp1 = sorted_order_first; tmp1 != NULL; tmp1 = tmp1->sorted_next) {
    bool found = false;
    for (Node *tmp2 = primary_order_top; tmp2 != NULL; tmp2 = tmp2->after) {
      if (tmp1 == tmp2) { found = true; break; }
    }
    if (found == false) { return false; }
    count_nodes++;
  }

  // verify that the number of nodes in the sorted order is the same
  // as the primary order
  assert (count_nodes > 0);


  //
  // once DeckSize is implemented, uncomment this line
  //assert (count_nodes == DeckSize(primary_order_top));
  //


  // now do the other way around...
  for (Node *tmp2 = primary_order_top; tmp2 != NULL; tmp2 = tmp2->after) {
    bool found = false;
    for (Node *tmp1 = sorted_order_first; tmp1 != NULL; tmp1 = tmp1->sorted_next) {
      if (tmp1 == tmp2) { found = true; break; }
    }
    if (found == false) { return false; }
    count_nodes--;
  }

  // verify that the number of nodes in the sorted order is the same
  // as the primary order
  assert (count_nodes == 0);
  return true;
}


// Build a deck (a linked list of Nodes containing playing cards) with
// the specified number of cards.  This automatically cycles through
// the 52 different cards.  If the requested number of cards is > 52,
// the cards will be repeated.
Node* CreateDeck(int numCards) {
  int count = 0;
  Node *answer = NULL;
  int current_suit = 0;
  int current_face_value = 1;
  // while loop that increments the suit & face value
  while (count < numCards) {
    DeckPushBackCard(answer,suit_names[current_suit],current_face_value);
    current_face_value++;
    if (current_face_value > 13) {
      current_face_value = 1;
      current_suit++;
      if (current_suit > 3) {
        current_suit = 0;
      }
    }
    count++;
  }
  return answer;
}


// This helper function simply creates a new card (allocates the memory) 
// and adds the card to back back of the linked list chain of cards.
//
// NOTE: This function creates a new Node object, and should not be
// called by functions that aim to change the link structure of
// existing Nodes.
//
void DeckPushBackCard(Node* &deck, const std::string& suit, int num) {
  assert(SanityCheckPrimary(deck));
  if (deck == NULL) {
    // handle an empty deck
    deck = new Node(PlayingCard(suit,num));
  } else {
    Node* tmp = deck;
    // search for the end of the chain
    while (tmp->after != NULL) {
      tmp = tmp->after;      
    }
    // create and add the new card
    tmp->after = new Node(PlayingCard(suit,num));
    tmp->after->before = tmp;
  }
  assert(SanityCheckPrimary(deck));
}


// Helper function to output the cards in the primary order (the order
// they are dealt or added to the linked list)
void PrintDeckPrimary(const std::string &description, Node* deck) {
  std::cout << description;
  Node *tmp = deck;
  while (tmp != NULL) {
    std::cout << " " << tmp->getCard().getString();
    tmp = tmp->after;
  }
  std::cout << std::endl;
}


// =================================================================
// TEST CASES
// =================================================================

// =================================================================
// TEST OF PERFECT IN/OUT SHUFFLE
// =================================================================


int PerfectShuffleTest(int numCards, bool out_shuffle) {
  if (out_shuffle) {
    std::cout << "In PerfectOutShuffleTest, numCards = " << numCards << std::endl;
  } else {
    std::cout << "In PerfectInShuffleTest, numCards = " << numCards << std::endl;
  }

  // create a deck with the specified number of cards
  Node* deck = CreateDeck(numCards);
  assert (DeckSize(deck) == numCards);
  PrintDeckPrimary("INITIAL:",deck);
  assert (SanityCheckPrimary(deck));

  // make a copy of the initial deck (so we can tell when we've restored the deck)
  Node *deck2 = CopyDeck(deck);
  assert (SanityCheckPrimary(deck));
  assert (SanityCheckPrimary(deck2));

  // repeatedly cut, shuffle & compare the deck to the original
  Node *top, *bottom;
  int numShuffles = 0;
  while(1) {
    assert (SanityCheckPrimary(deck));
    CutDeck(deck,top,bottom,"perfect");
    //PrintDeckPrimary("shuffle:",deck);
    //assert (deck == NULL);
    // verify that the structure of the two sub-decks is sound
    assert (SanityCheckPrimary(top));
    assert (SanityCheckPrimary(bottom));
    if (out_shuffle) {
      // an out shuffle takes a card first from the top half
      deck = Shuffle(top,bottom,"perfect");
    } else {
      // an in shuffle takes a card first from the bottom half
      // (so we just swap the order of the piles)
      deck = Shuffle(bottom,top,"perfect");
    }
    numShuffles++;
    // verify that the primary order of the deck is sound
    assert (SanityCheckPrimary(deck));
    PrintDeckPrimary("shuffle:",deck);
    if (SamePrimaryOrder(deck,deck2))
      break;
    if (!out_shuffle && ReversePrimaryOrder(deck,deck2)) {
      std::cout << "for deck size = " << numCards  << ", the deck is reversed after " 
                << numShuffles  << " perfect in shuffles." << std::endl;
    }
  }

  // output the results
  std::cout << "for deck size = " << numCards  << ", the deck is restored after " << numShuffles;
  if (out_shuffle) {
    std::cout << " perfect out shuffles." << std::endl;
  } else {
    std::cout << " perfect in shuffles." << std::endl;
  }
  // cleanup the structure
  DeleteAllCards(deck);
  DeleteAllCards(deck2);
  std::cout << std::endl;
  return numShuffles;
}



// =================================================================
// TEST OF DEALING
// =================================================================


void DealingTest() {
  std::cout << "In DealingTest" << std::endl;

  // deal all 52 cards to 4 people, 13 cards each
  Node* deck = CreateDeck(52);
  PrintDeckPrimary(" deck:",deck);
  assert (DeckSize(deck) == 52);

  // prepare space to store the resulting sub-decks
  Node* hands[4];

  Deal(deck,hands,4,"one-at-a-time",13);
  // check the size of the decks
  assert (deck == NULL);
  assert (DeckSize(hands[0]) == 13);
  assert (DeckSize(hands[1]) == 13);
  assert (DeckSize(hands[2]) == 13);
  assert (DeckSize(hands[3]) == 13);
  // verify that the structure of the sub-decks is sound
  assert (SanityCheckPrimary(hands[0]));
  assert (SanityCheckPrimary(hands[1]));
  assert (SanityCheckPrimary(hands[2]));
  assert (SanityCheckPrimary(hands[3]));

  // print the decks
  PrintDeckPrimary(" west:",hands[0]);
  PrintDeckPrimary("north:",hands[1]);
  PrintDeckPrimary(" east:",hands[2]);
  PrintDeckPrimary("south:",hands[3]);

  // cleanup
  DeleteAllCards(hands[0]);
  DeleteAllCards(hands[1]);
  DeleteAllCards(hands[2]);
  DeleteAllCards(hands[3]);
  std::cout << std::endl;
}


// =================================================================
// TEST OF HAND SORTING
// =================================================================


void SortingTest() {
  std::cout << "In SortingTest" << std::endl;

  // sort just a single suit (13 cards)
  std::cout << "Sort a single suit" << std::endl;
  Node* deck = CreateDeck(13);
  assert (DeckSize(deck) == 13);
  Node *top, *bottom;
  // perform a couple perfect cut & perfect in shuffles
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  PrintDeckPrimary  ("            primary order before:",deck);
  assert(SanityCheckPrimary(deck));
  // Initialize the secondary linked list structure within the cards.
  // This code does not create any new node objects.
  // Furthermore, the links for the primary structure should not change.
  Node *sorted = SortHand(deck);
  PrintDeckSorted("                    sorted order:",sorted);
  PrintDeckPrimary  ("primary order after (no change!):",deck);
  // verify that the sorted order is sound and the primary order is still sound
  assert(SanityCheckPrimary(deck));
  assert(SanityCheckSorted(sorted));
  assert(SanityCheckBoth(deck));
  // cleanup
  DeleteAllCards(deck);

  // sort all 52 cards
  std::cout << "Sort the whole deck" << std::endl;
  deck = CreateDeck(52);
  assert (DeckSize(deck) == 52);
  // perform a number of in & out shuffles to sufficiently scramble the order
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  PrintDeckPrimary  ("primary before:",deck);
  sorted = SortHand(deck);
  PrintDeckSorted("        sorted:",sorted);
  PrintDeckPrimary  (" primary after:",deck);
  assert(SanityCheckSorted(sorted));
  assert(SanityCheckBoth(deck));
  DeleteAllCards(deck);
  std::cout << std::endl;
}


// =================================================================
// COMBINED SHUFFLE-DEALING-SORTING TEST
// =================================================================


void ShuffleDealingSortingTest() {

  std::cout << "In ShuffleDealingSortingTest" << std::endl;

  // create a full deck
  Node* deck = CreateDeck(52);
  assert (DeckSize(deck) == 52);
  Node *top, *bottom;
  // perform several perfect cut and in/out shuffles
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");

  // only deal 15 cards to each of 3 people 
  Node* hands[3];
  Deal(deck,hands,3,"one-at-a-time",15);
  // print the decks
  PrintDeckPrimary(" west:",hands[0]);
  PrintDeckPrimary("north:",hands[1]);
  PrintDeckPrimary(" east:",hands[2]);
  PrintDeckPrimary(" deck:",deck);
  // confirm the hand sizes
  assert (DeckSize(hands[0]) == 15);
  assert (DeckSize(hands[1]) == 15);
  assert (DeckSize(hands[2]) == 15);
  // verify that the primary linking structure is valid
  assert (SanityCheckPrimary(hands[0]));
  assert (SanityCheckPrimary(hands[1]));
  assert (SanityCheckPrimary(hands[2]));
  // 7 cards should be left in the deck
  assert (DeckSize(deck) == 7);
  assert (SanityCheckPrimary(deck));

  // sort each of the hands
  Node* sorted_hands[3];
  sorted_hands[0] = SortHand(hands[0]);
  sorted_hands[1] = SortHand(hands[1]);
  sorted_hands[2] = SortHand(hands[2]);
  // verify that the size is unchanged and that the primary and sorted structure is sound
  assert (DeckSize(hands[0]) == 15);
  assert (DeckSize(hands[1]) == 15);
  assert (DeckSize(hands[2]) == 15);
  assert (SanityCheckPrimary(hands[0]));
  assert (SanityCheckPrimary(hands[1]));
  assert (SanityCheckPrimary(hands[2]));
  assert (SanityCheckSorted(sorted_hands[0]));
  assert (SanityCheckSorted(sorted_hands[1]));
  assert (SanityCheckSorted(sorted_hands[2]));
  assert (SanityCheckBoth(hands[0]));
  assert (SanityCheckBoth(hands[1]));
  assert (SanityCheckBoth(hands[2]));
  PrintDeckSorted(" west (sorted):",sorted_hands[0]);
  PrintDeckSorted("north (sorted):",sorted_hands[1]);
  PrintDeckSorted(" east (sorted):",sorted_hands[2]);
  // cleanup everything
  DeleteAllCards(hands[0]);
  DeleteAllCards(hands[1]);
  DeleteAllCards(hands[2]);
  DeleteAllCards(deck);
  std::cout << std::endl;
}


// =================================================================
// STUDENT TESTS
// =================================================================

void StudentTests() {

  std::cout << "In StudentTests" << std::endl;
  std::cout << "First create a enough large deck of odd number, " 
            << "then cut the deck several times, and mix shuffle(top-> bottom & bottom-> top): " << endl;
  Node* deck = CreateDeck(43);
  Node *top, *bottom;

  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(bottom,top,"perfect");
  CutDeck(deck,top,bottom,"perfect");
  deck = Shuffle(top,bottom,"perfect");
  PrintDeckPrimary(" deck:",deck);
  std::cout << std::endl;
  
  std::cout << "Sort the deck: " << std::endl;
  Node *sorted = SortHand(deck);
  PrintDeckSorted(" sorted order:",sorted);
  std::cout << std::endl;
  
  std::cout << "Make a copy of the deck, and deal the new deck to 5 people, each with 8 cards, "
            << "remaining 3 cards in the copy of the deck: " << std::endl;
  Node *deck0 = CopyDeck(deck);
  
  Node* hands[5];
  Deal(deck0,hands,5,"one-at-a-time",8);
  assert (DeckSize(deck0) == 3);
  PrintDeckPrimary(" west:  ",hands[0]);
  PrintDeckPrimary("north:  ",hands[1]);
  PrintDeckPrimary(" east:  ",hands[2]);
  PrintDeckPrimary("south:  ",hands[3]);
  PrintDeckPrimary("middle: ",hands[4]);
  PrintDeckPrimary(" deck:  ",deck0);
  std::cout << std::endl;
  
  std::cout << "Sort deck of all 5 people and the remaining deck: " << std::endl;
  Node* sorted_hands[6];
  sorted_hands[0] = SortHand(hands[0]);
  sorted_hands[1] = SortHand(hands[1]);
  sorted_hands[2] = SortHand(hands[2]);
  sorted_hands[3] = SortHand(hands[3]);
  sorted_hands[4] = SortHand(hands[4]);
  sorted_hands[5] = SortHand(deck0);
  PrintDeckSorted(" west (sorted):   ",sorted_hands[0]);
  PrintDeckSorted(" north (sorted):  ",sorted_hands[1]);
  PrintDeckSorted(" east (sorted):   ",sorted_hands[2]);
  PrintDeckSorted(" south (sorted):  ",sorted_hands[3]);
  PrintDeckSorted(" middle (sorted): ",sorted_hands[4]);
  PrintDeckSorted(" deck (sorted):   ",sorted_hands[5]);
  std::cout << std::endl;
  
  std::cout << "Delete all sub-decks and copied-decks, end of student test!" << std::endl;
  DeleteAllCards(hands[0]);
  DeleteAllCards(hands[1]);
  DeleteAllCards(hands[2]);
  DeleteAllCards(hands[3]);
  DeleteAllCards(hands[4]);
  DeleteAllCards(deck);
  DeleteAllCards(deck0);
  std::cout << std::endl;
}

// =================================================================
// RANDOMIZED SHUFFLING TESTS (EXTRA CREDIT)
// =================================================================


/*void RandomizedShufflingTests() {

  std::cout << "In RandomizedShufflingTests" << std::endl;

  // create a deck with the specified number of cards
  int numCards = 52;
  Node* original = CreateDeck(numCards);
  assert (DeckSize(original) == numCards);
  Node* perfect_deck = CopyDeck(original);
  Node* random_deck1 = CopyDeck(original);
  Node* random_deck2 = CopyDeck(original);
  Node* random_deck3 = CopyDeck(original);
  Node* random_deck4 = CopyDeck(original);
  PrintDeckPrimary("    original:",original);  

  std::cout << "testing randomized Shuffle" << std::endl;
  // Perform a perfect cuts, but use random shuffle on 4 of the decks
  // (with reasonably high probability, this should be different from
  // the perfect shuffle, and different from other random shuffles)
  Node *top, *bottom;
  CutDeck(perfect_deck,top,bottom,"perfect");
  perfect_deck = Shuffle(top,bottom,"perfect");
  PrintDeckPrimary("perfect_deck:",perfect_deck);
  CutDeck(random_deck1,top,bottom,"perfect");
  random_deck1 = Shuffle(top,bottom,"random");
  PrintDeckPrimary("random_deck1:",random_deck1);
  CutDeck(random_deck2,top,bottom,"perfect");
  random_deck2 = Shuffle(top,bottom,"random");
  PrintDeckPrimary("random_deck2:",random_deck2);
  CutDeck(random_deck3,top,bottom,"perfect");
  random_deck3 = Shuffle(top,bottom,"random");
  PrintDeckPrimary("random_deck3:",random_deck3);
  CutDeck(random_deck4,top,bottom,"perfect");
  random_deck4 = Shuffle(top,bottom,"random");
  PrintDeckPrimary("random_deck4:",random_deck4);
  // compare the perfect deck to the 4 randomly shuffled decks
  int num_shuffle_same = 0;
  if (SamePrimaryOrder(random_deck1,perfect_deck)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck2,perfect_deck)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck3,perfect_deck)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck4,perfect_deck)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck1,random_deck2)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck1,random_deck3)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck1,random_deck4)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck2,random_deck3)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck2,random_deck4)) num_shuffle_same++;
  if (SamePrimaryOrder(random_deck3,random_deck4)) num_shuffle_same++;
  // if randomness was not implemented, num_shuffle_same will == 10
  // if the "random" flag does something different than "perfect",
  // but it is always the same, then num_shuffle_same will == 6
  // if num_shuffle_same is <= 5, then we know this thing is really different!
  std::cout << "num_shuffle_same = " << num_shuffle_same << std::endl;
  if (num_shuffle_same == 10 || num_shuffle_same == 6) {
    std::cout << "Effective random shuffling was not implemented" << std::endl;
  } else {
    std::cout << "Random shuffling was implemented (extra credit!)" << std::endl;
  }

  std::cout << "testing randomized Cut" << std::endl;
  int num_exact_split = 0;
  int sum = 0;
  int sum_squared_diff = 0;
  int num_random_cuts = 10;
  for (int i = 0; i < num_random_cuts; i++) {
    assert (DeckSize(random_deck1) == 52);
    PrintDeckPrimary("  deck:",random_deck1);
    CutDeck(random_deck1,top,bottom,"random");
    PrintDeckPrimary("   top:",top);
    PrintDeckPrimary("bottom:",bottom);
    int top_size = DeckSize(top);
    int bottom_size = DeckSize(bottom);
    sum += top_size;
    sum_squared_diff += (26-top_size)*(26-top_size);
    assert (top_size + bottom_size == 52);
    if (top_size == bottom_size) num_exact_split++;
    random_deck1 = Shuffle(top,bottom,"random");
    PrintDeckPrimary("random_deck3:",random_deck3);
  }
  double average_top_deck_size = sum / double(num_random_cuts);
  double std_dev_top_deck_size = sqrt(sum_squared_diff/double(num_random_cuts));
  std::cout << "num_exact_split = " << num_exact_split << std::endl;
  std::cout << "average top deck size = " << average_top_deck_size << std::endl;
  std::cout << "standard deviation of top deck size = " << std_dev_top_deck_size << std::endl;
  if (num_exact_split == num_random_cuts) {
    std::cout << "Deck was always cut exactly in half" << std::endl;
  } else {
    // the split point should still be "approximately" in half
    // (these numbers are just a rough guess, not based on a scientific 
    // study of physical shuffling)
    if (fabs(26-average_top_deck_size) > 5 ||
        std_dev_top_deck_size > 10) {
      std::cout << "Random deck cutting was implemented, but is not physically realistic" << std::endl;
    } else {
      std::cout << "Effective and realistic random deck cutting was implemented (extra credit!)" << std::endl;
    }
  }

  //cleanup
  DeleteAllCards(original);
  DeleteAllCards(perfect_deck);
  DeleteAllCards(random_deck1);
  DeleteAllCards(random_deck2);
  DeleteAllCards(random_deck3);
  DeleteAllCards(random_deck4);
  std::cout << std::endl;
}*/


// =================================================================
// MAIN
// =================================================================

int main(int argc, char* argv[]) {

  // PARSE COMMAND LINE ARGUMENTS
  // (Note: A command line argument is only necessary if the suit
  // characters do not correctly display in your development & test
  // environment.
  //
  // First try:
  //   cards.exe
  //
  // If the hearts & diamonds suits are not legible, try:
  //   cards.exe no_outline_symbols
  //
  // If you can't see any of the suit characters, use:
  //   cards.exe no_symbols
  //
  if (argc > 1) {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " [ no_symbols | no_outline_symbols ]" << std::endl;
      exit(1);
    }
    if (std::string(argv[1]) == std::string("no_outline_symbols")) {
      GLOBAL_suit_print_symbols = 1;
    } else if (std::string(argv[1]) == std::string("no_symbols")) {
      GLOBAL_suit_print_symbols = 2;
    } else {
      std::cerr << "Unknown command line argument: " << argv[1] << std::endl;
      std::cerr << "Usage: " << argv[0] << " [ no_symbols | no_outline_symbols ]" << std::endl;
      exit(1);
    }
  }

  
  // PERFECT OUT SHUFFLE TEST CASES
  int restore;
  restore = PerfectShuffleTest(8,true);
  assert (restore == 3);
  restore = PerfectShuffleTest(52,true);
  assert (restore == 8);

  // PERFECT IN SHUFFLE TEST CASES
  restore = PerfectShuffleTest(8,false);
  assert (restore == 6);
  restore = PerfectShuffleTest(52,false);
  assert (restore == 52);

  // DEALING & SORTING TESTS
  SortingTest();
  DealingTest();
  ShuffleDealingSortingTest();

  // STUDENT TESTS
  StudentTests();

  // RANDOMIZED SHUFFLING TESTS (EXTRA CREDIT)
  //RandomizedShufflingTests();
  
}
