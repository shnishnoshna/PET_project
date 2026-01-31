#include <stdio.h>
#include <string.h>

void get_morse_code(char *morse_str_out, const char *str, char *simvol_str, const char  *morse_simvol_str[])
{
    const char *ptr_str = str;
    for(int i = 0; ptr_str[i] != '\0'; ++i)
    {
        for(int j = 0; simvol_str[j] != '\0'; ++j)
        {
            if(ptr_str[i] == simvol_str[j] || ptr_str[i] == (simvol_str[j] + 32))
            {
                strcat(morse_str_out, morse_simvol_str[j]);
                if(ptr_str[i + 1] != '\0')
                    strcat(morse_str_out, " ");
                break;
            }
        }
    }
}

int main(void)
{
    char simvol_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    const char *morse_simvol_str[] = {".-",
    "-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",
    ".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--",
    "-..-","-.--",".----","-----",".----","..---","...--","....-",".....",
    "-....","--...","---..","----.","-...-"};
    char str[100] = {0};
    char morse_str[1000];
    morse_str[0] = '\0';
    fgets(str, sizeof(str)-1, stdin);
    char* ptr_n = strrchr(str, '\n');
    if(ptr_n != NULL)
        *ptr_n = '\0';
    
    get_morse_code(morse_str, str, simvol_str, morse_simvol_str);
    puts("----translation----");
    puts(morse_str);
    

    return 0;
}
