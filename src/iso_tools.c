#include "fdf.h"

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
	node->p_y = node->p_y - ft_round((float)node_data->data / s->data_dev);
	node->colour = node_data->colour;
}
