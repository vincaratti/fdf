/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:09:58 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 09:53:12 by vincenzocarat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		get_file_len(char *filename)
{
	int		len;
	int		read_ret;
	int		fd;
	char	buffer[1000];

	read_ret = 1;
	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (read_ret > 0)
	{
		read_ret = read(fd, buffer, 1000);
		if (read_ret == -1)
			return (close(fd), -1);
		len += read_ret;
	}
	return (close(fd), len);
}

void	free_n(char ***data, int n)
{
	int	i;

	while (n-- > 0)
	{
		if (data[n])
		{
			i = 0;
			while (data[n][i])
				free(data[n][i++]);
			free(data[n]);
		}
	}
	free(data);
}

void	free_arr(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		free(data[i++]);
	free(data);
}

char	***split_lines(char **data)
{
	char	***new_data;
	int		last_len;
	int		i;

	last_len = -1;
	i = 0;
	new_data = malloc(sizeof(char **) * (arr_len(data) + 1));
	if (!new_data)
		return (NULL);
	while (data[i])
	{
		new_data[i] = ft_split(data[i], ' ');
		if (!new_data[i])
			return (free_n(new_data, i), NULL);
		if (last_len == -1 || last_len == arr_len(new_data[i]))
			last_len = arr_len(new_data[i]);
		else
			return (free_n(new_data, i + 1), NULL);
		i++;
	}
	new_data[i] = 0;
	return (new_data);
}

char	***read_file(char *filename)
{
	char	**data;
	char	***ret;
	char	*file_str;
	int		file_size;
	int		fd;

	file_size = get_file_len(filename);
	if (file_size == -1)
		return (printf("111\n"),NULL);
	fd = open(filename, O_RDONLY);
	file_str = malloc(sizeof(char) * (file_size + 2));
	file_str[file_size + 1] = 0;
	file_str[file_size] = '\n';
	if (file_str == NULL || fd == -1)
		return (printf("222\n"),close(fd), free(file_str), NULL);
	if (read(fd, file_str, file_size) != file_size)
		return (printf("333\n"),close(fd), free(file_str), NULL);
	data = ft_split(file_str, '\n');
	if (data == NULL)
		return (close(fd), free(file_str), NULL);
	ret = split_lines(data);
	return (close(fd), free(file_str), free_arr(data), ret);
}
