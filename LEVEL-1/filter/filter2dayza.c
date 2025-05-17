#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main(int ac , char **av)
{
    if(ac != 2)
    {
        printf("error: usage: %s <word>\n", av[0]);
        return 1;
    }
    char *word = av[1];
    int lenth_word = strlen(word);
    char *input = malloc(1);
    if (!input)
    {
        perror("initial malloc failed");
        return 1;
    }
    int buffer_size = 1024;
    char *buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer)
    {
        perror("buffer malloc failed");
        free(input);
        return 1;
    }
    int bytes;
    int size_total = 0;
    while((bytes = read(0, buffer, buffer_size)) > 0)
    {
        char *tmp = realloc(input, size_total + bytes + 1);
        if(!tmp)
        {
            perror("error of allocation");
            free(input);
            free(buffer);
            return 1;
        }
        input = tmp;
        int i = 0;
        while (i < bytes)
        {
            input[size_total + i] = buffer[i];
            i++;
        }

        size_total += bytes;
        input[size_total] = '\0';
    }
    free(buffer);

    if(lenth_word == 0)
    {
        printf("error: Empty word\n");
        free(input);
        return 1;
    }

    char *p = input;
    while(*p)
    {
        if(ft_strncmp(p, word, lenth_word) == 0)
        {
            int i = 0;
            while(i < lenth_word)
            {
                p[i] = '*';
                i++;
            }
            p += lenth_word;
        }
        else 
        {
            p++;
        }
    }
    printf("%s", input);
    free(input);
    return 0;
}
