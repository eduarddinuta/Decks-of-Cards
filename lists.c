// Copyright 2022 Dinuta Eduard-Stefan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "card_decks.h"

void free_list(double_list_t** list)
{
    node_t *curr = (*list)->head;

    for (int i = 0; i < (*list)->size; i++) {
        node_t *tmp = curr->next;
        free(curr->data);
        free(curr);
        curr = tmp;
    }

    free(*list);
    *list = NULL;
}

// elibereaza memoria tuturor pachetelor de carti si a listei de pachete
void free_all(double_list_t **list)
{
    node_t *deck = (*list)->head;
    while (deck != NULL) {
        node_t* tmp = deck->next;
        double_list_t *d = (double_list_t *)deck->data;
        free_list(&d);
        free(deck);
        deck = tmp;
    }
    free(*list);
}

// creeaza o lista dublu inlantuita, de tipul de date cu dimensiunea
// data_size
double_list_t* create_list(unsigned int data_size)
{
    double_list_t *list = malloc(sizeof(double_list_t));
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;
    return list;
}

// creeaza un nod al unei liste dublu inlantuite, caruia ii atribuie
// informatia din pointerul void data, in functie de dimensiunea
// datelor din lista
node_t* create_node(double_list_t *list, const void* data)
{
    node_t *new = malloc(sizeof(node_t));
    new->data = malloc(list->data_size);
    memcpy(new->data, data, list->data_size);
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// adauga un nod pe pozitia n a unei liste dublu inlantuite
void add_nth_node(double_list_t* list, unsigned int n, const void* new_data)
{
    list->size++;
    node_t *new, *curr, *prev;
    curr = list->head;
    prev = NULL;
    new = create_node(list, new_data);

    while (curr != NULL && n > 0) {
        prev = curr;
        curr = curr->next;
        n--;
    }

    if (prev == NULL) {
        if (list->head != NULL)
            list->head->prev = new;
        new->next = list->head;
        list->head = new;
        return;
    }

    prev->next = new;
    new->prev = prev;
    new->next = curr;
    if (curr != NULL)
        curr->prev = new;
}

// elimina nodul de pe pozitia n a unei liste dublu inlantuite si
// il returneaza, eliberarea memoriei facandu-se ulterior, dupa terminarea
// functiei
node_t* remove_nth_node(double_list_t* list, unsigned int n)
{
    node_t *curr = list->head;
    if (list->size == 0)
        return NULL;

    list->size--;
    while (n > 0) {
        curr = curr->next;
        n--;
    }

    if (curr == list->head) {
        list->head = curr->next;
        if (list->head != NULL)
            list->head->prev = NULL;
    } else {
        curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
    }

    return curr;
}

// parcurge o lista dublu inlantuita si returneaza al n-lea nod din lista
node_t* get_nth_node(double_list_t* list, unsigned int n)
{
    node_t *curr = list->head;
    while (n > 0) {
        curr = curr->next;
        n--;
    }

    return curr;
}

// afiseaza cartiele dintr-un pachet prin parcurgerea listei dublu inlantuite
void print_deck(double_list_t* list, int n)
{
    node_t *curr = list->head;
    printf("Deck %d:\n", n);
    while (curr != NULL) {
        card_t *card = (card_t *)(curr->data);
        printf("\t%d %s\n", card->value, card->symbol);
        curr = curr->next;
    }
}

// afiseaza toate cartile din toate pachetele din lista de pachete
void print_cards(double_list_t* list)
{
    node_t *deck = list->head;
    int n = 0;
    while (deck != NULL) {
        double_list_t *d = (double_list_t *)deck->data;
        print_deck(d, n);
        deck = deck->next;
        n++;
    }
}

// interschimba prima jumatate a unui pachet cu a doua jumatate
// prin legarea primului nod la ultimul si actualizarea legaturilor
void shuffle(double_list_t* list)
{
    node_t *curr = list->head, *last;
    for (int i = 0; i < list->size / 2 - 1; i++)
        curr = curr->next;

    last = curr;
    while (last->next != NULL)
        last = last->next;

    last->next = list->head;
    list->head->prev = last;
    list->head = curr->next;
    curr->next->prev = NULL;
    curr->next = NULL;
}

// creeaza un nou pachet de carti prin unirea a doua pachete, luand pe rand
// cate o carte din fiecare si apoi ce ramane din cel cu dimensiunea mai mare
double_list_t* merge_decks(double_list_t* deck1, double_list_t* deck2)
{
    double_list_t *new_deck = create_list(sizeof(card_t));
    node_t *card1 = deck1->head;
    node_t *card2 = deck2->head;
    while (card1 != NULL && card2 != NULL) {
        add_nth_node(new_deck, new_deck->size, card1->data);
        add_nth_node(new_deck, new_deck->size, card2->data);
        card1 = card1->next;
        card2 = card2->next;
    }

    while (card1 != NULL) {
        add_nth_node(new_deck, new_deck->size, card1->data);
        card1 = card1->next;
    }

    while (card2 != NULL) {
        add_nth_node(new_deck, new_deck->size, card2->data);
        card2 = card2->next;
    }

    return new_deck;
}

// separa un pachet in doua prin construirea a doua pachete noi
// primul va contine cartile pana la pozitia pos, iar al doilea
// restul cartilor
void split_deck(double_list_t* list, double_list_t** deck, int idx, int pos)
{
    if (pos == 0 || pos == (*deck)->size)
        return;

    double_list_t *deck1 = create_list(sizeof(card_t));
    double_list_t *deck2 = create_list(sizeof(card_t));

    node_t *curr = (*deck)->head;
    for (int i = 0; i < pos; i++) {
        add_nth_node(deck1, deck1->size, curr->data);
        curr = curr->next;
    }

    for (int i = pos; i < (*deck)->size; i++) {
        add_nth_node(deck2, deck2->size, curr->data);
        curr = curr->next;
    }

    node_t *remove = remove_nth_node(list, idx);
    free_list(deck);
    free(remove);
    remove = NULL;
    add_nth_node(list, idx, deck1);
    add_nth_node(list, idx + 1, deck2);
    free(deck1);
    free(deck2);
}

// sterge un pachet de carti din lista de pachete si elibereaza memoria
// alocata acestuia
void delete_deck(double_list_t* list, int n)
{
    if (!check_index(list, n)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *remove = remove_nth_node(list, n);
    double_list_t *d = (double_list_t *)remove->data;
    free_list(&d);
    free(remove);
    remove = NULL;
}

// inverseaza ordinea cartilor intr-un pachet, prin inversarea
// ordinii nodurilor dintr-o lista dublu inlantuita
void reverse_deck(double_list_t* list)
{
    node_t *curr;
    curr = list->head;
    while (curr != NULL) {
        if (curr->next == NULL)
            list->head = curr;
        node_t *tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = tmp;
    }
}

// functie de comparare folosita la sortarea cartilor dintr-un pachet
int compare_cards(void *a, void *b)
{
    char *symbols[10] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
    card_t *card1 = (card_t*)a;
    card_t *card2 = (card_t*)b;
    if (card1->value < card2->value) {
        return -1;
    } else if (card1->value > card2->value) {
        return 1;
    } else {
        int idx1 = 0, idx2 = 0;
        for (int i = 0; i < 4; i++) {
            if (strcmp(card1->symbol, symbols[i]) == 0)
                idx1 = i;
            if (strcmp(card2->symbol, symbols[i]) == 0)
                idx2 = i;
        }
        if (idx1 < idx2) {
            return -1;
        } else  {
            return 1;
        }
    }
    return 0;
}

// sorteaza elementele unei liste dublu inlantuite folosint o functie de
// comparare generica
void sort_deck(double_list_t* list, int (*compare_function)(void*, void*))
{
    node_t *card1 = list->head;
    while (card1 != NULL) {
        node_t *card2 = card1->next;
        while (card2 != NULL) {
            if ((*compare_function)(card1->data, card2->data) > 0) {
                void *tmp = card1->data;
                card1->data = card2->data;
                card2->data = tmp;
            }
            card2 = card2->next;
        }
        card1 = card1->next;
    }
}
