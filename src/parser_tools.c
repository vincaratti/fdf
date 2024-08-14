#include "parser.h"

int	arr_len(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);
}

int	d_arr_len(char ***data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	return (i);	
}

void	free_2d_arr(char ***arr)
{
	int counter;

	counter = 0;
	while (arr[counter])
		free(arr[counter++]);
}

void	free_n_data(t_node ***data, int n)
{
	int	i;

	while (--n >= 0)
	{
		i = 0;
		while (data[n][i])
			free(data[n][i++]);
		free(data[n]);
	}
	free(data);
}

void	free_data(t_node ****data)
{
	int	i;
	int	j;

	i = 0;
	while ((*data)[i])
	{
		j = 0;
		while ((*data)[i][j])
			free((*data)[i][j++]);
		free((*data)[i++]);
	}
	free(*data);
}
