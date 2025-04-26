#include <unistd.h>
#include <stdlib.h>

int is_safe(int *positions, int current_col, int current_row){
    for (int prev_col = 0; prev_col < current_col; prev_col++)
    {
        int prev_row = positions[prev_col];

        if (prev_row == current_row ||
            prev_row - prev_col == current_row - current_col ||
            prev_row + prev_col == current_row + current_col)
            return 0;
    }
    return 1;
}

void solve(int *positions, int col, int n){
    if (col == n){
        char buffer[12];
        for (int i = 0; i < n; i++)
        {
            if (i > 0)
                write(1, " ", 1);
            int len = 0;
            int num = positions[i];
            if (num == 0)
                buffer[len++] = '0';
            while (num > 0)
            {
                buffer[len++] = (num % 10) + '0';
                num /= 10;
            }
            while (len--)
                write(1, &buffer[len], 1);
        }
        write(1, "\n", 1);
        return;
    }
    for(int row = 0; row < n; row++){
        if(is_safe(positions, col, row))
        {
            positions[col] = row;
            solve(positions, col + 1, n);
        }
    }
}

int main(int ac, char **av){
	if(ac == 2 && av[1][0] != '-'){
		int n = atoi(av[1]);
		int *positions = malloc(sizeof(int) * n);
        if (!positions)
            return 1;
        solve(positions, 0, n);
        free(positions);
    }
    return 0;
}