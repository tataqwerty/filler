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
	char *line;
	short **array;

	if (!(array = (short**)malloc(sizeof(short *) * height)))
		return (NULL);
	while (--height >= 0)
	{
		if (!(array[height] = (short*)malloc(sizeof(short) * width)))
			return (NULL);
		ft_memset(array[height], 0, width);
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

void	put_players_on_board(t_filler *s)
{
	while (s->me)
	{
		s->array[s->me->y][s->me->x] = -1;
		s->me = s->me->next;
	}
	while (s->enemy)
	{
		s->array[s->enemy->y][s->enemy->x] = -2;
		s->enemy = s->enemy->next;
	}
}

void	add_coordinate_on_array(t_filler *s, short x, short y)
{
	short	steps;
	short	tmp;

	steps = 32767;
	while (s->enemy)
	{
		tmp = ABS(s->enemy->x - x) + ABS(s->enemy->y - y);
		if (tmp < steps)
			steps = tmp;
		s->enemy = s->enemy->next;
	}
	s->array[y][x] = steps;
}

void	fill_array(t_filler *s)
{
	short		x;
	short		y;

	put_players_on_board(s);
	// y = -1;
	// while (++y < s->height)
	// {
	// 	x = -1;
	// 	while (++x < s->width)
	// 	{
	// 		if (s->array[y][x] == 0)
	// 			add_coordinate_on_array(s, x, y);
	// 	}
	// }
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
	//fill_array(s);
	
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
