#include <stdlib.h>
#include <unistd.h>

void sorted(char *s){
	char tmp;
	for(int i = 0;s[i];i++){
		for(int j = i+1;s[j];j++){
			if(s[i] > s[j]){
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void perm(char *s, char *result, int *used, int dep, int n){
	if(dep == n){
		for(int i =0; i<n; i++){
			write(1, &result[i], 1);
		}
		write(1, "\n", 1);
		return;
	}
	for(int i = 0; i < n; i++){
		if(used[i])
			continue;
		used[i] = 1;
		result[dep] = s[i];
		perm(s, result, used, dep + 1, n);
		used[i] = 0;
	}
}

int main(int ac, char **av){
	if(ac!=2)
		return 1;
	int i = 0;
	while(av[1][i])
		i++;
	int len = i;
	char *result = malloc(len+1);
	int *used = calloc(len, sizeof(int));
	sorted(av[1]);
	perm(av[1], result, used, 0, len);
	free(result);
	free(used);
}
