#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void	print_error(char **dest, char **str, int free1, int free2)
{
	if(free1 == 1)
		free(dest);
	if(free2 == 1)
		free(str);
	perror("Error: ");
	exit(1);
}

char *ft_strjoin(char *s1, char *s2){
	char *join = malloc(strlen(s1) + strlen(s2) + 1);
	if (!join)
		return (NULL);
	char *result = join;
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (result);
}

void ft_check_replace(char **str, char *arg){
	char	*new_str = malloc(strlen(*str) + 1);
	size_t	len = strlen(arg);
	if (!new_str)
	{
		free(*str);
		perror("Error: ");
		exit(1);
	}
	char *src = *str;
	char *dst = new_str;
	while (*src)
	{
		size_t i = 0;
		while (arg[i] && src[i] == arg[i])
			i++;
		if (i == len)
		{
			for (size_t j = 0; j < len; j++)
				*dst++ = '*';
			src += len;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(*str);
	*str = new_str;
}

int main(int ac, char **av){
	if(ac != 2 || av[1][0] == '\0')
		return 1;
	char *str = calloc(1, 1);
	char *dest = malloc((size_t)BUFFER_SIZE + 1);
	if(!dest)
		print_error(&dest, &str, 0, 0);
	ssize_t line_b = 1;
	while(line_b > 0){
		line_b = read(0, dest, BUFFER_SIZE);
		if (line_b == -1)
			print_error(&dest, &str, 1, 1);
		dest[line_b] = '\0';
		char *tmp = ft_strjoin(str, dest);
		if (!tmp)
			print_error(&dest, &str, 1, 1);
		free(str);
		str = tmp;
	}
	free(dest);
	ft_check_replace(&str, av[1]);
	printf("%s", str);
	free(str);
	return (0);
}