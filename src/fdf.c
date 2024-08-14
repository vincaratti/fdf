/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:22:43 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/14 10:20:31 by vincenzocarat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	draw_horizontal(t_node ***data, t_scaler *s, t_data *img)
{
	int	x;
	int	y;
	t_pnode	last;
	t_pnode new;

	y = -1;
	assign_to_node(&last, s->start.p_x, s->start.p_y);
	add_data_to_node(&last, s, data[0][0]);
	while ( ++y < s->height)
	{
		iso_to_pixel(iso_x(0, y * 2), iso_y(0, y * 2), s, &last);
		add_data_to_node(&last, s, data[y][0]);
		x = 0;
		while ( ++x < s->width)
		{
			iso_to_pixel(iso_x(x * 2, y * 2), iso_y(x * 2, y * 2), s, &new);
			add_data_to_node(&new, s, data[y][x]);
			draw_line(&last, &new, img);
			assign_to_node(&last, new.p_x, new.p_y);
			last.colour = new.colour;
		}
	}
}

void	draw_vertical(t_node ***data, t_scaler *s, t_data *img)
{
	int	x;
	int	y;
	t_pnode	last;
	t_pnode new;

	x = -1;
	assign_to_node(&last, s->start.p_x, s->start.p_y);
	add_data_to_node(&last, s, data[0][0]);
	while ( ++x < s->width)
	{
		iso_to_pixel(iso_x(x * 2, 0), iso_y(x * 2, 0), s, &last);
		add_data_to_node(&last, s, data[0][x]);
		y = 0;
		while ( ++y < s->height)
		{
			iso_to_pixel(iso_x(x * 2, y * 2), iso_y(x * 2, y * 2), s, &new);
			add_data_to_node(&new, s, data[y][x]);
			draw_line(&last, &new, img);
			assign_to_node(&last, new.p_x, new.p_y);
			last.colour = new.colour;
		}
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	fdf(t_node ****data, t_scaler *s, char *filename, t_data *img)
{
	s->width = 0;
	s->height = 0;
	s->data_dev = 5;
	if (parser(filename, s, data))
		return (1);
	//printf("yar???");fflush(stdout);
	set_scaler(s, *data);
	/*
	printf("wut?");fflush(stdout);
	t_pnode truc;
	iso_to_pixel(iso_x(2,0), iso_y(2,0), s, &truc);
	draw_line(&(s->start), &truc, img);*/
	printf("height: %d, width: %d\n", s->height, s->width);
	draw_vertical(*data, s, img);
	draw_horizontal(*data, s, img);
	return (0);
}

#include <stdio.h>
int main(int argc, char **argv)
{
	t_node		***data;
	t_scaler	s;
	void		*mlx;
	void		*mlx_win;
	t_data		img;

	if (argc != 2)
		return (1);//printf("yesssssssss: %d\n", parser(argv[1], &s, &data));
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	//do stuff
	if (fdf(&data, &s, argv[1], &img))//***data
		return (printf("ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n"),free(mlx), free(mlx_win), system("leaks fdf"), 1);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, handle_input, (void *)data);//***data
	mlx_loop(mlx);
	//print_map(data, &s);
	map_free(data);//***dta
	system("leaks fdf");
	return (0);
}
