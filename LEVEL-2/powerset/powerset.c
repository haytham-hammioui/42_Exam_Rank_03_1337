#include <unistd.h>
#include <stdlib.h>

void	ft_putnbr(int n)
{
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    char c = (n % 10) + '0';
    write(1, &c, 1);
}

void	recherche(int *nums, int size, int target, int *subset, int index, int sub_size, int curr_sum)
{
    if (index == size)
    {
        if (curr_sum == target){
			for (int i = 0; i < sub_size; i++){
        		ft_putnbr(subset[i]);
        		if (i != sub_size - 1)
            	write(1, " ", 1);
    		}
    		write(1, "\n", 1);
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
	int subset[ac-2];
	recherche(nums, (ac-2), target, subset, 0, 0, 0);
	free(nums);
	return 0;
}
