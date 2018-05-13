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

void	skip_shit()
{
	static  char	flag = 0;
	char 			*line;

	if (flag != 0)
	{
		get_next_line(0, &line);
		free(line);
	}
	get_next_line(0, &line);
	free(line);
	flag = 1;
}

void	get_players_coords(t_filler *s)
{
	static int counter = 0;
	char	*line;
	short	h;
	short	w;

	h = -1;
	skip_shit();
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
	short max;

	len--;
	max = array[len];
	while (--len >= 0)
	{
		if (max < array[len])
			max = array[len];
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
	if (!(piece->y = (short*)malloc(sizeof(short) * piece->height))
	|| !(piece->x = (short*)malloc(sizeof(short) * piece->width)))
		return (NULL);
	piece->min_y = 32767;
	piece->min_x = 32767;
	fill_piece_arrays(piece, line);
	nullify_piece_arrays(piece);
	piece->shape_height = max_arr(piece->y, piece->k) + 1;
	piece->shape_width = max_arr(piece->x, piece->k) + 1;
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

short	value_of_piece(t_piece *piece)
{
	short my_counter;
	short x;
	short y;
	short sum;

	sum = 0;
	y = -1;
	my_counter = 0;
	while (++y < piece->shape_height)
	{
		x = -1;
		while (++x < piece->shape_width)
		{
			if (piece->arr[y][x] == -2)
				return (-1);
			else if (piece->arr[y][x] == -1)
				my_counter++;
			else
				sum += piece->arr[y][x];
		}
	}
	if (my_counter != 1)
		return (-1);
	return (sum);
}

short	put_piece_on_map(t_filler *s, t_piece *piece, short x, short y)
{
	short px;
	short py;

	py = -1;
	while (++py < piece->shape_height)
	{
		px = -1;
		while (++px < piece->shape_width)
		{
			if (piece->arr[py][px] == -3 &&
			(py + y) < s->height && (x + px) < s->width)
				piece->arr[py][px] = s->array[y + py][x + px];
		}
	}
	return (value_of_piece(piece));	
}

void	piece_del(t_piece *piece)
{
	free(piece->x);
	free(piece->y);
	while (--(piece->shape_height) >= 0)
		free(piece->arr[piece->shape_height]);
	free(piece->arr);
}

short	algorithm(t_filler *s, t_piece *piece, short x, short y)
{
	short tmp;
	short tmp2;
	short opt_y;
	short opt_x;

	opt_y = -1;
	opt_x = -1;
	tmp = 30000;
	if (!(piece->arr = create_array(piece->shape_width, piece->shape_height)))
		return (-1);
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
		{
			init_piece_arr(piece);
			tmp2 = put_piece_on_map(s, piece, x, y);
			if (tmp2 < tmp && tmp2 > 0)
			{
				tmp = tmp2;
				opt_x = x;
				opt_y = y;
			}
		}
	}
	piece_del(piece);
	if (opt_x == -1 && opt_y == -1)
		return (-1);	
	ft_putnbr(opt_y - piece->min_y);
	write(1, " ", 1);
	ft_putnbr(opt_x - piece->min_x);
	write(1, "\n", 1);
	return (1);
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

void	shit_happens(t_filler *s)
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

int		main(void)
{
	t_piece			*piece;
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
		if (!(s->array = create_array(s->width, s->height)))
			return (-1);
	}
	get_players_coords(s);
	bzero_board(&s->array, s->width, s->height);
	put_players_on_board(s, s->array);
	fill_array(s);
	piece = create_piece();
	if ((algorithm(s, piece, -1, -1)) == -1)
		shit_happens(s);

	// short y = -1;
	// short x;
	// while (++y < s->height)
	// {
	// 	x = -1;
	// 	while (++x < s->width)
	// 		ft_nbr(s->array[y][x]);
	// 	ft_pc('\n');
	// }

	// // short k = -1;

	// // while (++k < piece->k)
	// // {
	// // 	ft_str("x = ");
	// // 	ft_nbr(piece->x[k]);
	// // 	ft_pc('\n');
	// // 	ft_str("y = ");
	// // 	ft_nbr(piece->y[k]);
	// // 	ft_pc('\n');
	// // }
	return (0);
}
