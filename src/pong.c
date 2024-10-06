#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define BALL 'o'
#define BOARD '|'
#define NET ':'
#define TOPBOT '-'
#define FIELD ' '
#define RACKET '|'
#define racket_left_x 1
#define racket_right_x WIDTH - 1
#define LEFTUP 'a'
#define LEFTDOWN 'z'
#define RIGHTUP 'k'
#define RIGHTDOWN 'm'

void clear(void) { printf("\e[1;1H\e[2J"); }

void drow(int ball_x, int ball_y, int racket_left_y, int racket_right_y, int score_player_left,
          int score_player_right) {
    printf(" Player 1 score - %d                     | Player 2 score - %d\n", score_player_left,
           score_player_right);
    for (int i = 0; i <= HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH) {
                putchar(BOARD);  // left/right board
            } else if (i == 0 || i == HEIGHT) {
                putchar(TOPBOT);                      // top/bottom board
            } else if (i == ball_y && j == ball_x) {  // ball
                putchar(BALL);
            } else if (j == WIDTH / 2) {
                putchar(NET);  // net
            } else if ((i == racket_left_y || i == racket_left_y - 1 || i == racket_left_y + 1) &&
                       j == racket_left_x) {
                putchar(RACKET);
            } else if ((i == racket_right_y ||  i == racket_right_y - 1 ||  i == racket_right_y + 1) &&
                       j == racket_right_x) {
                putchar(RACKET);
            } else {
                putchar(FIELD);  // field
            }
        }
        putchar('\n');
    }
}

int main(void) {
    clear();
    // ball start
    int y_ball = HEIGHT / 2;
    int x_ball = WIDTH / 2 - 1;

    // racket_left start
    int racket_left_y = HEIGHT / 2;

    // racket_right start
    int racket_right_y = HEIGHT / 2;

    // direction ball
    int ball_x_dir = 1;
    int ball_y_dir = 0;

    int racket_left_dir = 1;
    int racket_right_dir = 1;

    int score_player_left = 0;
    int score_player_right = 0;

    char command;

    while (1) {
        if (racket_left_y - 1 == y_ball && racket_left_x + 1 == x_ball) {
            ball_x_dir = -ball_x_dir;
            ball_y_dir = 1;

        } else if (racket_left_y + 1 == y_ball && racket_left_x + 1 == x_ball) {
            ball_x_dir = -ball_x_dir;
            ball_y_dir = -1;

        } else if (racket_right_y == y_ball && racket_right_x - 1 == x_ball + 1) {
            ball_x_dir = -ball_x_dir;

        } else if (racket_left_y == y_ball && racket_left_x + 1 == x_ball) {
            ball_x_dir = -ball_x_dir;

        } else if (racket_right_y - 1 == y_ball && racket_right_x - 1 == x_ball) {
            ball_x_dir = -ball_x_dir;
            ball_y_dir = 1;

        } else if (racket_right_y + 1 == y_ball && racket_right_x - 1 == x_ball) {
            ball_x_dir = -ball_x_dir;
            ball_y_dir = -1;

        } else if (y_ball == HEIGHT - 1) {
            ball_y_dir = 1;

        } else if (y_ball == 1) {
            ball_y_dir = -1;

        } else if (x_ball < 1) {
            score_player_right++;
            x_ball = WIDTH / 2 - 1;
            y_ball = HEIGHT / 2;
            ball_x_dir = 1;
            racket_left_y = HEIGHT / 2;
            racket_right_y = HEIGHT / 2;

        } else if (x_ball >= WIDTH) {
            score_player_left++;
            x_ball = WIDTH / 2 + 1;
            y_ball = HEIGHT / 2;
            ball_x_dir = -1;
            racket_left_y = HEIGHT / 2;
            racket_right_y = HEIGHT / 2;
        }

        drow(x_ball, y_ball, racket_left_y, racket_right_y, score_player_left, score_player_right);
        x_ball -= ball_x_dir;
        y_ball -= ball_y_dir;
        command = getchar();

        if (score_player_left == 21 || score_player_right == 21) {
            break;
        }

        if (command == LEFTUP && racket_left_y > 2) {
            racket_left_y--;

        } else if (command == LEFTDOWN && racket_left_y < HEIGHT - 2) {
            racket_left_y++;

        } else if (command == RIGHTUP && racket_right_y > 2) {
            racket_right_y--;

        } else if (command == RIGHTDOWN && racket_right_y < HEIGHT - 2) {
            racket_right_y++;
        }

        clear();
    }
    printf("%s", (score_player_left == 21) ? "Player 1 won!\n" : "Player 2 won!\n");
    return 0;
}
