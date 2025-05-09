#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac , char **av)
{
    if(ac != 2)
    {
        return 1;
    }
    char *word = av[1];
    int lenth_word = strlen(word);
    char *input = malloc(1);
    int buffer_size = 1024;
    char *buffer = malloc(sizeof(char ) * buffer_size);
    int bytes ;
    int size_total = 0;
    while((bytes = read(0,buffer,buffer_size)) > 0)
    {
        char *tmp = realloc(input, size_total + bytes + 1);
        if(!tmp)
        {
            perror("error of allocation");
            free(input);
            free(buffer);
            return 0;
        }
        input = tmp;
        memmove(input + size_total,buffer ,bytes);
        size_total += bytes;
        input[size_total] = '\0';
    }
    free(buffer);
    if(lenth_word == 0)
    {
        fprintf(stderr,"error : Empty word\n");
        return 1;
    }
    // printf("%s",input);
    char *p = input;
    while(*p)
    {
        if(strncmp(p,word,lenth_word) == 0) // code your strncmp
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
    fprintf(stdout,"%s",input);
    free(input);
    return 0;

}