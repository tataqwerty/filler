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

void	del_everything(t_filler *s)
{
	while (--(s->height) >= 0)
		free(s->array[s->height]);
	free(s->array);
	s->array = NULL;
	list_del(s->me);
	list_del(s->enemy);
	free(s);
	write(1, "0 0\n", 4);
	exit(0);
}

void	init_piece_arr(t_piece *piece)
{
	short k;

	bzero_board(&piece->arr, piece->shape_width, piece->shape_height);
	k = -1;
	while (++k < piece->k)
		piece->arr[piece->y[k]][piece->x[k]] = -3;
}

void	piece_del(t_piece *piece)
{
	short y;

	free(piece->x);
	free(piece->y);
	y = -1;
	while (++y < piece->shape_height)
		free(piece->arr[y]);
	free(piece->arr);
	free(piece);
}

short	value_of_piece(t_piece *piece)
{
	short counter;
	short res;
	short x;
	short y;

	y = -1;
	res = 0;
	counter = 0;
	while (++y < piece->shape_height)
	{
		x = -1;
		while (++x < piece->shape_width)
		{
			if (piece->arr[y][x] == -2)
				return (-1);
			else if (piece->arr[y][x] == -1)
				counter++;
			else
				res += piece->arr[y][x];
		}
	}
	if (counter != 1)
		return (-1);
	return (res);
}

short	put_piece_on_map(t_filler *s, t_piece *piece, short x, short y)
{
	short tmp_x;
	short tmp_y;

	tmp_y = -1;
	while (++tmp_y < piece->shape_height)
	{
		tmp_x = -1;
		while (++tmp_x < piece->shape_width)
		{
			if ((y + tmp_y) < s->height && (x + tmp_x) < s->width)
			{
				if (piece->arr[tmp_y][tmp_x] == -3)
					piece->arr[tmp_y][tmp_x] = s->array[y + tmp_y][x + tmp_x];
			}
			else
				return (-1);
		}
	}
	return (value_of_piece(piece));
}
