/**
 * C program to find first occurrence of a word in file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1000


/* Function declarations */
int indexOf(FILE *fptr, const char *word, int *line, int *col);


int main()
{
    FILE *fptr;
    char path[100];

    char word[50];

    int line, col;


    /* Input file path */
    printf("Enter file path: ");
    scanf("%s", path);

    /* Input word to search in file */
    printf("Enter word to search in file: ");
    scanf("%s", word);


    /* Try to open file */
    fptr = fopen(path, "r");

    /* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }


    // Find index of word in fptr
    indexOf(fptr, word, &line, &col);

    if (line != -1)
        printf("'%s' found at line: %d, col: %d\n", word, line + 1, col + 1);
    else
        printf("'%s' does not exists.", word);


    // Close file
    fclose(fptr);

    return 0;
}


/**
 * Finds, first index of a word in given file. First index is represented
 * using line and column.
 */
int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;

    *line = -1;
    *col  = -1;

    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;

        // Find first occurrence of word in str
        pos = strstr(str, word);

        if (pos != NULL)
        {
            // First index of word in str is
            // Memory address of pos - memory
            // address of str.
            *col = (pos - str);
            break;
        }
    }


    // If word is not found then set line to -1
    if (*col == -1)
        *line = -1;

    return *col;
}
