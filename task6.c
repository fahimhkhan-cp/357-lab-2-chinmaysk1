#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("No file provided\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    char *last_line = NULL;
    char *second_last_line = NULL;

    while ((nread = getline(&line, &len, file)) != -1)
    {
        if (second_last_line)
        {
            free(second_last_line);
        }
        second_last_line = last_line;
        last_line = strdup(line);
    }

    fclose(file);

    if (second_last_line)
    {
        printf("%s", second_last_line);
    }
    if (last_line)
    {
        printf("%s", last_line);
    }

    free(second_last_line);
    free(last_line);
    free(line);

    return 0;
}
