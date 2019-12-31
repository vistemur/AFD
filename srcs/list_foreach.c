#include "list.h"

void	list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list *counter_el;

	counter_el = begin_list;
	while (counter_el && f)
	{
		f(counter_el->data);
		counter_el = counter_el->next;
	}
}
