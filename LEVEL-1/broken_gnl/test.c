#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *ft_strdup(char *line){
	int i = 0;
	while(line[i])
		i++;
	char *ptr = (char *)malloc(i + 1);
	if(!ptr)
		return NULL;
	i = 0;
	while(line[i])
	{
		ptr[i] = line[i];
		i++;
	}
	ptr[i] = '\0';
	return ptr;
}

char    *get_next_line(int fd){
	static char buffer[BUFFER_SIZE];
	static int b_read;
	static int b_pos;
	char line[70000];
	int i = 0;
	if(fd < 0 || BUFFER_SIZE < 1)
		return NULL;
	while(1){
		if(b_pos >= b_read)
		{
			b_read = read(fd, buffer, BUFFER_SIZE);
			b_pos = 0;
			if(b_read <= 0)
				break;
		}
		line[i++] = buffer[b_pos++];
		if(buffer[b_pos - 1] == '\n')
			break;
	}
	line[i] = '\0';
	if(i == 0)
		return NULL;
	return ft_strdup(line);
}

int main(){
	int fd = open("file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("----------------------\n");
	close(fd);
}