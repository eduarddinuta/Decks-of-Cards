// Copyright 2022 Dinuta Eduard-Stefan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "card_decks.h"

// verifica daca o carte de joc introdusa la input este valida
// si poate fi adaugata intr-un pachet
int check_card(card_t card)
{
    char *symbols[10] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
    if (card.value < 1 || card.value > 14)
        return 0;
    for (int i = 0; i < 4; i++)
        if (strcmp(card.symbol, symbols[i]) == 0)
            return 1;
    return 0;
}

// verifica daca indexul unui nod se incadreaza in dimensiunile unei liste
int check_index(double_list_t* list, int idx)
{
    if (idx < 0 || idx >= list->size)
        return 0;
    return 1;
}

// functia creeaza un nou pachet de carti, citind carti pana cand
// n dintre acestea sunt valide si il introduce in lista de pachete
void ADD_DECK(double_list_t *list, int n, char *line)
{
    char *bad = malloc(NMAX);
    double_list_t *deck = create_list(sizeof(card_t));
    card_t card;
    for (int i = 0; i < n; i++) {
        fgets(line, 100, stdin);
        int arg = sscanf(line, "%d%s%s", &card.value, card.symbol, bad);
        if (!check_card(card) || arg != 2) {
            printf("The provided card is not a valid one.\n");
            i--;
            continue;
        }
        add_nth_node(deck, deck->size, &card);
    }
    add_nth_node(list, list->size, deck);
    free(deck);
    printf("The deck was successfully created with %d cards.\n", n);
    free(bad);
}

// sterge o carte dintr-un pachet, iar daca pachetul ramane gol
// il elimina si pe acesta din lista de pachete
void DEL_CARD(double_list_t *list, int deck_i, int card_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    if (!check_index(d, card_i)) {
        printf("The provided index is out of bounds for deck %d.\n", deck_i);
        return;
    }
    node_t *remove = remove_nth_node(d, card_i);
    free(remove->data);
    free(remove);
    if (d->size == 0) {
        remove = remove_nth_node(list, deck_i);
        double_list_t *d = (double_list_t *)remove->data;
        free_list(&d);
        free(remove);
    }
    printf("The card was successfully deleted from deck %d.\n", deck_i);
}

// adauga un numar n de carti la un pachet deja existent, citind
// carti pana cand n dintre ele sunt valide
void ADD_CARDS(double_list_t *list, int deck_i, int n)
{
    char *line = malloc(NMAX);
    char *bad = malloc(NMAX);
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        free(line);
        free(bad);
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    card_t card = {0, ""};
    for (int i = 0; i < n; i++) {
        fgets(line, 100, stdin);
        int arg = sscanf(line, "%d%s%s", &card.value, card.symbol, bad);
        if (!check_card(card) || arg != 2) {
            printf("The provided card is not a valid one.\n");
            i--;
            continue;
        }
        add_nth_node(d, d->size, &card);
    }
    printf("The cards were successfully added to deck %d.\n", deck_i);
    free(line);
    free(bad);
}

// gaseste pachetul cu indexul deck_i si apeleaza functia de shuffle
// pentru a il inversa la jumatate
void SHUFFLE_DECK(double_list_t *list, int deck_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    shuffle(d);
    printf("The deck %d was successfully shuffled.\n", deck_i);
}

// gaseste doua pachete cu indecsii d1 si d2, creeaza
// un nou pachet prin combinarea celor doua, pe care il adauga in
// lista de pachete, iar deck1_i si deck2_i sunt eliminate
void MERGE_DECKS(double_list_t *list, int d1, int d2)
{
    if (!check_index(list, d1) || !check_index(list, d2)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, d1);
    double_list_t *deck1 = (double_list_t *)node->data;
    node = get_nth_node(list, d2);
    double_list_t *deck2 = (double_list_t *)node->data;
    double_list_t *new_deck = merge_decks(deck1, deck2);
    delete_deck(list, d1);
    if (d1 < d2)
        d2--;
    delete_deck(list, d2);
    add_nth_node(list, list->size, new_deck);
    free(new_deck);
    if (d1 <= d2)
        d2++;
    printf("The deck %d and the deck %d were successfully merged.\n", d1, d2);
}

// afiseaza dimeansiunea pachetului deck_i
void DECK_LEN(double_list_t *list, int deck_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    printf("The length of deck %d is %d.\n", deck_i, d->size);
}

// gaseste pachetul cu indexul deck_i si il separa la pozitia pos
// in alte doua pachete
void SPLIT_DECK(double_list_t *list, int deck_i, int pos)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    if (!check_index(d, pos)) {
        printf("The provided index is out of bounds for deck %d.\n", deck_i);
        return;
    }
    split_deck(list, &d, deck_i, pos);
    printf("The deck %d was successfully split by index %d.\n", deck_i, pos);
}

// gaseste pachetul cu indexul deck_i si inverseaza ordinea cartilor
void REVERSE_DECK(double_list_t *list, int deck_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    reverse_deck(d);
    printf("The deck %d was successfully reversed.\n", deck_i);
}

// afiseaza cartile continute de pachetul deck_i
void SHOW_DECK(double_list_t* list, int deck_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    print_deck(d, deck_i);
}

// sorteaza cartile unui pachet prin apelarea functiei sort_deck cu
// functia de comaparare compare_cardss
void SORT_DECK(double_list_t *list, int deck_i)
{
    if (!check_index(list, deck_i)) {
        printf("The provided index is out of bounds for the deck list.\n");
        return;
    }
    node_t *node = get_nth_node(list, deck_i);
    double_list_t *d = (double_list_t *)node->data;
    sort_deck(d, compare_cards);
    printf("The deck %d was successfully sorted.\n", deck_i);
}
