/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkiselev_filler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char			get_player(void)
{
	char		*line;
	char		p;

	get_next_line(0, &line);
	if (ft_strstr(line, "p1"))
		p = 'O';
	else
		p = 'X';
	free(line);
	return (p);
}

void			get_width_n_height(short *width, short *height, char *line)
{
	short		i;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++;
	*height = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	*width = ft_atoi(line + i);
}

short			**create_array(short width, short height)
{
	short		**array;
	short		x;

	if (!(array = (short**)malloc(sizeof(short *) * height)))
		return (NULL);
	while (--height >= 0)
	{
		x = -1;
		if (!(array[height] = (short*)malloc(sizeof(short) * width)))
			return (NULL);
		while (++x < width)
			array[height][x] = 0;
	}
	return (array);
}

void			add_coords_if(t_coords **head, short x, short y)
{
	t_coords	*helper;
	t_coords	*tmp;

	helper = *head;
	while (helper)
	{
		if (helper->x == x && helper->y == y)
			return ;
		else if (helper->next)
			helper = helper->next;
		else
			break ;
	}
	if (!(tmp = (t_coords*)malloc(sizeof(t_coords))))
		return ;
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	if (helper)
		helper->next = tmp;
	else
		*head = tmp;
}

void			get_players_coords(t_filler *s)
{
	char		*line;
	short		h;
	short		w;

	h = -1;
	get_next_line(0, &line);
	free(line);
	while (++h < s->height && get_next_line(0, &line) > 0)
	{
		w = 3;
		while (line[++w])
		{
			if (s->player == line[w] || s->player == (line[w] - 32))
				add_coords_if(&s->me, w - 4, h);
			else if (line[w] != '.')
				add_coords_if(&s->enemy, w - 4, h);
		}
		free(line);
	}
}
