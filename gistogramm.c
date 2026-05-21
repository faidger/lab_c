#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 40
#define MAX_HEIGHT 20

int main() {
    srand(time(NULL));
    int data[SIZE];
    
    // Генерируем 40 случайных чисел от 0 до MAX_HEIGHT
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % (MAX_HEIGHT + 1);
    }
    
    // Рисуем гистограмму
    printf("\n=== ГИСТОГРАММА (40 значений) ===\n\n");
    
    for (int h = MAX_HEIGHT; h > 0; h--) {
        printf("%2d | ", h);
        for (int i = 0; i < SIZE; i++) {
            if (data[i] >= h)
                printf("█");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("   +");
    for (int i = 0; i < SIZE; i++) printf("-");
    printf("\n    ");
    for (int i = 0; i < SIZE; i += 5) printf("%d   ", i);
    printf("\n\n");
    
    // Масштабное вычисление: сумма квадратов всех чисел
    long long sum_sq = 0;
    for (int i = 0; i < SIZE; i++) {
        sum_sq += (long long)data[i] * data[i] * data[i] * data[i];
    }
    printf("Масштабное вычисление: Σ(value^4) = %lld\n", sum_sq);
    
    return 0;
}