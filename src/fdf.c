/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:22:43 by vcaratti          #+#    #+#             */
/*   Updated: 2024/08/12 12:46:30 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_free(t_node ***data)
{
	int	i;
	int	j;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
			free(data[i][j++]);
		free(data[i++]);
	}
}

int	iso_x(int x, int y)
{
	return (x - y);
}

int	iso_y(int x, int y)
{
	return ((x / 2) + y / 2);
}

void	iso_to_pixel(int iso_x, int iso_y, t_scaler *s, t_pnode *p)
{
	p->p_x = s->start.p_x + ft_round((iso_x * s->multiplier));
	p->p_y = s->start.p_y + ft_round((iso_y * s->multiplier));
}

void	assign_to_node(t_pnode *node, int x, int y)
{
	node->p_x = x;
	node->p_y = y;
}

void	add_data_to_node(t_pnode *node, t_scaler *s, t_node *node_data)
{
	printf("data: %d, data_dev: %f, added pixels: %d\n",node_data->data, s->data_dev, ft_round((float)node_data->data / s->data_dev));
	node->p_y = node->p_y - ft_round((float)node_data->data / s->data_dev); //MULTIPLIER !!!!!! if data too high, can go above the map
	node->colour = node_data->colour;
	//printf("colour?: %X\n", node_data->colour);
}

void	draw_horizontal(t_node ***data, t_scaler *s, t_data *img)
{
	int	x;
	int	y;
	t_pnode	last;
	t_pnode new;

	y = 0;
	x = 0;
	assign_to_node(&last, s->start.p_x, s->start.p_y);
	add_data_to_node(&last, s, data[0][0]);
	printf("START: [%d, %d]\n", last.p_x, last.p_y);
	while ( y < s->height * 2 )
	{
		iso_to_pixel(iso_x(0, y), iso_y(0, y), s, &last);
		add_data_to_node(&last, s, data[y/2][0]);
		x = 2;
		while ( x < s->width * 2)
		{
			iso_to_pixel(iso_x(x, y), iso_y(x, y), s, &new);
			add_data_to_node(&new, s, data[y/2][x/2]);
			//printf("COLUR?????: %X\n", data[y/2][x/2]->colour);
			//ft_draw(&last, &new);
			printf("GOING TO map: [x: %d][y: %d]-> iso: [x: %d][y: %d] pixel:[%d, %d]\n", x,y,iso_x(x,y), iso_y(x, y), new.p_x, new.p_y);fflush(stdout);	
			draw_line(&last, &new, img);
			assign_to_node(&last, new.p_x, new.p_y);
			last.colour = new.colour;
			x+= 2;
		}
		printf("DONE\n");fflush(stdout);
		iso_to_pixel(iso_x(x, y), iso_y(x, y), s, &last);
		y += 2;
	}
}

void	draw_vertical(t_node ***data, t_scaler *s, t_data *img)
{
	int	x;
	int	y;
	t_pnode	last;
	t_pnode new;

	x = 0;
	y = 0;
	assign_to_node(&last, s->start.p_x, s->start.p_y);
	add_data_to_node(&last, s, data[0][0]);
	printf("START: [%d, %d]\n", last.p_x, last.p_y);
	while ( x < s->width * 2 )
	{
		//iso_to_pixel(iso_x(x, y), iso_y(x, y), s, &last);
		iso_to_pixel(iso_x(x, 0), iso_y(x, 0), s, &last);
		add_data_to_node(&last, s, data[0][x/2]);
		y = 2;
		while ( y < s->height * 2 )
		{
			//printf("Drawing line:(%d,%d)->[%d, %d]\n",x,y, iso_x(x,y), iso_y(x,y));fflush(stdout);
			iso_to_pixel(iso_x(x, y), iso_y(x, y), s, &new);
			add_data_to_node(&new, s, data[y/2][x/2]);
			//ft_draw(&last, &new);
			printf("GOING TO map: [x: %d][y: %d]-> iso: [x: %d][y: %d] pixel:[%d, %d]\n", x,y,iso_x(x,y), iso_y(x, y), new.p_x, new.p_y);fflush(stdout);	
			draw_line(&last, &new, img);
			assign_to_node(&last, new.p_x, new.p_y);
			last.colour = new.colour;
			y += 2;
		}
		printf("DONE\n");fflush(stdout);
		x += 2;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//printf("[x: %d][y: %d][data ll: %d][color: %X]\n",x,y,data->line_length, color);fflush(stdout);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	set_max_data(t_scaler *s, t_node ***data)
{
	int	max;
	int	i;
	int	j;

	max = -1000000;
	i = -1;
	while (data[++i])
	{
		j = -1;
		printf("[ ");
		while (data[i][++j])
		{
			if (data[i][j]->data > max)
				max = data[i][j]->data;
			printf("%d ", data[i][j]->data);
		}
		printf("[\n");fflush(stdout);
	}
	s->max = max;
}

void	set_scaler(t_scaler *s, t_node ***data)
{
	s->multiplier = (float)(850 / ((float)((s->width / 2) +(float)(s->height / 2)) * 2)); //MULTIPLIER
	s->start.p_x = 960 + (s->height - s->width) * ft_round(s->multiplier);
	s->start.p_y = 80;
	set_max_data(s, data); 
	printf("===============max: %d\n", s->max);
	s->data_dev = ( (float)1 / ((float)40 / (float)s->max));
	printf("data_dev: %f============\n", s->data_dev);
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
void	print_map(int **data, t_scaler *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->height)
	{
		j = 0;
		while (j < s->width)
		{
			printf("%d\t", data[i][j]);
			j++;	
		}
		printf("\n");
		i++;
	}
}

int	handle_input(int key, void *param)
{
	printf("ok: %d\n", key);fflush(stdout);
	if (key == 53)
	{
		map_free((t_node ***)param);
		exit(0);
	}
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
	//printf("yesssssssss: %d\n", parser(argv[1], &s, &data));
	//map_free(data);//convert to ***data
	//printf("yarr");fflush(stdout);
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



/*
0 , 1
-1, 0,5
x = (x-()y) y = (x/2+y)
largeur_fenetre/2  -  (largeur - hauteur)/2
*/

