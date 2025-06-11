#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ft_strncmp(char *p, char *word, int n){
	int i =0;
	while(i<n && p[i] && word[i] && p[i] == word[i])
		i++;
	if(i == n)
		return 0;
	return p[i] - word[i];
}

int main(int ac, char **av){
	if(ac != 2)
		return (printf("ERROR args"), 1);
	char *word = av[1];
	int s_word = strlen(word);
	if(s_word == 0)
		return (printf("ERROR empty word"), 1);
	char *input = malloc(1);
	if(!input)
		return (perror("failed allocation input"), 1);
	int buffer_size = 1024;
	char *buffer = malloc(buffer_size);
	if(!buffer)
		return (perror("failed allocation buffer"), free(input), 1);
	int b_read;
	int size_total = 0;
	while((b_read = read(0, buffer, buffer_size)) > 0){
		char *tmp= realloc(input, size_total + b_read + 1);
		if(!tmp)
			return (perror("failed allocation TMP"), free(buffer),free(input), 1);
		input = tmp;
		int i = 0;
		while(i < b_read){
			input[size_total + i] = buffer[i];
			i++;
		}
		size_total += b_read;
		input[size_total] = '\0';
	}
	free(buffer);
	char *ptr = input;
	while(*ptr){
		if((ft_strncmp(ptr, word, s_word)) == 0){
			int i = 0;
			while(i < s_word){
				ptr[i] = '*';
				i++;
			}
			ptr += s_word;
		}
		else
			ptr++;
	}
	printf("%s", input);
	free(input);
	return 0;
}