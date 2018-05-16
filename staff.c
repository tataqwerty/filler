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

void	ft_win(short x, short y)
{
	ft_putnbr(y);
	write(1, " ", 1);
	ft_putnbr(x);
	write(1, "\n", 1);
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