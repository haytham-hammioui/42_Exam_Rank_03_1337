#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	print_error(void)
{
	perror("Error");
	exit(1);
}
char	*ft_strdup(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	cpy = malloc(sizeof(char) * (strlen(s) + 1));
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	dest = malloc(strlen(s1) + strlen(s2) + 1);
	if (!dest)
		return (NULL);
	result = dest;
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (result);
}

void	ft_check_replace(char **str, char *to_replace)
{
	if (!str || !*str || !to_replace)
		return;
	char	*new_str = malloc(strlen(*str) + 1);
	size_t	len = strlen(to_replace);
	size_t	src_len = strlen(*str);
	if (!new_str)
	{
		free(*str);
		print_error();
	}
	char *src = *str;
	char *dst = new_str;
	while (*src)
	{
		size_t i = 0;
		while (to_replace[i] && src[i] == to_replace[i])
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

int	main(int ac, char **av)
{
	if (ac != 2 || !(av[1][0]))
		return (1);

	char	*dest;
	char	*str = NULL;
	dest = malloc((size_t)BUFFER_SIZE + 1);
	if (!dest)
		print_error();
	ssize_t line_b = 1;
	while (line_b > 0)
	{
		line_b = read(0, dest, BUFFER_SIZE);
		if (line_b == -1)
		{
			free(dest);
			free(str);
			print_error();
		}
		dest[line_b] = '\0';
		char *tmp = ft_strjoin(str, dest);
		if (!tmp)
		{
			free(dest);
			free(str);
			print_error();
		}
		free(str);
		str = tmp;
	}
	free(dest);
	ft_check_replace(&str, av[1]);
	printf("%s", str);
	free(str);
	return (0);
}
