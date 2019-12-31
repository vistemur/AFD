#include "inc.h"
#include "list.h"

void	list_push_back(t_list **begin_list, void *data)
{
	t_list		*counter_el;

	counter_el = *begin_list;
	if (*begin_list)
	{
		while (counter_el->next)
			counter_el = counter_el->next;
		counter_el->next = create_elem(data);
	}
	else
		*begin_list = create_elem(data);
}
