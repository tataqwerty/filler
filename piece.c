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

void		get_piece_width_n_height(t_piece *piece, char *line)
{
	short	i;

	i = 0;
	get_next_line(0, &line);
	while (line[i] < '0' || line[i] > '9')
		i++;
	piece->height = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		piece->height = piece->height * 10 + line[i] - 48;
		i++;
	}
	i++;
	piece->width = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		piece->width = piece->width * 10 + line[i] - 48;
		i++;
	}
	free(line);
	line = NULL;
}

void		fill_piece_arrays(t_piece *piece, char *line)
{
	short	x;
	short	y;

	y = -1;
	piece->k = 0;
	while (++y < piece->height && get_next_line(0, &line) > 0)
	{
		x = -1;
		while (line[++x])
		{
			if (line[x] == '*')
			{
				piece->y[piece->k] = y;
				piece->x[piece->k] = x;
				piece->k++;
				if (y < piece->min_y)
					piece->min_y = y;
				if (x < piece->min_x)
					piece->min_x = x;
			}
		}
		free(line);
	}
}

void		nullify_piece_arrays(t_piece *piece)
{
	short	k;

	k = -1;
	while (++k < piece->k)
	{
		piece->x[k] -= piece->min_x;
		piece->y[k] -= piece->min_y;
	}
}

short		max_arr(short *array, short len)
{
	short k;
	short max;

	k = 0;
	max = array[0];
	while (++k < len)
	{
		if (max < array[k])
			max = array[k];
	}
	return (max);
}

t_piece		*create_piece(void)
{
	char	*line;
	t_piece	*piece;

	if (!(piece = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	line = NULL;
	get_piece_width_n_height(piece, line);
	if (!(piece->y = (short*)malloc(sizeof(short) *
		piece->height * piece->width))
	|| !(piece->x = (short*)malloc(sizeof(short) *
		piece->width * piece->height)))
		return (NULL);
	piece->min_y = 32767;
	piece->min_x = 32767;
	fill_piece_arrays(piece, line);
	nullify_piece_arrays(piece);
	piece->shape_height = max_arr(piece->y, piece->k) + 1;
	piece->shape_width = max_arr(piece->x, piece->k) + 1;
	piece->arr = create_array(piece->shape_width, piece->shape_height);
	return (piece);
}
