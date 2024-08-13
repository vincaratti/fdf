/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:14:34 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/12 12:01:23 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "parser.h"
# include "structs.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>

#include <stdio.h>

//== draw_line.c ==//
int		ft_round(float x);
void	draw_line(t_pnode *a, t_pnode *b, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
