#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char    *ft_strdup(const char *str)
{
    char    *copy;
    int        i;

    copy = (char *)malloc(sizeof(char) * strlen(str) + 1);
    if (copy == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0')
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

char    *get_next_line(int fd)
{
    static char    buffer[BUFFER_SIZE];
    char        line[70000];
    static int    b_read;
    static int    b_pos;
    int            i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    while (1337)
    {
        if (b_pos >= b_read)
        {
            b_read = read(fd, buffer, BUFFER_SIZE);
            b_pos = 0;
            if (b_read <= 0)
                break ;
        }
        line[i++] = buffer[b_pos++];
        if (buffer[b_pos - 1] == '\n')
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}