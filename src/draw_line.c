/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:15:55 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 09:47:22 by vincenzocarat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_round(float x)
{
	float	x2;

	x2 = x - (float)((int)x);
	if (x2 > (float) 1 / (float) 2)
		return ((int)x + 1);
	return ((int)x);
}

void draw_line(t_pnode *a, t_pnode *b, t_data *img) 
{
    int		steps;
    float	x;
    float	y;
    int		i;
	int		chosen_colour;

    x = a->p_x;
    y = a->p_y;
    if (ft_abs(b->p_x - a->p_x) > ft_abs(b->p_y - a->p_y))
	    steps = ft_abs(b->p_x - a->p_x);
    else
	    steps = ft_abs(b->p_y - a->p_y);
    i = 0;
    while (i <= steps) 
    {
		chosen_colour = 0xFFFFFF;
		if (a->colour == b->colour)
			chosen_colour = a->colour;
        my_mlx_pixel_put(img, ft_round(x), ft_round(y), chosen_colour);
		x += (b->p_x - a->p_x) / (float) steps;
        y += (b->p_y - a->p_y) / (float) steps;
	i++;
    }
}
