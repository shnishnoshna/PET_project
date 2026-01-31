#include <stdio.h>

#define SIZE    3

int is_win(char (*arr)[SIZE])
{
    char *ptr = (char *)arr;
    char output_status = -1;
    
        for(int i = 0; i < SIZE; ++i){
            output_status = arr[i][0] == arr[i][1] && arr[i][0] == arr[i][2] ? arr[i][0] : -1;
            if(output_status != -1){
                //printf("%d\n", output_status);
                return (output_status == 'x') ? 1 :(output_status == 'o' ? 2 : 0);
            }
        }
        for(int i = 0; i < SIZE; ++i){
            output_status = arr[0][i] == arr[1][i] && arr[0][i] == arr[2][i] ? arr[0][i] : -1;
            if(output_status != -1){
                //printf("%d\n", output_status);
                return (output_status == 'x') ? 1 : (output_status == 'o' ? 2 : 0);
            }
        }
        //printf("%d\n", output_status);
        if(((arr[1][1] == arr[0][0] && arr[1][1] == arr[SIZE - 1][SIZE - 1]) || (arr[1][1] == arr[0][SIZE - 1] && arr[1][1] == arr[SIZE - 1][0])) && arr[1][1] != 0){
            return arr[1][1] == 'x' ? 1 : (arr[1][1] == 'o' ? 2 : 0);
        }
        
        int count_nul = 0;
        for(int i = 0; i < SIZE * SIZE; ++i){
            if(ptr[i] == 0)
            count_nul++;
        }
        if(count_nul > 0)
            output_status = 0;
        else{
            output_status = 3;
        }
            //printf("%d\n", output_status);
    
    return output_status;
}

int main(void)
{
    char pole[SIZE][SIZE] = {0};
    char* ptr_p = &pole[0][0];
    int count = 0;
    while(count < SIZE * SIZE && scanf("%hhd", ptr_p) == 1) {
        *ptr_p = (*ptr_p == 1) ? 'x' : (*ptr_p == 2) ? 'o': *ptr_p;
        ptr_p++;
        count++;
    }
    puts("----check_game----");
    //is_win(pole);
    printf("%d\n",is_win(pole));

    return 0;
}