#include "filler.h"


void	func(t_coords **head)
{
	t_coords *tmp;
	t_coords *helper;

	helper = *head;
	// printf("%s\n", (helper == NULL) ? "NULL" : "OK");
	while (helper)
	{
		if (helper->x == 1)
			return ;
		else if (helper->next)
			helper = helper->next;
		else
			break ;
	}
	tmp = (t_coords*)malloc(sizeof(t_coords));
	tmp->x = 0;
	tmp->y = 0;
	tmp->next = NULL;
	if (helper)
		helper->next = tmp;
	else
		*head = tmp;
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

int		main()
{
	t_coords *helper;
	t_coords *s;

	func(&s);
	func(&s);
	func(&s);
	func(&s);

	list_del(s);
	while (s)
	{
		printf("x = %d", s->x);
		printf("y = %d\n", s->y);
		s = s->next;
	}
	return (0);
}