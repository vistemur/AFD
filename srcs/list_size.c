#include "list.h"

int		list_size(t_list *begin_list)
{
	int			counter;
	t_list		*counter_el;

	counter_el = 0;
	counter = 0;
	counter_el = begin_list;
	while (counter_el)
	{
		counter++;
		if (counter_el->next)
			counter_el = counter_el->next;
		else
			return (counter);
	}
	return (counter);
}
