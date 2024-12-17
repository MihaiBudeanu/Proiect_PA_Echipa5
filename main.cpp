#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "calc.h"//Includerea fisierului antet
#define error 1//constanta simbolica

//Game noughts and crosses
//tic-tac-toe
struct rows{//store table rows
    char table[50];
    char linie[20];
}row[3];

struct users {//store data user
    char username[50];
    int numb_play;
    int place[20];
}name[3];

 void message(){//requires a number from 1 to 100
     for(int i = 0; i < 2; i++){
        printf("\t%s enter a number from 1 to 100: ",name[i].username);
        scanf("\t%d",&name[i].numb_play);
     }
 }

int comp_rand_num(){//generate random number
    srand(time(NULL));
    int max = 100, min = 1;
    int num_rand = rand() % (max - min +1) + min;

    int *p;//pointer
    p = &num_rand;//atribuire poenterului adresa lui num_rand

    for(int i =0; i<2 ;i++){
        name[i].numb_play = name[i].numb_play - *p;//num_rand;
    }

    printf("\tRandom number %d. \n",num_rand);

    if(fabs(name[0].numb_play) > fabs(name[1].numb_play)){
        printf("\tPlayer %s goes first with X.\n",name[1].username);
        printf("\tThen %s goes with O.\n",name[0].username);
        return 1;
    }
    else{
        printf("\tPlayer %s goes first with X.\n",name[0].username);
        printf("\tThen %s goes with O.\n",name[1].username);
        return 0;
    }
 }

 void show_tables(){//show tables
     printf("\n\t\t%s\n",row[0].table);
     printf("\t\t%s \n",row[0].linie);
     printf("\t\t%s \n",row[1].table);
     printf("\t\t%s \n",row[0].linie);
     printf("\t\t%s \n \n",row[2].table);
 }
/*void calc_row_1(int &num){
    num -= 3;
    num *=4;
}*/
//check winning combination
int check_turns(int k, int player) {//transferu parametrelor unei funciei prin valoare
    int arr[8] = {0};
    int winn_row[8][3] = {
        {0, 1, 2},
        {0, 4, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {3, 4, 5},
        {6, 7, 8},
        {6, 4, 2}
    };

    for (int d = 0; d < k + 1; d++){
        for (int i = 0; i < 8; i++){
                for(int j=0;j<3;j++){
                    if (name[player].place[d] ==*(*(winn_row+i)+j))//pointer si tablou udemensional
                        arr[i]+=1;
                }
            if (arr[i] == 3)
                return 1;
        }
    }
    return 0;
}

void replace_O_X(int ind, int ind2, char nought_cross){//replace X and O
    int num =name[ind].place[ind2];
    if(name[ind].place[ind2] >= 0 && name[ind].place[ind2] < 3){
        num = num * 4;
        row[0].table[num] = nought_cross;
        }
     if(name[ind].place[ind2] >= 3 && name[ind].place[ind2] < 6 ){
        calc_row_1(num);//fisier extern calc.h
        row[1].table[num] = nought_cross;
     }
     if(name[ind].place[ind2] >= 6 && name[ind].place[ind2] <= 8 ){
        num-=3;
        calc_row_1(num);//fisier extern calc.h
        row[2].table[num] = nought_cross;
     }
}

//separate replacement of the O symbol
 int slect_gamer0(int &j,char *username){//Transferul parametrilor unei funcții cu ajutorul pointerilor
     //si transferul parametrilor unei funcții prin adresă cu ajutorul referinţelor
    printf("\t%s choose a place:",username);
    scanf("\t %d",&name[0].place[j]);

    replace_O_X(0,j,'O');

    show_tables();

    if(check_turns(j,0))
        return 1;
    j++;
    return 0;
 }

  int slect_gamer1(int &i,char *username){//separate replacement of the X symbol
    printf("\t %s choose a place:",username);
    scanf("\t %d",&name[1].place[i]);

    replace_O_X(1,i,'X');

    show_tables();

    if(check_turns(i,1))
        return 1;
    i++;
    return 0;
 }

int main()
{
    int i,j,d;
    i=j=d=0;
    printf("\n \t\tGAME TIC-TOC-TOE\n");
    //table
    strcpy(row[0].table,"0 | 1 | 2");
    strcpy(row[1].table,"3 | 4 | 5");
    strcpy(row[2].table,"6 | 7 | 8");
    strcpy(row[0].linie,"---------");

    for(int i = 0;i < 2;i++){//requires names from users
        printf("\tEnter the player's name N%d: ",i+1);
        scanf("%s",name[i].username);
    }

    again:
    message();
    //checking if the number is entered correctly
    if(name[0].numb_play == name[1].numb_play || name[1].numb_play < 1 || name[1].numb_play >= 100 || name[0].numb_play < 1 || name[0].numb_play >= 100){
        printf("\tThe numbers were the same or do not fit in the range between 1 and 100, enter other numbers.\n");
        goto again;
    }

    int turn = comp_rand_num();

    show_tables();


    #if defined (error)//compilare conditionata
    while(d < 5 ){//loop determining the end of the game and displaying a message about the winner
        if(slect_gamer1(i,name[turn].username)){
            printf("\t WINNER is the %s. \n",name[turn].username);
            break;
        }

        if(d == 4){
            printf("\n \t\tGAME OVER\n");
            break;
        }
        if(slect_gamer0(j,name[1-turn].username)){
            printf("\t WINNER is the %s. \n",name[1-turn].username);
            break;
        }
        d++;
    }
    #endif
    #ifndef error
    printf("ERORR");
    #endif // e_error
    return 0;
}
