#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "playing_card.h"
#include "node.h"
#include "deck.h"
using namespace std;

int DeckSize(Node* deck) {
  int size = 0;
  Node* tmp = deck; //a pointer points to first node of the deck
  if (deck != NULL) {
  	size = 1;
    while (tmp-> after != NULL) {
  	  size += 1;
      tmp = tmp-> after; //move the pointer to teh right
    }
  }
  return size;
}

Node* CopyDeck(Node* deck) {
  if (deck == NULL) {
  	return deck;
  }
  else {
    Node* tmp = deck;
    Node* new_deck = new Node(PlayingCard(tmp-> getCard().getSuit(), 
                              tmp-> getCard().getCard())); //create a new node of the first card
    new_deck-> before = NULL; new_deck-> after = NULL;
    new_deck-> sorted_prev = NULL; new_deck-> sorted_next = NULL;
    if (tmp-> after != NULL) {
      Node* new_tmp = new_deck; //new pointer points to the new node
      while (tmp-> after != NULL) {
        tmp = tmp-> after; //move pointer to the right
        new_tmp-> after = new Node(PlayingCard(tmp-> getCard().getSuit(), 
                                   tmp-> getCard().getCard())); //create a new node which connects to the previous new node
        new_tmp-> after-> before = new_tmp; //new created node also points to the previous new node
        new_tmp = new_tmp-> after; //move new pointer to the right
        new_tmp-> after = NULL;
        new_tmp-> sorted_prev = NULL; new_tmp-> sorted_next = NULL;
      }
    }
    return new_deck;
  }
}

void DeleteAllCards(Node* &deck) {
  Node* tmp = deck;
  if (tmp == NULL) {
  	return;
  }
  else {
    if (tmp-> after == NULL) { //if it's only one node in the deck
      tmp-> before = NULL; //set all links to null and delete the node
  	  tmp-> sorted_prev = NULL; tmp-> sorted_next = NULL;
  	  delete tmp;
      tmp = NULL;
    }
    else {
  	  while (tmp-> after != NULL) { //if not the last
  	    tmp-> before = NULL;
  	    tmp-> sorted_prev = NULL; tmp-> sorted_next = NULL;
  	    tmp = tmp-> after; //move to the next node
  	    tmp-> before-> after = NULL;
  	    delete tmp-> before; //delete the node before and set all links to NULL
        tmp-> before = NULL;
  	  }
  	  tmp-> before = NULL; //set links of the last node to NULL and delete the node
  	  tmp-> sorted_prev = NULL; tmp-> sorted_next = NULL;
  	  delete tmp;
      tmp = NULL;
    }
  }
}

bool SamePrimaryOrder(Node* left, Node* right) {
  Node* tmp_left = left; //two pointers point to the first nodes of the two decks respectively
  Node* tmp_right = right;
  int deck_size = DeckSize(left);
  int count = 0;
  while (count < deck_size) {
  	if (tmp_left-> getCard() != tmp_right-> getCard()) { //if any node different then not same
  	  return false;
  	}
  	tmp_left = tmp_left-> after; //both move to the right
  	tmp_right = tmp_right-> after;
  	count += 1;
  }
  return true;
}

bool ReversePrimaryOrder(Node* left, Node* right) {
  Node* tmp_left = left; //both point to the first node
  Node* tmp_right = right;
  while (tmp_right-> after != NULL) {
  	tmp_right = tmp_right-> after; //one moves to the last node
  }
  int deck_size = DeckSize(left);
  int count = 0;
  while (count < deck_size) {
    if (tmp_left-> getCard() != tmp_right-> getCard()) { //if any node different then not same
  	  return false;
  	}
  	tmp_left = tmp_left-> after; //move in opposite direction
  	tmp_right = tmp_right-> before;
  	count += 1;
  }
  return true;
}

void CutDeck(Node* &deck, Node* &top, Node* &bottom, const std::string& perfect) {
  if (perfect == "perfect") {
    int half_size = DeckSize(deck) / 2;
    int count = 1;
    top = deck; //top pointer points to the first node
    while (count <= half_size) {
      deck = deck-> after; //deck pointer moves to the right
      count += 1;
    }
    bottom = deck; //when reaches half, bottom pointer points to where the deck pointer points
    bottom-> before-> after = NULL;
    bottom-> before = NULL;
    while (deck-> after != NULL) {
      deck = deck-> after; //mode the deck pointer to the rightmost to make it non-exist
    }
    deck = deck-> after;
  }
}

Node* Shuffle(Node* &part1, Node* &part2, const std::string& perfect) {
  if (perfect == "perfect") {
    Node* tmp_top = part1; //two pointers point to first nodes respectively
    Node* tmp_bottom = part2;
    int each_size;
    bool which_larger;
    if (DeckSize(part1) > DeckSize(part2)) { //let size of sub-deck smaller of the two subdecks if size different
      each_size = DeckSize(part2);
      which_larger = false;
    }
    else if (DeckSize(part1) < DeckSize(part2)) {
      each_size = DeckSize(part1);
      which_larger = true;
    }
    else {
      each_size = DeckSize(part1);
      which_larger = true;
    }
    int count = 1;
    while (count < each_size) {
      tmp_top = tmp_top-> after; //moe two pointers to correspoinding node
      tmp_bottom = tmp_bottom-> after;
      tmp_top-> before-> after = tmp_bottom-> before; //link before and after nodes correspondingly
      tmp_bottom-> before-> before = tmp_top-> before;
      tmp_top-> before = NULL; //set temporary last node to NULL
      tmp_bottom-> before-> after = tmp_top;
      tmp_top-> before = tmp_bottom-> before;
      tmp_bottom-> before = NULL;
      count += 1;
    }
    if (which_larger == false) { //if first deck has more cards
      tmp_bottom-> after = tmp_top-> after; //link last of second deck and last of first deck together
      tmp_top-> after-> before = tmp_bottom;
    }
    tmp_top-> after = tmp_bottom; //if two deck size same or second deck has more, link last card of two decks together
    tmp_bottom-> before = tmp_top; //if first deck has more, link second last card of the first deck and last card of the second deck together 
    while (tmp_top-> before != NULL) {
      tmp_top = tmp_top-> before; //mode the ponter to the first node of the full node
    }
    return tmp_top;
  }
  else {
    return part1;
  }
}

void Deal(Node* &deck, Node** hands, int num_people, const string& at_time, int num_cards) {
  if (at_time == "one-at-a-time") {
    hands[0] = deck; //first nodes of person's deck
    Node* tmp0[num_cards]; //create a tmp pointer for operation
    tmp0[0] = deck;
    int move = 1;
    while (move < num_people*num_cards) {
      deck = deck-> after; //move the deck node to the right to make it NULL
      move += 1;
    }
    deck = deck-> after;
    int count = 1;
    while (count < num_people) {
      hands[count] = hands[count-1]-> after; //first nodes of all people's deck points to first n positions
      count += 1;
    }
    int counter = 1;
    while (counter < num_cards) { //move tmp pointers to corrrespoinding position, with interval = number of people
      tmp0[counter] = tmp0[counter-1]-> after;
      int incounter = 1;
      while (incounter < num_people) {
        tmp0[counter] = tmp0[counter]-> after;
        incounter += 1;
      }
      counter += 1;
    }
    int loop = 1;
    while (loop < num_people) {
      int num = 0;
      while (num < num_cards) {
        tmp0[num] = tmp0[num]-> after; //move all tmp pointers to next position for later operation
        num += 1;
      }
      num = 0;
      while (num < num_cards-1) {
        tmp0[num]-> before-> after = tmp0[num+1]-> before; //link all nodes pointer by tmp pointers together
        tmp0[num+1]-> before-> before = tmp0[num]-> before;
        tmp0[num]-> before = NULL;
        num += 1;
      }
      tmp0[num]-> before-> after = NULL; //disconnect nodes pointed by tmp pointers with previous nodes
      tmp0[num]-> before = NULL;
      loop += 1;
    }
    loop = 0;
    while (loop < num_cards-1) {
      tmp0[loop]-> after = tmp0[loop+1]; //connect last person' cards together
      tmp0[loop+1]-> before = tmp0[loop];
      loop += 1;
    }
    if (tmp0[loop]-> after != NULL) { //if there's remaining cards in the deck, disconnect the two sub-decks
      tmp0[loop]-> after-> before = NULL;
      tmp0[loop]-> after = NULL;
    }
  }
}

Node* SortHand(Node* &deck) { //use of insertion sort
  if (DeckSize(deck) == 1 || deck == NULL) {
    return deck;
  }
  int out_count = 1;
  Node* primary = deck;
  while (out_count < DeckSize(deck)) { //check for each card except the first one
    int in_count = 0;
    primary = primary-> after; //pointer points to next node in primary order
    Node* tmp = primary-> before; //make a tmp pointer points to primary previous node
    while (tmp-> sorted_next != NULL) { //find the maximum value of already sorted list
      tmp = tmp-> sorted_next;
    }
    bool smaller = false;
    while (primary-> getCard() < tmp-> getCard()) { //if the targeted card less than previously largest card
      smaller = true;
      if (out_count == 1) { //if it's the second card of the deck, directly connect the two cards
        primary-> sorted_next = tmp;
        tmp-> sorted_prev = primary;
        break;
      }
      else { //if not second card (sorted list already existed)
        if (in_count == 0) { //targeted card not in sorted list yet
          tmp-> sorted_prev-> sorted_next = primary; //insert before the maximum of the sorted list since less than
          primary-> sorted_next = tmp;
          primary-> sorted_prev = tmp-> sorted_prev;
          tmp-> sorted_prev = primary;
          tmp = primary-> sorted_prev;
          in_count += 1;
        }
        else { //targeted card already in the sorted list
          tmp-> sorted_next = primary-> sorted_next; //disconnect with the larger node
          primary-> sorted_next -> sorted_prev = tmp;
          primary-> sorted_next = tmp;
          if (tmp-> sorted_prev == NULL) { //if the previous smaller card is the first in the sorted list
            tmp-> sorted_prev = primary;
            primary-> sorted_prev = NULL;
            break;
          }
          else { //if the previous smaller card is not the first in the sorted list
            tmp-> sorted_prev-> sorted_next = primary;
            primary-> sorted_prev = tmp-> sorted_prev;
            tmp-> sorted_prev = primary;
            tmp = primary-> sorted_prev;
          }
        }
      }
    }
    if (smaller == false) { //if the targeted card is larger than the maximum of the sorted list
      primary-> sorted_prev = tmp; //directly connect to the right
      tmp-> sorted_next = primary;
    }
    out_count += 1;
  }
  while (primary-> sorted_prev != NULL) { //move tmp pointer to the first of the sorted list
    primary = primary-> sorted_prev;
  }
  return primary;
} 

void PrintDeckSorted(const string& sentence, Node* sorted_deck) {
  std::cout << sentence;
  Node* tmp = sorted_deck;
  while (tmp-> sorted_next != NULL) {
  	std::cout << " " << tmp-> getCard().getString();
  	tmp = tmp-> sorted_next; //print the content of the card and move pointer to the next
  }
  std::cout << " " << tmp-> getCard().getString() << std::endl; //print last card
}