// Copyright 2022 Dinuta Eduard-Stefan
#ifndef CARD_DECKS_H_
#define CARD_DECKS_H_
#define NMAX 100

typedef struct card_t
{
    int value;
    char symbol[10];
} card_t;

int check_index(double_list_t* , int);

int check_card(card_t);

void ADD_DECK(double_list_t *, int , char *);

void DEL_CARD(double_list_t *, int , int);

void ADD_CARDS(double_list_t *, int , int);

void SHUFFLE_DECK(double_list_t *, int);

void MERGE_DECKS(double_list_t *, int , int);

void DECK_LEN(double_list_t *, int);

void DECK_LEN(double_list_t *, int);

void SPLIT_DECK(double_list_t *, int , int);

void REVERSE_DECK(double_list_t *, int);

void SHOW_DECK(double_list_t* , int);

void SORT_DECK(double_list_t *, int);

#endif  // CARD_DECKS_H_
