/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:49:07 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/12 12:53:28 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_i_str(int *ints, char *line)
{
	free(ints);
	free(line);
}
/*
int	verify_lens(char *filename)
{
	int		fd;
	int		wc[2];
	int		*ints[2];
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 1);
	if (str_map_atoi(line, &ints[0], &(wc[0])))
		return (free(line), close(fd), 1);
	while (line)
	{
		if (str_map_atoi(line, &ints[1], &(wc[1])))
			return (free_i_str(ints[0], line), close(fd), 1);
		if (wc[0] != wc[1])
			return (free_i_str(ints[1], line), close(fd), free(ints[0]), 1);
		wc[0] = wc[1];
		free_i_str(ints[1], line);
		line = get_next_line(fd);
	}
	return (close(fd), free(ints[0]), 0);
}

int	get_dimensions(char *filename, t_scaler *s)
{
	int		fd;
	char	*line;
	int		*first_ints;
	int		wc;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 1);
	if (str_map_atoi(line, &first_ints, &wc))
		return (free(line), close(fd), 1);
	s->width = wc;
	s->height = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		s->height++;
	}
	return (free(first_ints), close(fd), 0);
}
i*/

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

int	malloc_data_line(t_node **d_ptr, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		d_ptr[j] = (t_node *)malloc(sizeof(t_node));
		if (!d_ptr)
		{
			while (--j >= 0)
				free(d_ptr[j]);
			return (free(d_ptr), 1);
		}
		j++;
	}
	return (0);
}

int	malloc_data(t_node ****data, t_scaler *s)
{	
	int	i;

	*data = (t_node ***)malloc(sizeof(t_node **) * (s->height + 1));
	if (!data)
		return (1);
	(*data)[s->height] = 0;
	i = 0;
	while (i < s->height)
	{
		(*data)[i] = malloc(sizeof(t_node *) * (s->width + 1)); ///	gonna have to turn this shit into pointers
		if (!(*data)[i])
			return (free_n_data(*data, i), 1);
		(*data)[i][s->width] = NULL;
		if (malloc_data_line((*data)[i], s->width))
			return (free_n_data(*data, i), 1);
		i++;
	}
	return (0);
}

int	get_colour(t_node *n_data, char **s_data)
{
	char	**ret;
	char	**hex_colour;	

	ret = ft_split(*s_data, ',');
	if (!ret)
		return (1);
	free(*s_data);
	*s_data = ret[0];
	hex_colour = ft_split(ret[1], 'x');
	if (!hex_colour)
		return (free(ret[1]), 1);
	free(ret[1]);
	free(hex_colour[0]);
	n_data->colour = ft_atoi_base(hex_colour[1],"0123456789ABCDEF");
	free(hex_colour[1]);
	return (0);
}

int	extract_colour(t_node ****data, char ***data_str)
{
	int		i;
	int		j;

	i = 0;
	while (data_str[i])
	{
		j = 0;
		while (data_str[i][j])
		{
			if (ft_strchr(data_str[i][j], ','))
			{
				if (get_colour((*data)[i][j], &((data_str[i])[j])))
					return (1);
			}
			else
				(*data)[i][j]->colour = 0xFFFFFF;
			//printf("color: %X\n", (*data)[i][j]->colour);
			j++;
		}
		i++;
	}
	return (0);
}

int parser(char *filename, t_scaler *s, t_node ****data)
{
	int		counter;
	char	***data_str;

	data_str = read_file(filename);
	if (!data_str)
		return (printf("1"),fflush(stdout),-1);
	s->height = d_arr_len(data_str);
	s->width = arr_len(data_str[0]);
	//*data = (t_node **)malloc(sizeof(t_node *) * (s->height + 1));
	//(*data)[s->height] = 0;
	if (malloc_data(data, s))
		return (printf("2"),fflush(stdout),free_n(data_str, d_arr_len(data_str)), 1);
	if (extract_colour(data, data_str))
		return (free_n(data_str, d_arr_len(data_str)), 1);
	counter = 0;
	while (counter < s->height)
	{
		if (str_map_atoi(data_str[counter], &((*data)[counter]), s->width))
			return (printf("3"),fflush(stdout),free_data(data), free_n(data_str, d_arr_len(data_str)), 1);//bumnch to free
		counter++;
	}

	int i = 0; int j = 0;
	while ((*data)[i]){ j = 0;while((*data)[i][j]){printf("%X\t", (*data)[i][j]->colour); j++;} printf("\n");i++;}
	
	(*data)[counter] = 0;
	return (free(data_str),  0);
}
