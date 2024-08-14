/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:58:26 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 10:01:27 by vincenzocarat    ###   ########.fr       */
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
void	free_i_str(int *ints, char *line);

//##== str_map_atoi_tools.c ==##//

int	is_whitespace(char c);
int	str_arr_len(char **str_arr);
int	map_free_str_e_ret(char **arr, int counter, int length, int error);
int	map_free_e_ret(char **arr, int error);

//##==parser_tools.c==##//

int	arr_len(char **data);
int	d_arr_len(char ***data);
void	free_2d_arr(char ***arr);
void	free_n_data(t_node ***data, int n);
void	free_data(t_node ****data);

#endif
