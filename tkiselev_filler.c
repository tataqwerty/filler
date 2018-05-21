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

short			easy_algorithm(t_filler *s, t_piece *piece, short x, short y)
{
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			init_piece_arr(piece);
			if (put_piece_on_map(s, piece, x, y) == 0)
			{
				ft_win(x - piece->min_x, y - piece->min_y);
				piece_del(piece);
				return (1);
			}
		}
	}
	piece_del(piece);
	return (-1);
}

short			minihelp(t_filler *s, t_piece *piece, short opt_x, short opt_y)
{
	if (opt_x == -1 && opt_y == -1)
	{
		if (easy_algorithm(s, piece, -1, -1) == 1)
			return (1);
		else
			return (-1);
	}
	else
	{
		ft_win(opt_x - piece->min_x, opt_y - piece->min_y);
		piece_del(piece);
		return (1);
	}
}

short			hard_algorithm(t_filler *s, t_piece *piece, short x, short y)
{
	short		tmp_mvop;
	short		mvop;
	short		opt_x;
	short		opt_y;

	opt_x = -1;
	opt_y = -1;
	mvop = 32767;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			init_piece_arr(piece);
			tmp_mvop = put_piece_on_map(s, piece, x, y);
			if (tmp_mvop < mvop && tmp_mvop > 0)
			{
				mvop = tmp_mvop;
				opt_x = x;
				opt_y = y;
			}
		}
	}
	return (minihelp(s, piece, opt_x, opt_y));
}

void			func(t_filler *s, char *line)
{
	t_piece		*piece;

	if (s->flag_for_arr == 0)
	{
		s->flag_for_arr = 1;
		get_width_n_height(&s->width, &s->height, line);
		s->array = create_array(s->width, s->height);
	}
	free(line);
	bzero_board(&s->array, s->width, s->height);
	get_players_coords(s);
	fill_array(s);
	piece = create_piece();
	if (enemy_closed(s) == 1)
	{
		if (easy_algorithm(s, piece, -1, -1) == -1)
			del_everything(s);
	}
	else if (hard_algorithm(s, piece, -1, -1) == -1)
		del_everything(s);
}

int				main(void)
{
	char		*line;
	t_filler	*s;

	if (!(s = (t_filler*)malloc(sizeof(t_filler))))
		return (-1);
	s->width = 0;
	s->height = 0;
	s->flag_for_arr = 0;
	s->player = get_player();
	while (get_next_line(0, &line) > 0)
		func(s, line);
	return (0);
}
