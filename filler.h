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

#include <stdio.h> // DELETE_ME

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
	t_coords	*enemy;
	t_coords	*me;
}				t_filler;
#endif
