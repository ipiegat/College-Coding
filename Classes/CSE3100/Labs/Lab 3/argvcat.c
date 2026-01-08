#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO 
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int total_len = s1_len + s2_len;

    char *new_string = malloc(total_len+1);

    strcpy(new_string, s1);
    strcat(new_string, s2);
    
    
    if (new_string == NULL) {
        my_error("malloc");
    }
    return new_string;
}

int main(int argc, char *argv[])
{
    char    *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        char* old_s = s;
        s = my_strcat(s, argv[i]);
        free(old_s);
    }

    printf("%s\n", s);
    free(s);
    return 0;
}