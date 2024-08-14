#include "fdf.h"

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

void	set_scaler(t_scaler *s, t_node ***data)
{
	s->multiplier = (float)(850 / ((float)((s->width / 2) +(float)(s->height / 2)) * 2));
	s->start.p_x = 960 + (s->height - s->width) * ft_round(s->multiplier);
	s->start.p_y = 80;
	set_max_data(s, data); 
	printf("===============max: %d\n", s->max);
	s->data_dev = ( (float)1 / ((float)40 / (float)s->max));
	printf("data_dev: %f============\n", s->data_dev);
}

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
		while (data[i][++j])
		{
			if (data[i][j]->data > max)
				max = data[i][j]->data;
		}
	}
	if (max <= 0)
		max = 1;
	s->max = max;
}
