
#include "parser.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	str_arr_len(char **str_arr)
{
	int	counter;

	counter = 0;
	while (str_arr[counter])
		counter++;
	return (counter);
}

int	map_free_str_e_ret(char **arr, int counter, int length, int error)
{
	while (counter < length)
	{
		free(arr[counter]);
		counter++;
	}
	free(arr);
	return (error);
}

int	map_free_e_ret(char **arr, int error)
{
	int	counter;

	counter = 0;
	while (arr[counter])
	{
		free(arr[counter]);
		counter++;
	}
	return (error);
}

void	free_i_str(int *ints, char *line)
{
	free(ints);
	free(line);
}
