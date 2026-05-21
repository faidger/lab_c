#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 60
#define HEIGHT 20
#define PARTICLES 5

int main() {
    srand(time(NULL));
    
    int x[PARTICLES], y[PARTICLES];
    char symbols[PARTICLES] = {'@', '#', '$', '%', '&'};
    int finished = 0;
    int winner = -1;
    
    // Стартовые позиции
    for (int i = 0; i < PARTICLES; i++) {
        x[i] = 0;
        y[i] = i * 3 + 2;
    }
    
    printf("\n\x1b[36m========== ГОНКА ЧАСТИЦ ==========\x1b[0m\n");
    printf("\x1b[33mПервая частица на финише (правая граница) побеждает!\x1b[0m\n\n");
    sleep(1);
    
    while (!finished) {
        // Очистка экрана
        printf("\033[H\033[J");
        
        // Отрисовка трассы
        printf("\x1b[36m+");
        for (int i = 0; i < WIDTH; i++) printf("-");
        printf("+\x1b[0m\n");
        
        for (int row = 0; row < HEIGHT; row++) {
            printf("\x1b[36m|\x1b[0m");
            for (int col = 0; col < WIDTH; col++) {
                int drawn = 0;
                for (int p = 0; p < PARTICLES; p++) {
                    if (x[p] == col && y[p] == row && !finished) {
                        printf("\x1b[32m%c\x1b[0m", symbols[p]);
                        drawn = 1;
                        break;
                    }
                }
                if (!drawn) {
                    if (col == WIDTH - 1) printf("\x1b[36m|\x1b[0m");
                    else printf(" ");
                }
            }
            printf("\n");
        }
        
        printf("\x1b[36m+");
        for (int i = 0; i < WIDTH; i++) printf("-");
        printf("+\x1b[0m\n");
        
        // Статистика
        printf("\n\x1b[33mПозиции частиц:\x1b[0m\n");
        for (int i = 0; i < PARTICLES; i++) {
            printf("  %c: %d/%d", symbols[i], x[i], WIDTH);
            if (x[i] >= WIDTH - 1) printf(" \x1b[32mФИНИШ!\x1b[0m");
            printf("\n");
        }
        
        // Движение частиц
        for (int i = 0; i < PARTICLES; i++) {
            if (x[i] < WIDTH - 1) {
                // Случайный шаг: -1, 0, 1, 2 (чаще вперёд)
                int step = rand() % 4;
                if (step == 0) step = -1;  // шаг назад (редко)
                if (step == 2) step = 1;   // шаг вперёд (часто)
                if (step == 3) step = 2;   // рывок (редко)
                
                x[i] += step;
                if (x[i] < 0) x[i] = 0;
                if (x[i] >= WIDTH - 1) {
                    x[i] = WIDTH - 1;
                    if (!finished) {
                        finished = 1;
                        winner = i;
                    }
                }
            }
        }
        
        usleep(100000);
    }
    
    // Финиш
    printf("\n\n\x1b[35m╔══════════════════════════════╗\x1b[0m\n");
    printf("\x1b[35m║     🏆  ПОБЕДИТЕЛЬ: %c  🏆     ║\x1b[0m\n", symbols[winner]);
    printf("\x1b[35m╚══════════════════════════════╝\x1b[0m\n\n");
    
    return 0;
}