#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
//#include <future>
//#include <unistd.h>
using namespace std;

#define row 20
#define col 10


// row 20 col 10

int i, j, k, m;
char boardrc[row][col];

class board {
    public:
        board() {
            for (i = 0; i < row; i++) {
                for (j = 0; j < col; j++) {
                    boardrc[i][j] = '.';
                }
            }
        }
        void printBoard() {
            for (j = 0; j < col; j++) {
                printf("--");
            }
            printf("\n");
            for (i = 0; i < row; i++) {
                for (j = 0; j < col; j++) {
                    printf("%c ", boardrc[i][j]);
                }
                printf("\n");
            }
            for (j = 0; j < col; j++) {
                printf("--");
            }
            printf("\n");
            
        }
};

// COMPLETE!!!!!
class cube {
    public:
        int x1, x2, y1, y2;
        void spawn() {
            boardrc[0][4] = 'o';
            boardrc[0][5] = 'o';
            boardrc[1][4] = 'o';
            boardrc[1][5] = 'o';
            x1 = 4;
            x2 = 5;
            y1 = 0;
            y2 = 1;
        }
        int down() {
            if (boardrc[y2+1][x1] == 'o' || boardrc[y2+1][x2] == 'o' || y2 == row-1) {
                return 1;
            }
            boardrc[y1][x1] = '.';
            boardrc[y1][x2] = '.';
            y1++;
            y2++;
            boardrc[y2][x1] = 'o';
            boardrc[y2][x2] = 'o';
            return 0;
        }
        void left() {
            if (x1 && boardrc[y1][x1-1] != 'o' && boardrc[y2][x1-1] != 'o') {
                boardrc[y1][x2] = '.';
                boardrc[y2][x2] = '.';
                x1--;
                x2--;
                boardrc[y1][x1] = 'o';
                boardrc[y2][x1] = 'o';
            }
        }
        void right() {
            if (x2 != col-1 && boardrc[y1][x2+1] != 'o' && boardrc[y2][x2+1] != 'o') {
                boardrc[y1][x1] = '.';
                boardrc[y2][x1] = '.';
                x1++;
                x2++;
                boardrc[y1][x2] = 'o';
                boardrc[y2][x2] = 'o';
            }
        }
};



// COMPLETE!!!!!
class line {
    public:
        int x1, x2, x3, x4, y1, y2, y3, y4, config;
        void spawn() {
            boardrc[0][3] = 'o';
            boardrc[0][4] = 'o';
            boardrc[0][5] = 'o';
            boardrc[0][6] = 'o';
            x1 = 3;
            x2 = 4;
            x3 = 5;
            x4 = 6;
            y1 = 0;
            y2 = 0;
            y3 = 0;
            y4 = 0;
            config = 0;
        }

        int down() {
            if (!config) {
                if (boardrc[y1+1][x1] == 'o' || boardrc[y2+1][x2] == 'o' || boardrc[y3+1][x3] == 'o' || boardrc[y4+1][x4] == 'o' || y1 == row-1) {
                    return 1;
                }
                boardrc[y1][x1] = '.';
                boardrc[y2][x2] = '.';
                boardrc[y3][x3] = '.';
                boardrc[y4][x4] = '.';
                y1++;
                y2++;
                y3++;
                y4++;
                boardrc[y1][x1] = 'o';
                boardrc[y2][x2] = 'o';
                boardrc[y3][x3] = 'o';
                boardrc[y4][x4] = 'o';
                return 0;
            } else {
                if (boardrc[y4+1][x4] == 'o' || y4 == row-1) {
                    return 1;
                }
                boardrc[y1][x1] = '.';
                y1++;
                y2++;
                y3++;
                y4++;
                boardrc[y4][x4] = 'o';
                return 0;
            }
        }
        void left() {
            if (!config && (boardrc[y1][x1-1] != 'o' && x1)) {
                boardrc[y4][x4] = '.';
                x1--;
                x2--;
                x3--;
                x4--;
                boardrc[y1][x1] = 'o';
            } else if (boardrc[y1][x1-1] != 'o' && boardrc[y2][x2-1] != 'o' && boardrc[y3][x3-1] != 'o' && boardrc[y4][x4-1] != 'o' && x1){
                boardrc[y1][x1] = '.';
                boardrc[y2][x2] = '.';
                boardrc[y3][x3] = '.';
                boardrc[y4][x4] = '.';
                x1--;
                x2--;
                x3--;
                x4--;
                boardrc[y1][x1] = 'o';
                boardrc[y2][x2] = 'o';
                boardrc[y3][x3] = 'o';
                boardrc[y4][x4] = 'o';
            }
        }
        void right() {
            if (!config && (boardrc[y4][x4+1] != 'o' && x4 != col-1)) {
                boardrc[y1][x1] = '.';
                x1++;
                x2++;
                x3++;
                x4++;
                boardrc[y4][x4] = 'o';
            } else if (config == 1 && boardrc[y1][x1+1] != 'o' && boardrc[y2][x2+1] != 'o' && boardrc[y3][x3+1] != 'o' && boardrc[y4][x4+1] != 'o' && x1 != col-1){
                boardrc[y1][x1] = '.';
                boardrc[y2][x2] = '.';
                boardrc[y3][x3] = '.';
                boardrc[y4][x4] = '.';
                x1++;
                x2++;
                x3++;
                x4++;
                boardrc[y1][x1] = 'o';
                boardrc[y2][x2] = 'o';
                boardrc[y3][x3] = 'o';
                boardrc[y4][x4] = 'o';
            }
        }

        void rotate() {
            if (!config && boardrc[y1-1][x1+1] == '.' && boardrc[y3+1][x3-1] == '.' && boardrc[y4+2][x4-2] == '.') {
                boardrc[y1][x1] = '.';
                boardrc[y3][x3] = '.';
                boardrc[y4][x4] = '.';
                x1++;
                y1--;
                x3--;
                y3++;
                x4 -= 2;
                y4 += 2;
                boardrc[y1][x1] = 'o';
                boardrc[y3][x3] = 'o';
                boardrc[y4][x4] = 'o';
                config = 1;
            } else if (boardrc[y1+1][x1-1] == '.' && boardrc[y3-1][x3+1] == '.' && boardrc[y4-2][x4+2] == '.') {
                boardrc[y1][x1] = '.';
                boardrc[y3][x3] = '.';
                boardrc[y4][x4] = '.';
                x1--;
                y1++;
                x3++;
                y3--;
                x4 += 2;
                y4 -= 2;
                boardrc[y1][x1] = 'o';
                boardrc[y3][x3] = 'o';
                boardrc[y4][x4] = 'o';
                config = 0;
            }
        }
};




class tee {
    public:
    int x1, x2, x3, y1, y2, y3, config;
        void spawn() {
            boardrc[0][4] = 'o';
            boardrc[1][3] = 'o';
            boardrc[1][4] = 'o';
            boardrc[1][5] = 'o';
            x1 = 3;
            x2 = 4;
            x3 = 5;
            y1 = 0;
            y2 = 1;
            y3 = 2;
            config = 0;
        }
        int down() {
            if (!config) {
                if (boardrc[y3][x1] == 'o' || boardrc[y3][x2] == 'o' || boardrc[y3][x3] == 'o' || y2 == row-1) {
                    return 1;
                }
                boardrc[y1][x2] = '.';
                boardrc[y2][x1] = '.';
                boardrc[y2][x3] = '.';
                y1++;
                y2++;
                y3++;
                boardrc[y1][x2] = 'o';
                boardrc[y2][x1] = 'o';
                boardrc[y2][x2] = 'o';
                boardrc[y2][x3] = 'o';
                return 0;
            } else if (config == 1) {
                if (boardrc[y3+1][x2] == 'o' || boardrc[y3][x3] == 'o' || y3 == row-1) {
                    return 1;
                }
                boardrc[y1][x2] = '.';
                boardrc[y2][x3] = '.';
                y1++;
                y2++;
                y3++;
                boardrc[y3][x2] = 'o';
                boardrc[y2][x3] = 'o';
                return 0;
            } else if (config == 2) {
                // TODO
            } else if (config == 3) {
                
            }
            return 0;
        }
        void rotate() {
            if (!config) {
                boardrc[y2][x1] = '.';
                boardrc[y3][x2] = 'o';
                config = 1;
            } else if (config == 1) {
                boardrc[y1][x2] = '.';
                boardrc[y2][x1] = 'o';
                config = 2;
            } else if (config == 2) {
                boardrc[y2][x3] = '.';
                boardrc[y1][x2] = 'o';
                config = 3;
            } else {
                boardrc[y3][x2] = '.';
                boardrc[y2][x3] = 'o';
                config = 0;
            }
        }
};



int main() {
    int running = 1, num, endTurn, count;
    bool condition;
    char shape, ch;
    srand(time(NULL));
    board tetb;
    cube c;
    line l;
    tee t;


    /*

    do:
        select random int that corresponds to selected shape
        create the object
        do:
            selection process for arrow keys
            if else statements for shape and movement
        while the shape is not at the ground
    while game is running

    */

    // TODO use async to concurrently update board with user inputs


    do {

        /*
        num = rand() % 2;
        if (!num) {
            shape = 'c';
            c.spawn();
        } else if (num == 1) {
            shape = 'l';
            l.spawn();
        }
            else if (num == 2) {
            shape = 't';
            t.spawn();
        }
        */


        shape = 't';
        t.spawn();

        cout << shape << endl;


        do {
            tetb.printBoard();
            system("stty raw");
            ch = getchar();
            system("stty cooked");
            if (ch == '\033'){
                getchar();
                ch = getchar();
                switch(ch) { // the real value
                    case 'A':
                        if (shape == 'l' && l.y2 != 0 && l.y2 < row-2 && l.x2 != 0 && l.x2 < col-2) {
                            l.rotate();
                        } else if (shape == 't') {
                            t.rotate();
                        }
                        break;
                    case 'B':
                        // code for arrow down
                        if (shape == 'c') {
                            endTurn = c.down();
                        } else if (shape == 'l') {
                            endTurn = l.down();
                        } else if (shape == 't') {
                            endTurn = t.down();
                        }
                        break;
                    case 'C':
                        // code for arrow right
                        if (shape == 'c') {
                            c.right();
                        } else if (shape == 'l') {
                            l.right();
                        }
                        break;
                    case 'D':
                        // code for arrow left
                        if (shape == 'c') {
                            c.left();
                        } else if (shape == 'l') {
                            l.left();
                        }
                        break;
                    default:
                        ch = ' ';
                }

            } else if (ch == 'q') {
                running = 0;
            } else {
                system("stty cooked");
                cout << "invalid input\n";
            }
            cout << ch << endl;
        } while (running && !endTurn);

        if (boardrc[0][4] == 'o') {
            running = 0;
        }

        for (i = row-1; i > 0; i--) {
            count = 0;
            for (j = 0; j < col; j++) {
                if (boardrc[i][j] == 'o') {
                    count++;
                }
            }
            if (count == col) {
                for (k = row-1; k > 0; k--) {
                    for (m = 0; m < col; m++) {
                        boardrc[k][m] = boardrc[k-1][m];
                    }
                }
                i++;
            }
        }

    } while (running);

    tetb.printBoard();
    
    //oh my it works?!

    return 0;
}