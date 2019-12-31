#include "list.h"
#include <stdlib.h>

t_list		*create_elem(void *data)
{
	t_list *element;

	element = (t_list*)malloc(sizeof(t_list));
	element->data = data;
	element->next = NULL;
	return (element);
}
