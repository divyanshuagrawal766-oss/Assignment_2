#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// fast screen clear (no flicker)
void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

// sound effects
void bg_tick() { Beep(700, 10); }
void score_beep() { Beep(1200, 80); }
void crash_beep() { Beep(300, 600); }

int main() {

    // enable unicode/emoji
    system("chcp 65001 > nul");
    system("cls");
    system("color 0A");

    srand(time(0));

    int lane = 1;              
    int step = 0;              
    int obsLane = rand() % 3;  
    int score = 0;
    int speed = 140;            // starting speed (lower = faster)

    char *CAR = "🚗";
    char *OBS = "🔥";

    while (1) {

        // KEY INPUT
        if (_kbhit()) {
            char ch = getch();
            if (ch == 75 && lane > 0) lane--;    // LEFT
            if (ch == 77 && lane < 2) lane++;    // RIGHT
        }

        // DRAW GAME UI
        clear_screen_fast();
        printf("====== 🚦 CAR DODGE GAME 🚦 ======\n");
        printf(" SCORE : %d    |   SPEED : %d%%\n", score, (200-speed)*1);
        for (int i = 0; i < 10; i++) {

            if (i == step) {
                if (obsLane == 0)
                    printf("   %s           \n", OBS);
                else if (obsLane == 1)
                    printf("        %s      \n", OBS);
                else
                    printf("              %s\n", OBS);

            } else {
                printf("                \n");
            }
        }

        // PLAYER CAR DRAW
        if (lane == 0)
            printf("   %s           \n", CAR);
        else if (lane == 1)
            printf("        %s      \n", CAR);
        else
            printf("              %s\n", CAR);

        // COLLISION
        if (step == 10 && lane == obsLane) {
            crash_beep();
            clear_screen_fast();
            printf("\n\n💥 GAME OVER 💥\n");
            printf("FINAL SCORE : %d\n\n", score);
            break;
        }

        Sleep(speed);
        bg_tick();
        step++;

        // NEW OBSTACLE
        if (step > 10) {
            step = 0;
            obsLane = rand() % 3;
            score++;
            score_beep();

            // ---------------------------
            // 🔥 AUTO DIFFICULTY CONTROL
            // ---------------------------
            if (speed > 40) {              // minimum limit
                if (score % 3 == 0) {       // every 3 points
                    speed -= 10;            // speed up
                }
            }
        }
    }

    return 0;
}