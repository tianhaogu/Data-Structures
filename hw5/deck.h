#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "playing_card.h"
#include "node.h"

// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);
	

// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================


int DeckSize(Node* deck);
Node* CopyDeck(Node* deck);
void DeleteAllCards(Node* &deck);
bool SamePrimaryOrder(Node* left, Node* right);
bool ReversePrimaryOrder(Node* left, Node* right);
void CutDeck(Node* &deck, Node* &top, Node* &bottom, const std::string& perfect);
Node* Shuffle(Node* &part1, Node* &part2, const std::string& perfect);
void Deal(Node* &deck, Node** hands, int num_people, const std::string& at_time, int num_cards);
Node* SortHand(Node* &deck);
void PrintDeckSorted(const std::string& sentence, Node* sorted_deck);