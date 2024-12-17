#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifndef CALC_H_INCLUDE
#define CALC_H_INCLUDE
void calc_row_1(int &num){
    num -= 3;
    num *= 4;
}
#endif

struct rows {
    char table[50];
    char linie[20];
} row[3];

struct users {
    char username[50];
    int numb_play;
    int place[20];
    int score;  // Tracks each player's score
} name[2];

void reset_board() {
    strcpy(row[0].table, "0 | 1 | 2");
    strcpy(row[1].table, "3 | 4 | 5");
    strcpy(row[2].table, "6 | 7 | 8");
    strcpy(row[0].linie, "---------");
}

void show_tables() {
    printf("\n\t\t%s\n", row[0].table);
    printf("\t\t%s\n", row[0].linie);
    printf("\t\t%s\n", row[1].table);
    printf("\t\t%s\n", row[0].linie);
    printf("\t\t%s\n\n", row[2].table);
}

int validate_input() {
    char input[10];
    int value;
    while (1) {
        scanf("%s", input);
        int is_valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                is_valid = 0;
                break;
            }
        }

        if (is_valid) {
            value = atoi(input);
            if (value >= 0 && value <= 8) {
                int row_idx = value / 3;
                int col_idx = (value % 3) * 4;
                if (row[row_idx].table[col_idx] == 'X' || row[row_idx].table[col_idx] == 'O') {
                    printf("Position already taken. Choose another: ");
                    continue;
                }
                return value;
            }
        }
        printf("Invalid input. Please enter a number between 0 and 8: ");
    }
}

int check_turns(int k, int player) {
    int arr[8] = {0};
    int winn_row[8][3] = {
        {0, 1, 2}, {0, 4, 8}, {0, 3, 6}, {1, 4, 7}, 
        {2, 5, 8}, {3, 4, 5}, {6, 7, 8}, {6, 4, 2}
    };

    for (int d = 0; d <= k; d++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                if (name[player].place[d] == winn_row[i][j])
                    arr[i]++;
            }
            if (arr[i] == 3) return 1;
        }
    }
    return 0;
}

void replace_O_X(int ind, int ind2, char nought_cross) {
    int num = name[ind].place[ind2];
    if (num >= 0 && num < 3) {
        row[0].table[num * 4] = nought_cross;
    } else if (num >= 3 && num < 6) {
        calc_row_1(num);
        row[1].table[num] = nought_cross;
    } else if (num >= 6 && num <= 8) {
        num -= 3;
        calc_row_1(num);
        row[2].table[num] = nought_cross;
    }
}

int select_gamer(int &turns, int player, char symbol) {
    printf("\t%s, choose a place: ", name[player].username);
    name[player].place[turns] = validate_input();
    replace_O_X(player, turns, symbol);
    show_tables();

    if (check_turns(turns, player)) return 1;
    turns++;
    return 0;
}

int play_round() {
    int i = 0, j = 0, d = 0;
    int turn = rand() % 2;  // Randomize first player
    reset_board();
    show_tables();

    while (d < 5) {
        if (select_gamer(i, turn, 'X')) {
            printf("\tWINNER: %s!\n", name[turn].username);
            name[turn].score++;
            return turn;
        }
        if (d == 4) break;
        if (select_gamer(j, 1 - turn, 'O')) {
            printf("\tWINNER: %s!\n", name[1 - turn].username);
            name[1 - turn].score++;
            return 1 - turn;
        }
        d++;
    }
    printf("\n\tGAME OVER: It's a draw!\n");
    return -1;  // Draw
}

int main() {
    int rounds, winner;

    printf("\n\t\tWELCOME TO TIC-TAC-TOE\n");
    printf("\tEnter the score limit (1-8): ");
    scanf("%d", &rounds);

    for (int i = 0; i < 2; i++) {
        printf("\tEnter Player %d's name: ", i + 1);
        scanf("%s", name[i].username);
        name[i].score = 0;  // Initialize scores
    }

    srand(time(NULL));

    for (int r = 0; r < rounds; r++) {
        printf("\n\t--- ROUND %d ---\n", r + 1);
        winner = play_round();
    }

    printf("\n\tFINAL SCORES:\n");
    printf("\t%s: %d\n", name[0].username, name[0].score);
    printf("\t%s: %d\n", name[1].username, name[1].score);

    if (name[0].score > name[1].score)
        printf("\tOVERALL WINNER: %s!\n", name[0].username);
    else if (name[1].score > name[0].score)
        printf("\tOVERALL WINNER: %s!\n", name[1].username);
    else
        printf("\tIt's a tie!\n");

    return 0;
}
