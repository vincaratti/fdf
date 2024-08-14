/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:14:34 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 10:21:21 by vincenzocarat    ###   ########.fr       */
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

//== iso_tools.c ==//

int	iso_x(int x, int y);
int	iso_y(int x, int y);
void	iso_to_pixel(int iso_x, int iso_y, t_scaler *s, t_pnode *p);
void	assign_to_node(t_pnode *node, int x, int y);
void	add_data_to_node(t_pnode *node, t_scaler *s, t_node *node_data);

//== fdf_tools.c==//

void	set_max_data(t_scaler *s, t_node ***data);
void	map_free(t_node ***data);
void	set_scaler(t_scaler *s, t_node ***data);
int	handle_input(int key, void *param);

#endif
