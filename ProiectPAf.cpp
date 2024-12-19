#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <cstring>

using namespace std;

#ifndef CALC_H_INCLUDE
#define CALC_H_INCLUDE
void calc_row_1(int &num) {
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
    int score;  // Scorul fiecărui jucător
    int guess;  // Numărul ghicit pentru determinarea primului pas
} name[2];

// Resetează tabla de joc la valorile inițiale
void reset_board() {
    strcpy(row[0].table, "0 | 1 | 2");
    strcpy(row[1].table, "3 | 4 | 5");
    strcpy(row[2].table, "6 | 7 | 8");
    strcpy(row[0].linie, "---------");
}

// Afișează tabla de joc
void show_tables() {
    cout << "\n\t\t" << row[0].table << "\n";
    cout << "\t\t" << row[0].linie << "\n";
    cout << "\t\t" << row[1].table << "\n";
    cout << "\t\t" << row[0].linie << "\n";
    cout << "\t\t" << row[2].table << "\n\n";
}

// Validează intrarea utilizatorului
int validate_input() {
    char input[10];
    int value;
    while (1) {
        cin >> input;
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
                    cout << "Pozitia este deja ocupată. Alege altă poziție: ";
                    continue;
                }
                return value;
            }
        }
        cout << "Intrare invalidă. Introdu un număr între 0 și 8: ";
    }
}

// Verifică dacă jucătorul a câștigat
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

// Înlocuiește simbolurile pe tablă
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

// Determină jucătorul care începe pe baza numărului ghicit
int determine_first_player() {
    cout << "\n\tAlegeți un număr între 1 și 100:\n";
    for (int i = 0; i < 2; i++) {
        cout << "\t" << name[i].username << ", introduceți numărul: ";
        cin >> name[i].guess;
    }

    int random_number = rand() % 100 + 1;
    cout << "\n\tNumărul generat este: " << random_number << "\n";

    int diff1 = abs(random_number - name[0].guess);
    int diff2 = abs(random_number - name[1].guess);

    if (diff1 < diff2) {
        cout << "\t" << name[0].username << " este mai aproape și începe primul!\n";
        return 0;
    } else if (diff2 < diff1) {
        cout << "\t" << name[1].username << " este mai aproape și începe primul!\n";
        return 1;
    } else {
        cout << "\tEgalitate! " << name[0].username << " începe primul prin regula egalității.\n";
        return 0;
    }
}

// Selectează jucătorul curent
int select_gamer(int &turns, int player, char symbol) {
    cout << "\t" << name[player].username << ", alege o poziție: ";
    name[player].place[turns] = validate_input();
    replace_O_X(player, turns, symbol);
    show_tables();

    if (check_turns(turns, player)) return 1;
    turns++;
    return 0;
}

// Joacă o rundă
int play_round() {
    int i = 0, j = 0, d = 0;
    int turn = determine_first_player();  // Determină cine începe
    reset_board();
    show_tables();

    while (d < 5) {
        if (select_gamer(i, turn, 'X')) {
            cout << "\tCÂȘTIGĂTOR: " << name[turn].username << "!\n";
            name[turn].score++;
            return turn;
        }
        if (d == 4) break;
        if (select_gamer(j, 1 - turn, 'O')) {
            cout << "\tCÂȘTIGĂTOR: " << name[1 - turn].username << "!\n";
            name[1 - turn].score++;
            return 1 - turn;
        }
        d++;
    }
    cout << "\n\tJOC TERMINAT: Egalitate!\n";
    return -1;  // Egalitate
}

// Program principal
int main() {
    int rounds, winner;

    cout << "\n\t\tBUN VENIT LA X ȘI 0\n";
    cout << "\tIntroduceți scorul limită (1-8): ";
    cin >> rounds;

    for (int i = 0; i < 2; i++) {
        cout << "\tIntroduceți numele Jucătorului " << i + 1 << ": ";
        cin >> name[i].username;
        name[i].score = 0;  // Inițializează scorurile
    }

    srand(time(NULL));

    for (int r = 0; r < rounds; r++) {
        cout << "\n\t--- RUNDA " << r + 1 << " ---\n";
        winner = play_round();
    }

    cout << "\n\tSCORURI FINALE:\n";
    cout << "\t" << name[0].username << ": " << name[0].score << "\n";
    cout << "\t" << name[1].username << ": " << name[1].score << "\n";

    if (name[0].score > name[1].score)
        cout << "\tCÂȘTIGĂTORUL FINAL: " << name[0].username << "!\n";
    else if (name[1].score > name[0].score)
        cout << "\tCÂȘTIGĂTORUL FINAL: " << name[1].username << "!\n";
    else
        cout << "\tEste o egalitate!\n";

    return 0;
}
