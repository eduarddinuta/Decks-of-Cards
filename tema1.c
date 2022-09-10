// Copyright 2022 Dinuta Eduard-Stefan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "card_decks.h"

int main(void)
{
    double_list_t *list;
    list = create_list(sizeof(double_list_t));
    char *command = malloc(NMAX);
    char *line = malloc(NMAX);
    char *bad = malloc(NMAX);
    while (1) {
        int n, x, y;
        fgets(line, 100, stdin);
        if (sscanf(line, "%s ", command) == 0)
		    return -1;
        if (strcmp(command, "ADD_DECK") == 0) {
            int arg = sscanf(line, "%s %d %s", command, &n, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            ADD_DECK(list, n, line);
        } else if (strcmp(command, "SHOW_ALL") == 0) {
            int arg = sscanf(line, "%s %s ", command, bad);
            if (arg != 1) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            print_cards(list);
        } else if (strcmp(command, "DEL_DECK") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &n, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            int ok = check_index(list, n);
            delete_deck(list, n);
            if (ok)
                printf("The deck %d was successfully deleted.\n", n);
        } else if (strcmp(command, "DEL_CARD") == 0) {
            int arg = sscanf(line, "%s%d%d%s", command, &x, &y, bad);
            if (arg != 3) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            DEL_CARD(list, x, y);
        } else if (strcmp(command, "ADD_CARDS") == 0) {
            int arg = sscanf(line, "%s%d%d%s", command, &x, &n, bad);
            if (arg != 3) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
           ADD_CARDS(list, x, n);
        } else if (strcmp(command, "DECK_NUMBER") == 0) {
            int arg = sscanf(line, "%s%s", command, bad);
            if (arg != 1) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            printf("The number of decks is %d.\n", list->size);
        } else if (strcmp(command, "DECK_LEN") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &x, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            DECK_LEN(list, x);
        } else if (strcmp(command, "SHUFFLE_DECK") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &x, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            SHUFFLE_DECK(list, x);
        } else if (strcmp(command, "MERGE_DECKS") == 0) {
            int arg = sscanf(line, "%s%d%d%s", command, &x, &y, bad);
            if (arg != 3) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            MERGE_DECKS(list, x, y);
        } else if (strcmp(command, "SPLIT_DECK") == 0) {
            int arg = sscanf(line, "%s%d%d%s", command, &x, &y, bad);
            if (arg != 3) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            SPLIT_DECK(list, x, y);
        } else if (strcmp(command, "REVERSE_DECK") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &x, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            REVERSE_DECK(list, x);
        } else if (strcmp(command, "SHOW_DECK") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &x, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            SHOW_DECK(list, x);
        } else if (strcmp(command, "SORT_DECK") == 0) {
            int arg = sscanf(line, "%s%d%s", command, &x, bad);
            if (arg != 2) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            SORT_DECK(list, x);
        } else if (strcmp(command, "EXIT") == 0) {
            int arg = sscanf(line, "%s%s", command, bad);
            if (arg != 1) {
                printf("Invalid command. Please try again.\n");
                continue;
            }
            free_all(&list);
            break;
        } else {
            printf("Invalid command. Please try again.\n");
        }
    }
    free(command);
    free(line);
    free(bad);

    return 0;
}
