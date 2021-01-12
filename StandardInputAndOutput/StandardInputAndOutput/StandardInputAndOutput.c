
#include <stdio.h>
#include <stdbool.h>

void question1(void);
void question4(void);

int main() {
    int choice;
    printf("Enter which problem you would like to solve: ");
    scanf("%d", &choice);
    getchar();
    
    if (choice == 1) {
        question1();
    }
    else if (choice == 4) {
        question4();
    }
    else {
        printf("Please pick 1 or 4 uwu");
    }
    return 0;
}

void question1() {
    char string[1000];
    int count = 0;
    int i;
    
    printf("Please enter your string: ");
    fgets(string, 1000, stdin);
    /*
     the following code is based on the code found at:
     https://www.includehelp.com/c-programs/c-program-to-count-upper-and-lower-case-characters-in-a-string.aspx
     */
    
    for (i = 0; string[i] != NULL; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            count++;
        }
        else {
            continue;
        }
    }
    
    printf ("There are %d uppercase letters in that string.\n", count);
    return;
}

void question4() {
    char firstChar;
    char secondChar;
    
    printf("Please input your first character: ");
    scanf(" %c", &firstChar);
    printf("Please input your second character: ");
    scanf(" %c", &secondChar);
    
    bool xorResult = (firstChar ^ secondChar);
    bool bitDifference = (xorResult && (!(xorResult & (xorResult - 1))));
    
    printf("1 = true and 0 = false. Whether or not the two characters are different by a single bit: %d\n", bitDifference);
    return;
}
