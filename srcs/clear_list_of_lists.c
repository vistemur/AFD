#include "inc.h"

void clear_list_of_lists(t_list** begin_list)
{
    t_list *counter_el;
    
    counter_el = *begin_list;
    while (counter_el)
    {
        list_clear(&counter_el->data);
        counter_el = counter_el->next;
    }
    list_clear(begin_list);
}
