/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:03:35 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/31 13:18:48 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	treat_base(char *base)
{
	int	base_l;
	int	i;
	int	j;

	base_l = 0;
	while (base[base_l] != '\0')
	{
		if (base[base_l] == 45 || base[base_l] == 43)
			return (-1);
		base_l++;
	}
	i = 0;
	while (i < base_l)
	{
		j = i + 1;
		while (j <= base_l)
		{
			if (base[i] == base[j])
				return (-1);
			j++;
		}
		i++;
	}
	return (base_l);
}

int	find_in_base(char c, char *base)
{
	int	counter;

	counter = 0;
	while (base[counter] != '\0')
	{
		if (c == base[counter])
			return (counter);
		counter++;
	}
	return (-1);
}

int	get_sign(char *str, int *counter)
{
	int	sign;

	sign = 1;
	while (str[*counter] == 45 || str[*counter] == 43)
	{
		if (str[*counter] == 45)
			sign = sign * -1;
		(*counter)++;
	}
	return (sign);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	start;
	int	sign;
	int	result;
	int	base_l;

	base_l = treat_base(base);
	if (base_l <= 1)
		return (0);
	result = 0;
	start = skip_spaces(str);
	sign = get_sign(str, &start);
	if (sign == 0)
		return (0);
	while (find_in_base(str[start], base) >= 0)
	{
		result = (base_l * result) + find_in_base(str[start], base);
		start++;
	}
	return (result * sign);
}
/*
//#include <unistd.h>
#include <stdio.h>
int main(void)
{
	int result; 
	result = ft_atoi_base("a       \n  ----10t","0123456789abcdef");
	//printf("res: %d", result);
	printf("minint: %d\n",ft_atoi_base("FFFFFF","0123456789ABCDEF"));
	//printf("maxint: %d", );
	printf("0: %d", ft_atoi_base("0", "0123456789abcdef"));
	//printf("maxint+: %d", );
}
*/
