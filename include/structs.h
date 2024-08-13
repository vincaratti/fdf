/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:56:38 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/12 12:16:50 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_pnode
{
	int		p_x;
	int		p_y;
	int		colour;
}			t_pnode;

typedef	struct	s_scaler
{
	t_pnode	start;
	float	multiplier;
	float	data_dev;
	int		height;
	int		width;
	int		max;
}			t_scaler;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_node
{
	int		data;
	int		colour;
}			t_node;
#endif
