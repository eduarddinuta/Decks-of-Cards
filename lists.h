// Copyright 2022 Dinuta Eduard-Stefan
#ifndef LISTS_H_
#define LISTS_H_
#define NMAX 100

typedef struct node_t
{
    void *data;
    struct node_t *prev, *next;
} node_t;

typedef struct double_list_t
{
    node_t *head;
    int data_size;
    int size;
} double_list_t;

void free_list(double_list_t**);

void free_all(double_list_t **);

double_list_t* create_list(unsigned int);

node_t* create_node(double_list_t *, const void*);

void add_nth_node(double_list_t* , unsigned int n, const void*);

node_t* remove_nth_node(double_list_t* , unsigned int);

node_t* get_nth_node(double_list_t* , unsigned int);

void print_deck(double_list_t* , int);

void print_cards(double_list_t*);

void shuffle(double_list_t*);

double_list_t* merge_decks(double_list_t* , double_list_t*);

void split_deck(double_list_t* , double_list_t** , int , int);

void delete_deck(double_list_t* , int);

void reverse_deck(double_list_t*);

int compare_cards(void *, void *);

void sort_deck(double_list_t* , int (*compare_function)(void*, void*));

#endif   // LISTS_H_
