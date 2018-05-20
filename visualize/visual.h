/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:48:25 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/20 17:48:28 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include <curses.h>
# include "libft.h"
# include <stdio.h>

void	skip_shit_before_map(char *line);
void	preparation(char ***array, char *line, unsigned char *height);
void	ft_magic(char **array, char *line, unsigned char height);
void	init_results(char *line, short *p1, short *p2);
char	error_mamagement(char *line);
void	output_char(unsigned char y, unsigned char x, char c);
void	output_map(char **array, unsigned char height);
void	create_map(char **array, unsigned char height);
void	delete_map(char **array, unsigned char height);
void	skip_shit_after_map(char *line);
#endif
