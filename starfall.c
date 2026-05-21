#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 70
#define HEIGHT 20

int main() {
    srand(time(NULL));
    
    // Поле: 0 — пусто, 1 — звезда
    int stars[HEIGHT][WIDTH] = {0};
    
    for (int frame = 0; frame < 500; frame++) {
        // Очищаем экран
        printf("\033[H\033[J");
        
        // Сдвигаем все звёзды вниз
        for (int i = HEIGHT - 1; i > 0; i--) {
            for (int j = 0; j < WIDTH; j++) {
                stars[i][j] = stars[i-1][j];
            }
        }
        // Очищаем верхнюю строку
        for (int j = 0; j < WIDTH; j++) {
            stars[0][j] = 0;
        }
        
        // Добавляем новые звёзды сверху (5-15% шанс в каждой позиции)
        for (int j = 0; j < WIDTH; j++) {
            if (rand() % 100 < 10) {
                stars[0][j] = 1;
            }
        }
        
        // Рисуем поле
        printf("ЗВЕЗДОПАД (кадр %d)\n", frame);
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                printf("%s", stars[i][j] ? "*" : " ");
            }
            printf("\n");
        }
        printf("Нажми Ctrl+C для выхода");
        
        usleep(50000);
    }
    
    return 0;
}