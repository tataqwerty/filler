#include "filler.h"

char	get_player(char *line)
{
	get_next_line(0, &line);
	if (ft_strstr(line, "p1"))
	{
		free(line);
		return (1);
	}
	else
	{
		free(line);
		return (2);
	}
}

void	get_wh_of_sarray(t_filler *s, char *line)
{
	short i;

	i = 0;
	s->height = 0;
	s->width = 0;
	get_next_line(0, &line);
	if (!line)
		return ;
	while (line[i] < '0' || line[i] > '9')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		s->height = (s->height * 10) + line[i] - 48;
		i++;
	}
	i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		s->width = (s->width * 10) + line[i] - 48;
		i++;
	}
	free(line);
}

short	**create_array(short width, short height)
{
	short	y;
	short	x;
	short	**array;

	if (!(array = (short **)malloc(sizeof(short *) * height)))
		return (-1);
	y = -1;
	while (++y < height)
	{
		x = -1;
		if (!(array[y] = (short *)malloc(sizeof(short) * width)))
		{
			while (--y >= 0)
				free(array[y]);
			free(array);
			return (-1);
		}
		while (++x < width)
			array[y][x] = 0;
	}
	return (array);
}

void	get_players_coords(t_filler *s, char *line)
{
	short x;
	short y;

	y = -1;
	while (++y < s->height && get_next_line(0, &line) > 0)
	{
		x = -1;
		while (++x < s->width)
		{
			if (line[x] == ME)
				add_coords(&s->me, x, y);
			else if (line[x] == ENEMY)
				add_coords(&s->me, x, y);
		}
		free(line);
	}
}

char	func(t_filler *s, char *line)
{
	get_next_line(0, &line);
	free(line);
	get_players_coords(s, line);
}

int	main(void)
{
	char *line;
	t_filler *s;

	if (!(s = (t_filler*)malloc(sizeof(t_filler))))
		return (-1);
	line = NULL;
	s->flag = 0;
	s->player = get_player(line);
	get_wh_of_sarray(s, line);
	while (get_next_line(0, &line) > 0)
	{
		if (s->flag == 0)
		{
			s->flag = 1;
			if (!(s->array = create_array(s->width, s->height)))
				return (-1);
		}
		free(line);
		if (func(s, line) == -1)
			break ;
	}
	delete_all();
	return (0);
}
