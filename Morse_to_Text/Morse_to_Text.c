#include <stdio.h>
#include <string.h>

void get_word(char *word, const char *str,const char *morse_simvol_str[], const char *simvol_str, size_t morse_str_size, size_t size_word)
{
    const char *ptr_str = str;
    size_t temp_simvol_size;
    for(int i = 0; (size_t)i < size_word; ++i)
    {
        if(i > 0){
            ptr_str = strchr(ptr_str, ' ');
            ptr_str++;
        }
        
        for(int j = 0; (size_t)j < morse_str_size; ++j)
        {
            temp_simvol_size = strlen(morse_simvol_str[j]);
            if(strncmp(ptr_str, morse_simvol_str[j], temp_simvol_size) == 0 && (*(ptr_str + temp_simvol_size) == ' ' || *(ptr_str + temp_simvol_size) == '\0'))
            {
                word[i] = simvol_str[j];
                break;
            }
        }
    }
    word[size_word] = '\0';
}

int main(void)
{
    char str[100] = {0};
    fgets(str, sizeof(str)-1, stdin);
    char* ptr_n = strrchr(str, '\n');
    if(ptr_n != NULL)
        *ptr_n = '\0';
    
    int size_arr = 0;
    char *ptr_str = str;
    while(*ptr_str != '\0')
        if(*ptr_str++ == ' ')
            size_arr++;
    char word[size_arr + 1];
    //printf("%d", size_arr);
    char simvol_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    const char *morse_simvol_str[] = {".-",
    "-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",
    ".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--",
    "-..-","-.--",".----","-----",".----","..---","...--","....-",".....",
    "-....","--...","---..","----.","-...-"};
    
    get_word(word, str, morse_simvol_str, simvol_str, sizeof(morse_simvol_str) / sizeof(*morse_simvol_str), sizeof(word) / sizeof(*word));
    //printf("%d", &str[5] - &str[0]);
    puts("----translation----");
    puts(word);
    
    

    return 0;
}