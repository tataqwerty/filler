/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 20:27:07 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/09 21:24:51 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# define ABS(x) (x < 0 ? -x : x)

typedef struct			s_coords
{
	short				x;
	short				y;
	struct	s_coords	*next;
}						t_coords;

typedef struct
{
	char		player;
	short		**array;
	short		width;
	short		height;
	t_coords	*me;
	t_coords	*enemy;
	char		flag;
}				t_filler;

typedef struct
{
	short **arr;
	short k;
	short width;
	short height;
	short shape_width;
	short shape_height;
	short min_x;
	short min_y;
	short *x;
	short *y;
}				t_piece;

char	get_player(void);
void	get_width_n_height(short *width, short *height, char *line);
short	**create_array(short width, short height);
void	add_coords_if(t_coords **head, short x, short y);
void	get_players_coords(t_filler *s);
void	put_players_on_board(t_filler *s, short **array);
void	bzero_board(short ***array, short width, short height);
void	envelop_xy(t_filler *s, short x, short y, short d);
void	add_ones(t_filler *s);
void	fill_array(t_filler *s);
void	list_del(t_coords *head);
short	enemy_closed(t_filler *s);
void	ft_win(short x, short y);
char		get_player(void);
void	get_width_n_height(short *width, short *height, char *line);
short		**create_array(short width, short height);
void	add_coords_if(t_coords **head, short x, short y);
void	get_players_coords(t_filler *s);
void	del_everything(t_filler *s);
void	init_piece_arr(t_piece *piece);
void	piece_del(t_piece *piece);
short	value_of_piece(t_piece *piece);
short	put_piece_on_map(t_filler *s, t_piece *piece, short x, short y);
void	get_piece_width_n_height(t_piece *piece, char *line);
void	fill_piece_arrays(t_piece *piece, char *line);
void	nullify_piece_arrays(t_piece *piece);
short		max_arr(short *array, short len);
t_piece		*create_piece(void);

#endif
