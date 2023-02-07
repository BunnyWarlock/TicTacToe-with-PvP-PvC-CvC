/*
 * A game of Tic-Tac-Toe
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printBoard(char b1, char b2, char b3, short x){
    printf ("     |     |     \n");
    printf ("  %c  |  %c  |  %c  \n", b1, b2, b3);
    if (x == 1)
        printf ("_____|_____|_____\n");
    else
        printf ("     |     |     \n");
}

void updateBoard(char t[]){
    printf ("\n");
    printBoard (t[1], t[2], t[3], 1);
    printBoard (t[4], t[5], t[6], 1);
    printBoard (t[7], t[8], t[9], 0);
    printf ("\n");
}

char player(int track){
    if (track % 2 == 0)
        return 'O';
    else
        return 'X';
}

int ask(char count[]){
    int x;
    printf ("Move %d: %c's Turn --> ", count[0], player(count[0]));
    scanf ("%d", &x);

    if (x > 9 || x < 1 || count[x] != 0){
        printf ("\nInvalid Move !!! Try again... \n\n");
        ask(count);
    }
    else
        return x;
}

int gamemode(){
    int g;
    printf ("\nWhich Gamemode do you want to play? ");
    scanf ("%d", &g);
    printf ("\n");
    if ((g > 4 || g < 1) && g != 50){
        printf ("Invalid Gamemode... Try again. \n");
        gamemode();
    }
    else
        return g;
}

int welcome(){
    char t[10] = {1, 49, 50, 51, 52, 53, 54, 55, 56, 57};
    printf ("Welcome to Tic-Tac-Toe \n");
    printf ("Each tile of the board is numbered as shown below... \n");
    updateBoard(t);
    printf ("To register a move, enter the number of the tile (when asked) and press Enter. \n");
    printf ("DON'T ENTER LETTERS OR OTHER CHARACTERS !!! Or else the game will crash. \n\n");

    printf ("Gamemodes: \n");
    printf ("\t 1) Player Vs Player \n");
    printf ("\t 2) Player Vs Computer (Player goes first) \n");
    printf ("\t 3) Computer Vs Player (Computer goes first) \n");
    printf ("\t 4) Computer Vs Computer \n");
    return gamemode();
}

int check(char b[]){
    if (b[1] == b[2] && b[2] == b[3] && b[1] != 0)
        return 1;
    else if (b[4] == b[5] && b[5] == b[6] && b[4] != 0)
        return 1;
    else if (b[7] == b[8] && b[8] == b[9] && b[7] != 0)
        return 1;
    else if (b[1] == b[4] && b[4] == b[7] && b[1] != 0)
        return 1;
    else if (b[2] == b[5] && b[5] == b[8] && b[2] != 0)
        return 1;
    else if (b[3] == b[6] && b[6] == b[9] && b[3] != 0)
        return 1;
    else if (b[1] == b[5] && b[5] == b[9] && b[1] != 0)
        return 1;
    else if (b[3] == b[5] && b[5] == b[7] && b[3] != 0)
        return 1;
    else
        return 0;
}

void endMessage(char tile[], int end){
    updateBoard(tile);
    switch (end){
        case (1):
            tile[0]--;
            printf ("%c Wins in %d Moves !!! Congratulations !!! \n", player(tile[0]), tile[0]);
            break;
        default:
            printf ("The Game is a Draw... Good Game. \n");
            break;
    }
}

int commonSense(char f, char s, char t, char p, int loop){
    if ((f == p || s == p) && (f == p || t == p) && (s == p || t == p)){
        if (f == 0)
            return loop + 1;
        else if (s == 0)
            return loop + 2;
        else if (t == 0)
            return loop + 3;
    }
    return 0;
}

int helper(char t[]){
    int win[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 4, 7, 2, 5, 8, 3, 6, 9, 1, 5, 9, 3, 5, 7},
        loop = 0,
        sto;

    while (loop < 24){
        sto = commonSense(t[win[loop]], t[win[loop + 1]], t[win[loop + 2]], player(t[0]), loop);
        switch (sto){
        case (0):
            loop += 3;
            break;
        default:
            return win[sto - 1];
        }
    }

    return 0;
}

int comp(char board[], int lvl, int lap){
    int loop = 0,
        x = helper(board);
    srand(time(0) + lap);
    switch (x){
        case (0):
            board[0]++;
            x = helper(board);
            board[0]--;
    }
    if (x == 0){
        switch (lvl){
            case (1):
                while (loop < 1){
                    x = (rand() % 9) + 1;
                    if (board[x] == 0)
                        loop++;
                }
                break;
        }
    }

    return x;
}

int simulate(int loop){
    char tile[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int move,
        end = 0;

    while (end != 1 && tile[0] < 10){
        move = comp(tile, 1, loop);
        tile[move] = player(tile[0]);
        tile[0]++;
        end = check(tile);
    }

    if (end == 1){
        tile[0]--;
        return (tile[0] % 2);
    }
    else
        return 2;
}

void preset1(){
    char tile[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int move,
        end = 0;

    printf ("You have selected Player Vs Player. Enjoy. \n");
    while (end != 1 && tile[0] < 10){
        updateBoard(tile);
        move = ask(tile);
        tile[move] = player(tile[0]);
        tile[0]++;
        end = check(tile);
    }

    endMessage(tile, end);
}

void preset2(short m){
    char tile[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int move,
        end = 0;

    switch (m){
        case (0):
            printf ("You have selected Player Vs Computer (Player goes first). Enjoy. \n");
            break;
        case (1):
            printf ("You have selected Computer Vs Player (Computer goes first). Enjoy. \n");
            break;
        case (2):
            printf ("You have selected Computer Vs Computer. Enjoy. \n");
            break;
    }

    while (end != 1 && tile[0] < 10){
        updateBoard(tile);

        if (tile[0] % 2 == m || m == 2){
            printf ("Move %d: %c's Turn (Computer Thinking...) \n", tile[0], player(tile[0]));
            move = comp(tile, 1, 0);
        }
        else
            move = ask(tile);

        tile[move] = player(tile[0]);
        tile[0]++;
        end = check(tile);
    }

    endMessage(tile, end);
}

void preset3(){
    int s,
        x = 0, o = 0, d = 0;

    printf ("You have selected Developer mode. Enjoy. \n\n");
    printf ("Enter sample size --> ");
    scanf ("%d", &s);

    for (int loop = 0; loop < s; loop++){
        switch (simulate(loop)){
            case (0):
                o++;
                break;
            case (1):
                x++;
                break;
            case (2):
                d++;
                break;
        }
    }

    printf ("\n===Statistics=== \n");
    printf ("X wins \t= %d (%.3lf %%)\n", x, ((double) x / s) * 100);
    printf ("O wins \t= %d (%.3lf %%)\n", o, ((double) o / s) * 100);
    printf ("Draws \t= %d (%.3lf %%)\n\n", d, ((double) d / s) * 100);

    preset3();
}

void preset4(){
    printf ("Under Construction... Wait for future updates. \n");
}

void main(){
    switch (welcome()){
        case (1):
            preset1();
            break;
        case (2):
            preset2(0);
            break;
        case (3):
            preset2(1);
            break;
        case (4):
            preset2(2);
            break;
        case (50):
            preset3();
            break;
    }
}
