/*
For build input:~$ gcc interactive_pong.c -lncurses
 */

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

int main(void) {
    int x, y, dx, dy;
    int paddle1_x, paddle1_y;
    int paddle2_x, paddle2_y;

    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    int player1_score = 0;
    int player2_score = 0;

    x = WIDTH / 2;
    y = HEIGHT / 2;
    dx = 1;
    dy = 1;
    paddle1_x = 3;
    paddle1_y = HEIGHT / 2 - 1;
    paddle2_x = WIDTH - 4;
    paddle2_y = HEIGHT / 2 - 1;

    while (1) {
        x += dx;
        y += dy;
        if (x == 0 || x == WIDTH - 1) {
            dx = -dx;
        }
        if (y == 0 || y == HEIGHT - 1) {
            dy = -dy;
        }

        if ((x == paddle1_x - 1 && y >= paddle1_y && y <= paddle1_y + 5) ||
            (x == paddle2_x - 1 && y >= paddle2_y && y <= paddle2_y + 5))
            dx = -dx;

        char ch = getch();
        switch (ch) {
            case 'a':
                if (paddle1_y > 0) {
                    paddle1_y--;
                }
                break;
            case 'z':
                if (paddle1_y < HEIGHT - 3) {
                    paddle1_y++;
                }
                break;
            case 'k':
                if (paddle2_y > 0) {
                    paddle2_y--;
                }
                break;
            case 'm':
                if (paddle2_y < HEIGHT - 3) {
                    paddle2_y++;
                }
                break;
        }
        if (x <= 0) {
            player2_score++;
            x = WIDTH / 2;
            y = HEIGHT / 2;
            paddle1_y = HEIGHT / 2 - 1;
            paddle2_y = HEIGHT / 2 - 1;
        } else if (x >= WIDTH - 1) {
            player1_score++;
            x = WIDTH / 2;
            y = HEIGHT / 2;
            paddle1_y = HEIGHT / 2 - 1;
            paddle2_y = HEIGHT / 2 - 1;
        }

        if (player1_score == 21) {
            clear();
            mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Player 1 win!");
            refresh();
            break;
        } else if (player2_score == 21) {
            clear();
            mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Player 2 win!");
            refresh();
            break;
        }

        clear();
        mvhline(0, 0, '-', WIDTH);
        mvhline(HEIGHT - 1, 0, '-', WIDTH);
        mvvline(0, 0, '|', HEIGHT);
        mvvline(0, WIDTH / 2, ':', HEIGHT);
        mvvline(0, WIDTH - 1, '|', HEIGHT);
        mvaddch(y, x, 'O');
        mvprintw(1, 2, "Score: Player 1 - %d  Player 2 - %d", player1_score, player2_score);
        mvvline(paddle1_y, paddle1_x, '|', 3);
        mvvline(paddle2_y, paddle2_x, '|', 3);
        refresh();
        usleep(50000);
    }
    endwin();
    return 0;
}
