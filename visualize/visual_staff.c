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

#include "visual.h"

void	output_map(char **array, unsigned char height)
{
	unsigned char y;
	unsigned char x;
	unsigned char width;

	width = ft_strlen(array[0]);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			output_char(y, x, array[y][x]);
			x++;
		}
		y++;
	}
}

void	delete_map(char **array, unsigned char height)
{
	unsigned char i;

	i = 0;
	while (i < height)
		free(array[i++]);
}

void	ft_magic(char **array, char *line, unsigned char height)
{
	free(line);
	get_next_line(0, &line);
	free(line);
	create_map(array, height);
	output_map(array, height);
	refresh();
	delete_map(array, height);
	get_next_line(0, &line);
	skip_shit_after_map(line);
}

void	init_results(char *line, short *p1, short *p2)
{
	*p1 = ft_atoi(line + 10);
	free(line);
	get_next_line(0, &line);
	*p2 = ft_atoi(line + 10);
	free(line);
}

char	error_mamagement(char *line)
{
	if (ft_strstr(line, "Piece"))
	{
		skip_shit_after_map(line);
		get_next_line(0, &line);
	}
	if (ft_strstr(line, "fin"))
		return (1);
	return (0);
}
