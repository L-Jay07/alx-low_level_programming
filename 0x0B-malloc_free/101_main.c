#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_str - Splits a string into words
 * @str: The string to split
 *
 * Return: Pointer to an array of strings (words)
 */
char **split_str(char *str)
{
    if (str == NULL || *str == '\0')
        return NULL;

    int i, j, word_count = 0;
    char **words = NULL;
    int len = strlen(str);

    // Count the number of words
    for (i = 0; i < len; ++i)
    {
        if (str[i] != ' ')
        {
            word_count++;
            while (str[i] != ' ' && str[i] != '\0')
                i++;
        }
    }

    // Allocate memory for words array
    words = (char **)malloc((word_count + 1) * sizeof(char *));
    if (words == NULL)
        return NULL;

    words[word_count] = NULL;

    // Split the string into words
    i = 0;
    for (j = 0; j < word_count; ++j)
    {
        while (str[i] == ' ')
            i++;

        int word_len = 0;
        while (str[i] != ' ' && str[i] != '\0')
        {
            word_len++;
            i++;
        }

        words[j] = (char *)malloc((word_len + 1) * sizeof(char));
        if (words[j] == NULL)
        {
            // Free previously allocated memory on failure
            for (int k = 0; k < j; ++k)
                free(words[k]);
            free(words);
            return NULL;
        }

        strncpy(words[j], str + i - word_len, word_len);
        words[j][word_len] = '\0';
    }

    return words;
}

/**
 * print_tab - Prints an array of strings
 * @tab: The array to print
 *
 * Return: nothing
 */
void print_tab(char **tab)
{
    int i;

    for (i = 0; tab[i] != NULL; ++i)
    {
        printf("%s\n", tab[i]);
    }
}

int main(void)
{
    char **tab;

    tab = split_str("      ALX School         #cisfun      ");
    if (tab == NULL)
    {
        printf("Failed\n");
        return (1);
    }
    print_tab(tab);

    // Free the allocated memory
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);

    return (0);
}
}
