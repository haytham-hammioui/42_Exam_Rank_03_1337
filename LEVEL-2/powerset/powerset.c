#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void	recherche(int *nums, int size, int target, int *subset, int index, int sub_size, int curr_sum)
{
    if (index == size)
    {
        if (curr_sum == target){
			for (int i = 0; i < sub_size; i++){
				printf("%d", subset[i]);
        		if (i != sub_size - 1)
					printf(" ");
    		}
    		printf("\n");
		}
        return;
    }
    recherche(nums, size, target, subset, index + 1, sub_size, curr_sum);
    subset[sub_size] = nums[index];
    recherche(nums, size, target, subset, index + 1, sub_size + 1, curr_sum + nums[index]);
}
int main(int ac, char **av){
	if(ac < 3)
		return 1;
	int target = atoi(av[1]);
	int *nums = malloc(sizeof(int) * (ac - 2));
	for(int i = 0;i < (ac-2); i++){
		nums[i] = atoi(av[i+2]);
	}
	int subset[(ac-2)];
	recherche(nums, (ac-2), target, subset, 0, 0, 0);
	free(nums);
	return 0;
}
