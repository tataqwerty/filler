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

void	skip_shit_before_map(char *line)
{
	char i;

	i = 9;
	while (--i >= 0 && get_next_line(0, &line) > 0)
		;
}

void	skip_shit_after_map(char *line)
{
	unsigned char height;

	height = ft_atoi(line + 6);
	while (height-- > 0 && get_next_line(0, &line) > 0)
		;
	get_next_line(0, &line);
}

void	preparation(char ***array, char *line, unsigned char *height)
{
	unsigned char	i;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		*height = *height * 10 + line[i++] - 48;
	(*array) = (char**)malloc(sizeof(char*) * (*height));
}

void	create_map(char **array, unsigned char height)
{
	unsigned char i;

	i = 0;
	while (i < height)
		get_next_line(0, &(array[i++]));
}

void	output_char(unsigned char y, unsigned char x, char c)
{
	if (c == 'O')
	{
		attron(COLOR_PAIR(1));
		mvaddch(y, x, ' ');
		attroff(COLOR_PAIR(1));
	}
	else if (c == 'X')
	{
		attron(COLOR_PAIR(2));
		mvaddch(y, x, ' ');
		attroff(COLOR_PAIR(2));
	}
	else if (c == 'o' || c == 'x')
	{
		attron(COLOR_PAIR(3));
		mvaddch(y, x, ' ');
		attroff(COLOR_PAIR(3));
	}
	else
		mvaddch(y, x, c);
}
