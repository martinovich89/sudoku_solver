#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define GRID_WIDTH 9
#define GRID_HEIGHT 9

int	grid[GRID_HEIGHT][GRID_WIDTH] = 
{
	{5, 3, 0, 0, 7, 0, 0, 0, 0},
	{6, 0, 0, 1, 9, 5, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 6, 0},
	{8, 0, 0, 0, 6, 0, 0, 0, 3},
	{4, 0, 0, 8, 0, 3, 0, 0, 1},
	{7, 0, 0, 0, 2, 0, 0, 0, 6},
	{0, 6, 0, 0, 0, 0, 2, 8, 0},
	{0, 0, 0, 4, 1, 9, 0, 0, 5},
	{0, 0, 0, 0, 8, 0, 0, 7, 9}
};

void print_grid()
{
	size_t i;
	size_t j;

	i = 0;
	while (i < GRID_HEIGHT)
	{
		j = 0;
		while (j < GRID_WIDTH)
		{
			printf("%i ", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	next_blank(int *i, int *j)
{	
	while (*i < GRID_HEIGHT)
	{
		*j = 0;
		while (*j < GRID_WIDTH)
		{
			if (grid[*i][*j] == 0)
				return (0);
			(*j)++;
		}
		(*i)++;
	}
	return (1);
}


int is_valid_square(size_t x, size_t y)
{
	size_t i;
	size_t j;
	size_t imax;
	size_t jmax;

	i = y - y % 3;
	j = x - x % 3;
	imax = i + 3;
	jmax = j + 3;
	while (i < imax)
	{
		j = x - x % 3;
		while (j < jmax)
		{
			if (!(i == y && j == x) && grid[i][j] == grid[y][x])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_digit(size_t x, size_t y)
{
	size_t i;
	size_t j;

	i = 0;
	j = x;
	if (grid[y][x] > 9 || grid[y][x] < 1)
		return (0);
	while (i < GRID_HEIGHT)
	{
		if (i != y && grid[i][j] == grid[y][x])
			return (0);
		i++;
	}
	i = y;
	j = 0;
	while (j < GRID_WIDTH)
	{
		if (j != x &&grid[i][j] == grid[y][x])
			return (0);
		j++;
	}
	if (!is_valid_square(x, y))
		return (0);
	return (1);
}

int	next_valid_digit(int i, int j)
{
	grid[i][j]++;
	while (grid[i][j] < 9 && !is_valid_digit(j, i))
		grid[i][j]++;
	if (is_valid_digit(j, i))
		return (1);
	grid[i][j] = 0;
	return (0);
}

int solve_sudoku(int i, int j)
{
	if (i >= 8 && j >= 8)
		return (1);
	if (next_blank(&i, &j) == 1)
		return (1);
	while (next_valid_digit(i, j) != 0)
	{
		if (j == 8 && solve_sudoku(i + 1, 0))
				return (1);
		else if (solve_sudoku(i, j + 1))
				return (1);
	}
	return (0);
}

int main(void)
{
	print_grid();
	printf("----------\n");


	if (solve_sudoku(0, 0) == 1)

	printf("success\n");

	print_grid();

	return (0);
}
