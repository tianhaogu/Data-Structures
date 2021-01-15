// =================================================================
//
// IMPORTANT NOTE: Do not modify this file
//
// =================================================================

#ifndef _node_h_
#define _node_h_

#include "playing_card.h"

// ==================================================================================
// THE NODE CLASS 
// ==================================================================================

class Node {
public:
  Node(const PlayingCard &pc) 
    : before(NULL), after(NULL),  sorted_prev(NULL), sorted_next(NULL), card(pc) {} 

  const PlayingCard& getCard() const { return card; }

  // the pointers are public and can be edited by various functions to
  // rearrange the structure of the linked list
  Node *before;
  Node *after;
  Node *sorted_prev;
  Node *sorted_next;

private:
  // the playing card is not editable after the node is created
  PlayingCard card;
};

// ==================================================================================

#endif
