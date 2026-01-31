#include <stdio.h>

#define SIZE    4

void transpose(short *arr)
{ 
    int count = 0;
    for(int i = count; i < SIZE; ++i){
        for(int j = count; j < SIZE; ++j){
            short temp = arr[i * SIZE + j];
            arr[i * SIZE + j] = arr[j * SIZE + i];
            arr[j * SIZE + i] = temp;
        }
        count++;
    }
    
}

int main(void)
{
    short matrix[SIZE][SIZE] = {0};
    short* ptr = &matrix[0][0];
    int count = 0;
    while(count < SIZE * SIZE && scanf("%hd", ptr) == 1) {
        ptr++;
        count++;
    }
    transpose((short *)matrix);
    puts("----Transpose----");
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            printf(j + 1 >= SIZE ? "%d\n" : "%d ", matrix[i][j]);
        }
    }
    
    return 0;

}