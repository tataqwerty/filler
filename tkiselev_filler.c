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

void	ft_pc(char c)
{
	write(2, &c, 1);
}

void	ft_nbr(long int n)
{
	if (n >= 0 && n <= 9)
		ft_pc(n + 48);
	else if (n < 0)
	{
		write(2, "-", 1);
		ft_nbr(n * -1);
	}
	else
	{
		ft_nbr(n / 10);
		ft_nbr(n % 10);
	}
}

void	ft_str(char *str)
{
	int i = 0;

	if (!str)
		write(2, "(null)", 6);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

char		get_player(void)
{
	char *line;
	char p;

	get_next_line(0, &line);
	if (ft_strstr(line, "p1"))
		p = 'O';
	else
		p = 'X';
	free(line);
	return (p);
}

void	get_width_n_height(short *width, short *height)
{
	char	*line;
	short	i;

	i = 0;
	get_next_line(0, &line);
	while (line[i] < '0' || line[i] > '9')
		i++;
	*height = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	*width = ft_atoi(line + i);
	free(line);
}

short		**create_array(short width, short height)
{
	short	**array;
	short	x;

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

void	add_coords_if(t_coords **head, short x, short y)
{
	t_coords *helper;
	t_coords *tmp;

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

void	get_players_coords(t_filler *s)
{
	char	*line;
	short	h;
	short	w;

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

void	bzero_board(t_filler *s)
{
	short y;
	short x;

	y = -1;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
			s->array[y][x] = 0;
	}
}

void	array_del(short **array, short height)
{
	while (height >= 0)
		free(array[height--]);
	free(array);
}




short	ft_coord_helper(t_filler *s, short **array, short x, short y)
{
	short d;

	d = 1;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			if (array[y][x] == d)
			{
				if ((y > 0 && array[y - 1][x] == -2) || (y < (s->height - 1)
				&& array[y + 1][x] == -2) || (x > 0 && array[y][x - 1] == -2)
				|| (x < (s->width - 1) && array[y][x + 1] == -2))
					return (d);
				if (y > 0 && array[y - 1][x] == 0)
					array[y - 1][x] = d + 1;
				if (y < (s->height - 1) && array[y + 1][x] == 0)
					array[y + 1][x] = d + 1;
				if (x > 0 && array[y][x - 1] == 0)
					array[y][x - 1] = d + 1;
				if (x < (s->width - 1) && array[y][x + 1] == 0)
					array[y][x + 1] = d + 1;
			}
		}
		if (y == (s->height - 1))
		{
			d++;
			y = -1;
		}
	}
	return (0);
}

void	add_coordinate_to_board(t_filler *s, short x, short y)
{
	short **tmp_array;

	tmp_array = create_array(s->width, s->height);
	put_players_on_board(s, tmp_array);
	tmp_array[y][x] = 1;
	s->array[y][x] = ft_coord_helper(s, tmp_array, x, -1);
	//array_del(tmp_array, s->height);
}

void	fill_array(t_filler *s)
{
	short		x;
	short		y;

	bzero_board(s);
	put_players_on_board(s, s->array);
	y = -1;
	while (++y < s->height)
	{
		x = -1;
		while(++x < s->width)
		{
			if (s->array[y][x] == 0)
				add_coordinate_to_board(s, x, y);
		}
	}
}

int		main(void)
{
	static t_filler *s = NULL;

	if (!s)
	{
		if (!(s = (t_filler*)malloc(sizeof(t_filler))))
			return (-1);
		s->width = 0;
		s->height = 0;
		s->enemy = NULL;
		s->me = NULL;
		s->player = get_player();
		get_width_n_height(&s->width, &s->height);
		s->array = create_array(s->width, s->height);
	}
	get_players_coords(s);
	fill_array(s);

	int y = -1;
	int x;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
			ft_nbr(s->array[y][x]);
		ft_pc('\n');
	}
	return (0);
}
