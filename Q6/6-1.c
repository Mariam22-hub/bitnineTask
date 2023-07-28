#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIMIT 100000

char* convertToSmall (char word[MAX_LIMIT]){
    for (int i = 0; i< strlen(word); i++){
        word[i] = tolower(word[i]);
    }

    return word;
}

bool isPalindrome(char *string){
    
    int pointer1 = 0, pointer2 = strlen(string)-1;

    while (pointer1 < pointer2){
        if (string[pointer1] != string[pointer2]){
            return false;
        }
        pointer1++;
        pointer2--;
    }

    return true;
}

void reverseString(char* string){

    char reverse[strlen(string)];

    for (int i = 0; i<strlen(string); i++){
        reverse[i] = string[strlen(string) - i - 1];
    }

    printf("%s\n", reverse);
}

int main(){
    char word[MAX_LIMIT];

    scanf("%s", word);

    char *string = convertToSmall(word);

    bool flagPalindrome = isPalindrome(string);

    if (flagPalindrome){
        printf("%s%s",string, " is a palindrome");
    }
    else {
        reverseString(string);
    }

    return 0;
}