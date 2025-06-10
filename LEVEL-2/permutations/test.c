#include <stdlib.h>
#include <unistd.h>

void sorted(char *str){
	char tmp;
	for(int i = 0; str[i]; i++){
		for(int j = i+1; str[j]; j++)
			if(str[i] > str[j]){
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
	}
}

void perm(char *str, char *result, int *used, int dep, int len){
	if(dep ==len){
		for(int i = 0; i< len; i++){
			write(1, &result[i], 1);
		}
		write(1, "\n", 1);
		return ;
	}
	for(int i = 0; i < len; i++){
		if(used[i])
			continue;
		used[i] = 1;
		result[dep] = str[i];
		perm(str, result, used, dep + 1, len);
		used[i] = 0;
	}
}

int main(int ac, char **av){
	if(ac!= 2)
		return 1;
	int i = 0;
	while(av[1][i])
		i++;
	char *result= malloc(i + 1);
	int *used = calloc(i, sizeof(int));
	sorted(av[1]);
	perm(av[1], result, used, 0, i);
	free(result);
	free(used);
}