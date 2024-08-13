/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:58:26 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/05 14:34:14 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "structs.h"
//# include "get_next_line.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>

#include <stdio.h>

int		str_map_atoi(char **nums_str, t_node ***nums, int wc);
int 	parser(char *filename, t_scaler *s, t_node ****data);
char	***read_file(char *filename);
int		arr_len(char **data);
int		d_arr_len(char ***data);
void	free_arr(char **data);
void	free_n(char ***data, int n);

#endif
