/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_map_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:10:53 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 09:57:18 by vincenzocarat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	remove_newline(char **nums_str)
{
	char	*newline;
	int		counter;
	
	counter = 0;
	while (nums_str[counter])
	{
		newline = ft_strrchr(nums_str[counter], '\n');
		if (newline)
		{
			free(nums_str[counter]);
			nums_str[counter] = 0;
		}
		counter++;
	}
}

static int	verify_strings(char **nums_str)
{
	int		counter;
	int		str_i;
	char	*str;

	str_i = 0;
	while (nums_str[str_i])
	{
		counter = 0;
		str = nums_str[str_i];
		while (str[counter])
		{
			if (!ft_isdigit(str[counter]) && !is_whitespace(str[counter])
				&& str[counter] != 45)
				return (-1);
			counter++;
		}
		str_i++;
	}
	return (0);
}

static int	map_atoi(char **nums_str, int wc, t_node ***nums)
{
	int			counter;
	long int	res;

	counter = 0;
	while (counter < wc)
	{
		res = ft_atoi((const char *)nums_str[counter]);
		free(nums_str[counter]);
		if (res > 2147483647 || res < -2147483648)
			return (map_free_str_e_ret(nums_str, counter + 1, wc, 1));
		(*nums)[counter]->data = (int)res;
		counter++;;
	}
	free(nums_str);
	return (0);
}

int	str_map_atoi(char **nums_str, t_node ***nums, int wc)
{
	if (!nums_str)
		return (1);
	remove_newline(nums_str);
	if (nums_str == NULL)
		return (1);
	if (verify_strings(nums_str))
		return (map_free_e_ret(nums_str, 1));
	if (map_atoi(nums_str, wc, nums))
		return (free(*nums), 1);
	return (0);
}






