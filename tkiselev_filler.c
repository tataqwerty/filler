/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkiselev_filler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/16 19:10:13 by tkiselev         ###   ########.fr       */
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





void	ft_win(short x, short y)
{
	ft_putnbr(y);
	write(1, " ", 1);
	ft_putnbr(x);
	write(1, "\n", 1);
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

void	get_width_n_height(short *width, short *height, char *line)
{
	short	i;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++;
	*height = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	*width = ft_atoi(line + i);
}

short		**create_array(short width, short height)
{
	short	**array;
	short	x;
	short	y;

	if (!(array = (short**)malloc(sizeof(short *) * height)))
		return (NULL);
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (!(array[y] = (short*)malloc(sizeof(short) * width)))
			return (NULL);
		while (++x < width)
			array[y][x] = 0;
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

void	get_players_coords(t_filler *s, char *line)
{
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

void	get_piece_width_n_height(t_piece *piece, char *line)
{
	short i;

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

void	fill_piece_arrays(t_piece *piece, char *line)
{
	short x;
	short y;

	y = -1;
	piece->k = 0;
	while (++y < piece->height && get_next_line(0, &line) > 0)
	{		
		x = -1;
		while (++x < piece->width)
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

void	nullify_piece_arrays(t_piece *piece)
{
	short k;

	k = -1;
	while (++k < piece->k)
	{
		piece->x[k] -= piece->min_x;
		piece->y[k] -= piece->min_y;
	}
}

short		max_arr(short *array, short len)
{
	short i;
	short max;

	max = array[0];
	i = 0;
	while (++i < len)
	{
		if (max < array[i])
			max = array[i];
	}
	return (max);
}

t_piece		*create_piece(char *line)
{
	t_piece	*piece;

	if (!(piece = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	get_piece_width_n_height(piece, line);
	if (!(piece->y = (short*)malloc(sizeof(short) * (piece->height * piece->width)))
	|| !(piece->x = (short*)malloc(sizeof(short) * (piece->height * piece->width))))
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

void	init_piece_arr(t_piece *piece)
{
	short k;

	bzero_board(&piece->arr, piece->shape_width, piece->shape_height);
	k = -1;
	while (++k < piece->k)
		piece->arr[piece->y[k]][piece->x[k]] = -3;
}

void	list_del(t_coords *head)
{
	t_coords *next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void	del_everything(t_filler *s)
{
	short y;

	y = -1;
	while (++y < s->height)
		free(s->array[y]);
	free(s->array);
	list_del(s->me);
	list_del(s->enemy);
	free(s);
	write(1, "0 0\n", 4);
	exit(0);
}

short	enemy_closed(t_filler *s)
{
	short x;
	short y;

	y = -1;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			if (s->array[y][x] == 1)
				return (0);
		}
	}
	return (1);
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

short	easy_algorithm(t_filler *s, t_piece *piece, short x, short y)
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

short	minihelp(t_filler *s, t_piece *piece, short opt_x, short opt_y)
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

short	hard_algorithm(t_filler *s, t_piece *piece, short x, short y)
{
	short tmp_mvop;
	short mvop;
	short opt_x;
	short opt_y;

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

void	main_func(t_filler *s, char *line)
{
	t_piece *piece;

	if (s->flag == 0)
	{
		s->flag = 1;
		get_width_n_height(&s->width, &s->height, line);
		s->array = create_array(s->width, s->height);
	}
	free(line);
	get_players_coords(s, line);
	bzero_board(&s->array, s->width, s->height);
	fill_array(s);
	piece = create_piece(line);
	if (enemy_closed(s) == 1)
	{
		if (easy_algorithm(s, piece, -1, -1) == -1)
			del_everything(s);
	}
	else if (hard_algorithm(s, piece, -1, -1) == -1)
		del_everything(s);
}

int		main(void)
{
	char			*line;
	t_filler *s = NULL;

	if (!(s = (t_filler*)malloc(sizeof(t_filler))))
		return (-1);
	s->width = 0;
	s->height = 0;
	s->enemy = NULL;
	s->me = NULL;
	s->flag = 0;
	s->player = get_player();
	while (get_next_line(0, &line) > 0)
		main_func(s, line);
	return (0);
}
