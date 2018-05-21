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
				s->array[h][w - 4] = -1;
			else if (line[w] != '.')
				s->array[h][w - 4] = -2;
		}
		free(line);
	}
}
