#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE    5
#define MINES   5

int main(void)
{
    srand(time(NULL));
    char pg[SIZE][SIZE] = {0};
    char mines_count = MINES;
    while(mines_count > 0){
        
    char row = rand() % SIZE, col = rand() % SIZE;
    char top_start = row == 0 ? row : row - 1;
    char down_end = row == (SIZE - 1) ? row : row + 1;
    char lefr_start = col == 0 ? col : col - 1;
    char right_end = col == (SIZE - 1) ? col : col + 1;
    char flags = 0;
    for(int i = top_start; i <= down_end; i++){
        for(int j = lefr_start; j <= right_end; j++){
            if(pg[i][j] == '*'){
                flags = 1;
            }
        }
        
    }
        if((!flags) == 1){
            pg[(int)row][(int)col] = '*';
            mines_count--;
        }
    }
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j)
            printf("%c", pg[i][j] == 0 ? '#' : '*');
        putchar('\n');
    }
    return 0;
}