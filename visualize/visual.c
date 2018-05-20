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

void				ft_main_algo(short *p1, short *p2, char *line)
{
	unsigned char	height;
	char			**array;
	char			array_flag;

	height = 0;
	array_flag = 1;
	array = NULL;
	skip_shit_before_map(line);
	while (get_next_line(0, &line) > 0)
	{
		if (error_mamagement(line) == 1)
			break ;
		if (array_flag)
		{
			array_flag = 0;
			preparation(&array, line, &height);
		}
		ft_magic(array, line, height);
	}
	if (array)
		free(array);
	usleep(1500000);
	init_results(line, p1, p2);
}

int					main(void)
{
	FILE			*file;
	struct screen	*term;
	char			*line;
	short			p1;
	short			p2;

	p1 = 0;
	p2 = 0;
	line = NULL;
	file = fopen("/dev/tty", "r+");
	term = newterm(NULL, file, file);
	set_term(term);
	start_color();
	cbreak();
	noecho();
	init_pair(1, COLOR_GREEN, COLOR_GREEN);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	ft_main_algo(&p1, &p2, line);
	endwin();
	printf("p1 == %d\n", p1);
	printf("p2 == %d\n", p2);
	return (0);
}
