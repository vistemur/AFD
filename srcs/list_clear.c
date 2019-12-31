#include "list.h"
#include <stdlib.h>

void	list_clear(t_list **begin_list)
{
	t_list *counter_el;
	t_list *suiside;

	counter_el = *begin_list;
	if (begin_list)
		while (counter_el->next)
		{
			suiside = counter_el;
			counter_el = counter_el->next;
            if (suiside->data)
                free(suiside->data);
            if (suiside)
                free(suiside);
            suiside->data = 0;
            suiside = 0;
		}
	free(counter_el);
	*begin_list = 0;
}
