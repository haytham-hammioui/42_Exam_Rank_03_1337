#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// compute the distance between two points
float	distance(float a[2], float b[2])
{
	return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}
// Global variables for backtracking
static bool *visited;
static float shortest_length;
static ssize_t size_g;
static float (*cities)[2];

// Backtracking helper function
void backtrack(int current, int count, float current_length)
{
	// If we've visited all cities
	if (count == size_g) 
	{
		// Add distance back to starting city
		float total = current_length + distance(cities[current], cities[0]);
		if (total < shortest_length)
			shortest_length = total;
		return;
	}

    // Try all unvisited cities
    for (int i = 0; i < size_g; i++) 
	{
        if (!visited[i]) 
		{
            // Mark as visited
            visited[i] = true;
            
            // Calculate new distance and explore this path
            float new_length = current_length + distance(cities[current], cities[i]);
            backtrack(i, count + 1, new_length);
            
            // Backtrack - unmark as visited
            visited[i] = false;
        }
    }
}

float tsp(float (*array)[2], ssize_t size)
{
    // Initialize global variables
    shortest_length = INFINITY;
    size_g = size;
    cities = array;
    visited = calloc(size, sizeof(bool));
    
    // Start from first city
    visited[0] = true;
    backtrack(0, 1, 0.0);
    
    float result = shortest_length;
    free(visited);
    return result;
}
ssize_t	file_size(FILE *file)
{
	char	*buffer = NULL;
	size_t	n = 0;
	ssize_t ret;

	errno = 0;

	for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

	free(buffer);
	if (errno || fseek(file, 0, SEEK_SET))
		return -1;
	return ret;
}

int		retrieve_file(float (*array)[2], FILE *file)
{
	int tmp;
	for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
		if (tmp != 2)
		{
			errno = EINVAL;
			return -1;
		}
	if (ferror(file))
		return -1;
	return 0;
}

int		main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
	if (ac > 1)
    {
		filename = av[1];
		file = fopen(filename, "r");
    }

	if (!file)
	{
		fprintf(stderr, "Error opening %s: %m\n", filename);
		return 1;
	}

	ssize_t size = file_size(file);
	if (size == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", filename);
		fclose(file);
		return 1;
	}

	float (*array)[2] = calloc(size, sizeof (float [2]));
	if (!array)
	{
		fprintf(stderr, "Error: %m\n");
		fclose(file);
		return 1;
	}

	if (retrieve_file(array, file) == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", av[1]);
		fclose(file);
		free(array);
		return 1;
	}
    if (ac > 1)
	    fclose(file);

	printf("%.2f\n", tsp(array, size));
	free(array);
}