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

void	put_players_on_board(t_filler *s, short **array)
{
	t_coords	*me;
	t_coords	*enemy;

	me = s->me;
	enemy = s->enemy;
	while (me)
	{
		array[me->y][me->x] = -1;
		me = me->next;
	}
	while (enemy)
	{
		array[enemy->y][enemy->x] = -2;
		enemy = enemy->next;
	}
}

void	bzero_board(short ***array, short width, short height)
{
	short y;
	short x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			(*array)[y][x] = 0;
	}
}

void	envelop_xy(t_filler *s, short x, short y, short d)
{
	if (y > 0 && s->array[y - 1][x] == 0)
		s->array[y - 1][x] = d;
	if (x > 0 && s->array[y][x - 1] == 0)
		s->array[y][x - 1] = d;
	if (x < (s->width - 1) && s->array[y][x + 1] == 0)
		s->array[y][x + 1] = d;
	if (y < (s->height - 1) && s->array[y + 1][x] == 0)
		s->array[y + 1][x] = d;
}

void	add_ones(t_filler *s)
{
	t_coords *enemy;

	enemy = s->enemy;
	while (enemy)
	{
		envelop_xy(s, enemy->x, enemy->y, 1);
		enemy = enemy->next;
	}
}

void	fill_array(t_filler *s)
{
	short flag;
	short y;
	short x;
	short d;

	put_players_on_board(s, s->array);
	add_ones(s);
	d = 1;
	y = -1;
	flag = 0;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			if (s->array[y][x] == d && (flag = 1))
				envelop_xy(s, x, y, d + 1);
		}
		if (y == (s->height - 1) && flag)
		{
			flag = 0;
			y = -1;
			d++;
		}
	}
}
