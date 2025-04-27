#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int check_dup(char *str){
	for(int i = 0; str[i]; i++){
		for(int j = i+1; str[j]; j++){
			if(str[i] == str[j])
				return 1;
		}
	}
	return 0;
}

int ft_strlen(char *str) {
    int len = 0;
    while (str[len])
        len++;
    return len;
}

void sorted(char *str){
	char tmp;
	for(int i = 0; str[i]; i++){
		for(int j = i+1; str[j]; j++){
			if(str[i] > str[j]){
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
		}
	}
}

void generate(char *str, char *result, int *used, int len, int depth) {
    if (depth == len) {
        write(1, result, len);
        write(1, "\n", 1);
        return;
    }
    for (int i = 0; i < len; i++) {
        if (!used[i]) {
            used[i] = 1;
            result[depth] = str[i];
            generate(str, result, used, len, depth + 1);
            used[i] = 0;
        }
    }
}

int main(int ac, char **av)
{
	if(ac != 2 || check_dup(av[1]))
		return 1;
	int len = ft_strlen(av[1]);
	char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));
	if(!result || !used)
		return 1;
	sorted(av[1]);
    generate(av[1], result, used, len, 0);
    free(result);
    free(used);
	return 0;
}